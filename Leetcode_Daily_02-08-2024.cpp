// https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/description/?envType=daily-question&envId=2024-08-02
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        int z = 0;
        int o = 0;
        vector<int> nums2;
        int k = count(nums.begin(),nums.end(),1);
        // cout<<k<<endl;
        nums2 = nums;
        for(int i = 0;i<k;i++){
            nums2.push_back(nums[i]);
            if(nums[i]==0)z++;
            else o++;
        }

        int ans = z;
        // cout<<ans<<endl;
        for(int i = 0;i<nums2.size();i++){
            cout<<nums2[i]<<" ";
        }
        cout<<endl;
        for(int i = k;i<nums2.size();i++){
            if(nums2[i-k]==0)z--;
            else o--;

            if(nums2[i]==0)z++;
            else o++;
            ans = min(ans,z);
            // cout<<ans<<endl;
        }
        return ans;

       


        
    }
};
