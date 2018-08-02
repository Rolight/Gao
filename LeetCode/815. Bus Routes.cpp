#include <algorithm>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct QNode {
    int route_id, stop_id, dis;
    QNode(int route_id, int stop_id, int dis)
        : route_id(route_id), stop_id(stop_id), dis(dis) {}
};

class Solution {
    bool get(unordered_map<int, unordered_map<int, int> > &mp, int route_id,
             int stop_id) {
        return mp.count(route_id) && mp[route_id].count(stop_id);
    }

   public:
    int numBusesToDestination(vector<vector<int> > &routes, int S, int T) {
        if (S == T) return 0;
        unordered_map<int, vector<int> > hashp;
        queue<QNode> q;
        vector<bool> vis_routes(routes.size(), false);
        unordered_map<int, unordered_map<int, int> > dis;
        for (int i = 0; i < routes.size(); i++) {
            for (int j = 0; j < routes[i].size(); j++) {
                hashp[routes[i][j]].push_back(i);
                if (routes[i][j] == S) {
                    q.push(QNode(i, S, 0));
                }
            }
        }

        while (!q.empty()) {
            QNode node = q.front();
            q.pop();

            /*
            printf("route_id: %d, stop_id: %d, dis: %d\n", node.route_id,
                   node.stop_id, node.dis);
            */

            // change stop
            vector<int> &route_ids = hashp[node.stop_id];
            for (int i = 0; i < route_ids.size(); i++) {
                int route_id = route_ids[i];
                // printf("route_id -> %d\n", route_id);
                if (vis_routes[route_id]) continue;
                for (int j = 0; j < routes[route_id].size(); j++) {
                    int stop_id = routes[route_id][j];
                    if (get(dis, route_id, stop_id)) continue;
                    dis[route_id][stop_id] = node.dis + 1;
                    q.push(QNode(route_id, stop_id, node.dis + 1));
                    if (stop_id == T) return node.dis + 1;
                }
                vis_routes[route_id] = true;
            }
        }

        return -1;
    }
};