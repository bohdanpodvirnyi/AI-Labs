//
//  main.cpp
//  lab2
//
//  Created by hell 'n silence on 10/18/18.
//  Copyright © 2018 Bohdan Podvirnyi. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100000;

int n;
vector<int> g[MAXN];
bool used[MAXN];
bool q[MAXN];
vector<int> comp;
int line = 0;
vector<int> lines;

void dfs (int v) {
    used[v] = true;
    comp.push_back(v);
    for (int i = 0; i < g[v].size(); ++i) {
        line++;
        int to = g[v][i];
        if (!used[to]) {
            dfs(to);
        }
    }
}

void find_comps() {
    for (int i = 0; i < n; ++i)
        used[i] = false;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            comp.clear();
            line = 0;
            dfs(i);
            lines.push_back(line);
        }
    }
}

int main() {
    int m, x, y;
    
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    
    find_comps();
    
    sort(lines.begin(), lines.end());
    
    cout << lines.size() << endl;
    
    for (int i = 0; i < lines.size(); i++) {
        cout << lines[i]/2 << endl;
    }
    
    return 0;
}
