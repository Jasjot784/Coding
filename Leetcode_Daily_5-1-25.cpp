// https://leetcode.com/problems/shifting-letters-ii/?envType=daily-question&envId=2025-01-05
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();
        vector<int> shiftEffect(n + 1, 0);  // This will hold the net shift effects
        
        // Process each shift operation and store the effect in shiftEffect
        for (auto& shift : shifts) {
            int left = shift[0];
            int right = shift[1];
            int dir = shift[2];
            
            // If the direction is 0 (left shift), decrease the shift at 'left'
            // and increase it after 'right'. 
            if (dir == 0) {  // Left shift
                shiftEffect[left]--;
                if (right + 1 < n) shiftEffect[right + 1]++;
            } else {  // Right shift
                shiftEffect[left]++;
                if (right + 1 < n) shiftEffect[right + 1]--;
            }
        }

        // Apply the cumulative shifts and update the string
        int cumulativeShift = 0;
        for (int i = 0; i < n; ++i) {
            cumulativeShift += shiftEffect[i];  // Sum up the shift effects

            // Apply the cumulative shift, with modulo 26 to wrap around the alphabet
            int newChar = (s[i] - 'a' + cumulativeShift + 26) % 26;  // Adjusting for negative shifts
            s[i] = 'a' + newChar;  // Convert back to a character
            if(s[i]<'a')s[i]+=26;
        }

        return s;
    }
};
