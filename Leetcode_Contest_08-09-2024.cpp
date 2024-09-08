// https://leetcode.com/problems/maximum-number-of-moves-to-kill-all-pawns/
class Solution {
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        // Static variables to store distances and visited states
        static vector<vector<int>> dist(2500, vector<int>(2500, 0));
        static vector<bool> done(2500, false);

        // Define the dimensions of the board
        int m = 50, n = 50;
        
        // Add the knight's starting position to the list of positions
        positions.push_back({kx, ky});
        
        // Iterate over all positions to compute distances
        for (auto el : positions) {
            int i = el[0];
            int j = el[1];
            int source = n * i + j;  // Flatten the 2D position (i, j) into a single integer
            
            // Skip computation if distances from this source have already been computed
            if (done[source]) continue;
            
            // Initialize BFS to compute distances from (i, j)
            deque<tuple<int, int, int>> q;  // Queue to store positions and distances
            q.emplace_back(i, j, 0);  // Start BFS from the position (i, j) with distance 0
            
            vector<vector<bool>> v(m, vector<bool>(n, false));  // Visited matrix
            v[i][j] = true;  // Mark the start position as visited

            // Perform BFS to calculate the minimum moves required to reach each position
            while (!q.empty()) {
                auto [ii, jj, d] = q.back(); q.pop_back();  // Get the current position and distance
                dist[source][n * ii + jj] = d;  // Store the distance from source to (ii, jj)

                // Explore all 8 possible moves of a knight
                for (int dx : {-2, -1, 1, 2}) {
                    for (int dy : {-2, -1, 1, 2}) {
                        if (abs(dx) == abs(dy)) continue;  // Skip moves that are not valid knight moves
                        int x = ii + dx, y = jj + dy;  // New position after the move
                        if (x >= 0 && x < m && y >= 0 && y < n && !v[x][y]) {
                            v[x][y] = true;  // Mark the new position as visited
                            q.emplace_front(x, y, d + 1);  // Add the new position to the queue with updated distance
                        }
                    }
                }
            }
            
            // Mark the source as done
            done[source] = true;
        }

        // Number of positions including the starting position
        int n_positions = positions.size();
        int target = (1 << n_positions) - 1;  // Target mask where all positions are visited
        
        // DP table to store the maximum moves for each position and state
        vector<vector<vector<int>>> dp(n_positions, vector<vector<int>>(1 << n_positions, vector<int>(2, -1)));
        
        // Initialize DP table for the last position (end game state)
        for (int i = 0; i < n_positions; ++i) 
            dp[i][target][0] = dp[i][target][1] = 0;
        
        // Iterate over all possible masks (states)
        for (int mask = target - 1; mask >= 0; --mask) {
            for (int curr = 0; curr < n_positions; ++curr) {
                for (int alice = 0; alice < 2; ++alice) {
                    // Initialize the DP value based on whose turn it is
                    dp[curr][mask][alice] = alice ? -1e7 : 1e7;
                    
                    // Iterate over all positions to find the best move
                    for (int i = 0; i < n_positions - 1; ++i) {
                        if (!(mask & (1 << i))) {  // Check if position i is not yet visited
                            int cost = dist[n * positions[curr][0] + positions[curr][1]][n * positions[i][0] + positions[i][1]];
                            
                            // Update the DP table based on whether it's Alice's or Bob's turn
                            if (alice) {
                                dp[curr][mask][alice] = max(dp[curr][mask][alice], cost + dp[i][mask | (1 << i)][1 - alice]);
                            } else {
                                dp[curr][mask][alice] = min(dp[curr][mask][alice], cost + dp[i][mask | (1 << i)][1 - alice]);
                            }
                        }
                    }
                }
            }
        }
        // Return the maximum moves Alice can achieve when starting from the initial position
        return dp[n_positions - 1][1 << (n_positions - 1)][1];
    }
};
