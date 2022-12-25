#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums) {
        long long xor_sum = 0;                               
        for (auto num : nums) {              //суммируем ксором(xor) все числа и записываем результат в xor_sum. Дубликаты взаимно уничтожатся, 
            xor_sum ^= num;                  //останется только xor двух уникальных чисел
        }
        long long deviding_num = 1;          //здесь находим наименьший бит, в котором 2 искомых числа различаются(в их xor он единичка)
        for (int bit = 1; bit <= 32; bit++) {
            if ((deviding_num ^ xor_sum) < xor_sum) {
                break;
            }
            deviding_num *= 2;
        }
        int first_number = 0;
        int second_number = 0;
        for (auto num : nums) {             // разбиваем числа на 2 "корзины" - у которых в рассматриваемом бите стоит 0 и у которых стоит 1
            if ((deviding_num ^ num) < num) {       // очевидно 2 искомых числа оказались в разных корзинах по свойству этого бита
                
                first_number ^= num;             // внутри каждой "корзины" делаем xor всех её чисел, дубликаты снова взаимно уничтожаются
            }
            else {
                second_number ^= num;           // результатами xor всех чисел каждой из корзин будут искомые числа
            }
        }
        std::vector<int> answer = { first_number, second_number };  // кладем найденные числа в вектор
        return answer;
    }
    
};


//test
/*
int main()
{
    Solution S;
    std::vector<int> prices = { 1,2,1,3,2,5 };
    std::vector<int> ans = S.singleNumber(prices);
    std::cout << ans[0] << ' ' << ans[1] << '\n';
}
*/