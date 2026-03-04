#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int INF = 1e9; // large number used to represent "impossible"

int main() {

    int N, K, S;
    cin >> N >> K >> S; // read array size, window size K, and required sum S

    vector<int> A(N);
    for(int i = 0; i < N; i++)
        cin >> A[i]; // read the array elements

    vector<vector<int>> groups(K); 
    // create K groups to store values with the same index % K

    for(int i = 0; i < N; i++)
        groups[i % K].push_back(A[i]); 
    // place each element into its mod group
    // because in a K-smooth array: A[i] = A[i+K]

    vector<int> dp(S + 1, INF); 
    // dp[x] = minimum changes needed to make the chosen pattern sum to x

    dp[0] = 0; 
    // base case: sum 0 requires 0 changes before choosing any groups

    for(int i = 0; i < K; i++) { // process each mod group

        unordered_map<int,int> freq; 
        // counts how many times each value appears in this group

        for(int v : groups[i])
            freq[v]++; // build frequency table

        int size = groups[i].size(); 
        // number of elements in this group

        vector<int> new_dp(S + 1, INF); 
        // new dp table after processing this group

        int best = *min_element(dp.begin(), dp.end()); 
        // smallest cost among previous sums

        for(int s = 0; s <= S; s++)
            new_dp[s] = best + size; 
        // baseline: change every element in this group
        // cost = group size

        for(auto &p : freq) { 
            // try keeping values that already appear in the group

            int val = p.first;   // the value
            int count = p.second; // how many times it appears

            if(val > S) continue; 
            // cannot use this value if it exceeds allowed sum

            int cost = size - count; 
            // changes needed if we choose this value

            for(int s = val; s <= S; s++) { 
                // update DP if we add this value to the sum

                if(dp[s - val] == INF) continue; 
                // skip impossible states

                new_dp[s] = min(
                    new_dp[s],
                    dp[s - val] + cost
                ); 
                // update minimum cost
            }
        }

        dp = new_dp; 
        // move to next group
    }

    cout << dp[S] << endl; 
    // final answer: minimum changes to get total sum S
}