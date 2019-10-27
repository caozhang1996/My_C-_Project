#ifndef __MYSTRING__
#define __MYSTRING__

#include <cstring>

class String
{
private:
    char* m_data; 

public:
    String(const char*);
    String(const String&);  //拷贝构造
    String& operator = (const String&);  //拷贝赋值
    ~String();
    char* get_c_str() const { return m_data; } 
};

inline String::String(const char* cstr = 0)
{
    if(cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else     //未指定初值时的构造
    {
        m_data = new char[1];
        *m_data = '\0';
    }
    
}

//拷贝构造函数
inline String::String(const String& str)
{
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

//拷贝赋值
inline String& String:: operator = (const String& str)
{
    if(this == &str)   //检测自我赋值(一定要写 )
        return *this;
    
    delete[] m_data;  //先清空自己的内容
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}

inline String::~String()
{
    delete[] m_data;
}
#endif