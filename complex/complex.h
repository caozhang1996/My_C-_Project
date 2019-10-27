#ifndef __COMPLEX__
#define __COMPLEX__


//使用模板
template<typename T>
class complex
{
private:
    T re, im;

public:
    complex(T r = 0, T i = 0) : re(r), im(i){ }   //构造函数特有语法：initialization list(初值化，初始化)
    //complex(double r = 0, double i = 0) {re = r, im = i;}   //assignment（赋值），与上一种写法一样，推荐上一种写法 
    T real() const { return re; }    //const:不会改变函数中数据的内容，成员函数中有一个默认的参数即this指针，return re 即为 return this->re(不显示写，编译器会帮我们加上)
    T imag() const { return im; }    
    complex<T>& operator += (const complex<T>&);
    complex<T>& operator -= (const complex<T>& );
    complex<T>& operator *= (const complex<T>&);
};

//do assignment plus(做赋值加法)
template<typename T>
inline complex<T>& complex<T>::operator += (const complex<T>& r)  // +=操作符左边的数作为一个隐藏的参数传进来
{   
    this->re += r.re;
    this->im += r.im;
    return *this;
}

template<typename T>
inline complex<T>& complex<T>::operator -= (const complex<T>& r)
{
    this->re -= r.re;
    this->im -= r.im;
    return *this;
}

template<typename T>
inline complex<T>& complex<T>:: operator *= (const complex<T>& r)
{
    T f = this->re * r.re - this->im * r.im;
    this->im = this->re * r.im + this->im * r.re;
    this->re = f;
    return *this;
}

//class body之外的函数(非成员函数)
template<typename T>
inline T real(const complex<T>& x)
{
    return x.real();
}

template<typename T>
inline T imag(const complex<T>& x)
{
    return x.imag();
}

/*
    operator overloading(非成员函数的操作符重载)
    为了对付client的三种可能用法，这儿对应开发三个函数
    {
        complex c1(2, 1);
        complex c2;
        c2 = c1 + c2;
        c2 = c1 + 5;
        c2 = 7 + c1;
    }
*/
/*
    下面这些函数绝不可return by reference，因为，它们返回的必定是个local object
*/
template<typename T>
inline complex<T> operator + (const complex<T>& x, const complex<T>& y)
{
    return complex<T>(real(x) + real(y), imag(x) + imag(y));
}

template<typename T>
inline complex<T> operator + (const complex<T>& x, T y)
{
    return complex<T>(real(x) + y, imag(x));
}

template<typename T>
inline complex<T> operator + (T x, const complex<T>& y)
{
    return complex<T>(x + real(y), imag(y));
}

template<typename T>
inline complex<T> operator - (const complex<T>& x, const complex<T>& y)
{
    return complex<T>(real(x) - real(y), imag(x) - imag(y));
}

template<typename T>
inline complex<T> operator - (const complex<T>& x, T y)
{
    return complex<T>(real(x) - y, imag(x));
}

template<typename T>
inline complex<T> operator - (T x, const complex<T>& y)
{
    return complex<T>(x - real(y), -imag(y));
}

//复数的乘法:
template<typename T>
inline complex<T> operator * (const complex<T>& x, const complex<T>& y)
{
  return complex<T>(real (x) * real (y) - imag (x) * imag (y),
			   real (x) * imag (y) + imag (x) * real (y));
}
 
template<typename T>
inline complex<T> operator * (const complex<T>& x, T y)
{
  return complex<T>(real (x) * y, imag (x) * y);
}
 
template<typename T>
inline complex<T> operator * (T x, const complex<T>& y)
{
  return complex<T>(x * real (y), x * imag (y));
}

//复数的除法:
template<typename T>
inline complex<T> operator / (const complex<T>& x, T y)
{
    return complex<T>(real(x) / y, imag(x) / y);
}


/* 
    netege(取反)
    complex c1(2, 1);
    complex c2;
    cout << -c1;
    cout << +c1;
*/
template<typename T>
inline complex<T> operator + (const complex<T>& x)
{
    return x;
}

template<typename T>
inline complex<T> operator - (const complex<T>& x)
{
    return complex<T>(-real(x), -imag(x));
}

/*
    判断相等
    complex c1(2, 1);
    complex c2;
    cout << (c1 == c2);
    cout << (c1 == 2);
    cout << (0== c2);
*/
template<typename T>
inline bool operator == (const complex<T>& x, const complex<T>& y)
{
    return real(x) == real(y) && imag(x) == imag(y);
}

template<typename T>
inline bool operator == (const complex<T>& x, double y)
{
    return real(x) == y && imag(x) == 0;
}

template<typename T>
inline bool operator == (double x, const complex<T>& y)
{
    return x == real(y) && imag(y) == 0;
}

/*
    判断不等
    complex c1(2, 1);
    complex c2;
    cout << (c1 != c2);
    cout << (c1 != 2);
    cout << (0 != c2);
*/
template<typename T>
inline bool operator != (const complex<T>& x, const complex<T>& y)
{
    return real(x) != real(y) || imag(x) != imag(y);
}

template<typename T>
inline bool operator != (const complex<T>& x, T y)
{
    return real(x) != y || imag(x) != 0;
}

template<typename T>
inline bool operator != (T x, const complex<T>& y)
{
    return x != real(y) || imag(y) != 0;
}


#include <cmath>

//极坐标形式转换为复数表达形式
template<typename T>
inline complex<T> polar(T r, T t)
    /*
        r:半径
        t:角度
    */   
{
    return complex<T>(r * cos(t), r * sin(t));
}
/*
    共轭复数
*/
template<typename T>
inline complex<T> conj (const complex<T>& x)
{
    return complex<T>(real(x), -imag(x));
}

template<typename T>
inline T norm(const complex<T>& x)
{
    return real(x) * real(x) + imag(x) * imag(x);
}
#endif 