#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Represents one investment opportunity
struct Investment {
    long long daily_profit;  // How much money this investment earns per day (d_i)
    long long cost;          // Initial amount borrowed to buy this investment (c_i)
    long long start_day;     // First day this investment becomes profitable
};

int main() {

    int n;
    long long target_money;

    // n = number of investment options
    // target_money = how much money we need to retire
    cin >> n >> target_money;

    vector<Investment> investments;

    // Read all investment options
    for (int i = 0; i < n; i++) {

        long long daily, cost;
        cin >> daily >> cost;

        Investment inv;
        inv.daily_profit = daily;
        inv.cost = cost;

        // This is the key idea:
        // If we invest in this option, we borrow "cost"
        // We earn "daily" per day
        // It becomes profitable starting from day (cost / daily) + 1
        inv.start_day = cost / daily + 1;

        investments.push_back(inv);
    }

    // Sort investments by:
    // 1) When they start being profitable (earlier is better)
    // 2) Smaller daily profit first
    // 3) Larger cost first (tie-breaker)
    sort(investments.begin(), investments.end(),
         [](Investment a, Investment b) {

        if (a.start_day != b.start_day)
            return a.start_day < b.start_day;

        if (a.daily_profit != b.daily_profit)
            return a.daily_profit < b.daily_profit;

        return a.cost > b.cost;
    });

    long long total_daily_profit = 0;  // Total money earned per day from all chosen investments
    long long total_cost = 0;          // Total money borrowed from friend
    int index = 0;

    // Start checking from the earliest possible profitable day
    long long current_day = investments[0].start_day;

    while (true) {

        // Add all investments that become profitable today
        while (index < n && investments[index].start_day == current_day) {

            total_daily_profit += investments[index].daily_profit;
            total_cost += investments[index].cost;

            index++;
        }

        // After "current_day" days,
        // total money earned = current_day * total_daily_profit
        // but we must subtract what we borrowed (total_cost)
        long long net_money = current_day * total_daily_profit - total_cost;

        // If we have enough money to retire, stop
        if (net_money >= target_money) {
            break;
        }

        // Otherwise, move to next day
        current_day++;
    }

    // Print the minimum number of days needed
    cout << current_day << endl;

    return 0;
}