#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>

using namespace std;

const int Mouse = 1;
const int Cat = 2;
const int Draw = 0;


class State {
    public:
    int turn, result, mouse_pos, cat_pos;
    State(int t, int r, int s1, int s2): turn(t), result(r), mouse_pos(s1), cat_pos(s2) {}
};

int f[3][256][256];
int deg[3][256][256];

class Solution {
  public:
    int catMouseGame(vector<vector<int>> &graph) {
        int m = graph.size();
        memset(f, 0, sizeof(f));
        memset(deg, 0, sizeof(deg));
        queue<State> q;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                deg[Mouse][i][j] = graph[i].size();
                deg[Cat][i][j] = graph[j].size();
                for(int k = 0; k < graph[j].size(); k++) {
                    if(graph[j][k] == 0) {
                        deg[Cat][i][j]--;
                    }
                }
            }
        }
        for(int i = 1; i < m; i++) {
            q.push(State(Mouse, Cat, i, i));
            q.push(State(Cat, Cat, i, i));
            q.push(State(Cat, Mouse, 0, i));
            f[Mouse][i][i] = f[Cat][i][i] = Cat;
            f[Cat][0][i] = Mouse;
        }
        while(!q.empty()) {
            State now = q.front();
            q.pop();
            int current_pos = (now.turn == Mouse ? now.cat_pos : now.mouse_pos);
            for(int i = 0; i < graph[current_pos].size(); i++) {
                int nxt_pos = graph[current_pos][i];
                int nxt_turn = ((now.turn - 1) ^ 1) + 1;
                if(nxt_turn == Cat && nxt_pos == 0) continue;
                State nxt = now;
                nxt.turn = nxt_turn;
                if(now.turn == Mouse) nxt.cat_pos = nxt_pos;
                else nxt.mouse_pos = nxt_pos;
                if(f[nxt.turn][nxt.mouse_pos][nxt.cat_pos] != 0) continue;
                if(nxt.turn == now.result) {
                    nxt.result = now.result;
                    f[nxt.turn][nxt.mouse_pos][nxt.cat_pos] = nxt.result;
                    // printf("%s %d, %d = %d\n", nxt.turn == Mouse ? "Mouse" : "Cat", nxt.mouse_pos, nxt.cat_pos, nxt.result);
                    q.push(nxt);
                } else {
                    deg[nxt.turn][nxt.mouse_pos][nxt.cat_pos]--;
                    if(deg[nxt.turn][nxt.mouse_pos][nxt.cat_pos] == 0) {
                        f[nxt.turn][nxt.mouse_pos][nxt.cat_pos] = now.turn;
                        nxt.result = now.turn;
                        // printf("%s %d, %d = %d\n", nxt.turn == Mouse ? "Mouse" : "Cat", nxt.mouse_pos, nxt.cat_pos, nxt.result);
                        q.push(nxt);
                    }
                }
            }
        }
        return f[Mouse][1][2];
    }
};