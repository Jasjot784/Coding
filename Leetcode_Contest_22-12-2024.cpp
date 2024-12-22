// https://leetcode.com/problems/smallest-substring-with-identical-characters-ii/
class Solution {
public:
    int minLength(string s, int numOps) {
        // Initialize two counters to track the number of characters that match
        // a certain alternating pattern (odd and even indexed).
        int cnt = 0, cnt2 = 0;

        // Traverse through the string to count the number of characters that match 
        // either the alternating pattern '0' and '1' (cnt) or the opposite pattern (cnt2).
        for (int i = 0; i < s.size(); i++) {
            // If the character matches the pattern for index i (even or odd), increase cnt.
            if ((s[i] - '0') == i % 2) cnt++;
            // Otherwise, increase cnt2 for the opposite pattern.
            else cnt2++;
        }

        // If the number of operations is sufficient to make the entire string match one pattern,
        // return 1, meaning the string can be reduced to length 1.
        if (cnt <= numOps || cnt2 <= numOps) return 1;

        // Initialize binary search boundaries.
        int Min = 1, Max = s.size();

        // Start a binary search between the values of Min and Max to find the smallest 
        // length that can be reduced after performing at most numOps operations.
        while (Min + 1 < Max) {
            // Calculate the mid-point between Min and Max to check this length.
            int mid = (Max + Min) / 2;

            // Track the last character processed and the current count of consecutive characters.
            int last = s[0], cnt = 0;

            // Initialize the total operations counter to zero.
            int tot = 0;

            // Loop through the string to calculate the number of consecutive characters that 
            // would need to be removed or replaced.
            for (auto it : s) {
                // If the current character is the same as the previous one, increase the count.
                if (it == last) cnt++;
                else {
                    // If the character is different, reset the count and update the last character.
                    last = it;
                    cnt = 1;
                }

                // If the count exceeds the current mid value, we need an operation to split the sequence.
                if (cnt > mid) {
                    // Increment the total operations needed and reset the count.
                    tot++;
                    cnt = 0;
                }
            }

            // If the total operations needed is greater than the allowed numOps, adjust Min to mid.
            if (tot > numOps) Min = mid;
            // Otherwise, adjust Max to mid, reducing the length further.
            else Max = mid;
        }

        // Return the maximum possible length after the operations, which is now found.
        return Max;
    }
};
