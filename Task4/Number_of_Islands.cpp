#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {    
        if (grid.size() == 0) {
            return 0;
        }
        std::vector<bool> false_vec(grid[0].size(), false);
        for (int x = 0; x < grid.size(); ++x) {
            considered_.push_back(false_vec);
        }
        int islands_count = 0;
        for (int x = 0; x < grid.size(); ++x) {
            for (int y = 0; y < grid[x].size(); ++y) {
                if (grid[x][y] != '0' && !considered_[x][y]) {
                    ++islands_count;
                    bfs(x, y, grid);
                }
            }
        }
        return islands_count;
    }


private:
    void bfs(int x, int y, std::vector<std::vector<char>>& grid) {
        if (grid[x][y] == '0'  || considered_[x][y]) {
            return;
        }
        considered_[x][y] = true;
        if (x + 1 < grid.size()) {
            bfs(x + 1, y, grid);
        }
        if (x - 1 >= 0) {
            bfs(x - 1, y, grid);
        }
        if (y + 1 < grid[x].size()) {
            bfs(x, y + 1, grid);
        }
        if (y - 1 >= 0) {
            bfs(x, y - 1, grid);
        }
    }

    std::vector<std::vector<bool>> considered_;
};


int main()
{
    std::vector<std::vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1' }
    };
    Solution s;
    std::cout << s.numIslands(grid);
}

