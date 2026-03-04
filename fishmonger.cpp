#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// This struct represents one fishmonger (buyer)
struct Fishmonger {
    int amount; // how many fish this buyer wants to buy
    int price;  // how much money the buyer pays per kg
};

// This function is used for sorting fishmongers
// It makes sure buyers paying MORE money come first
bool comparePrice(Fishmonger a, Fishmonger b) {
    return a.price > b.price; // higher price first
}

int main() {

    int n, m;

    // n = number of fish you have
    // m = number of fishmongers (buyers)
    cin >> n >> m;

    // vector to store the weight of each fish
    vector<int> fish(n);

    // read the weights of the fish
    for (int i = 0; i < n; i++) {
        cin >> fish[i];
    }

    // vector to store information about each fishmonger
    vector<Fishmonger> buyers(m);

    // read how many fish each buyer wants
    // and how much they pay per kg
    for (int i = 0; i < m; i++) {
        cin >> buyers[i].amount >> buyers[i].price;
    }

    // sort the fish from largest weight to smallest
    // this helps us sell the biggest fish first
    sort(fish.begin(), fish.end(), greater<int>());

    // sort the buyers from highest price to lowest
    // this helps us sell to the highest paying buyer first
    sort(buyers.begin(), buyers.end(), comparePrice);

    long long money = 0; // total money we earn
    int fishIndex = 0;   // keeps track of which fish we are currently selling

    // go through each fishmonger
    for (int i = 0; i < m && fishIndex < n; i++) {

        // how many fish this buyer can still buy
        int canBuy = buyers[i].amount;

        // keep selling fish to this buyer until:
        // 1) they bought enough fish OR
        // 2) we run out of fish
        while (canBuy > 0 && fishIndex < n) {

            // add the money we get from selling this fish
            money += (long long)fish[fishIndex] * buyers[i].price;

            // move to the next fish
            fishIndex++;

            // buyer has now bought one fish
            canBuy--;
        }
    }

    // print the total money earned
    cout << money << endl;

    return 0;
}