// subsets2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <algorithm>


class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<std::vector<int>> answers;      // вектор, в который будет записан итоговый ответ
        nums_len = nums.size();                     // запоминаем длину nums в отдельную приватную переменную класса, это удобно в дальнейшем
        if (nums_len > 0) {                      // необходимо проверить, что ввод не пустой, это используется в далее
            std::sort(nums.begin(), nums.end());    // отсортируем вводные числа, чтобы удобнее было их обработать
            int number_of_inclidings = 1;           // переменная, отвечающая за кол-во вхождений числа в списке
            std::vector<std::pair<int, int>> possibilities;          // эта вектор хранит пару: число - кол-во его вхождений
            for (int count = 1; count < nums_len; ++count) {      // пробегаемся по nums
                if (nums[count] == nums[count - 1]) {                // Если текущее число равно предыдущему 
                    ++number_of_inclidings;                          // то надо увеличить счетчик вхождений в nums рассматриваемого числа
                }
                else {
                    possibilities.push_back(std::make_pair(nums[count - 1], number_of_inclidings));     // иначе надо завершить подсчет вхождений предыдущего числа(ведь оно нам больше не встретится, т.к. вектор отсортирован), положив данные в possibilities
                    number_of_inclidings = 1;     // обновляем счетчик вхождений, теперь он считает вхождений числа nums[count]
                }
            }
            possibilities.push_back(std::make_pair(nums[nums_len - 1], number_of_inclidings));    // кладем данные, оставшиеся после того, как весь вектор nums уже пробежали
            std::vector<int> subset;             // вектор, в котором будем хранить текущее подмножество(то, что уже сформировали)
            BackTrack(subset, possibilities, 0, answers);     // Запускаем функцию поиска всех подмножетсв
        }
        return answers;
    }

private:
    void BackTrack(std::vector<int>& subset, std::vector<std::pair<int, int>>& possibilities,     // функция принимает subset - текущее подмножество, possibilities - варианты продолжения в формате <число, кол-во оставшихся вхождений>
        int max_number_pos, std::vector<std::vector<int>>& answers) {       // max_number_pos - позиция максимального из уже использованных чисел в отсортированном possibilities и answers - вектор, куда кладем все полученные подмножества
                                                                            // max_number_pos используется, чтобы не брать в подмножество одни и те же числа в разном порядке - берем числа от меньшего к большему.        
        answers.push_back(subset);                                          // кладем текущее подмножество в список ответов
        if (subset.size() != nums_len) {                                    // если длина подмножества не достигла своего максимально допустимого размера
            for (int variant = max_number_pos; variant < possibilities.size(); ++variant) {     // пробегаемся по списку кандидатов на следующую позицию начиная с позиции max_number_pos
                if (possibilities[variant].second > 0) {                           // если не все экземпляры рассматриваемого числа уже вовлечены в подмножетсво
                    possibilities[variant].second -= 1;                            // уменьшаем кол-во вхождений этого числа в ещё не рассмотренное окончание подмножетсва
                    subset.push_back(possibilities[variant].first);           // ставим текущее число на рассматриваемую позицию
                    BackTrack(subset, possibilities, variant, answers);       // рекурсивно запускаемся, но теперь считаем рассмотренную позицию пройденным этапом
                    subset.pop_back();                                        // убираем текущее число с рассматриваемой позиции
                    possibilities[variant].second += 1;                            // возвращаем кол-во вхождений числа на прежний уровень
                }
            }
        }
    }
    int nums_len;     // храним длину исходного массива. Так удобно следить за тем, чтобы subsets не превысила своего максимального размера. Проще сделать эту величину отдельно приватной, чем таскать её за собой в BackTrack 
};


//тестовая часть
int main()
{
    std::vector<int> nums;
    int n, a;
    Solution S;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        nums.push_back(a);
    }
    std::vector<std::vector<int>> answer = S.subsetsWithDup(nums);
    for (int i = 0; i < answer.size(); ++i) {
        for (int j = 0; j < answer[i].size(); ++j)
            std::cout << answer[i][j] << ' ';
        std::cout << '\n';
    }
}


