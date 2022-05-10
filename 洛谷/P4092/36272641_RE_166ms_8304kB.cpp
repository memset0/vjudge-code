// luogu-judger-enable-o2
// test

#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <vector>

class Graph {
private:
    std::vector<unsigned> closest, count, parent;
    std::vector<std::vector<unsigned>> edge;

    void join(const unsigned u, const unsigned v) {
        closest[find(v)] = find(u);
        return;
    }

public:
    Graph(unsigned n) : closest(n), count(n), parent(n), edge(n) {}

    void addEdge(const unsigned u, const unsigned v) {
        edge[u].push_back(v);
        edge[v].push_back(u);
        return;
    }

    void bfs(const unsigned s) {
        std::queue<unsigned> q({s});
        std::vector<bool> vis(edge.size());
        count[s] = 1;
        closest[s] = parent[s] = s;
        while (!q.empty()) {
            const unsigned u = q.front();
            q.pop();
            vis[u] = true;
            for (const auto &v : edge[u]) {
                if (!vis[v]) {
                    parent[v] = u;
                    closest[v] = (count[v] ? v : closest[u]);
                    q.push(v);
                }
            }
        }
        return;
    }

    unsigned find(const unsigned u) {
        if (closest[u] != u) {
            closest[u] = find(closest[u]);
        }
        return closest[u];
    }

    void mark(const unsigned u) {
        ++count[u];
        return;
    }

    void unmark(const unsigned u) {
        if (!--count[u]) {
            join(parent[u], u);
        }
        return;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    unsigned n, q;
    std::cin >> n >> q;
    Graph g(n);
    for (unsigned i = 1; i < n; ++i) {
        unsigned u, v;
        std::cin >> u >> v;
        --u, --v;
        g.addEdge(u, v);
    }
    std::stack<std::pair<char, unsigned>> s;
    for (unsigned i = 0; i < q; ++i) {
        char op;
        unsigned u;
        std::cin >> op >> u;
        --u;
        if (op == 'C') {
            g.mark(u);
        }
        s.push({op, u});
    }
    g.bfs(0);
    std::stack<unsigned> ans;
    while (!s.empty()) {
        switch (s.top().first) {
            case 'C':
                g.unmark(s.top().second);
                break;
            case 'Q':
                ans.push(g.find(s.top().second));
                break;
            default:
                break;
        }
        s.pop();
    }
    while (!ans.empty()) {
        std::cout << (ans.top() + 1) << '\n';
        ans.pop();
    }
    return 0;
}