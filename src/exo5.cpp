#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

const int BARRAGE_REMPLI = 5;

// faire monter l'eau
void up(int& value, std::mutex& m, std::condition_variable& cond_var)
{
    for(int i = 1 ; i <= 5 ; ++i)
    {
        // std::unique_lock<std::mutex> lck(m);
        std::lock_guard<std::mutex> lck(m);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        value += 1;
        std::cout<<"<on fait monter l'eau>"<<std::endl;
        std::cout<<"quantité d'eau = "<<value<<std::endl<<std::endl;
        cond_var.notify_one();
    }
}

// faire baisser l'eau
void down(int& value, std::mutex& m, std::condition_variable& cond_var)
{
    std::unique_lock<std::mutex> lck(m);
    cond_var.wait(lck, [value]{return value == BARRAGE_REMPLI;});
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    value = 0;
    std::cout<<"<on fait descendre l'eau>"<<std::endl;
    std::cout<<"quantité d'eau = "<<value<<std::endl<<std::endl;
}

// g++ -o bin/exo5 src/exo5.cpp --std=c++11 -lpthread
int main()
{
    std::mutex m;
    std::condition_variable cond_var;
    int value = 0;

    std::thread t1(up, std::ref(value), std::ref(m), std::ref(cond_var));
    std::thread t2(down, std::ref(value), std::ref(m), std::ref(cond_var));

    t1.join();
    t2.join();

	return 0;
}
