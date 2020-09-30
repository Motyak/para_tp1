#include <iostream>
#include <thread>

float[][] prodSeq(float[][] a, float[][] b, int dim) 
{ 
    float res[dim][dim];
    for(int n = 0 ; n < dim ; ++n)
    {
        for(int i = 0 ; i < dim ; ++i)
        {
            float tmp = 0.f;
            for(int j = 0 ; j < dim ; ++j)
            {
                tmp += a[i][j] * b[j][i];
            }
            res[n][i] = tmp;
        }
    }
}

// g++ f.cpp --std=c++11 -lpthread
int main()
{
    float m1[][] = { 
        {1.f, 2.f, 3.f}, 
        {4.f, 5.f, 6.f}, 
        {7.f, 8.f, 9.f} 
    };
    float m2[][] = { 
        {2.f, 2.f, 2.f}, 
        {2.f, 2.f, 2.f}, 
        {2.f, 2.f, 2.f} 
    };

	std::thread t1(sayHello);
	std::thread t2(sayHello);
	
	t1.join();
	t2.join();

	return 0;
}
