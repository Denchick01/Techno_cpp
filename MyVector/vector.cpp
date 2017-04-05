#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "my_macro.h"
#include "my_vector.h"
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
    mcr::MyVector<T> test_vector_1 (10 , 1);

    std::vector<T> reference_vector_1 = {1 , 2, 3, 4, 5};
    std::vector<T> reference_vector_2;
   
    test_vector_1.insert(test_vector_1.begin(), reference_vector_1.begin(), reference_vector_1.end());
    reference_vector_1.insert(reference_vector_1.end(), 10, 1); 
///Проверка freach
    for (T value : test_vector_1) {
        reference_vector_2.push_back(value);
    }

///Проверка конструктора со списком инициализации 
    Test (reference_vector_2, reference_vector_1, "Проверка конструктора со списком инициализации + insert");

    mcr::MyVector<T> test_vector_2(test_vector_1);

    for (T value : test_vector_2) {
        reference_vector_2.push_back(value);
    }
///Проверка конструктора копирования 
    Test (reference_vector_2, reference_vector_1, "Проверка конструктора копирования");


///Проверка функций push_back , clear и back
    reference_vector_1.clear();
    test_vector_1.clear();
    reference_vector_2.clear();

    for (size_t it = 0; it < 10000; ++it) {
        int r_temp = rand() % 100;
        reference_vector_1.push_back(r_temp);   
        test_vector_1.push_back(r_temp);
        reference_vector_2.push_back(test_vector_1.back());
    }
    Test (reference_vector_2, reference_vector_1, "Проверка функций push_back , clear и back");    

///Проверка исключения
    test_vector_2.clear();

    std::cout << "Проверка исключения\n";
    try {
        test_vector_2.pop_back();
    }
    catch (mcr::MyException& e) {
        std::cout << e.what() << "\n";
        std::cout << "test...ok\n";
    }
 
    std::cout << "END test for type: " << type_str << "\n";
}











