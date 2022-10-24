#include <iostream>
#include <vector>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        std::vector<int> dynamic_amount(amount + 1, 1e5);     // в векторе для каждого значения суммы храним наименьшее число монет, необзодимое для его получения
        dynamic_amount[0] = 0;                                //
        for (int current_amount = 0; current_amount <= amount; ++current_amount) {     // Пробегаемся по всем значениям суммы вплоть до amount
            for (int coin: coins) {                                                    // Пробегаемся по всем значениям монет
                if (current_amount >= coin && dynamic_amount[current_amount - coin] + 1 < dynamic_amount[current_amount]) {     // Если номинал монеты меньше рссматриваемой суммы(чтобы не выйти за пределы массива dynamic_amount) и использование её для достижения данной суммы дает оптимальный результат среди рассмотренных способов
                    dynamic_amount[current_amount] = dynamic_amount[current_amount - coin] + 1;                                 // обновим минимальное число монет для достижения данной суммы
                }
            }
        }
        if (dynamic_amount[amount] < 1e5) {     // если удалось достичь искомой суммы использую монеты
            return dynamic_amount[amount];      // возвращаем ответ
        }
        else {
            return -1;     // иначе возвращаем провал
        }
    }
};

/*int main()
{
    Solution S;
    std::vector<int> coins = { 2, 5 };
    int amount = 3;
    std::cout << S.coinChange(coins, amount);
}*/
