// https://leetcode.com/problems/bag-of-tokens/solutions/4818951/maximizing-scores-the-bag-of-tokens-c-java-two-pointer-97-beats/?envType=daily-question&envId=2024-03-04
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = tokens.size();
        int count= 0 ;
        sort(tokens.begin(), tokens.end());
        int left=0,right=n-1;
        int maxScore = 0;
        while(left<=right){
            if(tokens[left] <= power){
                power -= tokens[left++];
                count++;
                maxScore = max(maxScore,count);
            }
            else if(count>0){
                power += tokens[right--];
                count--;
            }
            else{
                break;
            }
        }
        return maxScore;
    }
};
