#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>>& edges) {
        std::vector<std::vector<int>> graph(edges.size());
        for (auto edge: edges) {
            graph[edge[0] - 1].emplace_back(edge[1] - 1);
        }
        std::vector<int> parents(graph.size(), -1);
        for (auto edge: edges) {
            if (parents[edge[1] - 1] == -1) {
                parents[edge[1] - 1] = edge[0] - 1;
            }
            else {
                parents[edge[1] - 1] = -2;
            }
        }
        std::vector<bool> false_roots(graph.size(), false);
        for (int vertex = 0; vertex < graph.size(); ++vertex) {
            if (parents[vertex] == -1) {
                for (int edge_ind = edges.size() - 1; edge_ind >= 0; --edge_ind) {
                    delete_edge(graph, edges[edge_ind][0] - 1, edges[edge_ind][1] - 1);
                    if (is_tree(graph, vertex)) {
                        return edges[edge_ind];
                    }
                    graph[edges[edge_ind][0] - 1].emplace_back(edges[edge_ind][1] - 1);
                }
            }
            if (parents[vertex] >= 0) {
                delete_edge(graph, parents[vertex], vertex);
                if (is_tree(graph, vertex)) {
                    false_roots[vertex] = true;
                }
                graph[parents[vertex]].emplace_back(vertex);
            }
        }

        for (int edge_ind = edges.size() - 1; edge_ind >= 0; --edge_ind) {
            if (false_roots[edges[edge_ind][1] - 1] == true) {
                return edges[edge_ind];
            }
        }
        std::vector<int> not_find = { -1, -1 };
        return not_find;
    }


private:
    bool is_tree(std::vector<std::vector<int>>& graph, int root) {
        std::vector<bool> colors(graph.size(), false);
        if (dfs(graph, root, colors)) {
            for (auto color : colors) {
                if (!color) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool dfs(std::vector<std::vector<int>>& graph, int root, std::vector<bool>& colors) {
        if (colors[root]) {
            return false;
        }
        colors[root] = true;
        for (int neigh_ind = 0; neigh_ind < graph[root].size(); ++neigh_ind) {
            if (!dfs(graph, graph[root][neigh_ind], colors)) {
                return false;
            }
        }
        return true;
    }

    void delete_edge(std::vector<std::vector<int>>& graph, int begin, int end) {
        for (int ind = 0; ind < graph[begin].size(); ++ind) {
            if (graph[begin][ind] == end) {
                std::swap(graph[begin][ind], graph[begin][graph[begin].size() - 1]);
                graph[begin].resize(graph[begin].size() - 1);
            }
        }
    }
};

/*
int main()
{
    std::vector<std::vector<int>> edges = { {1, 2} ,{2, 3},{3, 4},{4, 1},{1, 5} };
    Solution S;
    std::vector<int> ans = S.findRedundantDirectedConnection(edges);
    std::cout << ans[0] << ' ' << ans[1] << '\n';
}*/
