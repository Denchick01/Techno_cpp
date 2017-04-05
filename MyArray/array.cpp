#include <iostream>
#include <string>
#include <vector>
#include "my_array.h"
#include "my_tests.hpp"
#include <cstdlib>
#include <stdexcept>
#include <map>

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
    mcr::MyArray<T, 10> test_vector_1 = {1, 2, 3, 4, 5};

    std::vector<T> reference_vector_1 = {1 , 2, 3, 4, 5, 0, 0, 0, 0, 0};
    std::vector<T> reference_vector_2;

///Проверка  агрегатного инициализатора
    for (T value: test_vector_1) {
        reference_vector_2.push_back(value);
    }

     Test (reference_vector_2, reference_vector_1, "Проверка  агрегатного инициализатора");

    std::cout << "END test for type: " << type_str << "\n";
}

