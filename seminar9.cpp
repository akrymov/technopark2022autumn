#include <iostream>
#include <vector>
#include <algorithm>

class DSU {
public:
    explicit DSU(int size) {
        parent.resize(size);
        rank.resize(size, 1);

        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        parent[v] = find_set(parent[v]);
        return parent[v];
    }

    void union_set(int v, int u) {
        int v_set = find_set(v);
        int u_set = find_set(u);

        if (v_set == u_set) {
            return;
        }

        if (rank[v_set] < rank[u_set]) {
            parent[v_set] = u_set;
            rank[u_set] += rank[v_set];
        } else {
            parent[u_set] = v_set;
            rank[v_set] += rank[u_set];
        }
    }
private:
    std::vector<int> parent;
    std::vector<int> rank;
};

struct Edge
{
    int from;
    int to;
    int weight;
};

void kruskal(std::vector<Edge>& edges, void (*callback)(const Edge&)) {
    std::sort(edges.begin(), edges.end(), [](const Edge& l, const Edge& r) {
        return l.weight < r.weight;
    });

    DSU dsu(edges.size());

    for (const Edge& edge : edges) {
        int from_set = dsu.find_set(edge.from);
        int to_set = dsu.find_set(edge.to);

        if (from_set != to_set) {
            dsu.union_set(from_set, to_set);
            callback(edge);
        }
    }
}


int main() {
    std::vector <Edge> edges = {
        { 2, 3, 3 },
        { 1, 6, 4 },
        { 5, 7, 5 },
        { 6, 8, 5 },
        { 7, 8, 5 },
        { 2, 4, 1 },
        { 3, 4, 1 },
        { 1, 3, 2 },
        { 0, 3, 6 },
        { 4, 7, 6 },
        { 3, 6, 7 },
        { 0, 1, 9 },
        { 3, 5, 9 },
        { 5, 6, 1 },
        { 5, 8, 1 },
        { 0, 2, 2 }
    };

    kruskal(edges, [](const Edge& edge) {
        std::cout << "(" << edge.from << ", " << edge.to << ")" << std::endl;
    });
}
