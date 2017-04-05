#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "my_macro.h"
#include "my_stack.h"
#include "my_tests.hpp"
#include <cstdlib>
#include <stdexcept>


int main()
{
	all_tests<int>("INT");
	all_tests<double>("DOUBLE");
 	all_tests<char>("CHAR");
	all_tests<float>("FLOAT");
//	all_tests<bool>("BOOL");
//        all_tests<std::map<int, int>>("MAP");
//        all_tests<std::string>("STRING");
//        all_tests<std::vector<int>>("VECTOR");
}


///Проверка встроенных типов
template <typename T>
void all_tests (const std::string& type_str)
{
    std::cout << "START test for type: " << type_str << "\n";
    mcr::MyStack<T> test_stack_1 (10 , 1);

    std::vector<T> reference_stack_1 (10, 1);
    std::vector<T> reference_stack_2;

///Проверка функций empty, pop и top 
    while(!test_stack_1.empty()) {
        reference_stack_2.push_back(test_stack_1.top());
        test_stack_1.pop();
    }

    Test (reference_stack_2, reference_stack_1, "Проверка функций empty, pop и top");

///Проверка функций push, size 
    reference_stack_2.clear();
    reference_stack_1.clear();
    size_t num_iter = 100;
    for (size_t it = 0; it < num_iter; ++it) {
       int r_value = rand() % 100;
       test_stack_1.push(r_value);
       reference_stack_1.push_back(r_value);
       reference_stack_2.push_back(test_stack_1.top());
    }

     Test (reference_stack_2, reference_stack_1, "Проверка функций push");
     simple_test(num_iter, test_stack_1.size(), "Проверка функций size");

///Проверка функции swap

    mcr::MyStack<T> test_stack_2;
    test_stack_2.swap(test_stack_1);

    while(!test_stack_2.empty()) {
        reference_stack_2.push_back(test_stack_2.top());
        test_stack_2.pop();
    }

    Test (reference_stack_2, reference_stack_1, "Проверка функций swap");


}
