#include <iostream>
#include <thread>

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

// g++ src/exo2.cpp --std=c++11 -lpthread
int main()
{
    float m1[] = { 
        1.f, 2.f, 3.f, 
        4.f, 5.f, 6.f, 
        7.f, 8.f, 9.f
    };
    float m2[] = { 
        2.f, 2.f, 2.f, 
        2.f, 2.f, 2.f, 
        2.f, 2.f, 2.f 
    };

    // float m1[3][3] = { 
    //     {1.f, 2.f, 3.f}, 
    //     {4.f, 5.f, 6.f}, 
    //     {7.f, 8.f, 9.f} 
    // };
    // float m2[3][3] = { 
    //     {2.f, 2.f, 2.f}, 
    //     {2.f, 2.f, 2.f}, 
    //     {2.f, 2.f, 2.f} 
    // };

	float* res = prodSeq(m1, m2, 3, 3);
    // float** res = prodSeq((float**)m1, (float**)m2, 3);

    // affichage resultat
    for(int i = 0 ; i < 3 * 3 ; ++i)
    {
        std::cout << res[i] << "\t";
        if((i+1) % 3 == 0)
            std::cout << std::endl;
    }

    // for(int i = 0 ; i < 3 ; ++i)
    // {
    //     for(int j = 0 ; j < 3 ; ++j)
    //         std::cout << res[i][j] << "\t";
    //     std::cout<<std::endl;
    // }

    delete(res);

	return 0;
}
