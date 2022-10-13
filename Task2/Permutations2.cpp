// Permutations2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <algorithm>


class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::vector<std::vector<int>> answers;      // вектор, в который будет записан итоговый ответ
        if (nums.size() > 0) {                      // необходимо проверить, что ввод не пустой, это используется в далее
            std::sort(nums.begin(), nums.end());    // отсортируем вводные числа, чтобы удобнее было их обработать
            int number_of_inclidings = 1;           // переменная, отвечающая за кол-во вхождений числа в списке
            std::vector<std::pair<int, int>> possibilities;          // эта вектор хранит пару: число - кол-во его вхождений
            for (int count = 1; count < nums.size(); ++count) {      // пробегаемся по nums
                if (nums[count] == nums[count - 1]) {                // Если текущее число равно предыдущему 
                    ++number_of_inclidings;                          // то надо увеличить счетчик вхождений в nums рассматриваемого числа
                }
                else {
                    possibilities.push_back(std::make_pair(nums[count - 1], number_of_inclidings));     // иначе надо завершить подсчет вхождений предыдущего числа(ведь оно нам больше не встретится, т.к. вектор отсортирован), положив данные в possibilities
                    number_of_inclidings = 1;     // обновляем счетчик вхождений, теперь он считает вхождений числа nums[count]
                }
            }
            possibilities.push_back(std::make_pair(nums[nums.size() - 1], number_of_inclidings));    // кладем данные, оставшиеся после того, как весь вектор nums уже пробежали
            std::vector<int> permutation(nums.size());             // вектор, в котором будем хранить текущую перестановку(то, что уже сформировали)
            BackTrack(permutation, possibilities, 0, answers);     // Запускаем функцию поиска всех перестановок
        }
        return answers;
    }

private:
    void BackTrack(std::vector<int>& permutation, std::vector<std::pair<int, int>>& possibilities, // функция принимает permutation - текущую перестановку, possibilities - варианты продолжения в формате <число, кол-во оставшихся вхождений>,
        int step_number, std::vector<std::vector<int>>& answers) {      //  step_number - кол-во заполненных позиций и answers - вектор, куда кладем все полученные перестановки
        if (step_number == permutation.size()) {
            answers.push_back(permutation);     // обработка случая, если вся перестановка уже сформирована(свободных позиций не осталось)
        }
        for (int variant = 0; variant < possibilities.size(); ++variant) {     // пробегаемся по списку кандидатов на следующую позицию
            if (possibilities[variant].second > 0) {                           // если не все экземпляры рассматриваемого числа уже вовлечены в перестановку
                possibilities[variant].second -= 1;                            // уменьшаем кол-во вхождений этого числа в ещё не рассмотренное окончание перестановки
                permutation[step_number] = possibilities[variant].first;       // ставим текущее число на рассматриваемую позицию (её указывает step_number)
                BackTrack(permutation, possibilities, step_number + 1, answers);     // рекурсивно запускаемся, но теперь считаем рассмотренную позицию пройденным этапом
                possibilities[variant].second += 1;                            // возвращаем кол-во вхождений числа на прежний уровень
            }
        }
    }
};



//тестовая часть
/*int main()
{
    std::vector<int> nums;
    int n, a;
    Solution S;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        nums.push_back(a);
    }
    std::vector<std::vector<int>> answer = S.permuteUnique(nums);
    for (int i = 0; i < answer.size(); ++i) {
        for (int j = 0; j < n; ++j) 
            std::cout << answer[i][j] << ' ';
        std::cout << '\n';
    }
}*/

