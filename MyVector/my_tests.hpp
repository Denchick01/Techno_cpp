#include <iostream>
#include <string>
#include <vector>
#include <chrono>


template <typename T, typename G> 
bool Test (const std::vector<T>&, const std::vector<G>&, const std::string&);


template <typename T>
void all_tests (const std::string&);

template <typename T, typename G>
bool simple_test (const T&, const G&, const std::string& messeg);


template <typename T, typename G>
bool Test (const std::vector<T>& test_v, const std::vector<G>& refer_v, const std::string& messeg)
{
    bool err_f = true;
    size_t num_it = 0;
    size_t time;
    std::chrono::system_clock::time_point m_log_time_point = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point current_time;   
  
    std::cout << messeg << "\ntest...";
	
    try {        

        for (num_it = 0; num_it < refer_v.size(); ++num_it) {
            if (test_v[num_it] != refer_v[num_it]){
                err_f = false;
                break;
            }
        }  
        current_time  =  std::chrono::system_clock::now();
    } catch (...) { 
        err_f = false;
        std::cout << "not ok\n";
        std::cout << "Unexpected interruption on iteration: " << num_it << "\n";
        return err_f;
    }
            	
    if (!err_f) {
        std::cout << "not ok\n";
        std::cout << "Error on iteration: " << num_it << "\n";
    }
    else {
        time = std::chrono::duration_cast<std::chrono::seconds>(current_time - m_log_time_point).count();
        std::cout << "ok" << std::endl;
        std::cout << "number of iterations: " << num_it << " time: " << time/60.0 << "\n";
    }

    return err_f;
}

template <typename T, typename G>
bool simple_test (const T& test_v, const G& refer_v, const std::string& messeg)
{
    bool err_f = true;
    size_t time;
    std::chrono::system_clock::time_point m_log_time_point = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point current_time;   
  
    std::cout << messeg << "\ntest...";
	
    try { 
        if (test_v != refer_v)
		err_f = false;

        current_time  =  std::chrono::system_clock::now();
    } catch (...) { 
        err_f = false;
        std::cout << "not ok\n";
        std::cout << "Unexpected interruption" << "\n";
        return err_f;
    }
            	
    if (!err_f) {
        std::cout << "not ok\n";
    }
    else {
        time = std::chrono::duration_cast<std::chrono::seconds>(current_time - m_log_time_point).count();
        std::cout << "ok" << std::endl;
        std::cout << "time: " << time/60.0 << "\n";
    }

    return err_f;
}













