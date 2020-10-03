#include <iostream>

#include "RandSqMatrix.h"

// g++ -o bin/exo2 src/RandSqMatrix.cpp src/exo2.cpp --std=c++11 -lpthread
int main()
{
    const int DIM = 2;

    RandSqMatrix m1(DIM);
    RandSqMatrix m2(DIM);

    std::cout<<m1<<std::endl<<m2<<std::endl;

    m1.setStrategy(new Sequentially());
    // m1.setStrategy(new ByValue());
    // m1.setStrategy(new ByBlocks());

    RandSqMatrix res = m1 * m2;

    std::cout<<res;

	return 0;
}
