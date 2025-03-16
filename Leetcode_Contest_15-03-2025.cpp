// https://leetcode.com/problems/longest-common-prefix-of-k-strings-after-removal/
class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& w, int k) {
         int n = w.size();
         vector<int>ans(n);
        
        map<vector<long long>,int>m;
        priority_queue<vector<long long>>pq;
        
         int b1 = 31;
         int mod1 = 1e9 + 7;
         int b2 = 37;
         int mod2 = 1e9 + 9;
        
         for(int i = 0;i<w.size();i++){
             long long hs1 = 0,hs2 = 0;
             
             for(int j = 0;j<w[i].size();j++){
                  hs1 = ((hs1 * b1) % mod1 + w[i][j] - 'a' + 1) % mod1; 
                  hs2 = ((hs2 * b2) % mod1 + w[i][j] - 'a' + 1) % mod2; 
                    m[{1ll*j+1,hs1,hs2}]++;
             }
         }
         for(auto &it:m){
             auto v = it.first;
             if(it.second >= k)
               pq.push({v[0],it.second,v[1],v[2]});
         }
         for(int i = 0;i<n;i++){
             if(pq.empty())
                 continue;
             if(pq.top()[1] > k || w[i].size() < pq.top()[0]){
                 ans[i] = pq.top()[0];
                 continue;
             }
             long long hs1 = 0,hs2 = 0;
             vector<vector<long long>>dup;
             vector<pair<long long,long long>>hs(w[i].size());
             
             for(int j = 0;j<w[i].size();j++){
                  hs1 = ((hs1 * b1) % mod1 + w[i][j] - 'a' + 1) % mod1; 
                  hs2 = ((hs2 * b2) % mod1 + w[i][j] - 'a' + 1) % mod2; 
                  hs[j] = {hs1,hs2};
             }
             while(pq.size()){
                 auto v = pq.top();
                 if(v[1] > k || v[0] > w[i].size()){
                     ans[i] = v[0];
                     break;
                 }
                 if(v[2] == hs[v[0] - 1].first && v[3] == hs[v[0] - 1].second){
                    pq.pop();
                    dup.push_back(v);
                 }
                 else{
                     ans[i] = v[0];
                     break;
                 }
             }
             for(auto &it:dup){
                  pq.push(it);
             }
         }
      return ans;
    }
};
