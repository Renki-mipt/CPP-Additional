#include <iostream>
#include <vector>

class Solution {
public:
    int trap(std::vector<int>& height) {
        int water_amount = 0;                                        // в этой переменной будем собирать итоговое значение кол-ва воды                             
       std::vector<std::pair<int, int>> stairs;                      // в этом векторе будем хранить "видимые" из текущей позиции  столбы, то есть список тех вершин с координатами их высот, которые видны, если смотреть справа 
                                                                     // налево из конкретной точки. Для примера из условия, если смотреть из самой  правой точки картинки, то в векторе будут лежать: (11, 1), (10, 2), (7, 3).
        for (int column = 0; column < height.size(); ++column) {     // пробегаемся по столбам слева направо
            int prev_height = 0;                                     // храним высоту предыдущего рассмотренного столбца
            int index = stairs.size() - 1;                           // переменная, чтобы пробегаться по видимым столбам в порядке их близости к данной точке(получается также в порядке их высоты, так как высокие столбы загораживают низкие)
            while (index >= 0 && height[column] >= stairs[index].first) {     // пока есть нерассмотренные видимые столбы, высота которых не больше высоты столба в colomn,
                water_amount += (stairs[index].first - prev_height) *         // прибавляем к ответу кол-во воды между рассматриваемыми точками: stairs[index].first - prev_height - высота рассматриваемой полости по вертикали, 
                    (column - stairs[index].second - 1);                      // column - stairs[index].second - 1 - расстояние между точками по горизонтали
                prev_height = stairs[index].first;                            // теперь stairs[index] становится последней из рассмотренных вершин, видимых из точки colomn                     
                --index;                                                      // переходим к следующей(и по порядку, и по высоте) видимой вершине(=столбцу)
            }
            if (index >= 0) {                                                                             // если нашлась видимая из colomn вершина, которая выше неё,
                water_amount += (height[column] - prev_height) * (column - stairs[index].second - 1);     // добавляем к ответу кол-во воды между точками(расстояние по вертикали теперь считается до точки height[column], так как эта вершина нижняя из двух)
            }
            stairs.resize(index + 1);                                                                     // удаляем из списка видимых вершин те, которые теперь будет заслонять вершина colomn
            stairs.push_back(std::make_pair(height[column], column));                                     // добавляем точку colomn в список видимых вершин(её пока ничто не заслоняет, так что её мы точно будем видеть из colomn+1)
        }
        return water_amount;                                                                              // возвращаем ответ
    }
};

/*int main()
{
    Solution S;
    std::vector<int> height = { 4,2,0,3,2,5 };
    std::cout << S.trap(height) << '\n';
    return 0;
}*/
