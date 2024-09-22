// https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>>q;
        long long ans = 0;
        long long n = workerTimes.size();
        for(int i=0;i<n;i++){
            q.push({workerTimes[i], 1});
        }

        while(mountainHeight--) {
            pair<long long, long long> p = q.top();
            q.pop();

            ans = max(ans, p.first);
           
            long long summSec = ((p.second)*(p.second+1))/2;
            long long workerTime = p.first / summSec;
            p.first = p.first + (workerTime * (p.second+1)); 
            p.second = p.second + 1;
            q.push(p);
        }
        return ans;
    }
};
