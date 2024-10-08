// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/?envType=daily-question&envId=2024-10-08
class Solution {
public:
    bool isBalanced(std::string& str) {
    std::stack<char> s;

    for (char ch : str) {
        if (ch == '[') {
            s.push(ch); // Push opening bracket onto the stack
        } else if (ch == ']') {
            // If we encounter a closing bracket, check the stack
            if (s.empty()) {
                return false; // No matching opening bracket
            }
            s.pop(); // Pop the matching opening bracket
        }
    }

    // If the stack is empty, all brackets are matched
    return s.empty();
}
    int minSwaps(string s) {
        int n = s.size();
        if(isBalanced(s))return 0;

        int open = 0,close = 0;
        int lastopen = -1;
        for(int i = n-1;i>=0;i--){
            if(s[i]=='['){
                lastopen = i;
                break;
            }
        }
int cnt=0;
        for(int i = 0;i<n;i++){
            if(s[i]=='[')open++;
            else{
                close++;
                if(close>open){
                    swap(s[i],s[lastopen]);
                    close--;
                    open++;
                    cnt++;

                    for(int j = lastopen-1;j>=0;j--){
                         if(s[j]=='['){
                lastopen = j;
                break;
            }
                    }
                }
            }
        }

        return cnt;


    }
};
