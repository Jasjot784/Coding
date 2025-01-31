// https://leetcode.com/problems/making-a-large-island/?envType=daily-question&envId=2025-01-31
class Solution {
public:
    map<tuple<int, int>, int> vis; // Visited map to store island sizes
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 4 directions (right, down, left, up)

    // Helper function to perform BFS and calculate the size of an island
    int bfs(vector<vector<int>>& grid, int r, int c, int islandId) {
        queue<pair<int, int>> q;
        q.push({r, c});
        grid[r][c] = islandId; // Mark the cell as part of this island

        int size = 1; // Current island size
        while (!q.empty()) {
            auto [curR, curC] = q.front();
            q.pop();

            for (auto [dr, dc] : directions) {
                int newR = curR + dr, newC = curC + dc;
                if (newR >= 0 && newR < grid.size() && newC >= 0 && newC < grid[0].size() && grid[newR][newC] == 1) {
                    grid[newR][newC] = islandId; // Mark as part of this island
                    q.push({newR, newC});
                    size++; // Increase island size
                }
            }
        }
        return size;
    }

    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int islandId = 2; // Start labeling islands from 2 (1 is already used)
        map<int, int> islandSize; // Maps islandId to its size
        int maxIslandSize = 0;

        // First pass: label all islands and calculate their sizes
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int size = bfs(grid, i, j, islandId);
                    islandSize[islandId] = size;
                    maxIslandSize = max(maxIslandSize, size); // Track the max island size
                    islandId++; // Increment islandId for the next island
                }
            }
        }

        // Second pass: try changing one 0 to 1 and check the largest possible island size
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    set<int> neighboringIslands; // Store islandIds of neighboring islands
                    int potentialSize = 1; // Start with the current cell turned into 1

                    for (auto [dr, dc] : directions) {
                        int newR = i + dr, newC = j + dc;
                        if (newR >= 0 && newR < n && newC >= 0 && newC < n && grid[newR][newC] > 1) {
                            neighboringIslands.insert(grid[newR][newC]); // Record neighboring island ids
                        }
                    }

                    // Calculate the potential size by merging neighboring islands
                    for (int island : neighboringIslands) {
                        potentialSize += islandSize[island]; // Add their sizes
                    }

                    maxIslandSize = max(maxIslandSize, potentialSize); // Update the max island size
                }
            }
        }

        return maxIslandSize;
    }
};
