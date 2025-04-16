#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

#define MAX_N 5
#define MAX_D 36
#define INITIAL_CASH 100000.0

double getMaxProfit(int n, int d, double prices[MAX_N][MAX_D], double fees[MAX_N]) {
    double cash = INITIAL_CASH;
    double holdings = 0;
    int current_metal = -1;
    
    // Track lowest price seen for each metal during current trend
    double lowest_prices[MAX_N];
    for(int i = 0; i < n; i++) {
        lowest_prices[i] = DBL_MAX;
    }
    
    // Track when we bought each metal (to calculate profit from buy point)
    double buy_prices[MAX_N];
    for(int i = 0; i < n; i++) {
        buy_prices[i] = DBL_MAX;
    }
    
    // For each day except the last
    for (int day = 0; day < d - 1; day++) {
        printf("%f\n", cash);
        // Update lowest prices seen
        for(int metal = 0; metal < n; metal++) {
            if(day > 0 && prices[metal][day] <= prices[metal][day-1]) {
                // Price dropped, reset lowest price
                lowest_prices[metal] = prices[metal][day];
            } else {
                lowest_prices[metal] = fmin(lowest_prices[metal], prices[metal][day]);
            }
        }
        printf("here1\n");
        // If we're holding a metal
        if (current_metal != -1) {
            double current_value = holdings * prices[current_metal][day];
            // Calculate potential profit if we keep current metal from our buy price
            double current_metal_next_value = holdings * prices[current_metal][day + 1];
            double current_metal_profit = current_metal_next_value - (holdings * buy_prices[current_metal]);
            bool should_sell = false;
            
            // Check if another metal has better potential from its lowest price
            for (int metal = 0; metal < n; metal++) {
                if (metal == current_metal) continue;
                
                // Calculate how much we would have after selling current metal
                double sale_cash = (holdings * prices[current_metal][day]) / (1.0 + fees[current_metal]);
                
                // Calculate potential profit from lowest price seen
                double potential_buy_amount = (sale_cash / (1.0 + fees[metal])) / lowest_prices[metal];
                double potential_next_value = potential_buy_amount * prices[metal][day + 1];
                double potential_profit = potential_next_value - (potential_buy_amount * lowest_prices[metal]);
                
                if (potential_profit > current_metal_profit) {
                    should_sell = true;
                    
                    // Execute the trade
                    cash = sale_cash;
                    holdings = (cash / (1.0 + fees[metal])) / prices[metal][day];
                    current_metal = metal;
                    buy_prices[metal] = prices[metal][day];
                    break;
                }
            }
            
            // If price will drop tomorrow and we haven't switched
            if (prices[current_metal][day] > prices[current_metal][day + 1] && !should_sell) {
                cash = (holdings * prices[current_metal][day]) / (1.0 + fees[current_metal]);
                holdings = 0;
                current_metal = -1;
                // Reset buy price for this metal
                buy_prices[current_metal] = DBL_MAX;
            }
        }
        printf("here2\n");
        printf("current_metal: %d\n", current_metal);
        // If we're not holding any metal
        if (current_metal == -1) {
            double best_potential_profit = 0;
            int best_metal = -1;
            double best_buy_price = 0;
            
            // Look for best metal to buy based on lowest price seen
            for (int metal = 0; metal < n; metal++) {
                double buy_amount = (cash / (1.0 + fees[metal])) / lowest_prices[metal];
                double next_day_value = buy_amount * prices[metal][day + 1];
                double potential_profit = next_day_value - (buy_amount * lowest_prices[metal]);
                
                if (potential_profit > best_potential_profit) {
                    best_potential_profit = potential_profit;
                    best_metal = metal;
                    best_buy_price = prices[metal][day];
                }
            }
            
            // If we found a profitable metal
            if (best_metal != -1 && best_potential_profit > 0) {
                double amount = cash / (1.0 + fees[best_metal]);
                holdings = amount / prices[best_metal][day];
                cash = 0;
                current_metal = best_metal;
                buy_prices[best_metal] = best_buy_price;
            }
        }
        printf("here3\n");
    }
    
    // On the last day, sell any holdings
    if (current_metal != -1) {
        cash = (holdings * prices[current_metal][d-1]) / (1.0 + fees[current_metal]);
    }
    
    return floor(cash);
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    
    double prices[MAX_N][MAX_D];
    double fees[MAX_N];
    
    // Read prices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%lf", &prices[i][j]);
        }
    }
    
    // Read fees
    for (int i = 0; i < n; i++) {
        scanf("%lf", &fees[i]);
    }
    
    printf("%d\n", (int)getMaxProfit(n, d, prices, fees));
    return 0;
}