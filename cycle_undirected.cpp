// https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
bool detect(int src, vector<int> adj[], int vis[]){
        vis[src]=1;
        queue<pair<int, int>> q;
        q.push({src, -1});
        while(!q.empty()){
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();
            
            for(auto adjNode: adj[node]){
                if(!vis[adjNode]){
                    vis[adjNode]=1;
                    q.push({adjNode, node});
                }
                else if(parent!=adjNode){
                    return true;
                }
            }
        }
    }
    bool isCycle(int V, vector<int> adj[]) {
        // Code here
        int vis[V] = {0};
        
        for (int i=0; i<V; i++){ // iterate through all nodes
            if (!vis[i]){
                if (detect(i, adj, vis)) return true;
            }
        }
        return false;
    }
