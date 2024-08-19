// When we look at the problem, the main challenge is to minimize the number of operations required to produce exactly n characters 'A' using only "Copy All" and "Paste" operations. Since "Copy All" copies everything on the screen, it suggests that we should think in terms of copying when we have a beneficial number of 'A's that will allow us to reach n through multiple pastes. This leads us to consider the factors of n because these represent meaningful points at which we can perform a "Copy All" to maximize efficiency
// https://leetcode.com/problems/2-keys-keyboard/description/?envType=daily-question&envId=2024-08-19
class Solution {
public:
    int minSteps(int n) {
        if (n == 1) return 0;
        
        int steps = 0;
        int factor = 2;
        
        while (n > 1) {
            while (n % factor == 0) {
                steps += factor;
                n /= factor;
            }
            factor++;
        }
        
        return steps;
    }
};
