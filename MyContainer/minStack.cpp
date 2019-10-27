#include <iostream>
#include <stack>
using namespace std;

/*
    设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

    push(x) -- 将元素 x 推入栈中。
    pop() -- 删除栈顶的元素。
    top() -- 获取栈顶元素。
    getMin() -- 检索栈中的最小元素。

    示例:

    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin();   --> 返回 -3.
    minStack.pop();
    minStack.top();      --> 返回 0.
    minStack.getMin();   --> 返回 -2.
*/

class MinStack{
private:
    stack<int>  data_stack;   //数据栈
    stack<int>  min_stack;    //最小值栈

public:
    MinStack(){

    }

    void push(int x){
        data_stack.push(x);
        if(min_stack.empty()){
            min_stack.push(x);
        }else{
            if(x > min_stack.top())
                min_stack.push(min_stack.top());
            else
                min_stack.push(x);
        }
    }

    void pop(){
        data_stack.pop();
        min_stack.pop();
    }

    int top(){
        return data_stack.top();
    }

    int getMin(){
        return min_stack.top();
    }
};

int main(int argc, char const *argv[])
{
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    cout << minStack->getMin() <<endl;   
    // minStack->pop();
    // minStack->top();      
    // minStack->getMin();   
    return 0;
}
