#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "my_vector.h"


template <typename T, typename G> 
bool Test (const std::vector<T>&, const std::vector<G>&, const std::string&);


template <typename T>
void all_tests (const std::string&);

template <typename T, typename G>
bool simple_test (const T&, const G&, const std::string& messeg);

int main()
{
	all_tests<int>("INT");
//	all_tests<double>("DOUBLE");
 //	all_tests<char>("CHAR");
//	all_tests<float>("FLOAT");
//	all_tests<bool>("BOOL");
//        all_tests<std::map<int, int>>("MAP");
 //       all_tests<std::string>("string");
  //      all_tests<std::vector<int>>("vector");
}



template <typename T>
void all_tests (const std::string& type_str)
{

	std::vector<T> refer_v;
	std::vector<T> test_v;
	
	mcr::MyVector<T> test_0;
	mcr::MyVector<T> test_1;
	
	size_t size_i = 0;
	
	std::cout << "\n\tALL_TESTS " << type_str <<" TYPE\n";

///Тест функции empty
	simple_test<bool, bool> (test_0.empty(), true, "test: empty");
	
///Тест функции push и top

	for  (size_t i = 0; i < 100; i++) {
		test_0.push_back(T());
		refer_v.push_back(T());
		test_v.push_back(test_0.back());
		size_i = i;
	}
	Test<T, T> (test_v, refer_v, "test: push & top");

	refer_v.clear();
	test_v.clear();

        
        std::cout << &(*test_0.end())  << "\t" << &(*(test_0.end() - 10)) << "\t" << &(*test_0.begin())<< std::endl;
        test_0.insert((test_0.end() - 10), 5, -1);
        test_0.show_v();

///Тест функции size
	simple_test<size_t, size_t> (test_0.size(), size_i + 1, "test: size");
	
///Тест функции swap и take_any

	test_1 = (mcr::MyVector<T>(test_0));

        size_t i = 0;
	for (auto v_t : test_0) {
		test_v.push_back(v_t);
		refer_v.push_back(test_1.at(i++));
	}
 	Test<T, T> (test_v, refer_v, "test: swap & take_any");

	std::cout << "\tALL_TESTS " << type_str <<" TYPE END!\n\n";
}

template <typename T, typename G>
bool Test (const std::vector<T>& test_v, const std::vector<G>& refer_v, const std::string& messeg)
{

	bool err_f = true;

	std::cout << messeg << "...";
	
	for (size_t it = 0; it < refer_v.size(); ++it) {
		if (test_v[it] != refer_v[it]){
			err_f = false;
			break;
		}
	}
		
	if (!err_f) 
		std::cout << "TEST FAILED!!!\n";
	else
		std::cout << "TEST PASSED!!!" << std::endl;

	return err_f;
}

template <typename T, typename G>
bool simple_test (const T& test_v, const G& refer_v, const std::string& messeg)
{
	bool err_f = true;

	std::cout << messeg << "...";

	if (test_v != refer_v)
		err_f = false;

	if (!err_f) 
		std::cout << "TEST FAILED!!!\n";
	else
		std::cout << "TEST PASSED!!!" << std::endl;

	return err_f;
}
