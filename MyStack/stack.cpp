#include <iostream>
#include <string>
#include <vector>
#include "MyStack.h"


template <typename T, typename G> 
bool Test (const std::vector<T>&, const std::vector<G>&, const std::string&);


template <typename T>
void all_tests (const std::string&);

template <typename T, typename G>
bool simple_test (const T&, const G&, const std::string& messeg);

int main()
{
	all_tests<int>("INT");
	all_tests<double>("DOUBLE");
 	all_tests<char>("CHAR");
	all_tests<float>("FLOAT");
	all_tests<bool>("BOOL");
}



template <typename T>
void all_tests (const std::string& type_str)
{

	std::vector<T> refer_v;
	std::vector<T> test_v;
	
	MyStack<T> test_0;
	MyStack<T> test_1;
	
	size_t size_i = 0;
	
	std::cout << "\n\tALL_TESTS " << type_str <<" TYPE\n";

///Тест функции empty
	simple_test<bool, bool> (test_0.empty(), true, "test: empty");
	
///Тест функции push и top

	for  (size_t i = 0; i < 1000; i++) {
		test_0.push(i);
		refer_v.push_back(i);
		test_v.push_back(test_0.top());
		size_i = i;
	}
	Test<T, T> (test_v, refer_v, "test: push & top");

	refer_v.clear();
	test_v.clear();

///Тест функции size
	simple_test<size_t, size_t> (test_0.size(), size_i + 1, "test: size");
	
///Тест функции swap и take_any

	test_1.swap(test_0);

	for  (size_t i = 0; i < test_0.size(); i++) {
		test_v.push_back(test_0.take_any(i));
		refer_v.push_back(test_1.take_any(i));
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
