// https://leetcode.com/problems/maximum-number-of-items-from-sale-ii/
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);
        vector<int> gain(n + 1, 0);

        int minPrice = INT_MAX;

        // Step 1: Frequency of every factor
        for (auto &it : items) {
            freq[it[0]]++;
            minPrice = min(minPrice, it[1]);
        }

        // Step 2: Calculate gain for every factor
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                gain[i] += freq[j];
            }

            if (freq[i] > 0) {
                gain[i]--;
            }
        }

        // Step 3: Sort items by price
        sort(items.begin(), items.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        // Step 4: Aggregate double-value purchases by price
        map<int, long long> mp;

        for (auto &it : items) {
            int factor = it[0];
            int price = it[1];

            if (price >= 2LL * minPrice) break;

            if (gain[factor] > 0) {
                mp[price] += gain[factor];
            }
        }

        // Step 5: Greedily spend budget
        long long ans = 0;
        long long remaining = budget;

        for (auto &[price, cnt] : mp) {
            long long take = min(cnt, remaining / price);

            ans += 2LL * take;
            remaining -= take * price;
        }

        // Remaining budget buys cheapest items (single value)
        ans += remaining / minPrice;

        return (int)ans;
    }
};
