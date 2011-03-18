#include "matrix.h"
#include <cstdlib>
Matrix::Matrix()
{
  this->rows_=0;
  this->columns_=0;
  this->p_=NULL;
}

Matrix::Matrix (long m, long n)
{
    this->columns_=n;
    this->rows_=m;
    p_ = new double [columns_*rows_];
}
Matrix::Matrix (const Matrix &m)
{
    this->rows_=m.rows_;
    this->columns_=m.columns_;
    this->p_= new double [columns_*rows_];
    for (int i=0;i<columns_*rows_;i++) this->p_[i]=m.p_[i];
}

Matrix& Matrix::operator = (const Matrix& m)
{
	delete [] p_;
	this->columns_=m.columns_;
	this->rows_=m.rows_;
	p_= new double [columns_*rows_];
	for (int i=0;i<columns_*rows_;i++)
		this->p_[i]=m.p_[i];
	return *this;
}
Matrix& Matrix::operator += (const Matrix& m)
{
	BadDimensions err;

    if (this->rows_!=m.rows_ || this->columns_!=m.columns_) throw (err);
    for (int i=0;i<this->rows_*this->columns_;i++) this->p_[i]+=m.p_[i];
    return *this;
}

Matrix& Matrix::operator -= (const Matrix& m)
{

	BadDimensions err;
    if (this->rows_!=m.rows_ || this->columns_!=m.columns_) throw (err);
    for (int i=0;i<this->rows_*this->columns_;i++) this->p_[i]-=m.p_[i];
    return *this;
}

Matrix& Matrix::operator *= (const double& d)
{
    for (int i=0;i<this->rows_*this->columns_;i++) this->p_[i]*=d;
	return *this;
}


inline Matrix::~Matrix () { delete[] p_;}
void Matrix::makeUnitMatrix (long n)
{
	this->rows_=n;
	this->columns_=n;
	delete [] p_;

	 p_=new double [n*n];
	 int j=0;
	 for (int i=0;i<n*n;i++)
	 {
		if ((i+j)%n==0)
		{
			p_[i]=1;
			j++;
		}
		else p_[0];
	 }
}


Matrix& Matrix::operator *=(const Matrix &m)
{
	BadDimensions err;
	if (this->rows_!=m.columns_) throw (err);
	Matrix tmp (this->rows_,m.columns_);
	for (int i=0;i<this->rows_;i++)
		for (int j=0;j<m.columns_;j++)
			for (int r=0; r<this->columns_;r++)
			{
				double a = m[r][i];
				double b = (*this)[j][r];
				tmp[i][j]= tmp[i][j]+a*b;
			}
	delete[] this->p_;
	*this=tmp;
	return *this;
}

Matrix::Row::Row (long rowN, double *p)
{
	p_=p;
	columns_=rowN;
}

Matrix::Row& Matrix::operator [](long i)
{
	BadFirstIndex err;
	if (i>=rows_) throw (err);
	return Matrix::Row (this->columns_,p_+i*this->columns_);
}


double& Matrix::Row::operator [](long j)
{
	BadSecondIndex err;
	if (j>=this->columns_) throw (err);
	return p_[j];
}