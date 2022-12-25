// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int cur_min = INF;  // поддерживаем текущий минимум
        int cur_max_profit = 0;  // храним наибольшую текущую выгоду
        for (auto price : prices) {
            if (price - cur_min > cur_max_profit) { //обновляем наибольшую текущую выгоду, если есть возможность её увеличить, продав за цену price
                cur_max_profit = price - cur_min;
            }
            if (price < cur_min) {  // обновляем cur_min, если price стала меньше её
                cur_min = price;
            }
        }
        return cur_max_profit;
    }

private:
    int INF = 1e9;
};

/*
int main()
{
    Solution S;
    std::vector<int> prices = { 7,1,5,3,6,4 };
    std::cout << S.maxProfit(prices);
}*/
