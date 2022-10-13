// Parentheses.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        parenthesis_len = n;                                   // храним длину строимой последовательности
        int open_number = 0;                                   // этот параметр считает кол-во уже использованных открытых скобок
        int close_number = 0;                                  // этот параметр считает кол-во уже использованных закрытых скобок
        std::string parenthesis(2 * parenthesis_len, ' ');     // вектор, в котором будем хранить текущую скобочную поледовательность(то, что уже сформировали)
        std::vector<std::string> answers;                      // вектор, в который будет записан итоговый ответ
        if (parenthesis_len > 0) {                             // необходимо это проверить, чтобы для n = 0 ответ был пустой, а не содержал пустую строку
            BackTrack(parenthesis, open_number, close_number, answers);     // Запускаем функцию поиска всех последовательностей
        }
        return answers;      
    }

private:
    void BackTrack(std::string& parenthesis, int open_number, int close_number, std::vector<std::string>& answers) {
        int current_pos = open_number + close_number;     // рассматриваемая позиция
        if (current_pos == parenthesis_len * 2) {         // если последовательность достигла нужной длины
            answers.push_back(parenthesis);               // записываем полученную последовательность в список ответов
        }
        else {          
            if (open_number < parenthesis_len) {          // если ещё есть места для открытых скобок   
                parenthesis[current_pos] = '(';           // ставим открытую скобку на рассматриваемую позицию
                BackTrack(parenthesis, open_number + 1, close_number, answers);     // запуск рассмотрения следующей позиции в последовательности
            }
            if (open_number > close_number) {             // если есть возможность для закртой скобки(должны быть незакрытые открытые скобки)
                parenthesis[current_pos] = ')';           // ставим открытую скобку на рассматриваемую позицию
                BackTrack(parenthesis, open_number, close_number + 1, answers);     // запуск рассмотрения следующей позиции в последовательности
            }
        }
    }

    int parenthesis_len;     // удобно отдельно хранить необходимую длину последовательности(вернее её половину), чтобы не таскать её в BackTrack
};

//тестовая часть
/*int main()
{
    std::vector<int> nums;
    int n, a;
    Solution S;
    std::cin >> n;

    std::vector<std::string> answer = S.generateParenthesis(n);
    for (int i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << '\n';
    }
}*/