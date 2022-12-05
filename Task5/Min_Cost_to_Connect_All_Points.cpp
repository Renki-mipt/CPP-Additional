#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        vertex_num = int(points.size());
        std::vector<int> empty;
        for (int point1_ind = 0; point1_ind < vertex_num; ++point1_ind) {     // заполняем список связностей между точками
            adjacency_list_.push_back(empty);
            for (int point2_ind = 0; point2_ind < vertex_num; ++point2_ind) {
                adjacency_list_[point1_ind].push_back(get_edge_price(points[point1_ind], points[point2_ind]));
            }
        }
        return get_min_tree_price_by_Prim();
    }

private:
    int get_edge_price(std::vector<int> point1, std::vector<int> point2) {     // возвращает вес ребра между точками
        return std::abs(point1[0] - point2[0]) + std::abs(point1[1] - point2[1]);
    }

    int get_min_tree_price_by_Prim() {     // ищем mst на точках как на вершинах графа. Далее идет классический алгоритм Прима за O(V^2)
        int sum_price = 0;
        const int INF = 1e9;
        std::vector<int> dist(adjacency_list_.size(), INF);
        std::vector<bool> in_tree(adjacency_list_.size(), false);
        dist[0] = 0;
        int vertex_closest = 0;     // индекс обрабатываемой на этапе цикла вершины
        while (vertex_closest != -1) {     
            sum_price += dist[vertex_closest];
            dist[vertex_closest] = INF;
            in_tree[vertex_closest] = true;
            for (int vertex_ind = 0; vertex_ind < vertex_num; ++vertex_ind) {     // проходимся по всем соседям vertex_closest, проводим релаксацию ребер
                if (!in_tree[vertex_ind] && dist[vertex_ind] > adjacency_list_[vertex_closest][vertex_ind]) {
                    dist[vertex_ind] = adjacency_list_[vertex_closest][vertex_ind];
                }
            }
            int min_dist = INF;
            vertex_closest = -1;
            for (int vertex_ind = 0; vertex_ind < vertex_num; ++vertex_ind) {  // поиск новой vertex_closest с минимальным расстоянием от текущего дерева до неё
                if (!in_tree[vertex_ind] && dist[vertex_ind] < min_dist) {
                    min_dist = dist[vertex_ind];
                    vertex_closest = vertex_ind;
                }
            }
        }
        return sum_price;
    }

    int vertex_num;  // количество вершин в графе
    std::vector<std::vector<std::pair<int, int>>> adjacency_list_;  // список связностей
};

/*
int main()
{
    std::vector<std::vector<int>> points = { {0, 0} ,{2, 2},{3, 10},{5, 2},{7, 0} };
    Solution s;
    std::cout << s.minCostConnectPoints(points);
    return 0;
}
*/