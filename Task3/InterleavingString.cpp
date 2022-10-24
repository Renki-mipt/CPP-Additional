#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3) {     
        if (s1.size() + s2.size() != s3.size()) {                           // этот костыль в дальнейшем помогает не думать о возможном несоответствии длин строк в дальнейшем
            return false;                                                   // 
        }
        std::vector<bool> s1_positions_now(s1.size() + 1, false);           // вектор, в котором true стоят на позициях, на которые может заканчиваться вклад строки s1 для конкретной длины префикса строки s3
        std::vector<bool> s1_positions_next(s1.size() + 1, false);          // вектор, в котором true стоят на позициях, на которые может заканчиваться вклад строки s1 для длины префикса строки s3 на 1 большей, чем фиксируется в векторе s1_positions_now
        s1_positions_now[0] = true;                                         // изначально(для нулевой длины строки s3) вклад строки s1 может быть только нулевой
        for (int s3_position = 0; s3_position < s3.size(); ++s3_position) {     // пробегаемся по всем позициям строки s3
            bool have_continuing_variants = false;                              // переменная хранит true, если есть хотя бы один вариант склеить рассматриваемый префикс s3(заканчивающийся на рассматриваемый символ) из строк s1 и s2. 
                                                                                // Это чтобы отсекать на ранней стадии очевидные случаи, когда s3 не может быть склеена из s1 и s2 
            for (int s1_position = 0; s1_position <= s1.size(); ++s1_position) {     // пробегаемся по всем позициям s1
                if (s1_positions_now[s1_position]) {                                 // смотрим, существует ли префикс s1, на который мог заканчиваться вклад строки s1 для предыдущего(на 1 меньшего) префикса s3
                    if (s1_position < s1.size() && s3[s3_position] == s1[s1_position]) {     // если префикс s3 можно продолжить символом из s1
                        s1_positions_next[s1_position + 1] = true;                           // отметим в векторе s1_positions_next соответствующий вариант продолжения(позиция символа при этом увеличивается на 1)
                        have_continuing_variants = true;                                     // хотя бы один вариант склеить рассматриваемый префикс s3 существует
                    }
                    if (s3_position - s1_position < s2.size() && s3[s3_position] == s2[s3_position - s1_position]) {     // если префикс s3 можно продолжить символом из s2
                        s1_positions_next[s1_position] = true;                               // отметим в векторе s1_positions_next соответствующий вариант продолжения(позиция символа не увеличивается, так как использовался символ из s2)
                        have_continuing_variants = true;                                     // хотя бы один вариант склеить рассматриваемый префикс s3 существует
                    }
                }
            }
            if (!have_continuing_variants) {     // если префикс не получилось склеить из префиксов s1 и s2, значит и всю строку s3 склеить не получится
                return false;                    //
            }
            for (int s1_position = 0; s1_position <= s1.size(); ++s1_position) {     // 
                s1_positions_now[s1_position] = s1_positions_next[s1_position];      // переносим результат вектора s1_positions_next в вектор s1_positions_now перед началом следующей итерации цикла по позиции в s3
                s1_positions_next[s1_position] = false;                              // очищаем вектор s1_positions_next
            }
        }
        return true;     // если даже для префикса s3, состоящего из всей строки s3, нашелся вариант чередования, значит возвращаем успех
    }
};

/*int main()
{
    Solution S;
    std::string s1 = "a";
    std::string s2 = "b";
    std::string s3 = "ab";
    //std::string s1 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa";
    //std::string s2 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab";
    //std::string s3 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab";
    std::cout << S.isInterleave(s1, s2, s3);
}*/

