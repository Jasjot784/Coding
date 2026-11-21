// https://leetcode.com/problems/find-subtree-sizes-after-changes/
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<int> originalParent = parent;

        // Original tree
        vector<vector<int>> adj(n);

        for(int i = 1; i < n; i++) {
            adj[originalParent[i]].push_back(i);
        }

        vector<int> ans(n, 1);

        // Similar to your onetwon map
        vector<vector<int>> onetwon(n, vector<int>(26, -1));

        onetwon[0][s[0] - 'a'] = 0;

        // First traversal: parent before child
        vector<int> v;
        stack<int> st;
        st.push(0);

        while(!st.empty()) {
            int u = st.top();
            st.pop();

            v.push_back(u);

            for(int child : adj[u]) {
                st.push(child);
            }
        }

        // Your original logic
        for(int i = 1; i < n; i++) {
            int ac = v[i];
            int p = originalParent[ac];

            onetwon[ac] = onetwon[p];

            int color = s[ac] - 'a';

            if(onetwon[p][color] != -1)
                parent[ac] = onetwon[p][color];

            onetwon[ac][color] = ac;
        }

        // Build modified tree
        vector<vector<int>> adj2(n);

        for(int i = 1; i < n; i++) {
            adj2[parent[i]].push_back(i);
        }

        // Second traversal
        v.clear();
        st.push(0);

        while(!st.empty()) {
            int u = st.top();
            st.pop();

            v.push_back(u);

            for(int child : adj2[u]) {
                st.push(child);
            }
        }

        // Reverse traversal: children before parents
        reverse(v.begin(), v.end());

        for(int i = 0; i < n; i++) {
            int ac = v[i];

            if(parent[ac] != -1) {
                ans[parent[ac]] += ans[ac];
            }
        }

        return ans;
    }
};
