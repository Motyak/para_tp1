#include <iostream>
#include <thread>

#include "RandSqMatrix.h"

float* prodSeq(float* m1, float* m2, int w, int h) 
// float** prodSeq(float** a, float** b, int dim)
{ 
    // float** res = new float*[dim];
    // for(int i = 0 ; i < dim ; ++i)
    //     res[i] = new float[dim];

    // for(int i = 0 ; i < dim ; ++i)
    // {
    //     for(int n = 0 ; n < dim ; ++n)
    //     {
    //         float tmp = 0.f;
    //         for(int j = 0 ; j < dim ; ++j)
    //             tmp += a[i][j] * b[j][i];
    //         res[i][n] = tmp;
    //     }
    // }

    // return res;

    float* m1xm2 = new float[w*h];

    for(int r = 0 ; r < h ; ++r)
    {
        for(int c = 0 ; c < w ; ++c)
        {
            m1xm2[r*w+c] = 0;
            for(int k = 0 ; k < w ; ++k)
                m1xm2[r*w+c] += m1[r*w+h] * m2[k*w+c];
        }
    }
    return m1xm2;
}

// g++ -o bin/exo2 src/RandSqMatrix.cpp src/exo2.cpp --std=c++11 -lpthread
int main()
{
    const int DIM = 3;

    RandSqMatrix m(DIM);

    std::cout<<m;

	return 0;
}
