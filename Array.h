#ifndef ARRAY__H
#define ARRAY__H


#include <iostream>
#include <cmath>
#include <string>

#define BAD_INPUT "ERROR: BAD-INPUT - Format error detected. Shorter line as output"

#define DEFAULT_SIZE 100

using namespace std;

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
    Array<T> & operator*( const T &);
    Array<T> & operator*=(const T &);
    template <class T1> friend istream& operator  >> (istream &, const Array <T1>&);
    template <class T1> friend ostream& operator  << (ostream &, const Array <T1>);
    Array<T> & operator / (const double);
    //Functions
    Array<T>& Even() const;
    Array<T>& Odd() const;
    size_t GetSize() const;
    void Reset();
    void Resize(size_t);
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

template <class T> Array<T> & Array<T>::operator*(const T & d)
{
    Array<T>* result;
    result=new Array<T>(*this);

    for(size_t i=0; i<size; i++)
        (*result)[i]*=d;

    return *result;
}

template <class T> Array<T> & Array<T>::operator*=(const T & d)
{
    for(size_t i=0; i<size; i++)
        (*this)[i]*=d;

    return *this;
}



template <class T1> std::istream& operator  >> (std::istream& is, Array <T1>& X)
{
    //Tirar excepcion en caso de error
    string line;
    getline(is, line);
    stringstream lstream(line);
    T1 buffer;
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

template <class T1> std::ostream& operator  << (std::ostream& os, Array <T1> X)
{
    size_t len=X.GetSize();
    for(size_t i=0; i<len; i++)
        os<<X[i];

    return os;
}

template <class T> Array<T> & Array<T>::operator / (const double b)
{
    T* aux=new T[size];
    for(size_t i=0;i<size;i++)
    {
       aux[i]=(*this)[i]/b;
    }
    delete []data;
    data=aux;
    return *this;
}


//FUNCTIONS

template <class T> Array<T>& Array<T>::Even() const
{
    size_t len=(size/2);

    Array<T> *result;
    result=new Array<T>(len);
    for(size_t i=0; i<len; i++)
        (*result)[i]=(*this)[0+2*i];

    return *result;
}

template <class T> Array<T>& Array<T>::Odd() const
{
    size_t len;
    if(!(size%2))
        len=size/2;
    else
        len=(size/2)+1;

    Array<T> *result;
    result=new Array<T>(len);
    for(size_t i=0; i<len; i++)
        (*result)[i]=(*this)[1+2*i];

    return *result;

}

template <class T> size_t Array <T>::GetSize()const {
    return size;
}

template <class T> void Array <T>::Resize(size_t n){
    T* aux;
    if(size!=n){
        aux=new T[n];
        size=n;
        for(size_t i=0;i<size;i++){
            aux[i]=(*this)[i];
        }
        delete []data;
        data=aux;
    }
    return;
}

template <class T> void Array <T>::Reset(){
    delete[] data;
    size=DEFAULT_SIZE;
    data=new T[DEFAULT_SIZE];
};
#endif
