#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 205
#define MAX_NAME_LENGTH 505
#define MAX_ELEMENTS 205
#define MAX_DEPTH 75
#define MAX_COMMANDS 305

// 前向宣告
typedef struct Node Node;

// 函數宣告
Node* create_node(const char* name, bool is_dir);
void free_tree(Node* root);
void print_json(Node* node, int indent, FILE* outfile);
int count_elements(Node* node, bool count_dir);
void trim_name(char* name);
Node* find_child(Node* parent, const char* name);

// 結構定義
typedef struct Node {
    char name[MAX_NAME_LENGTH];
    bool is_dir;
    Node* children[MAX_ELEMENTS];
    int num_children;
} Node;

Node* create_node(const char* name, bool is_dir) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        perror("Memory allocation failed");
        exit(1);
    }
    strcpy(node->name, name);
    node->is_dir = is_dir;
    node->num_children = 0;
    return node;
}

void free_tree(Node* root) {
    if (!root) return;
    for (int i = 0; i < root->num_children; i++) {
        free_tree(root->children[i]);
    }
    free(root);
}

void print_json(Node* node, int indent, FILE* outfile) {
    for (int i = 0; i < indent; i++) fprintf(outfile, "    ");
    if (!node->is_dir) {
        fprintf(outfile, "\"%s\"", node->name);
        return;
    }

    fprintf(outfile, "{\n");
    for (int i = 0; i < indent + 1; i++) fprintf(outfile, "    ");
    fprintf(outfile, "\"name\": \"%s\",\n", node->name);
    for (int i = 0; i < indent + 1; i++) fprintf(outfile, "    ");
    fprintf(outfile, "\"children\": [\n");

    for (int i = 0; i < node->num_children; i++) {
        print_json(node->children[i], indent + 2, outfile);
        if (i < node->num_children - 1) fprintf(outfile, ",\n");
        else fprintf(outfile, "\n");
    }

    for (int i = 0; i < indent + 1; i++) fprintf(outfile, "    ");
    fprintf(outfile, "]\n");
    for (int i = 0; i < indent; i++) fprintf(outfile, "    ");
    fprintf(outfile, "}");
}

int count_elements(Node* node, bool count_dir) {
    int count = 0;
    if (node->is_dir == count_dir) count++;
    for (int i = 0; i < node->num_children; i++) {
        count += count_elements(node->children[i], count_dir);
    }
    return count;
}


void trim_name(char* name) {
    int start = 0;
    while (isspace(name[start]) ||
           strncmp(&name[start], "│", strlen("│")) == 0 ||
           strncmp(&name[start], "├", strlen("├")) == 0 ||
           strncmp(&name[start], "└", strlen("└")) == 0 ||
           strncmp(&name[start], "─", strlen("─")) == 0) {
        if (strncmp(&name[start], "│", strlen("│")) == 0 ||
            strncmp(&name[start], "├", strlen("├")) == 0 ||
            strncmp(&name[start], "└", strlen("└")) == 0 ||
            strncmp(&name[start], "─", strlen("─")) == 0) {
          start += strlen("│"); // Increment by the length of the UTF-8 character
        } else {
          start++;
        }
    }
    int end = strlen(name) - 1;
    while (end > start && isspace(name[end])) {
        end--;
    }
    name[end + 1] = '\0';
    memmove(name, name + start, strlen(name + start) + 1);
}
// Helper function to find parent (much more robust)
Node* find_parent(Node* root, Node* child) {
    if (root == NULL || child == NULL || root == child) return NULL;

    for (int i = 0; i < root->num_children; i++) {
        if (root->children[i] == child) return root;
        Node* found = find_parent(root->children[i], child);
        if (found) return found;
    }
    return NULL;
}

Node* find_child(Node* parent, const char* name) {
    for (int i = 0; i < parent->num_children; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            return parent->children[i];
        }
    }
    return NULL;
}

void print_current_path(Node* root, Node* current) { // Corrected: root is now a parameter
    if (current == NULL) return;
    print_current_path(root, find_parent(root, current)); // Corrected: Pass root
    printf("/%s", current->name);
}

int main() {
    char input_filename[MAX_LINE_LENGTH];
    char output_filename[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];

    // Read input filename
    fgets(input_filename, MAX_LINE_LENGTH, stdin);
    input_filename[strcspn(input_filename, "\n")] = 0;

    FILE* infile = fopen(input_filename, "r");
    if (!infile) {
        perror("Error opening input file");
        return 1;
    }

    Node* root = create_node(".", true);
    Node* current_node = root;

    // Build the initial directory structure
    int root_level = -1;
    while (fgets(line, MAX_LINE_LENGTH, infile) && line[0] != '\n') {
        line[strcspn(line, "\n")] = 0;
        int level = 0;
        while (line[level * 4] == ' ') level++;

        char* name = line + level * 4;
        bool is_dir = (name[strlen(name) - 1] == '/');
        if (is_dir) name[strlen(name) - 1] = '\0';

        trim_name(name);

        Node* new_node = create_node(name, is_dir);
        Node* parent = root;

        if (root_level == -1) {
            root_level = level;
            continue;
        }
        else if (level == root_level + 1) {
            parent = root;
        }
        else if (level > root_level + 1){
            Node* temp = root;
            for(int i = 0; i < level - (root_level + 1) -1; i++){
                if(temp->num_children > 0)
                    temp = temp->children[temp->num_children -1];
                else
                    break;
            }
            parent = temp;
        }
        parent->children[parent->num_children++] = new_node;
    }
    fclose(infile);

    char command[MAX_LINE_LENGTH];
    char arg[MAX_NAME_LENGTH];
    bool output_filename_found = false;

    while (fgets(line, MAX_LINE_LENGTH, stdin)) {
        line[strcspn(line, "\n")] = 0;
        if (!output_filename_found) {
            if (sscanf(line, "%s %[^\n]", command, arg) == 2) {
                // printf("Command: %s, Arg: %s, Current Path: ", command, arg);
                // print_current_path(root, current_node);
                // printf("\n");

                if (strcmp(command, "cd") == 0) {
                    if (strcmp(arg, ".") == 0) continue;
                    if (strcmp(arg, "..") == 0) {
                        Node* parent = find_parent(root, current_node);
                        if (parent) current_node = parent;
                    } else {
                        Node* child = find_child(current_node, arg);
                        if (child) current_node = child;
                    }
                } else if (strcmp(command, "touch") == 0) {
                    Node* new_file = create_node(arg, false);
                    current_node->children[current_node->num_children++] = new_file;
                } else if (strcmp(command, "mkdir") == 0) {
                    Node* new_dir = create_node(arg, true);
                    current_node->children[current_node->num_children++] = new_dir;
                }
            } else {
                strcpy(output_filename, line);
                output_filename[strcspn(output_filename, "\n")] = 0;
                output_filename_found = true;
                // printf("Output file: %s, Current Path: ", output_filename);
                // print_current_path(root, current_node);
                // printf("\n");
                break;
            }
        }
    }
    if (!output_filename_found) {
        fprintf(stderr, "Error: Output filename missing.\n");
        free_tree(root);
        return 1;
    }

    FILE* outfile = fopen(output_filename, "w");
    if (!outfile) {
        perror("Error opening output file");
        free_tree(root);
        return 1;
    }

    printf("# dirs = %d\n", count_elements(current_node, true));
    printf("# files = %d\n", count_elements(current_node, false));

    print_json(current_node, 0, outfile);
    fprintf(outfile, "\n");

    fclose(outfile);
    free_tree(root);

    return 0;
}