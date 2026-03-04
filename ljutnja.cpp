#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

    long long m, n;
    cin >> m >> n;   // m = total candies available, n = number of children

    vector<long long> wish(n);  // stores how many candies each child wants
    long long total = 0;        // sum of all wishes

    // read each child's wish
    for(int i = 0; i < n; i++){
        cin >> wish[i];
        total += wish[i];       // keep track of total requested candies
    }

    // candies that cannot be given (total missing candies)
    long long extra = total - m;

    // sort wishes in ascending order
    // this helps us handle the smallest limits first
    sort(wish.begin(), wish.end());

    long long left = 0;
    long long right = wish.back(); // largest possible missing candies

    // Binary search to find the largest "missing level"
    // meaning each child is missing at most this many candies
    while(left < right){

        long long mid = (left + right + 1) / 2;

        long long sum = 0;

        // calculate how many candies would be missing
        // if every child missed up to "mid" candies
        for(long long w : wish){
            sum += min(w, mid);
        }

        // if this amount of missing candies is allowed
        if(sum <= extra)
            left = mid;        // try a larger level
        else
            right = mid - 1;   // level too big
    }

    // final missing level we can assign
    long long level = left;

    unsigned long long anger = 0;
    long long used = 0;

    // assign this missing level to every child
    for(long long w : wish){

        // a child cannot miss more candies than their wish
        long long d = min(w, level);

        anger += d * d;   // add squared anger
        used += d;        // track how many missing candies were used
    }

    // candies still left to assign as missing
    extra -= used;

    // distribute the remaining missing candies (+1)
    // starting from children with the largest wishes
    for(int i = n-1; i >= 0 && extra > 0; i--){

        if(wish[i] > level){

            // increase missing candies from level → level+1
            anger += (level+1)*(level+1) - level*level;

            extra--;
        }
    }

    // print the minimum total anger
    cout << anger << endl;
}