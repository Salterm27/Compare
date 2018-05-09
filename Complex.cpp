#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include"Complex.h"
#include <iostream>
#include <string>
#include <cmath>


using namespace std;

//CONSTRUCTORES

Complex::Complex(){
	Re_=0;
	Im_=0;
}

Complex::Complex(double const real,double const imag){
	Re_=real;
	Im_=imag;
}

Complex::Complex(double const real){
	Re_=real;
	Im_=0;
}

Complex::Complex(const Complex & c){
	Re_=c.Re_;
	Im_=c.Im_;
}

Complex const & Complex::operator=(Complex const & c){
	Re_=c.GetRe();
	Im_=c.GetIm();
	return *this;
}

//

double Complex::GetRe()const{
	return Re_;
}

double Complex::GetIm()const{
	return Im_;
}

void Complex::SetRe(double a){
	Re_=a;
}

void Complex::SetIm(double a){
	Im_=a;
}

Complex::~Complex(){}


//OPERADORES

Complex const operator+(Complex const & a,Complex const & b){
	Complex d(a.GetRe() + b.GetRe(),a.GetIm() + b.GetIm());
	return d;
}

Complex const operator-(Complex const & a,Complex const & b){
	Complex d(a.GetRe() - b.GetRe(),a.GetIm() - b.GetIm());
	return d;
}

Complex const operator*(Complex const & a,Complex const & b){
	return Complex(a.GetRe()*b.GetRe()-a.GetIm()*b.GetIm(),a.GetRe()*b.GetIm()+a.GetIm()*b.GetRe());
}
Complex const operator/(Complex const & a, double b){
	return Complex (a.GetRe()/b,a.GetIm()/b);
}
Complex const operator/(Complex const & a,Complex const & b){
	if(b.GetRe()==0 && b.GetIm()==0){
		return a;
	}
	else	return ((a * b.Conjugate2()) / (b.Abs_Square()));
}

Complex const & Complex::operator*=(Complex const &c){
	(*this) = (*this)*c;
	return *this;
}

Complex const & Complex::operator/=(Complex const &c){
	(*this) = (*this)/c;
	return *this;
}

Complex const & Complex::operator+=(Complex const &c){
	(*this) = (*this)+c;
	return *this;
}

Complex const & Complex::operator-=(Complex const &c){
	(*this) = (*this)-c;
	return *this;
}

Complex const & Complex:: Conjugate (){
	Im_*= -1;
	return *this;
}

Complex const Complex:: Conjugate2() const{
		return Complex(Re_,-Im_);
}

double Complex::Abs_Square()const{
	return (Re_ * Re_ + Im_ * Im_);
}

double Complex::Abs()const{
	return sqrt(Re_ * Re_ + Im_ * Im_);
}

istream & operator >> (istream & is, Complex &c){
	bool good=false;
	bool bad=false;
	double re=0,im=0;
	char ch=0;
	if(is >> ch && ch=='('){
		if(is >> re && is >>ch && ch==',' && is>>im && is>>ch && ch==')')
            good=true;
		else
            bad=true;
	}
	else if(is.good()){
	    is.putback(ch);
		if(is >> re)
            good=true;
		else
            bad=true;
	}
	if(good){
		c.Re_=re;
		c.Im_=im;
	}
	if(bad){
		cerr<<"BAD_INPUT"<<endl;
		is.clear(ios::badbit);
	}

	return is;
}

ostream & operator << (ostream & os, Complex &c){
	os<<'('<<c.GetRe()<<','<<c.GetIm()<<')';
	return os;
}