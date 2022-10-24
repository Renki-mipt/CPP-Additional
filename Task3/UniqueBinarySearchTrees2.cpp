#include <iostream>
#include <vector>

 /*struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};*/

class Solution {
public:
    std::vector<TreeNode*> generateTrees(int n) {
        return generateTrees_from_number(n, 1);
    }

private :
    std::vector<TreeNode*> generateTrees_from_number(int n, int diapason_begin) {     //функция принимает n - кол-во вершин из которых она должна сделать все возможные деревья и diapason_begin - наименьшее число  из диапазон тех чисел, что должны быть в узлах
        std::vector<TreeNode*> trees;     // сюда будем корни всех получившихся деревьев
        if (n == 0) {                     // база рекурсии: если n = 0, возвращаем вектор с единственным пустым указателем
            trees.push_back(nullptr);     //
        }
        else {
            for (int left_leaves_amount = 0; left_leaves_amount < n; ++left_leaves_amount) {                           // пробегаемся по всем возможным количествам вершин в левом поддереве
                std::vector<TreeNode*> left_trees = generateTrees_from_number(left_leaves_amount, diapason_begin);     // рекурсивно просим нам предоставить список всех возможных левых поддеревьев с данным числом вершин(диапазон чисел задается однозначно)
                std::vector<TreeNode*> right_trees = generateTrees_from_number(n - left_leaves_amount - 1, diapason_begin + 1 + left_leaves_amount);     // рекурсивно просим нам предоставить список всех возможных правых поддеревьев с оставшимся числом вершин
                for (auto left_leaf : left_trees) {                                                                    // пробегаемся по всем возможным левым поддеревьям
                    for (auto right_leaf : right_trees) {                                                              // пробегаемся по всем возможным правым поддеревьям
                        TreeNode* root = new struct TreeNode(diapason_begin + left_leaves_amount, left_leaf, right_leaf);     // создаем новое дерево с рассматриваемыми правым и левым поддеревьями
                        trees.push_back(root);                                                                                // и кладем его в ответ
                    }
                }
            }
        }
        return trees;     // возвращаем что просили
    }
};

/*int main()
{
    Solution S;
    S.generateTrees(3);
}*/
