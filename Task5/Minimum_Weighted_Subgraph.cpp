#include <iostream>
#include <vector>
#include <set>

class Solution {
public:
    long long minimumWeight(int n, std::vector<std::vector<int>>& edges, int src1, int src2, int dest) {
        std::vector<std::vector<std::pair<int, int>>> graph_table;                // список свзяности графа
        std::vector<std::vector<std::pair<int, int>>> reversed_graph_table;       // список свзяности реверсированного графа
        std::vector<std::pair<int, int>> empty;
        for (int i = 0; i < n; ++i) {        // следующие 2 цикла заполняем списки смежности
            graph_table.push_back(empty);
            reversed_graph_table.push_back(empty);
        }
        for (auto edge : edges) { 
            graph_table[edge[0]].push_back(std::make_pair(edge[1], edge[2]));
            reversed_graph_table[edge[1]].push_back(std::make_pair(edge[0], edge[2]));
        }
        std::vector<long long> dist_from_src1 = get_dist(src1, graph_table);     // вычисляем расстояние от src1 до всех вершин
        std::vector<long long> dist_from_src2 = get_dist(src2, graph_table);     // вычисляем расстояние от src2 до всех вершин
        std::vector<long long> dist_from_dest = get_dist(dest, reversed_graph_table);     // вычисляем расстояние от всех вершин до dest
        
        long long min_distance = INF;
        for (int ind = 0; ind < n; ++ind) {      // искомый ответ - минимум из расстояний от src1 до некоторой вершины + расстояний от src2 до не же + расстояний от неё до dest
            long long dist = dist_from_src1[ind] + dist_from_src2[ind] + dist_from_dest[ind];
            if (min_distance > dist) {
                min_distance = dist;
            }
        }
        return min_distance < INF ? min_distance: -1;
    }

private:
    std::vector<long long> get_dist(int start, std::vector<std::vector<std::pair<int, int>>>& graph_table) {     // алгоритм Дейкстры за O(E*log(V)) 
        int size = graph_table.size();
        std::vector<long long> dist(size, INF);
        dist[start] = 0;
        std::set<std::pair<long long, int>> current_dist;     // храним вершины с текущими расстояниями до них
        current_dist.insert(std::make_pair(0, start));
        while (!current_dist.empty()) {
            std::pair<long long, int> vertex_current = *current_dist.begin();     // извлекаем вершину с минимальным расстоянием до неё
            current_dist.erase(current_dist.begin());
            for (int vertex_ind = 0; vertex_ind < graph_table[vertex_current.second].size(); ++vertex_ind) {
                if (dist[graph_table[vertex_current.second][vertex_ind].first] > dist[vertex_current.second] + 
                    graph_table[vertex_current.second][vertex_ind].second) {          // проводим релаксацию каждого исходящего ребра    
                    if (dist[graph_table[vertex_current.second][vertex_ind].first] != INF) {   // обновляем   
                        current_dist.erase(std::make_pair(dist[graph_table[vertex_current.second][vertex_ind].first],  
                            graph_table[vertex_current.second][vertex_ind].first));      // удаляем предыдущее значением dist для вершины, в которую ведет ребро
                    }
                    dist[graph_table[vertex_current.second][vertex_ind].first] = dist[vertex_current.second] +     // обновляем расстояние до вершины в массиве dist
                        graph_table[vertex_current.second][vertex_ind].second;
                    current_dist.insert(std::make_pair(dist[graph_table[vertex_current.second][vertex_ind].first], //кладем обновленное значение расстояния до вершины в current_dist
                        graph_table[vertex_current.second][vertex_ind].first));
                }
            }
        }
        return dist;
    }   

    const long long INF = 1e17;
};

/*int main()
{
    int n = 6;
    std::vector<std::vector<int>> edges = { {0, 2, 2}, {0, 5, 6}, {1, 0, 3} ,{1, 4, 5},
        {2, 1, 1},{2, 3, 3},{2, 3, 4},{3, 4, 2},{4, 5, 1} };
    int src1 = 0, src2 = 1, dest = 5;
    Solution S;
    std::cout << S.minimumWeight(n, edges, src1, src2, dest);
}*/

