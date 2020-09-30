#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

const int BARRAGE_REMPLI = 5;

// faire monter l'eau
void up(int* value, std::mutex* m, std::condition_variable* cond_var)
{
    // std::lock_guard<std::mutex> lcm(*m);
    while(true)
    {
        std::unique_lock<std::mutex> lck(*m);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));//
        *value += 1;
        std::cout<<"quantité d'eau = "<<*value<<std::endl;
        cond_var->notify_one();
        cond_var->wait(lck, [value]{return *value == BARRAGE_REMPLI;});
    }
}

// faire baisser l'eau
void down(int* value, std::mutex* m, std::condition_variable* cond_var)
{
    while(true)
    {
        std::unique_lock<std::mutex> lck(*m);
        cond_var->wait(lck, [value]{return *value == BARRAGE_REMPLI;});
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));//
        *value = 0;
        std::cout<<"quantité d'eau = "<<*value<<std::endl;
        cond_var->notify_one();
    }
}

// g++ -o bin/exo5 src/exo5.cpp --std=c++11 -lpthread
int main()
{
    int* value = new int(0);
    std::mutex* m = new std::mutex();
    std::condition_variable* cond_var = new std::condition_variable();

    std::thread t1(up, value, m, cond_var);
    std::thread t2(down, value, m, cond_var);

    delete(value);
    delete(m);
    delete(cond_var);

	return 0;
}