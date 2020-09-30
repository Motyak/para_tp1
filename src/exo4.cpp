#include <iostream>
#include <thread>
#include <mutex>

// affiche tous les nombres impairs de 0 à 1000
void printOddsWithoutMutex()
{
    for(int i = 1 ; i <= 1000 ; i += 2)
        std::cout<<i<<std::endl;
}

// affiche tous les nombres pairs de 0 à 1000
void printEvensWithoutMutex()
{
    for(int i = 0 ; i <= 1000 ; i += 2)
        std::cout<<i<<std::endl;
}

// affiche tous les nombres impairs de 0 à 1000 avec mutex
void printOddsWithMutex(std::mutex* mutexEven, std::mutex* mutexOdd)
{
    for(int i = 1 ; i <= 1000 ; i += 2)
    {
        mutexOdd->lock();
        std::cout<<i<<std::endl;
        mutexEven->unlock();
    }
}

// affiche tous les nombres pairs de 0 à 1000 avec mutex
void printEvensWithMutex(std::mutex* mutexEven, std::mutex* mutexOdd)
{
    for(int i = 0 ; i <= 1000 ; i += 2)
    {
        mutexEven->lock();
        std::cout<<i<<std::endl;
        mutexOdd->unlock();
    }
}

// g++ -o bin/exo4 src/exo4.cpp --std=c++11 -lpthread
int main()
{
    std::mutex* mutexEven = new std::mutex();
    std::mutex* mutexOdd = new std::mutex();
    std::thread t1(printEvensWithMutex, mutexEven, mutexOdd);
    std::thread t2(printOddsWithMutex, mutexEven, mutexOdd);
    // il faut commencer par 0, qui est pair
    mutexOdd->lock();
    t1.join();
    t2.join();

    delete(mutexEven);
    delete(mutexOdd);

	return 0;
}
