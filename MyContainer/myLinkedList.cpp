#include<iostream>
using namespace std;

class MyLinkedList{
private:
    struct Node{
        int val;
        Node* next;
        Node(int x): val(x), next(NULL){}
    };
    Node* head;
    Node* tail;
    int len;

public:
    MyLinkedList(){
        int len = 0;
        Node* p = new Node(0);
        head = p;
        tail = p;
    }

    int get(int index){
        if(index < 0 || index >= len)
            return -1;
        Node* p = head;
        for(int i = 0; i < index; i++){
            p = p->next;
        }
        return p->val;
    }

    void addAtHead(int val){
        if(len == 0)
            head->val = val;
        else{
            Node* p = new Node(val);
            p->next = head;
            head = p;
        }
        len++;
    }

    void addAtTail(int val){
        if(len == 0)
            tail->val = val;
        else{
            Node* p = new Node(val);
            tail->next = p;
            tail = p;
        }
        len++;
    }

    void addAtIndex(int index, int val) {
        if(index > len)
            return;
        else if(index == 0)
            addAtHead(val);
        else if(index == len)
            addAtTail(val);
        else{
            Node* cur = head;
            for(int i = 0; i < index - 1; i++){
                cur = cur->next;
            }
            Node* p = new Node(val);
            p->next = cur->next;
            cur->next = p;
            len++; 
        }
    }

    void deleteAtIndex(int index){
        if(index >= 0 || index < len){
            if(index == 0)
                head = head->next;
            else{
                Node* cur = head;
                for(int i = 0; i < index - 1; i++){
                    cur = cur->next;
                }
                cur->next = cur->next->next;
                if(index == len - 1)
                    tail = cur;
            }
            len--;
        }   
    }
};

int main(int argc, char const *argv[])
{
    MyLinkedList* linkedList = new MyLinkedList();
    linkedList->addAtHead(1);
    linkedList->addAtTail(3);
    linkedList->addAtIndex(1,2);   //链表变为1-> 2-> 3
    cout << linkedList->get(1) << endl;            //返回2
    linkedList->deleteAtIndex(1);  //现在链表是1-> 3
    cout << linkedList->get(1) << endl;            //返回3
    return 0;
}
