// https://leetcode.com/problems/minimum-total-distance-traveled/submissions/1438877451/?envType=daily-question&envId=2024-10-31
class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Sort the robots and factories by their positions to facilitate distance calculations
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        // Get the number of robots (n) and factories (m)
        int n = robot.size();
        int m = factory.size();
        
        // Initialize a DP table where dp[i][j] represents the minimum distance to repair the first i robots with the first j factories
        long long dp[n + 1][m + 1];
        
        // Fill the DP table
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                // Base case: if there are no robots, distance is 0 regardless of factories
                if (i == 0) {
                    dp[i][j] = 0;
                    continue;
                }
                // Initialize the distance for the current state to a large value (infinity)
                dp[i][j] = 1e17;
            }
        }

        // Fill the DP table iteratively
        for (int i = 1; i <= n; i++) { // Loop through each robot
            for (int j = 1; j <= m; j++) { // Loop through each factory
                long long dist = 0; // Reset distance for current robot and factory
                int curr = i; // Set current robot index to i
                
                // Loop to consider using the j-th factory to serve up to its capacity
                for (int k = 0; k <= factory[j - 1][1]; k++) {
                    // Check if we can repair the first (i-k) robots with (j-1) factories
                    dp[i][j] = min(dp[i][j], dp[i - k][j - 1] + dist);
                    
                    // If we've considered all available robots, break the loop
                    if (curr - 1 < 0) {
                        break;
                    }
                    
                    // Calculate the distance for the current robot to the factory
                    dist += abs(robot[curr - 1] - factory[j - 1][0]);
                    
                    // Move to the previous robot for the next iteration
                    curr--;
                }
            }
        }
        
        // Return the minimum distance to repair all robots with all factories
        return dp[n][m];
    }
};
