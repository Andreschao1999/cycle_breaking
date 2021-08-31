#include <iostream>
#include <fstream>
#include "build_cycle.h"

using namespace std;
void help_message() { cout << "./cb <input_file> <output_file>" << endl; }
int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }
    //////////// read the input file as Graph/////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    char type_name;
    int n, e_num, a, b, w, sum;
    sum = 0;
    int c = -pow(2, 31);
    fin >> type_name;
    fin >> n;
    fin >> e_num;
    vector< vector< pair<int, int> > > e (n);
    int weight;
    vector< vector<int> > cut_edge;
    if (type_name == 'u') {
        for (int i = 0; i < e_num; i++) {
            fin >> a >> b >> w;
            e[a].push_back(pair<int, int>(b, w));
            sum += w;
            e[b].push_back(pair<int,int>(a, w));
        }
        Graphbc Graphbc(n, e, sum);
        Graphbc.MST();
        weight = Graphbc.call_cost_u();
        cut_edge = Graphbc.call_cut_u();
        fout << weight << '\n';
        for (int i = 0; i < n - 1; i++) {
            for (int j = (i + 1); j < n; j++) {
                if (cut_edge[i][j] != c && cut_edge[j][i] != c) {
                    fout << i << " " << j << " " << cut_edge[i][j] << '\n';
                }
            }
        }
    } else {
        for (int i = 0; i < e_num; i++) {
            fin >> a >> b >> w;
            sum += w;
            e[a].push_back(pair<int,int>(b, w));     } 
        Graphbc Graphbc(n, e, sum);
        Graphbc.DFS();
        weight = Graphbc.call_cost_d();
        cut_edge = Graphbc.call_cut_d();  
        fout << weight << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cut_edge[i][j] != c) {
                    fout << i << " " << j << " " << cut_edge[i][j] << '\n';
                }
            }
        }      
    }
    fin.close();
    fout.close();
    return 0;
}