#include <iostream>
#include <stack>
#include <queue>

using namespace std;

/*
    使用栈实现队列的下列操作：

    push(x) -- 将一个元素放入队列的尾部。
    pop() -- 从队列首部移除元素。
    peek() -- 返回队列首部的元素。
    empty() -- 返回队列是否为空。

    示例:

    MyQueue queue = new MyQueue();

    queue.push(1);
    queue.push(2);  
    queue.peek();  // 返回 1
    queue.pop();   // 返回 1
    queue.empty(); // 返回 false
*/

class MyQueue{    //使用栈实现队列
private: 
    stack<int> stack_push;    //压入栈
    stack<int> stack_pop;     //弹出栈

public:
    MyQueue(){

    }

    void push(int x){
        stack_push.push(x);
    }

    int pop(){
        int len = stack_push.size();
        for(int i = 0; i < len; i++){
            int t = stack_push.top();
            stack_push.pop();
            stack_pop.push(t);
        }
        int cur = stack_pop.top();
        stack_pop.pop();
        for(int i = 0; i < len - 1; i++){
            int t = stack_pop.top();
            stack_pop.pop();
            stack_push.push(t);
        }
        return cur;
    }

    int peek(){
        int len = stack_push.size();
        for(int i = 0; i < len; i++){
            int t = stack_push.top();
            stack_push.pop();
            stack_pop.push(t);
        }
        int cur = stack_pop.top();
        for(int i = 0; i < len - 1; i++){
            int t = stack_pop.top();
            stack_pop.pop();
            stack_push.push(t);
        }
        return cur;
    }

    bool empty(){
        return stack_push.empty() && stack_pop.empty();
    }
};

/*
    用队列实现栈：
        使用队列实现栈的下列操作：

        push(x) -- 元素 x 入栈
        pop() -- 移除栈顶元素
        top() -- 获取栈顶元素
        empty() -- 返回栈是否为空
*/
class MyStack{
private:
    queue<int> que1;   //存放数值
    queue<int> que2;   //辅助 

public:
    MyStack(){

    }

    void push(int x){
        que1.push(x);
    }

    int pop(){
        int t;
        while(que1.size() > 1){
            int cur = que1.front();
            que1.pop();
            que2.push(cur);
        }
        if(que1.size() == 1){
            t = que1.front();
            que1.pop();
            while(que2.size() > 0){
                int cur = que2.front();
                que2.pop();
                que1.push(cur);
            }
        }
        return t;
    }

    int top(){
         return que1.back();
    }

    bool empty(){
        return que1.empty(); 
    }
};

int main(int argc, char const *argv[])
{
    MyStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    s.pop();
    cout << s.top() << endl;
    return 0;
}
