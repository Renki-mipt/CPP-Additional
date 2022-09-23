// First_Actions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <map>

struct Operation //struct for saving the information about one buy or sell operation
{
    int id_operation_;
    std::string buy_sell_;
    std::string action_;
    int number_actions_;
    int price_for_one_;
    int next_buy_index_;
    Operation() {};
    Operation(int id_operation, std::string buy_sell, std::string action,
        int number_actions, int price_for_one, int next_buy_index) {
        id_operation_ = id_operation;
        buy_sell_ = buy_sell;
        action_ = action;
        number_actions_ = number_actions;
        price_for_one_ = price_for_one;
        next_buy_index_ = next_buy_index;
    }
};


struct Resale //struct for saving the result of deal
{
    std::string action_;
    int number_actions_;
    int openning_price_;
    int closing_price_;
    int profit_;
    std::string short_long_;
    int id_openning_operation_;
    int id_closing_operation_;
    Resale() {};
    Resale(std::string action, int number_actions, int openning_price, int closing_price,
        int profit, std::string short_long, int id_openning_operation, int id_closing_operation) {
        action_ = action;
        number_actions_ = number_actions;
        openning_price_ = openning_price;
        closing_price_ = closing_price;
        profit_ = profit;
        short_long_ = short_long;
        id_openning_operation_ = id_openning_operation;
        id_closing_operation_ = id_closing_operation;
    }
};

//the function for processing all the deals connected with the current selling operation
void sell_actions(std::vector<Operation> &operations, std::vector<Resale> &answer, int to_be_sold_next,
    int vector_id, std::map<std::string, int>& action_name) {
    while (to_be_sold_next != -1 &&
        operations[to_be_sold_next].number_actions_ <= operations[vector_id].number_actions_) {
        int profit = (operations[vector_id].price_for_one_ - operations[to_be_sold_next].price_for_one_) *
            operations[to_be_sold_next].number_actions_;
        answer.push_back(Resale(operations[vector_id].action_,
            operations[to_be_sold_next].number_actions_, operations[to_be_sold_next].price_for_one_,
            operations[vector_id].price_for_one_, profit, "-",
            operations[to_be_sold_next].id_operation_, operations[vector_id].id_operation_));
        operations[vector_id].number_actions_ -= operations[to_be_sold_next].number_actions_;
        to_be_sold_next = operations[to_be_sold_next].next_buy_index_;
    }
    action_name.erase(operations[vector_id].action_);
    if (to_be_sold_next == -1)
    {
        if (operations[vector_id].number_actions_ != 0)
        {
            answer.push_back(Resale(operations[vector_id].action_,
                operations[vector_id].number_actions_, operations[vector_id].price_for_one_,
                -1, -1, "-", operations[vector_id].id_operation_, -1));
        }
    }
    else {
        if (operations[vector_id].number_actions_ > 0) {
            int profit = (operations[vector_id].price_for_one_ - operations[to_be_sold_next].price_for_one_) *
                operations[vector_id].number_actions_;
            answer.push_back(Resale(operations[vector_id].action_,
                operations[vector_id].number_actions_, operations[to_be_sold_next].price_for_one_,
                operations[vector_id].price_for_one_, profit, "-",
                operations[to_be_sold_next].id_operation_, operations[vector_id].id_operation_));
            operations[to_be_sold_next].number_actions_ -= operations[vector_id].number_actions_;
        }
        action_name.insert(std::make_pair(operations[vector_id].action_,
            to_be_sold_next));
    }
}

void get_answer_for_first_action_sell(std::vector<Operation>& operations, std::vector<Resale>& answer,
    std::string& first_or_last_action_sell) {
    std::map<std::string, int> action_name; //here we will save the next buy operation in the queue for every type of action
    int current_operation = -1;
    int to_be_sold_next = -1;
    // we will sort out all the operations and handle them
    for (int vector_id = 0; vector_id < operations.size(); ++vector_id) {
        if (operations[vector_id].buy_sell_ == "buy") {
            std::map<std::string, int>::iterator it = action_name.find(operations[vector_id].action_);
            if (it == action_name.end()) {
                action_name.insert(std::make_pair(operations[vector_id].action_, vector_id));
            }
            else {
                if (first_or_last_action_sell == "first") {
                    operations[it->second].next_buy_index_ = vector_id;
                }
                if (first_or_last_action_sell == "last") {
                    operations[vector_id].next_buy_index_ = it->second;
                    action_name.erase(it);
                    action_name.insert(std::make_pair(operations[vector_id].action_,
                        vector_id));           
                }
            }
        }
        if (operations[vector_id].buy_sell_ == "sell") {
            std::map<std::string, int>::iterator it = action_name.find(operations[vector_id].action_);
            if (it == action_name.end()) { 
                answer.push_back(Resale(operations[vector_id].action_, 
                    operations[vector_id].number_actions_, operations[vector_id].price_for_one_, -1,
                     -1, "-", operations[vector_id].id_operation_, -1));
            }
            else {
                sell_actions(operations, answer, it->second, vector_id, action_name);
            }
        }
    }
    std::map<std::string, int>::iterator it = action_name.begin();
    //now we should all the buy operations remaining buy operations to the list of unclosed deals
    while (it != action_name.end()) {
        answer.push_back(Resale(it->first, operations[it->second].number_actions_, 
            operations[it->second].price_for_one_, -1, -1, "-", operations[it->second].id_operation_, -1));
        it++;
    }
}

int main()
{
    std::ifstream in; 
    
    in.open("test.txt");
    std::string first_or_last_action_sell;
    int number_of_opertions = 0;
    int number_of_tests;
    std::vector<Resale> answer;
    std::vector<Operation> operations;
    int id_operation = -1;
    std::string buy_sell = "";
    std::string action = "";
    int number_actions_ = 0;
    int price_for_one_ = 0;

    in >> number_of_tests;
    
    for (int test_number = 0; test_number < number_of_tests; test_number++) {
        in >> first_or_last_action_sell >> number_of_opertions;
        for (int operation_count = 0; operation_count < number_of_opertions; operation_count++) {
            in >> id_operation >> buy_sell >> action >> number_actions_ >> price_for_one_;
            operations.push_back(Operation(id_operation, buy_sell, action,
                number_actions_, price_for_one_, -1));
            
        }
        get_answer_for_first_action_sell(operations, answer, first_or_last_action_sell);
        for (Resale resale : answer) {
            if (resale.id_closing_operation_ != -1) {
                std::cout << resale.action_ << ' ' << resale.number_actions_ << ' ' << resale.openning_price_ <<
                    ' ' << resale.closing_price_ << ' ' << resale.profit_ << ' ' <<
                    resale.id_openning_operation_ << ' ' << resale.id_closing_operation_ << '\n';
            }
            else {
                std::cout << resale.action_ << ' ' << resale.number_actions_ << ' ' << resale.openning_price_ <<
                    ' ' << "-" << ' ' << "-" << ' ' << resale.id_openning_operation_ << '\n';
            }
        }
        operations.resize(0);
        answer.resize(0);
        std::cout << '\n';
    }
    fclose(stdin);
    return 0;
}


