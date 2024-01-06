// https://leetcode.com/problems/maximum-profit-in-job-scheduling/description/?envType=daily-question&envId=2024-01-06
struct job{
    int start;
    int end;
    int profit;
};

bool comp(job a, job b){
    return a.end <= b.end;
}

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<job> jobs;
        for(int i = 0; i < startTime.size(); i++){
            job temp;
            temp.start = startTime[i];
            temp.end = endTime[i];
            temp.profit = profit[i];
            jobs.push_back(temp);
            //cout<<temp.start<<" "<<temp.end<<" "<<temp.profit<<endl;
        }      
        sort(jobs.begin(), jobs.end(), comp);
        int n = jobs.size();
        vector<int> dp (n);
        dp[0] = jobs[0].profit; // profit of 1st process
        for(int i = 1; i < jobs.size(); i++){
            int pro = jobs[i].profit;
            int l = 0;
            int h = i-1;
            int possible = -1;
            while(l <= h){ // finding possible process which do not overlap
                int mid = (l+h)/2;
                if(jobs[mid].end <= jobs[i].start){
                    possible = mid;
                    l = mid+1;
                }else{
                    h = mid-1;
                }
            }
            if(possible != -1){ // if possible add profit
                pro += dp[possible];
            }                         
            dp[i] = max(dp[i-1], dp[i] + pro); // update with max profit
        }
        return dp[n-1];
    }
};
