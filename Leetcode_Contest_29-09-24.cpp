// https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/
// we need to know from which position k is copied 
class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        int ans = 0;
        while(k > 1)
        {
            int operIndex = log2(k-1);
            ans += operations[operIndex];
            k = ((k-1)%((int64_t)pow(2, operIndex)))+1;
            ans %= 26;
        }
        return 'a'+ans;
    }
};
