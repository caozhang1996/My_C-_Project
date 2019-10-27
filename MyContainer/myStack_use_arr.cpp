#include <iostream>
using namespace std;

class Array{  //使用数组实现栈
public:
	//构造函数
	Array(int size):m_data(new int[size]),m_size(size),m_top(0){
		cout << "构造函数：" << this << endl;
	}
	//析构函数
	~Array(void){
		cout << "析构函数："<< this << endl;
		delete[] m_data;
	}
	//压入
	bool push(int data){
	    //上溢检查
		if (m_top >= m_size){
			return false;
		}
		m_data[m_top++] = data;
	}
	//弹出
	bool pop(){
		//下溢检查
		if (!m_top){
			return false;
		}
		//int data = m_data[--m_top];
        --m_top;
		return true;
	}   
    int peek(){
        return m_data[m_top - 1];
    }
    bool empty(){
        return m_top == 0;
    }
    void print(void)const{
        for (int i = 0; i < m_top; ++i){
            cout << m_data[i] << ' ';
        }
        cout <<endl;
	}

private:
	int* m_data;   //数组指针
	int m_size;    //数组大小
	int m_top;     //栈顶指针
};


int main()
{
	Array arr(10);
	for (int i = 0;i < 5;++i)
	{
		arr.push(i);
	}

    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
    arr.pop();
	cout << arr.empty() << endl;
	return 0;
}