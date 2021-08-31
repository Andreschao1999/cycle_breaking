#include<vector>
#include <math.h>
#include <iostream>

using namespace std;

enum mark
{
    white,
    gray,
    black
};

class Graphbc {
    public:
        int n, sum_weight, weight;
        double c;
        vector<mark> v_color;
        vector<bool> visit;
        vector<int> key, parent;
        vector< vector<int> > trash;
        vector< vector< pair<int, int> > > e;
        Graphbc(int num, vector< vector< pair<int, int> > > edges, int sum) { 
            n = num;
            e = edges;
            sum_weight = sum;
            weight = 0;
            c = -pow(2, 31);
            vector<int> cc(n, c);
            for (int i = 0; i < n; i++) {
                trash.push_back(cc);
                v_color.push_back(white);
                visit.push_back(false);
                key.push_back(c);
                parent.push_back(-1);
            }
        }
        void MST() {
            v_color.clear();
            if (n > 0) {
                key[0] = -(c + 1);
                int vertex;
                for (int i = 0; i < n; i++) {
                    vertex = find_max();
                    visit[vertex] = true;
                    for (int j = 0; j < e[vertex].size(); j++) {
                        if (visit[e[vertex][j].first] == false && e[vertex][j].second > key[e[vertex][j].first]) {
                            if (parent[e[vertex][j].first] != -1) {
                                weight += key[e[vertex][j].first];
                                trash[parent[e[vertex][j].first]][e[vertex][j].first] = key[e[vertex][j].first];
                            }
                            key[e[vertex][j].first] = e[vertex][j].second;
                            parent[e[vertex][j].first] = vertex;
                        } else {
                            weight += e[vertex][j].second;
                            trash[vertex][e[vertex][j].first] = e[vertex][j].second;
                        }
                    }
                }
            }
        }
        int find_max() {
            int max_int = -pow(2, 31);
            int max_index = 0;
            for (int i = 0; i < n; i++) {
                if (visit[i] == false && key[i] > max_int) {
                    max_int = key[i];
                    max_index = i;
                }
            }
            return max_index;
        }
        int call_cost_u() {
            return weight - sum_weight;
        }
        vector< vector<int> >  call_cut_u() {
            return trash;
        }
        void DFS() {
            visit.clear();
            if (n > 0) {
                for (int i = 0; i < n; i++) {
                    DFS_visit_pre(i);
                }
            }
        }
        void DFS_visit_pre(int k) {
            for (int j = 0; j < e[k].size(); j++) {
                v_color[k] = gray;
                int k_child = e[k][j].first;
                if (trash[k][k_child] == c) {
                    key[k_child] = e[k][j].second;
                    parent[k_child] = k;
                    DFS_visit(k_child);
                }
                reset_vector();
            }
        }
        void DFS_visit(int k) {
            v_color[k] = gray;
            for (int j = 0; j < e[k].size(); j++) {
                int k_child = e[k][j].first;
                if (trash[k][k_child] == c) {
                    if (v_color[k_child] == white) {
                        key[k_child] = e[k][j].second;
                        parent[k_child] = k;
                        DFS_visit(k_child);
                    } else if (v_color[k_child] == gray) {
                        break_cycle(k, k_child, e[k][j].second);
                    }
                }
            }
            v_color[k] = black;
        }
        void break_cycle(int x, int y, int w) {
            int v_result = find_min(x, y);
            if (w <= key[v_result]) {
                weight += w;
                trash[x][y] = w;
            } else {
                if (trash[parent[v_result]][v_result] !=  key[v_result]) {
                    weight += key[v_result];
                    trash[parent[v_result]][v_result] = key[v_result];
                }
            }
        }
        int find_min(int x, int y) {
            int result;
            if (parent[x] == y) {
                return x;
            } else {
                result = find_min(parent[x], y);
                if (key[x] <= key[result]) {
                    return x;
                } else {
                    return result;
                }
            }
        }
        void reset_vector() {
            for (int q = 0; q < n; q++) {
                v_color[q] = white;
                parent[q] = -1;
                key[q] = c;
            }
        }
        int call_cost_d() {
            return weight;
        }     
        vector< vector<int> > call_cut_d() {
            return trash;
        }
};