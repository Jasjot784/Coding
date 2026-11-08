// https://leetcode.com/problems/minimum-cost-to-make-red-nodes-connected/

class Solution {
public:
    long long minCost(int n, string colors, vector<vector<int>>& edges) {
        map<int, vector<int>> mp;

        for(int i = 0; i < n-1; i++) {
            mp[edges[i][0]].push_back(edges[i][1]);
            mp[edges[i][1]].push_back(edges[i][0]);
        }

        // Calculate subtree sizes
        vector<int> cost(n, 1);
        vector<int> parent(n, -1);
        vector<int> order;

        order.push_back(0);

        for(int i = 0; i < order.size(); i++) {
            int u = order[i];

            for(int v : mp[u]) {
                if(v == parent[u]) continue;

                parent[v] = u;
                order.push_back(v);
            }
        }

        // Subtree sizes
        for(int i = n-1; i >= 0; i--) {
            int u = order[i];

            if(parent[u] != -1) {
                cost[parent[u]] += cost[u];
            }
        }

        // Initial cost: flip all Red nodes
        long long total = 0;

        for(int i = 0; i < n; i++) {
            if(colors[i] == 'R') {
                total += cost[i];
            }
        }

        // Maximum weight connected component DP
        vector<long long> dp(n, 0);

        long long maxi = 0;

        for(int i = n-1; i >= 0; i--) {
            int u = order[i];

            long long weight = (colors[u] == 'R')
                               ? cost[u] : -cost[u];

            dp[u] = weight;

            for(int v : mp[u]) {
                if(parent[v] == u) {
                    dp[u] += max(0LL, dp[v]);
                }
            }

            maxi = max(maxi, dp[u]);
        }

        return total - maxi;
    }
};
