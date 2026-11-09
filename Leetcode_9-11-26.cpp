// https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/


class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        int n = arrival.size();

        vector<int> cnt(k, 0);

        // Available servers
        set<int> available;

        for(int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {finishing_time, server_index}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> busy;

        for(int i = 0; i < n; i++) {

            // Release all servers that have become available
            while(!busy.empty() && busy.top().first <= arrival[i]) {
                int ind = busy.top().second;
                busy.pop();

                available.insert(ind);
            }

            if(available.empty()) continue;

            int ind = i % k;

            // Find first available server >= ind
            auto it = available.lower_bound(ind);

            // Wrap around if no such server exists
            if(it == available.end()) {
                it = available.begin();
            }

            ind = *it;

            available.erase(it);

            cnt[ind]++;

            busy.push({arrival[i] + load[i], ind});
        }

        int maxi = 0;

        for(int i = 0; i < k; i++) {
            maxi = max(maxi, cnt[i]);
        }

        vector<int> ans;

        for(int i = 0; i < k; i++) {
            if(cnt[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
