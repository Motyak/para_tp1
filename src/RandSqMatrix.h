#ifndef RAND_SQ_MATRIX_H
#define RAND_SQ_MATRIX_H

#include <iostream>
#include <thread>

class Strategy;

class RandSqMatrix
{
	int dim;
    float** randomContent;
    Strategy* strategy;

  public:
    RandSqMatrix(const int& dim);
    ~RandSqMatrix();
	int getDim() const;
    void setStrategy(Strategy* strategy);
    float* operator[](const int& i) const;
    friend std::ostream& operator<<(std::ostream& os, const RandSqMatrix& m);
    RandSqMatrix operator*(const RandSqMatrix& m) const;

};

class Strategy
{
	
  public:
	// virtual RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const = 0;
	virtual RandSqMatrix multiply(RandSqMatrix m1, RandSqMatrix m2) = 0;
};

class Sequentially : public Strategy
{

  public:
	// RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const override;
	RandSqMatrix multiply(RandSqMatrix m1, RandSqMatrix m2);
};

class ByValue : public Strategy
{
	// void callbackFn(RandSqMatrix& res, const RandSqMatrix& m1, const RandSqMatrix& m2, int i, int j);
	void callbackFn(RandSqMatrix& res, RandSqMatrix m1, RandSqMatrix m2, int i, int j);

  public:
	// RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const override;
	RandSqMatrix multiply(RandSqMatrix m1, RandSqMatrix m2) override;
};

class ByBlocks : public Strategy
{
	void callbackFn(RandSqMatrix& res, RandSqMatrix m1, RandSqMatrix m2, int i);
	
  public:
	// RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const override;
	RandSqMatrix multiply(RandSqMatrix m1, RandSqMatrix m2) override;
};

#endif