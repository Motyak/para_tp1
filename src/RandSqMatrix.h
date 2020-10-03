#ifndef RAND_SQ_MATRIX_H
#define RAND_SQ_MATRIX_H

#include <iostream>

class Strategy;

class RandSqMatrix
{
	int dim;
    float** randomContent;
    Strategy* strategy;

  public:
    RandSqMatrix(const int& dim);
	~RandSqMatrix();
	void setStrategy(Strategy* strategy);
    float* operator[](const int& i) const;
	// std::ostream& operator<<(std::ostream& os, const RandSqMatrix& m);
	friend std::ostream& operator<<(std::ostream& os, const RandSqMatrix& m);
    RandSqMatrix operator*(const RandSqMatrix& m) const;

};



class Strategy
{
	
  public:
	virtual RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const = 0;
};

class Sequentially : public Strategy
{

  public:
	RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const;
};

class ByValue : public Strategy
{
	
  public:
	RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const;
};

class ByBlocks : public Strategy
{
	
  public:
	RandSqMatrix multiply(const RandSqMatrix& m1, const RandSqMatrix& m2) const;
};

#endif