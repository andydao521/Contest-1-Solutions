#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;  // Number of papers you have written

    // We create an array to count how many papers
    // have exactly i citations.
    int* count = new int[n + 1];

    // Initialize all counts to 0
    for (int i = 0; i <= n; i++) {
        count[i] = 0;
    }

    // Read citations for each paper
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;

        // If citations are greater than n,
        // we treat them as n (because H-index can never exceed n)
        if (c >= n)
            count[n]++;
        else
            count[c]++;
    }

    int total = 0;  // This will track how many papers
                    // have at least h citations

    // We try possible h values starting from the largest (n)
    // and go downward
    for (int h = n; h >= 0; h--) {

        total += count[h];
        // Add number of papers that have exactly h citations
        // Now total = number of papers with >= h citations

        if (total >= h) {
            // If we have at least h papers with >= h citations,
            // then h is a valid H-index
            cout << h << endl;
            break;
        }
    }

    delete[] count;  // Free allocated memory
    return 0;
}