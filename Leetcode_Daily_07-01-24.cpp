// https://leetcode.com/problems/arithmetic-slices-ii-subsequence/description/?envType=daily-question&envId=2024-01-07 
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums)
    {
        vector<unordered_map<int, int>> mapArr(nums.size()); //array
        
        int ans = 0;
        
        for(int idx = 0; idx < nums.size(); idx++)
        {
            for(int in = idx - 1; in >= 0; in--)
            {
                long diff = (long)nums[idx] - nums[in];
                
                if(diff >= INT_MAX or diff <= INT_MIN) continue;
                else diff = (int)diff;
                
                if(mapArr[in].find(diff) != mapArr[in].end()){
                    int prevFreq = mapArr[in][diff];
                    int currFreq = mapArr[idx][diff];
                
                    ans += prevFreq;
                    mapArr[idx][diff] = currFreq + prevFreq + 1; // + 1 to update
                }
                
                else{
                    mapArr[idx][diff]++;
                }
            }
        }
        
        return ans;   
    }
};
