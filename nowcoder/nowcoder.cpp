#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;

class Sloution{
public:
    /*
        十进制转换为十六进制
    */
    void change(){
        string str;
        while(cin >> str){
            string temp = str.substr(2);
            int num = 0;
            int sum = 0;
            int count = 0;

            while(count < temp.size()){
                char ch = temp[temp.size() - 1 - count];
                if(ch >= '0' && ch <= '9')
                    num = ch - '0';
                else if(ch >= 'a' && ch <= 'z')
                    num = ch - 'a' + 10;
                else
                    num = ch - 'A' + 10;
                
                sum += num * pow(16, count);
                count++;
            }
            cout << sum << endl;
        }
    }

    /*
        质数因子：
            输入一个正整数，按照从小到大的顺序输出它的所有质数的因子（如180的质数因子为2 2 3 3 5 ）
            最后一个数后面也要有空格 
    */
    void get_factor(){
        int num;

        while(cin >> num){
            string res = "";
            int x = 2;
            while(num != 1){
                while(num % x ==0){
                    num /= x;
                    res += to_string(x) + " ";
                }
                x++;
            }
            cout << res << endl;
        }
    }

    /*
        合并表记录
    */
    void merge_map(){
        int n;

        while(cin >> n){
            map<int, int> m;
            for(int i = 0; i < n; i++){
                int key, value;
                cin >> key >> value;

                if(m.find(key) == m.end()){  //find()函数返回一个迭代器指向键值为key的元素，如果没找到就返回指向map尾部的迭代器
                    m[key] = value;
                } else{
                    m[key] = m[key] + value;
                }
            }

            for(auto iter = m.begin(); iter != m.end(); iter++){
                cout << iter->first << " " << iter->second << endl;
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Sloution s;
    s.merge_map();
    return 0;
}

