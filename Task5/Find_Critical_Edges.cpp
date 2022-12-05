#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<std::vector<int>> findCriticalAndPseudoCriticalEdges(int n, std::vector<std::vector<int>>& edges) {
        vertex_num = n;
        std::vector<std::pair<int, int>> empty;
        for (int i = 0; i < n; ++i) {       // заполняем список связностей пыстыми векторами
            adjacency_list_.push_back(empty);
        }
        for (auto edge : edges) {     // заполняем список связностей, перенося данные их списка ребер
            adjacency_list_[edge[0]].push_back(std::make_pair(edge[1], edge[2]));
            adjacency_list_[edge[1]].push_back(std::make_pair(edge[0], edge[2]));
        }

        int mst_val = get_min_tree_price_by_Prim(0, 0);     // вычисляем минимальный mst исходного графа
        std::vector<std::vector<int>> answer;
        if (mst_val == INF) {    // если mst исходного графа не существует, значит и критических и псевдокритических ребер нет
            return answer;
        }
        
        std::vector<int> critical_edges;
        std::vector<int> pseudo_critical_edges;
        int edge_index = -1;
        for (auto edge: edges) {
            ++edge_index;            // здесь считаем номер рассматриваемого ребра
            bool is_critical = false;
            for (int neigh_ind = 0; neigh_ind < adjacency_list_[edge[0]].size(); ++neigh_ind) {  // следующие 6 строк удаляем ребро в направлении edge[0] -> edge[1] 
                if (adjacency_list_[edge[0]][neigh_ind].first == edge[1]) {
                    std::swap(adjacency_list_[edge[0]][neigh_ind],
                        adjacency_list_[edge[0]][adjacency_list_[edge[0]].size() - 1]);
                    adjacency_list_[edge[0]].resize(adjacency_list_[edge[0]].size() - 1);  
                    break;
                }
            }
            for (int neigh_ind = 0; neigh_ind < adjacency_list_[edge[1]].size(); ++neigh_ind) {  // следующие 6 строк удаляем ребро в направлении edge[1] -> edge[0] 
                if (adjacency_list_[edge[1]][neigh_ind].first == edge[0]) {
                    std::swap(adjacency_list_[edge[1]][neigh_ind],
                        adjacency_list_[edge[1]][adjacency_list_[edge[1]].size() - 1]);
                    adjacency_list_[edge[1]].resize(adjacency_list_[edge[1]].size() - 1);
                    break;
                }
            }
            if (get_min_tree_price_by_Prim(0, 0) > mst_val) {     // если без ребра mst стал большего веса, значит ребро критическое
                critical_edges.push_back(edge_index);
                is_critical = true;
            }
            adjacency_list_[edge[0]].push_back(std::make_pair(edge[1], edge[2]));  // возвращаем удаленное ребро на место
            adjacency_list_[edge[1]].push_back(std::make_pair(edge[0], edge[2]));
            if (!is_critical) {                                                    // если не критическое, проверяем на псевдокритичность
                if (get_min_tree_price_by_Prim(edge[0], edge[1]) + edge[2] == mst_val) {      // если вес mst содержащго рассматриваемое ребро такой же как и mst_val
                    pseudo_critical_edges.push_back(edge_index);                              // значит ребро псевдокритическое
                }
            }
        }
        answer.push_back(critical_edges);
        answer.push_back(pseudo_critical_edges);
        return answer;
    }

private:
    int get_min_tree_price_by_Prim(int start_vertex, int extra_vertex_in) {     // считаем mst алгоритмом Прима; Изначально добавлено ребро, соединяющее изstart_vertex и extra_vertex_in
        int sum_price = 0;
        std::vector<int> dist(vertex_num, INF);     
        std::vector<bool> in_tree(vertex_num, false);
        in_tree[start_vertex] = true;
        for (auto neighbor : adjacency_list_[start_vertex]) {    
            dist[neighbor.first] = neighbor.second;
        }
        int vertex_closest = extra_vertex_in;
        dist[vertex_closest] = 0;
        // дальше классический алгоритм Прима
        while (vertex_closest != -1) {
            sum_price += dist[vertex_closest];
            in_tree[vertex_closest] = true;
            for (auto neighbor: adjacency_list_[vertex_closest]) {
                if (!in_tree[neighbor.first] && dist[neighbor.first] > neighbor.second) {
                    dist[neighbor.first] = neighbor.second;
                }
            }
            int min_dist = INF;
            vertex_closest = -1;
            for (int vertex_ind = 0; vertex_ind < vertex_num; ++vertex_ind) {
                if (!in_tree[vertex_ind] && dist[vertex_ind] < min_dist) {
                    min_dist = dist[vertex_ind];
                    vertex_closest = vertex_ind;
                }
            }
        }
        for (auto check : in_tree) {     // Тут проверка, что все вершины находятся в mst
            if (!check) {
                return INF;
            }
        }
        return sum_price;
    }

    const int INF = 1e9;
    int vertex_num;
    std::vector<std::vector<std::pair<int, int>>> adjacency_list_;
};

/*int main()
{
    Solution S;
    int n = 5;
    std::vector<std::vector<int>> edges = { {0, 1, 1},{1, 2, 1},{2, 3, 2},{0, 3, 2}, {0, 4, 3},{3, 4, 3},{1, 4, 6} };
    std::vector<std::vector<int>> s = S.findCriticalAndPseudoCriticalEdges(n, edges);
    //std::cout << "Hello World!\n";
}*/
