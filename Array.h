#ifndef ARRAY__H
#define ARRAY__H


#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

#define BAD_INPUT "ERROR: BAD-INPUT - Format error detected. Shorter line as output"

#define DEFAULT_SIZE 100

using namespace std;

template <class T>
class Array;

template <class T>
istream& operator >>(istream &, const Array <T>&);

template <class T>
ostream& operator <<(ostream &, const Array <T>);


template <class T>
class  Array
{
    size_t size;
    T* data;

    public:
    //Constructors
    Array(size_t s=DEFAULT_SIZE);
    Array(const Array <T> &);
    //Destructor
    ~Array();
    //Operators
    T & operator[](size_t const pos) const;
    T & operator[](size_t const pos);
    Array<T> & operator=( const Array<T> &);
    Array<T>   operator*( const T &) const;
    Array<T> & operator*=(const T &);
    friend istream& operator>> <T>(istream &, const Array <T>&);
    friend ostream& operator<< <T>(ostream &, const Array <T>);
    Array<T> operator/ (const T &) const;
    Array<T>& operator/=(const T &);
    //Functions
    Array<T> Even() const;
    Array<T> Odd() const;
    size_t GetSize() const;
    void Reset();
    void Resize(size_t const);
};

//CONSTRUCTORS

template <class T> Array <T>::Array(size_t s){
    size=s;
    data=new T[size];
}

template <class T> Array <T>::Array(const Array <T> & c){
    size=c.size;
    data=new T[size];
    for(size_t i=0;i<size;i++)
       data[i]=c[i];
}

//DESTRUCTORS

template <class T> Array <T>::~Array()
{
    delete []data;
}

//OPERATORS

template <class T> T & Array <T>::operator[](size_t const pos){
    if(pos>=size){
      if (size==0){
            Resize (1);
        }else {
            Resize(2*size);
        }
    }
    return data[pos];
}

template <class T> T & Array <T>::operator[](size_t const pos)const {
    return data[pos];
}

template <class T> Array<T> & Array<T>::operator=( const Array<T> &c ){
    if(this!=&c){
        if(size==c.size){
            for(size_t i=0;i<size;i++) data[i]=c.data[i];
        }
        else{
            Resize(c.size);
            for(size_t i=0;i<size;i++)
                data[i]=c.data[i];
        }
    }
    return *this;
}

template <class T> Array<T> Array<T>::operator*(const T & d) const
{
    Array<T> result(*this);

    for(size_t i=0; i<size; i++)
        result[i]*=d;

    return Array<T>(result);
}

template <class T> Array<T> & Array<T>::operator*=(const T & d)
{
    for(size_t i=0; i<size; i++)
        (*this)[i]*=d;

    return *this;
}



template <class T> std::istream& operator  >> (std::istream& is, Array <T>& X)
{
    string line;
    getline(is, line);
    stringstream lstream(line);
    T buffer;
    size_t i=0;

    while(lstream>>buffer){
        if(!lstream.fail()&&!lstream.bad()){
            X[i]=buffer;
            i++;
        }
       //else throw 'entrada invalida';
    }
    X.Resize(i);
    return is;
}

template <class T> std::ostream& operator  << (std::ostream& os, Array <T> X)
{
    size_t len=X.GetSize();
    for(size_t i=0; i<len; i++)
        os<<X[i];

    return os;
}

template <class T> Array<T>  Array<T>::operator/ (const T& b) const
{
    Array<T> aux(*this);

    for(size_t i=0;i<size;i++)
       aux[i]=data[i]/b;

    return Array<T>(aux);
}

template <class T> Array<T>& Array<T>::operator/=(const T& b)
{
    for(size_t i=0; i<size; i++)
        data[i]/=b;

    return *this;
}


//FUNCTIONS

template <class T> Array<T> Array<T>::Even() const
{
    size_t len=(size/2);

    Array<T> result(len);

    for(size_t i=0; i<len; i++)
       result[i]=(*this)[2*i];
    return Array<T>(result);
}

template <class T> Array<T> Array<T>::Odd() const
{
    size_t len;
    if(!(size%2))
        len=size/2;
    else
        len=(size/2)+1;

    Array<T> result(len);

    for(size_t i=0; i<len; i++)
        result[i]=(*this)[1+2*i];

    return Array<T>(result);
}

template <class T> size_t Array <T>::GetSize()const {
    return size;
}

template <class T> void Array <T>::Resize(size_t const n){
    if(size==n)
        return;

    T* aux;
    aux=new T[n];
    size_t limit=( (n<size)? n : size);

    for(size_t i=0; i<limit; i++)
            aux[i]=data[i];

    delete []data;
    data=aux;
    size=n;
}

template <class T> void Array <T>::Reset(){
    delete[] data;
    size=DEFAULT_SIZE;
    data=new T[DEFAULT_SIZE];
};
#endif


