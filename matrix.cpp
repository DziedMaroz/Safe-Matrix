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
	 for (int i=0;i<n;i++)
	     for (int j=0;j<n;j++)
		if (i==j) (*this)[i][j]=1;
		else (*this)[i][j]=0;
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

const Matrix::Row Matrix::operator [](long i) const
{
	BadFirstIndex err;
	if (i>=rows_) throw (err);
	Matrix::Row tmp  (this->columns_,this->p_+(i*this->columns_));
	return tmp;
}


const double& Matrix::Row::operator [](long j) const
{
	BadSecondIndex err;
	if (j>=this->columns_) throw (err);
	return p_[j];
}

Matrix::Row& Matrix::operator [] (long i)
{
    BadFirstIndex err;
    if (i>=rows_) throw (err);
    Matrix::Row tmp  (this->columns_,this->p_+(i*this->columns_));
    return tmp;
}

double& Matrix::Row::operator [] (long j)
{
    BadSecondIndex err;
    if (j>=this->columns_) throw (err);
    return p_[j];
}

Matrix& Matrix::toTriangleMatrix ()
{
    Matrix tmp = *this;
    int n=this->columns_<this->rows_?this->columns_:this->rows_;
    for (int i=0;i<n;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            double t=tmp[i][0];
            for (int k=0;k<n;k++)
            {
                tmp[i][k]*=tmp[j][0];
                tmp[j][k]*=t;
                tmp[j][k]-=tmp[i][k];
            }
        }
    }
    return tmp;
}
