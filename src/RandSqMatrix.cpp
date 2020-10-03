#include "RandSqMatrix.h"

#include <random>   //std::random_device

RandSqMatrix::RandSqMatrix(const int& dim)
{
    std::random_device random;
    this->dim = dim;
    this->randomContent = new float*[dim];
    for(int i = 0 ; i < dim ; ++i)
    {
        this->randomContent[i] = new float[dim];
        for(int j = 0 ; j < dim ; ++j)
            this->randomContent[i][j] = random() % 100;
    }

    this->strategy = new Sequentially();
}

RandSqMatrix::~RandSqMatrix()
{
    for(int i = 0 ; i < this->dim ; ++i)
        delete(this->randomContent[i]);
    delete(this->randomContent);
    delete(this->strategy);
}

int RandSqMatrix::getDim() const
{
    return this->dim;
}

void RandSqMatrix::setStrategy(Strategy* strategy)
{
    delete(this->strategy);
    this->strategy = strategy;
}

float* RandSqMatrix::operator[](const int& i) const
{
    return this->randomContent[i];
}

std::ostream& operator<<(std::ostream& os, const RandSqMatrix& m)
{
    for(int i = 0 ; i < m.dim ; ++i)
    {
        for(int j = 0 ; j < m.dim ; ++j)
            os<<m[i][j]<<"\t";
        os<<std::endl;
    }
    return os;
}

RandSqMatrix RandSqMatrix::operator*(const RandSqMatrix& m) const
{
    return this->strategy->multiply(*this, m);
}

// RandSqMatrix Sequentially::multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const
RandSqMatrix Sequentially::multiply(RandSqMatrix m1, RandSqMatrix m2)
{
    int dim = m1.getDim();
    RandSqMatrix res(dim);
    for(int i = 0 ; i < dim ; ++i)
        for(int j = 0 ; j < dim ; ++j)
            for(int k = 0 ; k < dim ; ++k)
                res[i][j] += m1[i][k] * m2[k][j];
    
    return res;
}

// void ByValue::callbackFn(RandSqMatrix& res, const RandSqMatrix& m1, const RandSqMatrix& m2, int i, int j)
void ByValue::callbackFn(RandSqMatrix& res, RandSqMatrix m1, RandSqMatrix m2, int i, int j)
{
    for(int k = 0 ; k < m1.getDim() ; ++k)
        res[i][j] += m1[i][k] * m2[k][j];
}

// RandSqMatrix ByValue::multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const
RandSqMatrix ByValue::multiply(RandSqMatrix m1, RandSqMatrix m2)
{
    int dim = m1.getDim();
    RandSqMatrix res(dim);
    std::thread th[dim][dim];

    for(int i = 0 ; i < dim ; ++i)
        for(int j = 0 ; j < dim ; ++j)
            th[i][j] = std::thread(&ByValue::callbackFn, this, std::ref(res), m1, m2, i, j);

    for(int i = 0 ; i < dim ; ++i)
        for(int j = 0 ; j < dim ; ++j)
            th[i][j].join();
}

void ByBlocks::callbackFn(RandSqMatrix& res, RandSqMatrix m1, RandSqMatrix m2, int i)
{
    for(int j = 0 ; j < m1.getDim() ; ++j) 
        for(int k = 0 ; k < m1.getDim() ; ++k) 
            res[i][j] += m1[i][k] * m2[k][j];
}

// RandSqMatrix ByBlocks::multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const
RandSqMatrix ByBlocks::multiply(RandSqMatrix m1, RandSqMatrix m2)
{
    int dim = m1.getDim();
    RandSqMatrix res(dim);
    std::thread th[dim];

    for(int i = 0 ; i < dim ; ++i)
            th[i] = std::thread(&ByBlocks::callbackFn, this, std::ref(res), m1, m2, i);

    for(int i = 0; i < dim ; ++i)
            th[i].join();

}