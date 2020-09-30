#include <iostream>
#include <thread>

// calcule la somme dans un tableau de n elements
float sumSeq(float* arr, int n)
{
    float res = 0.f;
    for(int i = 0 ; i < n ; ++i)
        res += arr[i];
    return res;
}

// calcule la somme dans un tableau de l'indice 'from' à 'to'
float sumSeq2(float* arr, int from, int to)
{
    float res = 0.f;
    for(int i = from ; i < to ; ++i)
        res += arr[i];
    return res;
}

// calcule la somme dans un tableau de n elements, 
// en utilisant des threads et des variables locales
float sumLoc(float* arr, int n)
{
    int mid = n/2;
    float sum1, sum2;
    std::thread t1([&sum1, arr, mid, n]{sum1 = sumSeq2(arr, 0, mid);});
    std::thread t2([&sum2, arr, mid, n]{sum2 = sumSeq2(arr, mid, n);});
    t1.join();
    t2.join();
    return sum1 + sum2;
}

// calcule la somme dans un tableau de n elements,
// en utilisant des threads et une variable partagée
float* sumPar(float* arr, int n)
{
    int mid = n/2;
    float* sum = new float(0.f);
    std::thread t1([sum, arr, mid, n]{*sum += sumSeq2(arr, 0, mid);});
    std::thread t2([sum, arr, mid, n]{*sum += sumSeq2(arr, mid, n);});
    t1.join();
    t2.join();
    return sum;
}

// g++ -o bin/exo3 src/exo3.cpp --std=c++11 -lpthread
int main()
{
    float arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // std::cout<<"somme :"<<sumSeq(arr, 0, 9)<<std::endl;
    // std::cout<<"somme :"<<sumLoc(arr, 9)<<std::endl;
    std::cout<<"somme :"<<*sumPar(arr, 9)<<std::endl;

	return 0;
}
