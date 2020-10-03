#include <iostream>
#include <thread>

void sayHello() { std::cout<<"Hello World"<<std::endl; }

// g++ -o bin/exo1 src/exo1.cpp --std=c++11 -lpthread
int main()
{
	std::thread t1(sayHello);
	std::thread t2(sayHello);
	
	t1.join();
	t2.join();

	return 0;
}
