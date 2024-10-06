// https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/
class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        // Step 1: Create an adjacency list to represent the graph
        vector<list<int>> graph(n);
        for (const auto& e : edges) {
            // Add both directions since it's an undirected graph
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        // Step 2: Initialize adjacency counts and degree categories
        vector<int> adj(n);
        vector<int> adjNum(5, 0); // To count how many nodes have degree 0 to 4
        vector<int> adj1, adj2; // To store nodes with degree 1 and 2

        // Count degrees of each node
        for (int i = 0; i < n; i++) {
            adj[i] = graph[i].size(); // Degree of node i
            adjNum[adj[i]]++; // Increment the count for the corresponding degree
            if (adj[i] == 1) adj1.push_back(i); // Store nodes with degree 1
            if (adj[i] == 2) adj2.push_back(i); // Store nodes with degree 2
        }

        vector<vector<int>> res; // Result grid to return
        if (adjNum[1] == 2) { // If there are exactly two nodes with degree 1
            res.resize(1, vector<int>(n)); // Initialize a single row for result
            int start = adj1[0]; // Start from one of the degree 1 nodes
            int i = 0; // To track position in the result row
            vector<bool> v(n, false); // Visited nodes tracker
            queue<int> q; // Queue for BFS
            q.push(start); // Start BFS from the chosen node
            v[start] = true; // Mark the starting node as visited

            // BFS to traverse the graph and fill the result row
            while (!q.empty()) {
                int cur = q.front(); // Current node
                q.pop();
                res[0][i++] = cur; // Add current node to the result row
                for (int next : graph[cur]) {
                    if (!v[next]) { // If the next node hasn't been visited
                        v[next] = true; // Mark it as visited
                        q.push(next); // Add it to the queue for BFS
                    }
                }
            }
            return res; // Return the result if we only need a single row
        } else {
            // If we have more complex connections (nodes with degree 2)
            int height = 0;
            int width = 0;
            int start = adj2[0]; // Start from one of the degree 2 nodes
            vector<bool> v(n, false); // Visited nodes tracker
            queue<int> q; // Queue for BFS
            q.push(start); // Start BFS from the degree 2 node
            v[start] = true; // Mark the starting node as visited
            vector<vector<int>> list; // To store nodes level-wise
            int l = 0; // Level counter

            // BFS to explore the graph level by level
            while (!q.empty()) {
                int size = q.size(); // Number of nodes at the current level
                l++; // Increment level counter
                vector<int> nextLevel; // Nodes at the next level
                int cur = q.front(); // Current node
                q.pop();
                nextLevel.push_back(cur); // Add current node to next level
                int min = -1; // Variable to find the minimum degree neighbor

                // Find the minimum degree neighbor that hasn't been visited
                for (int next : graph[cur]) {
                    if (!v[next] && (min == -1 || adj[min] > adj[next])) {
                        min = next; // Update minimum degree neighbor
                    }
                }

                // If we found a minimum degree neighbor, process it
                if (min != -1) {
                    q.push(min); // Add it to the queue
                    v[min] = true; // Mark it as visited
                    // Check if this neighbor is one of the degree 2 nodes
                    if (min != start && find(adj2.begin(), adj2.end(), min) != adj2.end() && height == 0) {
                        height = l + 1; // Set height based on level
                    }
                }

                // Process all other neighbors of the current node
                for (int next : graph[cur]) {
                    if (!v[next]) { // If not visited
                        v[next] = true; // Mark as visited
                        q.push(next); // Add to the queue
                    }
                }

                size--; // Decrease the level node count
                // Process remaining nodes at the current level
                while (size-- > 0) {
                    cur = q.front(); // Current node
                    q.pop();
                    nextLevel.push_back(cur); // Add to next level

                    // If this is a degree 2 node, track width
                    if (find(adj2.begin(), adj2.end(), cur) != adj2.end()) {
                        if (width == 0) width = l; // Set width based on first degree 2 node found
                    }

                    for (int next : graph[cur]) { // Explore neighbors
                        if (!v[next]) { // If not visited
                            v[next] = true; // Mark as visited
                            q.push(next); // Add to queue
                        }
                    }
                }
                list.push_back(nextLevel); // Store the current level's nodes
            }

            // Step 3: Prepare the result grid based on levels captured
            res.resize(height, vector<int>(width)); // Initialize result grid
            int lvl = -1; // Level index for placing nodes

            // Populate the result grid based on captured levels
            for (const auto& level : list) {
                int size = level.size(); // Number of nodes at this level
                lvl++; // Increment level index
                int row = min(lvl, height - 1); // Determine row index
                int col = lvl - row; // Determine column index
                for (int j = 0; j < size; j++) {
                    int val = level[j]; // Current node value
                    res[row - j][col + j] = val; // Place the value in the grid
                }
            }
        }
        return res;
    }
};
