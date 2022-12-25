
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> criticalConnections(int n, std::vector<std::vector<int>>& connections) {  // обычная задачка на поиск всех мостов в графе
        std::vector<std::pair<int, int>> empty;
        for (int vertex = 0; vertex < n; vertex++) {  // последующие 7 строк переводим данные о графе в более удобный формат - список связностей (приватное поле connection_list)
            connection_list.push_back(empty);
        }
        for (int edge_index = 0; edge_index < connections.size(); ++edge_index) {  
            connection_list[connections[edge_index][0]].push_back(std::make_pair(connections[edge_index][1], edge_index));
            connection_list[connections[edge_index][1]].push_back(std::make_pair(connections[edge_index][0], edge_index));
        }
        std::vector<int> bridges;       // сюда будем складывать критические ребра
        std::vector<int> times(n, -1);  // при обходе в глубину сюда записываем время входа для каждой вершины
        dfs(0, -1, 0, times, bridges);   // начинаем обход с 0-вершины, предыдущей для неё нету, текущее время - 0.
        std::vector<std::vector<int>> answer;
        for (auto bridge : bridges) {
            answer.push_back(connections[bridge]);
        }
        return answer;
    }

private:
    int dfs(int vertex, int prev_vertex, int cur_time, std::vector<int>& times, std::vector<int>& bridges) {
        // vertex - текущая вершина, prev_vertex - её родитель, cur_time - текущее время, times - вектор времен для каждой вершины(или -1, если ещё не дошли), bridges - сюда кладем мосты
        times[vertex] = cur_time;
        int min_time = cur_time;     // сюда считаем минимальное время вершин, доступных из текущей
        for (int neig = 0; neig < connection_list[vertex].size(); ++neig) {  // пробегаемся по всем соседям
            if (connection_list[vertex][neig].first == prev_vertex) {        // если непосредственный родитель - игнорируем
                continue;
            }
            if (times[connection_list[vertex][neig].first] != -1) {          // если уже были в вершине - обновляем минимальное время(min_time) вершин, доступных из текущей
                min_time = std::min(min_time, times[connection_list[vertex][neig].first]);
                continue;
            }
            int local_min_time = dfs(connection_list[vertex][neig].first, vertex, cur_time+1, times, bridges);  // если не были в вершине, рекурсивно идем в неё
            if (local_min_time > times[vertex]) {
                bridges.push_back(connection_list[vertex][neig].second);           // если по ребру нельзя добраться до ранее рассмотренных вершин - оно мост
            }
            min_time = std::min(min_time, local_min_time);              // при надобности обновляем min_time
        }
        return min_time;  
    }

    
    std::vector<std::vector<std::pair<int, int>>> connection_list;  // список связностей графа
};

/*
int main()
{
    Solution S;
    int n = 2;
    std::vector<std::vector<int>> connections = { {0, 1} };
    std::vector<std::vector<int>> ans = S.criticalConnections(n, connections);
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i][0] << ' ' << ans[i][1] << '\n';
    }

    std::cout << "Hello World!\n";
}
*/