#ifndef COMPLEX__H
#define COMPLEX__H

#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <exception>

using namespace std;

class Complex
{
		double Re_,Im_;
	public:
		Complex(double real=0,double imag=0);
		Complex(Complex const & z);
		~Complex();
		double GetRe() const;
		double GetIm() const;
		Complex const & operator=(Complex const & c);
		friend Complex const operator+(Complex const & z1,Complex const & z2);
		friend Complex const operator-(Complex const & z1,Complex const & z2);
		friend Complex const operator*(const Complex &,const Complex &);
		friend Complex const operator/(const Complex &,const Complex &);
		Complex & operator*=(Complex const &);
		Complex & operator+=(Complex const &);
		Complex & operator-=(Complex const &);
		Complex & operator/=(Complex const &);
		Complex & Conjugate ();
		Complex Conjugate2()const;
		double Abs_Square() const;
		double Abs() const;
		friend istream & operator >> (istream &, Complex &);
		friend ostream & operator << (ostream &, Complex &);
		void SetRe(double d=0);
		void SetIm(double d=0);

	
};

#endif
