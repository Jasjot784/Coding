// https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/submissions/1473419456/
class Solution {
public:
    long long maxRectangleArea(vector<int>& x, vector<int>& y) {
        // Step 1: Group y-values by x-coordinate
        map<int, vector<int>> m;
        for (int i = 0; i < x.size(); ++i) {
            m[x[i]].push_back(y[i]); // For each point (x[i], y[i]), add y[i] to the vector associated with x[i]
        }

        // Step 2: Initialize the answer to an invalid value
        long long ans = -1; // Initialize the maximum area as -1 (since areas are positive)
        
        // Step 3: Map to store the last found pair of y-values with their x-coordinate
        map<int, pair<int, int>> m2; // Key: y1, Value: pair of (y2, x-coordinate)

        // Step 4: Iterate over each x-coordinate (f is the x-coordinate, s is the list of y-values for that x)
        for (auto& [f, s] : m) {
            sort(s.begin(), s.end()); // Sort the y-values for the current x-coordinate

            // Step 5: Check pairs of y-values to see if they can form a rectangle
            for (int i = 0; i + 1 < s.size(); ++i) {
                int y1 = s[i], y2 = s[i + 1]; // Consider consecutive y-values
                if (m2.count(y1) && m2[y1].first == y2) { 
                    // If y1 exists in m2 and its associated y2 matches the current y2
                    long long next = f - m2[y1].second; // Calculate the width of the rectangle (difference in x-coordinates)
                    long long mult = y2 - y1; // Height of the rectangle (difference in y-values)
                    next *= mult; // Calculate the area (width * height)
                    ans = max(next, ans); // Update the maximum area found
                }
            }

            // Step 6: Clean up and remove elements from m2 based on certain conditions
            for (int i = 0; i < s.size() && !m2.empty(); ++i) {
                while (true) {
                    // Find the first element in m2 whose y-value is greater than or equal to s[i]
                    auto it = m2.lower_bound(s[i]);
                    if (it != m2.end()) {
                        auto [a, b] = *it; // Get the y1 and pair (y2, x-coordinate)
                        if (a == s[i]) {
                            // If y1 matches s[i], remove it from m2 and continue
                            m2.erase(it);
                            continue;
                        }
                    }
                    // If the iterator is not at the beginning, check the previous element
                    if (it != m2.begin()) {
                        it = prev(it); // Move the iterator backward by 1 step
                        auto [yStart, nextPair] = *it; // Get the yStart and corresponding pair (y2, x-coordinate)
                        if (nextPair.first >= s[i]) {
                            // If y2 is greater than or equal to s[i], remove it from m2 and continue
                            m2.erase(it);
                            continue;
                        }
                    }
                    break; // Exit the while loop once the conditions are satisfied
                }
            }

            // Step 7: For each pair of consecutive y-values, store the current x-coordinate in m2
            for (int i = 0; i + 1 < s.size(); ++i) {
                int y1 = s[i], y2 = s[i + 1]; // Consecutive y-values
                m2[y1] = {y2, f}; // Store (y2, x-coordinate) for y1 in m2
            }
        }

        // Step 8: Return the maximum area found
        return ans; // Return the maximum rectangle area found
    }
};
