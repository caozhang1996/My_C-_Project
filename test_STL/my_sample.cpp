#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>  //qsort, bsearch, NULL
#include <cstdio>

using namespace std;

const long ASIZE = 500000L;

long get_a_target_long()
{
    long target = 0;

    cout << "target (0 ~ " << RAND_MAX / 65538 << "): ";
    cin >> target;
    return target;
}

int compareLongs(const void* a, const void* b)
{   //表示为递增排序
    return (*(long*)a - *(long*)b);
}

string get_a_target_string()
{
    long target = 0;
    char buf[11];

    cout << "target (0 ~ " << RAND_MAX / 65538 << "): ";
    cin >> target;
    snprintf(buf, 10, "%ld", target);
    cout << string(buf);
}

int compareStrings(const void* a, const void* b)
{
    if( *(string*)a > *(string*)b )
        return 1;
    else if(*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}

template<typename T>
void print_container(T& c)
{
    for(auto iter = c.cbegin(); iter != c.cend(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
};

template<typename T>    //适用于除forward_list之外的所有序列式容器和关联式容器
void print_reverse(T& c)
{
    for(auto iter = c.crbegin(); iter != c.crend(); ++iter)  //reverse iterator将++进行操作符重载，里面实际上是--
    {
        cout << *iter << " ";
    }
    cout << endl;
};

//测试array标准库
namespace jj01
{
    void test_array()
    {
        cout << "\ntest_array().......... \n";

        array<long, ASIZE> c;
        clock_t timeStart = clock();

        for(long i = 0; i < ASIZE; i++){
            c[i] = rand() / 65538;    //rand()所提供的函数
        }
        cout << "milli-seconds: " << (clock() - timeStart) << endl;   //放50万个数据消耗的时间
        cout << "array.size()= " << c.size() << endl;     
        cout << "array.front()= " << c.front() << endl;   
        cout << "array.back()= " << c.back() << endl; 
        cout << "array.data()= " << c.data() << endl;    //返回数组的首地址
        
        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();

        timeStart = clock();
        qsort(c.data(), ASIZE, sizeof(long), compareLongs);  
        long* pItem = (long*)bsearch(&target, c.data(), ASIZE, sizeof(long), compareLongs);
        cout << "qSort()+bsearch(),milli-seconds: "<< clock() - timeStart << endl;
        if(pItem != NULL)
            cout << "found: " << *pItem << endl;
        else
            cout << "not found!" << endl;
        
        
        {   
            cout << "\n\ntest_array(): other function-------\n";
            array<int, 5> c1 = {42, 377, 611, 21, 44};
            array<int, 5> c2;

            cout << "c1: ";
            for(auto iter = c1.begin(); iter != c1.end(); iter++)
            {
                cout << *iter << " ";
            }
            cout << endl;
            
            cout << "array.front()= " << c1.front() << endl;
            cout << "array.back()= " << c1.back() << endl;
            cout << "array.at(2)= " << c1.at(2) << endl;    //返回索引2所指向的元素（如果idx超出范围就抛出range-error异常）
            cout << "*(array.begin())= " << *c1.begin() << endl;   //迭代器指向第一个元素
            cout << "*(array.end())= " << *c1.end() << endl;       //迭代器指向最末元素的下一位置
            cout << "*(array.rbegin())= " << *c1.rbegin() << endl;   //迭代器指向反向迭代的第一个元素
            cout << "*(array.rend())= " << *c1.rend() << endl;       //迭代器指向反向迭代的最末元素的下一位置

            cout << "\nswap elements between c1 and c2 and set c1 to 5: " << endl;
            c1.swap(c2);    //置换c1, c2的数据
            c1.fill(5);     //将所有的元素置5

            cout << "c1: ";
            print_container(c1);
            cout << "c2: ";
            print_container(c2);
        }
    }
}

//----------------------------------------------------------------
#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <cstdlib>   //abort()
#include <cstdio>    //snprintf()
#include <algorithm>  //sort()

namespace jj02{
    void test_vector(long& value){
         /*
            value: 传入元素个数
        */
        cout << "\ntest_vector().......... \n";

        vector<long> c;
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++){
            try{     //try-catch:　防止异常，例如：value值过大导致内存不足
                c.push_back(rand() / 65538);
            }
            catch(exception& e){
                cout << "i = " << i << " " <<e.what() << endl; //曾经最高i=67108864就分不到内存了
                abort();    //退出程序
            }
        }
        cout << "milli-seconds: " << clock() - timeStart << endl;
        cout << "vector.size()= " << c.size() << endl;
        cout << "vector.front()= " << c.front() << endl;
        cout << "vector.back()= " << c.back() << endl;
        cout << "vector.data()= " << c.data() << endl;
        cout << "vector.capacity= " << c.capacity() << endl;     //返回容器的容量

        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();
        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);   //返回一个迭代器
            cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

            if(pItem != c.end())
            {
                cout << "found: " << *pItem << endl << endl;
            }
            else
            {
                cout << "not found." << endl << endl;
            }
        }
        
        {
            timeStart = clock();
            sort(c.begin(), c.end());   //按字典序排序
            long* pItem = (long*)bsearch(&target, (c.data()), 
                                   c.size(), sizeof(long), compareLongs);  
            cout << "sort() + bsearch(), milli-seconds : " << (clock()-timeStart) << endl;   //二分查找比循序查找耗时长，因为需要先sort()
        
            if (pItem != NULL)
                cout << "found, " << *pItem << endl << endl;
            else
                cout << "not found! " << endl << endl;    
            
        }

        {
            cout << "\ntest_vector(): other function-------\n";
            vector<long> c1({42, 377, 611, 21, 44});
            vector<long> c2 = {7, 8, 9, 10};
            initializer_list<long> initlist({1, 2, 3, 4});

            cout << "c1: ";
            print_container(c1);
            print_reverse(c1);
            cout << "select insert function: \n";
            cout << "       (1)c.insert(pos, elem) (2)c.insert(pos, n, elem)\n";
            cout << "       (3)c.insert(pos, beg, end) (4)c.insert(pos, initlist)\n";
            int choice;
            cin >> choice;
            switch (choice)
            {
                case 1: cout << "insert a number 22: " << *c1.insert(c1.begin()+2, 22) << endl;
                        print_container(c1);
                        break;

                case 2: cout << "insert 3 number 22: " << *c1.insert(c1.begin()+2, 3, 22) << endl;
                        print_container(c1);
                        break;
                case 3: cout << "insert number in [c2.bedin(), c2.end()): " << *c1.insert(c1.begin()+2, c2.begin(), c2.end()) << endl;
                        print_container(c1);
                        break;
                case 4: cout << "insert a initlist : " << *c1.insert(c1.begin()+2, initlist) << endl;
                        print_container(c1);
                        break;

                // to be continued...
                default:
                        break;
            }
        }
    }

}

//----------------------------------------------------------------
#include <list>     //双向链表
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <algorithm> //find()
#include <iostream>
#include <ctime> 

namespace jj03
{
    void test_list(long& value)      //双向链表
    {
        cout << "\ntest_list()----------\n";
        
        list<long> c;
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++){
            try
            {
                c.push_back(rand() / 65538);
            }
            catch(exception& p)
            {
                cout << "i = " << i << " " << p.what() << endl;
                abort();
            }
            
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
        cout << "list.size()= " << c.size() << endl;
        cout << "list.max_size()= " << c.max_size() << endl;
        cout << "list.front()= " << c.front() << endl;
        cout << "list.back()= " << c.back() << endl;
        
        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);   //返回一个迭代器
        cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

        if(pItem != c.end())
            cout << "found: " << *pItem << endl << endl;
        else
            cout << "not found." << endl << endl;

        timeStart = clock();
        c.sort();   //当容器自己含有sort函数时，使用自带的sort会比较快
        cout << "list.sort(), milli-seconds: " << (clock() - timeStart) << endl;

        {
            cout << "\ntest_list(): other function-------\n";
            list<char> c;
            char num = 'a';

            for(int i = 0; i < 26; ++i)
            {
                c.push_back(num++);
            }
            cout << "c: ";
            print_container(c);
            print_reverse(c);

            c.pop_front();
            c.pop_back();
            cout << "after pop_front() and pop_back()\n" << "c: ";
            print_container(c);
        }
    }
} 


//----------------------------------------------------------------
#include <forward_list>      //单向链表
#include <iostream>
#include <cstdlib>    //abort()
#include <ctime>
#include <algorithm>

namespace jj04
{
    void test_forward_list(long& value)
    {
        cout << "\ntest_forward_list()--------\n";

        forward_list<long> c;
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++)
        {
            try
            {
                c.push_front(rand() / 65538);
            }
            catch(exception& p)
            {
                cout << "i = " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
        cout << "forward_list.max_size()= " << c.max_size() << endl;    //单向链表没有size函数，只有最大size函数？？？
        cout << "forward_list.front()= " << c.front() << endl;


        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);
        cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

        if(pItem != c.end())
        {
            cout << "found: " << *pItem << endl << endl;
        }
        else
        {
            cout << "not found" << endl << endl;
        }
        
        timeStart = clock();
        c.sort();
        cout << "forward_list.sort(), milli-seconds: " << (clock() - timeStart) << endl;

    }
}

//----------------------------------------------------------------
#include <deque>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>   //abort()

namespace jj05
{
    void test_deque(long& value)
    {
        cout << "\ntest_deque()---------\n";

        deque<long> c;
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++)
        {
            try
            {
                c.push_back(rand() / 65538);
            }
            catch(exception& p)
            {
                cout << "i = " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
        cout << "deque.size()= " << c.size() << endl;
        cout << "deque.front()= " << c.front() << endl;   
        cout << "deque.back()= " << c.back() << endl; 
        cout << "deque.max_size()= " << c.max_size() << endl;   

        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();  
        timeStart = clock();            
        auto pItem = find(c.begin(), c.end(), target);  
        cout << "std::find(), milli-seconds : " << (clock()-timeStart) << endl;   
        
        if (pItem != c.end())
            cout << "found, " << *pItem << endl << endl;
        else
            cout << "not found! " << endl << endl;  
            
        timeStart = clock();        
        sort(c.begin(), c.end());                       
        cout << "sort(), milli-seconds : " << (clock()-timeStart) << endl;
    }
}

//----------------------------------------------------------------
#include <set>
#include <iostream>
#include <ctime>
#include <algorithm>

namespace jj06
{
    void test_multiset(long& value)
    {
        cout << "\ntest_multiset()--------\n";

        multiset<long> c;       //multiset特点：1:安插数据很慢(因为存放数据时存在排序操作)，2:查找非常快, 3:元素可以重复
        clock_t timeStart = clock();
        
        for(long i = 0; i < value; i++)
        {
            try
            {
                c.insert(rand() / 65538);
            }
            catch(exception& p)
            {
                cout << "i = " << " " << i << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
        cout << "multiset.size()= " << c.size() << endl;
        cout << "multiset.max_size()= " << c.max_size() << endl;

        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();

        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);  //比c.find()慢很多
            cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

            if(pItem != c.end())
            {
                cout << "found, " << *pItem << endl << endl;
            }
            else
            {
                cout << "not found!" << endl << endl; 
            }
            
        }
        {
            timeStart = clock();
            auto pItem = c.find(target);    //自身的find()比std::find()快很多
            cout << "multiset.find(), milli-seconds: " << (clock() - timeStart) << endl;

            if(pItem != c.end())
            {
                cout << "found, " << *pItem << endl << endl;
            }
            else
            {
                cout << "not found!" << endl << endl; 
            }
        }
    }
}


//----------------------------------------------------------------
#include <map>
#include <iostream>
#include <ctime>
#include <algorithm>

namespace jj07
{
    void test_multimap(long& value)
    {
        cout << "\ntest_multimap()--------\n";

        multimap<long, long> c;  //multimap:key可以重复
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++)
        {
            try
            {
                c.insert(pair<long, long>(i, rand() / 65538));
            }
            catch(exception& p)
            {
                cout << "i = " << " " << i << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
        cout << "multimap.size()= " << c.size() << endl;
        cout << "multimap.max_size()= " << c.max_size() << endl;

        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();
        timeStart = clock();
        auto pItem = c.find(target);     //按key查找
        cout << "multimap.find(), milli-seconds: " << (clock() - timeStart) << endl;

        if(pItem != c.end())
            cout << "found, value = " << (*pItem).second << endl << endl;
        else
            cout << "not found!" << endl << endl;
    }
}

//----------------------------------------------------------------
#include <unordered_set>
#include <ctime>
#include <cstdlib>
#include <algorithm>

namespace jj08
{
    void test_unordered_multiset(long& value)
    {
        cout << "\ntest_unordered_multiset--------\n";

        unordered_multiset<long> c;
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++)
        {
            try
            {
                c.insert(rand() / 65538);
            }
            catch(exception& p)
            {
                cout << "i = " << i << " " << p.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds : " << (clock()-timeStart) << endl;        
        cout << "unordered_multiset.size()= " << c.size() << endl;
        cout << "unordered_multiset.max_size()= " << c.max_size() << endl;    //357913941
        cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;    
        cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;  
        cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor() << endl;  
        cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count() << endl;                
        for (unsigned i=0; i< 30; ++i)
        {
            cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";   //i表示第i个bucket
        }                   

        cout << "\n\nInput a target that you want to search."<< endl;          
        long target = get_a_target_long();  
        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);  //比 c.find(...) 慢很多 
            cout << "std::find(), milli-seconds : " << (clock()-timeStart) << endl;   
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;  
        }
    
        {
            timeStart = clock();        
            auto pItem = c.find(target);        //比 std::find(...) 快很多                          
            cout << "unordered_multiset.find(), milli-seconds : " << (clock()-timeStart) << endl;   
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;  
        }       
    }
}

//----------------------------------------------------------------
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace jj09
{
    void test_unordered_multimap(long& value)
    {
        cout << "\ntest_unordered_multimap--------\n";

        unordered_multimap<long, long> c;
             
        clock_t timeStart = clock();                                
        for(long i=0; i< value; ++i)
        {
            try {
                //multimap 不可使用 [] 進行 insertion 
                c.insert(pair<long, long>(i, rand() / 65538));
            }
            catch(exception& p) {
                cout << "i=" << i << " " << p.what() << endl; 
                abort();
            }
        }
        cout << "milli-seconds : " << (clock()-timeStart) << endl;        
        cout << "unordered_multimap.size()= " << c.size() << endl;    
        cout << "unordered_multimap.max_size()= " << c.max_size() << endl;   
        
        cout << "\n\nInput a target that you want to search."<< endl; 
        long target = get_a_target_long();      
        timeStart = clock();        
        auto pItem = c.find(target);                                
        cout << "unordered_multimap.find(), milli-seconds : " << (clock()-timeStart) << endl;       
        if (pItem != c.end())
            cout << "found, value=" << (*pItem).second << endl;
        else
            cout << "not found! " << endl; 
    }
}

//----------------------------------------------------------------
#include <set>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace jj10
{
    void test_set(long& value)
    {
        cout << "\ntest_set()-----------\n";

        set<long> c;
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++)
        {
            try
            {
                c.insert(rand() / 65538);
            }
            catch(exception& p)
            {
                cout << "i = " << i << " " << p.what() << endl;
                abort();
            }
        } 

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
        cout << "set.size()= " << c.size() << endl;
        cout << "set.max_size()= " << c.max_size() << endl;

        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();
        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);    //比c.find()慢很多
            cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

            if(pItem != c.end())
                cout << "find, " << *pItem << endl << endl;
            else
                cout << "not find!" << endl << endl;
        }
        {
            timeStart = clock();
            auto pItem = c.find(target);    //比std::find()快很多
            cout << "set.find(), milli-seconds: " << (clock() - timeStart) << endl;

            if(pItem != c.end())
                cout << "find, " << *pItem << endl << endl;
            else
                cout << "not find!" << endl << endl;
        }
    }
}

//----------------------------------------------------------------
#include <map>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

namespace jj11
{
    void test_map(long& value)
    {
        cout << "\ntest_map()-----------\n";

        map<long, long> c;
        clock_t timeStart = clock();

        for(long i = 0; i < value; i++)
        {
            try
            {
                c.insert(pair<long, long>(i, rand() / 65538));
            }
            catch(exception& p)
            {
                cout << "i = " << i << " " << p.what() << endl;
                abort();
            }
        } 

        cout << "milli-seconds: " << (clock() - timeStart) << endl;
        cout << "map.size()= " << c.size() << endl;
        cout << "map.max_size()= " << c.max_size() << endl;

        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();
        
        timeStart = clock();
        auto pItem = c.find(target);    //比c.find()慢很多
        cout << "std::find(), milli-seconds: " << (clock() - timeStart) << endl;

        if(pItem != c.end())
            cout << "find, " << (*pItem).second << endl << endl;
        else
            cout << "not find!" << endl << endl;
    }  
} 

//----------------------------------------------------------------
#include <unordered_set>
#include <stdexcept>
#include <cstdlib> //abort()
#include <iostream>
#include <ctime> 

namespace jj12
{
    void test_unordered_set(long& value)
    {
        cout << "\ntest_unordered_set().......... \n";
        
        unordered_set<long> c;              
        clock_t timeStart = clock();     

        for(long i=0; i< value; ++i)
        {
            try 
            {
                c.insert(rand()/ 65538);                      
            }
            catch(exception& p) 
            {
                cout << "i=" << i << " " << p.what() << endl; 
                abort();
            }
        }
        cout << "milli-seconds : " << (clock()-timeStart) << endl;        
        cout << "unordered_set.size()= " << c.size() << endl; 
        cout << "unordered_set.max_size()= " << c.max_size() << endl;  //357913941
        cout << "unordered_set.bucket_count()= " << c.bucket_count() << endl; 
        cout << "unordered_set.load_factor()= " << c.load_factor() << endl;   
        cout << "unordered_set.max_load_factor()= " << c.max_load_factor() << endl;   
        cout << "unordered_set.max_bucket_count()= " << c.max_bucket_count() << endl;         
        for (unsigned i=0; i< 30; ++i) {
            cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
        }           
        
        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();  
        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);  //比 c.find(...) 慢很多 
            cout << "std::find(), milli-seconds : " << (clock()-timeStart) << endl;       
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;  
        }
        {
            timeStart = clock();        
            auto pItem = c.find(target);        //比 std::find(...) 快很多                          
            cout << "unordered_set.find(), milli-seconds : " << (clock()-timeStart) << endl;       
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;  
        }   
    }                                                            
}

//----------------------------------------------------------------
#include <unordered_map>
#include <stdexcept>
#include <cstdlib> //abort()
#include <iostream>
#include <ctime> 

namespace jj13
{
    void test_unordered_map(long& value)
    {
        cout << "\ntest_unordered_map().......... \n";
    
        unordered_map<long, long> c;    
        clock_t timeStart = clock(); 

        for(long i=0; i< value; ++i)
        {
            try 
            {
                //map可使用 [] 進行 insertion
                c[i] = rand() / 65538;         
            }
            catch(exception& p) 
            {
                cout << "i=" << i << " " << p.what() << endl; 
                abort();
            }
        }
        cout << "milli-seconds : " << (clock()-timeStart) << endl;        
        cout << "unordered_map.size()= " << c.size() << endl; //357913941
        cout << "unordered_map.max_size()= " << c.max_size() << endl; 

        cout << "\n\nInput a target that you want to search."<< endl;
        long target = get_a_target_long();      
        timeStart = clock();    
        //! auto pItem = find(c.begin(), c.end(), target);  //map 不適用 std::find()           
        auto pItem = c.find(target);
                         
        cout << "unordered_map.find(), milli-seconds : " << (clock()-timeStart) << endl;       
        if (pItem != c.end())
            cout << "found, value=" << (*pItem).second << endl;
        else
            cout << "not found! " << endl;      
    }                                                            
}

//----------------------------------------------------------------
#include <stack>   //栈是不可以迭代的，若可以迭代，这可以随机取出栈中的元素，这样不符合栈的数据结构
#include <stdexcept>
#include <cstdlib> //abort()
#include <iostream>
#include <ctime> 
namespace jj14
{
    void test_stack(long& value)
    {
        cout << "\ntest_stack().......... \n";
        
        stack<long> c;      //默认是以deque作为底部支撑         
        clock_t timeStart = clock();      

        for(long i=0; i<value; ++i)
        {
            try 
            {
                c.push(rand() / 65538);                        
            }
            catch(exception& p) 
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock()-timeStart) << endl;    
        cout << "stack.size()= " << c.size() << endl;
        cout << "stack.top()= " << c.top() << endl;   
        c.pop();
        cout << "stack.size()= " << c.size() << endl;
        cout << "stack.top()= " << c.top() << endl;

        {
            cout<< "\ntest_stack(), other function--------------\n";
            stack<char, list<char> > c;
            char num = 'a';

            for(int i = 0; i < 26; ++i)
            {
                c.push(num++);
            }

            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.top()= " << c.top() << endl;
            c.pop();
            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.top()= " << c.top() << endl;
        }

        {
            cout<< "\ntest_stack(), other function--------------\n";
            stack<char, vector<char> > c;
            char num = 'a';

            for(int i = 0; i < 26; ++i)
            {
                c.push(num++);
            }

            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.top()= " << c.top() << endl;
            c.pop();
            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.top()= " << c.top() << endl;
        }
    }
}

//----------------------------------------------------------------s
#include <queue>   //queue是不可以迭代的，若可以迭代，这可以随机取出栈中的元素，这样不符合queue的数据结构
#include <stdexcept>
#include <cstdlib> //abort()
#include <iostream>
#include <ctime> 
namespace jj15
{
    void test_queue(long& value)
    {
        cout << "\ntest_queue().......... \n";
        
        queue<long> c;           
        clock_t timeStart = clock();    

        for(long i=0; i< value; ++i)
        {
            try 
            {
                c.push(rand() / 65538);                        
            }
            catch(exception& p) 
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock()-timeStart) << endl;    
        cout << "queue.size()= " << c.size() << endl;
        cout << "queue.front()= " << c.front() << endl;
        cout << "queue.back()= " << c.back() << endl;
        c.pop();
        cout << "queue.front()= " << c.front() << endl;
        cout << "queue.back()= " << c.back() << endl;

        {
            cout<< "\ntest_stack(), other function--------------\n";
            queue<char, list<char> > c;
            char num = 'a';

            for(int i = 0; i < 26; ++i)
            {
                c.push(num++);
            }

            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.front()= " << c.front() << endl;
            cout << "stack.back= " << c.back() << endl;
            c.pop();
            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.front()= " << c.front() << endl;
            cout << "stack.back= " << c.back() << endl;
        }

        {
            cout<< "\ntest_stack(), other function--------------\n";
            queue<char, vector<char> > c;     //使用vector作为底层，不能实现queue
            char num = 'a';

            for(int i = 0; i < 26; ++i)
            {
                c.push(num++);
            }

            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.front()= " << c.front() << endl;
            cout << "stack.back= " << c.back() << endl;
            //c.pop();   //[Error] 'class std::vector<std::basic_string<char> >' has no member named 'pop_front'
            cout << "stack.size()= " << c.size() << endl;
            cout << "stack.front()= " << c.front() << endl;
            cout << "stack.back= " << c.back() << endl;
        }
    }
}

//----------------------------------------------------------------
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>
#include <hashtable.h>

namespace jj16
{
    void test_sizeof()
    {
        cout << "\ntest_components_sizeof().......... \n";
        cout << "这是64位机器下的输出结果，64位下指针大小为8"<< endl;
    
    //containers
    cout << "sizeof(array<int,100>)= " << sizeof(array<int,100>) << endl;     //400
    cout << "sizeof(vector<int>)= " << sizeof(vector<int>) << endl;               //24: 三根指针(_M_start, _M_finish, _M_end_of_storage)
    cout << "sizeof(list<int>)= " << sizeof(list<int>) << endl;                   //24: 两根指针加上数据(_M_next, _M_prev, _M_data)
    cout << "sizeof(forward_list<int>)= " << sizeof(forward_list<int>) << endl;   //8: 一根指针
    cout << "sizeof(deque<int>)= " << sizeof(deque<int>) << endl;             //80
    cout << "sizeof(stack<int>)= " << sizeof(stack<int>) << endl;             //80
    cout << "sizeof(queue<int>)= " << sizeof(queue<int>) << endl;             //80
    cout << "sizeof(set<int>)= " << sizeof(set<int>) << endl;                 //48
    cout << "sizeof(map<int,int>)= " << sizeof(map<int,int>) << endl;         //48
    cout << "sizeof(multiset<int>)= " << sizeof(multiset<int>) << endl;           //48
    cout << "sizeof(multimap<int,int>)= " << sizeof(multimap<int,int>) << endl;   //48
    cout << "sizeof(unordered_set<int>)= " << sizeof(unordered_set<int>) << endl;                 //56
    cout << "sizeof(unordered_map<int,int>)= " << sizeof(unordered_map<int,int>) << endl;         //56    
    cout << "sizeof(unordered_multiset<int>)= " << sizeof(unordered_multiset<int>) << endl;           //56
    cout << "sizeof(unordered_multimap<int,int>)= " << sizeof(unordered_multimap<int,int>) << endl;   //56
    cout << "sizeof(_Rb_tree<...>)= " << sizeof(_Rb_tree<int,int,_Identity<int>,less<int>>) << endl; //48
     
    //iterators
    cout << "sizeof(array<int,100>::iterator)= " << sizeof(array<int,100>::iterator) << endl;     //8
    cout << "sizeof(vector<int>::iterator)= " << sizeof(vector<int>::iterator) << endl;               //8
    cout << "sizeof(list<int>::iterator)= " << sizeof(list<int>::iterator) << endl;                   //8
    cout << "sizeof(forward_list<int>::iterator)= " << sizeof(forward_list<int>::iterator) << endl; //8
    cout << "sizeof(deque<int>::iterator)= " << sizeof(deque<int>::iterator) << endl;             //32: deque的迭代器里面有四根指针
    //! cout << "sizeof(stack<int>::iterator)= " << sizeof(stack<int>::iterator) << endl; //[Error] 'iterator' is not a member of 'std::stack<int>'     
    //! cout << "sizeof(queue<int>::iterator)= " << sizeof(queue<int>::iterator) << endl; //[Error] 'iterator' is not a member of 'std::queue<int>          
    cout << "sizeof(set<int>::iterator)= " << sizeof(set<int>::iterator) << endl;                 //8
    cout << "sizeof(map<int,int>::iterator)= " << sizeof(map<int,int>::iterator) << endl;         //8
    cout << "sizeof(multiset<int>::iterator)= " << sizeof(multiset<int>::iterator) << endl;           //8
    cout << "sizeof(multimap<int,int>::iterator)= " << sizeof(multimap<int,int>::iterator) << endl;   //8
    cout << "sizeof(unordered_set<int>::iterator)= " << sizeof(unordered_set<int>::iterator) << endl; //8 
    cout << "sizeof(unordered_map<int,int>::iterator)= " << sizeof(unordered_map<int,int>::iterator) << endl; //8 
    cout << "sizeof(unordered_multiset<int>::iterator)= " << sizeof(unordered_multiset<int>::iterator) << endl;   //8
    cout << "sizeof(unordered_multimap<int,int>::iterator)= " << sizeof(unordered_multimap<int,int>::iterator) << endl;   //8                                     
    cout << "sizeof(_Rb_tree<...>::iterator)= " << sizeof(_Rb_tree<int,int,_Identity<int>,less<int>>::iterator) << endl;  //8
    }
}

//----------------------------------------------------------------
#include <iostream>
#include <functional>  //std:: minus 
#include <numeric>     //std:: acculuate

namespace jj17
{
    int myfunc(int x, int y)
    {
        return x + 2*y;
    }

    struct myclass
    {
        int operator()(int x, int y)
        {
            return x + 3*y;
        }
    }myobj;

    void test_accumulate()
    {
        cout << "\ntest_accumulate().......... \n";
        int init = 50;
        int nums[] = {1, 2, 3};

        cout << "using default acculuate: ";
        cout << accumulate(nums, nums+3, init) << endl;  //56

        cout << "using functional's minus: ";
        cout << accumulate(nums, nums+3, init, minus<int>()) << endl;   //minus<int>()是仿函数, 44

        cout << "using functional's multiplies: ";
        cout << accumulate(nums, nums+3, init, multiplies<int>()) << endl; //300

        cout << "using myfunc: ";
        cout << accumulate(nums, nums+3, init, myfunc) << endl;  //62

        cout << "using myobj: ";
        cout << accumulate(nums, nums+3, init, myobj) << endl;  //68
    }
}

//----------------------------------------------------------------
#include <iostream>
#include <algorithm>  //std::for_each
#include <vector>

namespace jj18
{
    void myfunc(int i)
    {
        cout << " " << 2*i;
    }

    struct myclass
    {
        void operator()(int i)
        {
            cout << " " << 3*i - 10;
        }
    }myobj;

    void test_for_each()
    {
        cout << "\ntest_for_each().......... \n";
        vector<int> myvec;
        myvec.push_back(100);
        myvec.push_back(200);
        myvec.push_back(300);

        for_each(myvec.cbegin(), myvec.cend(), myfunc);  //对每一个元素做同样的事情，传入的函数就是对元素所做的操作
        cout << endl;

        for_each(myvec.cbegin(), myvec.cend(), myobj);
        cout << endl;
    }
}

//----------------------------------------------------------------
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
namespace jj19
{
    bool myfunc (int i, int j) { return i > j; }
    
    //这里没有融入到STL functor体系中，因为没有继承binary_function或unary_function这两个类
    //没有融入到STL体系中的话，在这一步是可以执行的，但是如果进行下一步操作可能就不行了
    struct myclass {
        bool operator() (int i, int j) { return i < j; }
    } myobj;
    
    bool test_sort()
    {   
        cout << "\ntest_sort().......... \n";   
        
        int myints[] = {32,71,12,45,26,80,53,33};
        vector<int> myvec(myints, myints+8);          // 32 71 12 45 26 80 53 33
        
        // using default comparison (operator <):
        sort(myvec.begin(), myvec.begin()+4);         //(12 32 45 71)26 80 53 33
        print_container(myvec);
        
        // using function as comp
        sort(myvec.begin()+4, myvec.end(), myfunc);   // 12 32 45 71(80 53 33 26)
        print_container(myvec);

        // using object as comp
        sort(myvec.begin(), myvec.end(), myobj);      //(12 26 32 33 45 53 71 80)
        print_container(myvec);
                
        // using reverse iterators and default comparison (operator <):
        sort(myvec.rbegin(), myvec.rend());           //output: 80 71 53 45 33 32 26 12
        print_container(myvec);      

        // using explicitly default comparison (operator <):
        sort(myvec.begin(), myvec.end(), less<int>());      //output: 12 26 32 33 45 53 71 80
        print_container(myvec);   
                
        // using another comparision criteria (operator >):
        sort(myvec.begin(), myvec.end(), greater<int>());   //output: 80 71 53 45 33 32 26 12
        print_container(myvec);              
    }
}

//----------------------------------------------------------------
#include <iostream>     // std::cout
#include <iterator>     // std::iterator_traits
namespace jj20
{   
    //以下全是函数重载
    void _display_category(random_access_iterator_tag)
    { cout << "random_access_iterator_tag" << endl; }

    void _display_category(forward_iterator_tag)
    { cout << "forward_iterator_tag" << endl; }
    
    void _display_category(bidirectional_iterator_tag)
    { cout << "bidirectional_iterator_tag" << endl; }

    void _display_category(input_iterator_tag)
    { cout << "input_iterator_tag" << endl; }

    void _display_category(output_iterator_tag)
    { cout << "output_iterator_tag" << endl; }

    template<typename I>
    void display_category(I itr)
    {   
        //若I为vector<int>::iterator类型，下面等价于typename vector<int>::iterator::iterator_category cagy
        typename iterator_traits<I>::iterator_category cagy;  //萃取机，I是一种迭代器class(例如: vector<int>:: iterator)
        //typename I::iterator_category cagy; //当I为array<int, ASIZE>::iteartor类型时不好使，因为array的迭代器仅仅是一根指针
        _display_category(cagy);
    }

    void test_iterator_category()
    {
        cout << "\ntest_iterator_category().......... \n";
        display_category(array<int, 10>::iterator());  //array的迭代器就是一根指针(未包装成class)
        display_category(vector<int>::iterator());   //后面加小括号表示创建了一个迭代器对象，这里是临时对象
        display_category(list<int>::iterator());
        display_category(forward_list<int>::iterator());
        display_category(deque<int>::iterator());

        display_category(set<int>::iterator());
        display_category(map<int,int>::iterator());
        display_category(multiset<int>::iterator());
        display_category(multimap<int,int>::iterator());
        display_category(unordered_set<int>::iterator());
        display_category(unordered_map<int,int>::iterator());
        display_category(unordered_multiset<int>::iterator());
        display_category(unordered_multimap<int,int>::iterator());      
                
        display_category(istream_iterator<int>());
        display_category(ostream_iterator<int>(cout,""));
    }
}

//----------------------------------------------------------------
#include <set>
#include <functional>  //std::_Identity
#include <iostream>
namespace jj21
{   
    void test_Rb_tree_int()
    {
        //G2.9 vs. G2.9 : 
        //rb_tree => _Rb_tree, 
        //identity<> => _Identity<>
        //insert_unique() => _M_insert_unique()
        //insert_equal() => _M_insert_equal()
        cout << "\ntest_Rb_tree_int().......... \n";

        //这里_Key为int，_Val为int，这表示没有值的部分，即_Val就是_Key
        _Rb_tree<int, int, _Identity<int>, less<int>> itree;
        cout << itree.empty() << endl;  //1
        cout << itree.size() << endl;   //0

        /*
            rb_tree提供两种insertion操作: _M_insert_unique()和_M_insert_equal()。
            前者表示节点的key一定在整个tree中独一无二，否则安插失败；后者表示节点的key可以重复
        */
        
        itree._M_insert_unique(3);
        itree._M_insert_unique(8);
        itree._M_insert_unique(5);
        itree._M_insert_unique(9);
        itree._M_insert_unique(13);
        itree._M_insert_unique(5);  //no effect, since using insert_unique().
        cout << itree.empty() << endl;  //0
        cout << itree.size() << endl;   //5
        cout << itree.count(5) << endl; //1
    
        itree._M_insert_equal(5);
        itree._M_insert_equal(5);
        cout << itree.size() << endl;   //7, since using insert_equal().
        cout << itree.count(5) << endl; //3
        
        for(auto item: itree)
        {
            cout << " " << item;
        }
        cout << endl;
    }

    void test_Rb_tree_char()
    {
        cout << "\ntest_Rb_tree_char().......... \n";
        _Rb_tree<char, char, _Identity<char>, greater<char>> itree;  //改变比较大小的方法

        itree._M_insert_unique('a');
        itree._M_insert_unique('c');
        itree._M_insert_unique('d');
        itree._M_insert_unique('f');
        itree._M_insert_unique('g');
        itree._M_insert_unique('d');  //no effect, since using insert_unique().
        cout << itree.size() << endl;     //5
        cout << itree.count('d') << endl; //1

        itree._M_insert_equal('d');
        itree._M_insert_equal('d');
        cout << itree.size() << endl;   //7, since using insert_equal().
        cout << itree.count('d') << endl; //3
        
        for(auto item: itree)
        {
            cout << " " << item;
        }
        cout << endl;
    }

    void test_Rb_tree_map()
    {
        cout << "\ntest_Rb_tree_map().......... \n";
        _Rb_tree<char, pair<char, string>, _Select1st<pair<char, string>>, less<char>> itree;

        itree._M_insert_unique(pair<char, string>('a', "apple"));
        itree._M_insert_unique(pair<char, string>('f', "fish"));
        itree._M_insert_unique(pair<char, string>('d', "damn"));
        itree._M_insert_unique(pair<char, string>('g', "gama"));
        itree._M_insert_unique(pair<char, string>('c', "cigarette"));
        itree._M_insert_unique(pair<char, string>('d', "damn"));  //no effect, since using insert_unique().
        itree._M_insert_unique(pair<char, string>('d', "duck"));  //no effect, since using insert_unique().(unique应保证key是独一无二的)
        cout << itree.size() << endl;     //5
        cout << itree.count('d') << endl; //1


        itree._M_insert_equal(pair<char, string>('d', "duck"));
        itree._M_insert_equal(pair<char, string>('d', "damn"));
        cout << itree.size() << endl;   //7, since using insert_equal().
        cout << itree.count('d') << endl; //3

        for(auto item: itree)
        {
            cout << " " << item.second;
        }
        cout << endl;
        
    }
    void test_Rb_tree()
    {
        cout << "\ntest_Rb_tree().......... \n";

        cout << "select test_Rb_tree function: \n";
        cout << "       (1)test_Rb_tree_int (2)test_Rb_tree_char (3)test_Rb_tree_map\n";
        int choice;
        cin >> choice;

        switch(choice)
        {
            case 1: test_Rb_tree_int();
                    break;
            case 2: test_Rb_tree_char();
                    break;
            case 3: test_Rb_tree_map();
                    break;
        }
    }
}

//----------------------------------------------------------------
#include <iostream>
namespace jj22
{
    void test_istream_ostream_iterator()
    {
        {
            cout << "\ntest_ostream_iterator().......... \n";

            list<string> c;
            c.push_back("apple");
            c.push_back("banana");
            c.push_back("cigarette");

            //ostream_iterator中实现了*, =，++等操作符的重载，从而实现输出
            copy(c.begin(), c.end(), ostream_iterator<string>(cout, ", ")); //将c中的数据打印到屏幕
            cout << endl;
        }

        {
            cout << "\ntest_istream_iterator().......... \n";

            double value1, value2;
            cout << "Please insert two values: ";
            istream_iterator<double> eos;  //只要没有初始值，那么就是end-of-stream iterator;
            istream_iterator<double> iit(cin); // stdin iterator;(这就相当于cin >> value)

            if(iit != eos) value1 = *iit;

            ++iit;  //输入下一个数字
            if(iit != eos) value2 = *iit;

            cout << value1 << "*" << value2 << "=" << (value1*value2) << endl;
        }
    }
}

//----------------------------------------------------------------
#include <iostream>
#include <unordered_set>
#include <functional>
namespace jj23
{
    template<typename T>
    inline void hash_combine(size_t& seed, const T& val)  //4
    {
        seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<typename T>
    inline void hash_val(size_t& seed, const T& val)   //3
    {
        hash_combine(seed, val);
    }

    template<typename T, typename... Types>
    inline void hash_val(size_t& seed, const T& val, const Types&... args)  //2
    {
        hash_combine(seed, val);
        hash_val(seed, args...);
    }

    //auxiliary generic function: 辅助泛型函数
    template<typename... Types>   //可变参数模板
    inline size_t hash_val(const Types&... args)     //1
    {
        size_t seed = 0;     
        hash_val(seed, args...);  //seed传进去的是引用，所以seed值改变了
        return seed;
    }


    class Customer
    {
        public:
            string fname;
            string lname;
            long no;
             
            Customer(string f, string l, long n): fname(f), lname(l), no(n) { }

            bool operator==(const Customer& c) const     //必须要写，因为unordered_set插入元素的时候，需要比较两者是否相等
            {
                return (this->fname == c.fname) && (this->lname == c.lname) && (this->no == c.no);
            }
    };  

    class CustomerHash   //这个类用来Customer对象的hashcode,这是一个万能hash函数
    {
        public:
            size_t operator()(const Customer& c) const
            {
                return hash_val(c.fname, c.lname, c.no);
            }
    };

    void test_hash_table()
    {
        cout << "\ntest_hash_table() using unordered_set.......... \n";

        unordered_set<Customer, CustomerHash> custset;
        custset.insert(Customer("Ace", "Hou", 1l));
        custset.insert(Customer("Sabri", "Hou", 2l));
        custset.insert(Customer("Stacy", "Chen", 3l));
        custset.insert(Customer("Mike", "Tseng", 4l));
        custset.insert(Customer("Paili", "Chen", 5l));
        custset.insert(Customer("Light", "Shiau", 6l));
        custset.insert(Customer("Shally", "Hwung", 7l));
        custset.insert(Customer("Ace", "Hou", 1l));      //相同的元素插不进去

        cout << "custset size: " << custset.size() << endl;
        cout << "custset current bucket_count: " << custset.bucket_count() << endl;

        CustomerHash hh;
        cout << "bucket position of Ace = " << hh(Customer("Ace", "Hou", 1l)) % custset.bucket_count() << endl;         //4
        cout << "bucket position of Sabri = " << hh(Customer("Sabri", "Hou", 2l)) % custset.bucket_count() << endl;     //10
        cout << "bucket position of Stacy = " << hh(Customer("Stacy", "Chen", 3l)) % custset.bucket_count() << endl;    //4
        cout << "bucket position of Mike = " << hh(Customer("Mike", "Tseng", 4l)) % custset.bucket_count() << endl;     //8
        cout << "bucket position of Paili = " << hh(Customer("Paili", "Chen", 5l)) % custset.bucket_count() << endl;    //1
        cout << "bucket position of Light = " << hh(Customer("Light", "Shiau", 6l)) % custset.bucket_count() << endl;   //10
        cout << "bucket position of Shally = " << hh(Customer("Shally", "Hwung", 7l)) % custset.bucket_count() << endl; //9

        for(int i = 0; i < custset.bucket_count(); i++)
        {
            cout << "bucket #" << i << " has " << custset.bucket_size(i) << endl;
        }

        {
            cout << "\ntest_hash_table() using unordered_map.......... \n";

            unordered_map<Customer, string, CustomerHash> custmap;
            custmap.insert(pair<Customer, string>(Customer("Ace", "Hou", 1l), "Ace Hou"));
            custmap.insert(pair<Customer, string>(Customer("Sabri", "Hou", 2l), "Sabri Hou"));
            custmap.insert(pair<Customer, string>(Customer("Stacy", "Chen", 3l), "Stacy Chen"));
            custmap.insert(pair<Customer, string>(Customer("Mike", "Tseng", 4l), "Mike Tseng"));
            custmap.insert(pair<Customer, string>(Customer("Paili", "Chen", 5l), "Paili Chen"));
            custmap.insert(pair<Customer, string>(Customer("Light", "Shiau", 6l), "Light Shiau"));
            custmap.insert(pair<Customer, string>(Customer("Shally", "Hwung", 7l), "Shally Hwung"));
            custmap.insert(pair<Customer, string>(Customer("Tom", "Paul", 8l), "Tom Paul"));
            custmap.insert(pair<Customer, string>(Customer("James", "Harden", 9l), "James Harden"));
            custmap.insert(pair<Customer, string>(Customer("Judith", "Crimes", 10l), "Judith Crimes"));
            custmap.insert(pair<Customer, string>(Customer("Stacy", "Chen", 3l), "stacy Chen"));   //key值相同，插不进去
            custmap.insert(pair<Customer, string>(Customer("Light", "Shiau", 11l), "Light Shiau"));   //key值不同，可以插进去
            cout << "custmap size: " << custmap.size() << endl;
            cout << "custmap current bucket_count: " << custmap.bucket_count() << endl;
            auto pItem = custmap.find(Customer("Mike", "Tseng", 4l));
            if(pItem != custmap.end())
                cout << "found, value = " << (*pItem).second << endl;
            else
                cout << "not found! " << endl; 
            }
    }
}

//---------------------------------------------------------------
#include <iostream>
#include <tuple>   //元组: 元之组合，数之组合
namespace jj24
{
    void test_tuple()
    {
        //tuples
        //create a four-element tuple
        //elements are initialized with default value(0 for fundamental:基本的 types)

        cout << "\ntest_tuple..........\n";
        tuple<int, float, string> t1(41, 3.2, "nico");
        //itreate over elements:
        cout << "t1: " << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1) << " " << endl;

        
        auto t2 = make_tuple(22, 44, "stacy");  //create tuple with make_tuple()
        get<1>(t1) = get<1>(t2);                //assign second value in t2 to t1

        if(t1 < t2)    //逐个元素比较(当两者元素个数一样时)
        {
            cout << "t1 < t2" << endl;
        }else
        {
            cout << "t1 >= t2" << endl;
        }
        t1 = t2;       //assigns value for value
        //cout << t1 << endl;  不能编译通过，因为tuple没有实现<<操作符重载

        tuple<int, int, string> t3(75, 2.56, "more light");
        int i1;
        float f1;
        string s1;
        tie(i1, f1, s1) = t3;    //assigns values of t3 to i1, f1 and s1
        cout << "i1= " <<i1<< " f1= "<< f1 << " s1= "<< s1 << endl; 
    }

}

//----------------------------------------------------------------
#include <iostream>
#include <type_traits>    //std::is_void<int>, ...
#include <typeinfo>     // typeid
namespace jj25
{
    template<typename T>
    void test_traits_output(const T x)
    {

        cout << "\ntest_traits_output..........\n";
        cout <<"\ntype traits for type: " << typeid(T).name() << endl; 

        cout << "is_void\t" << is_void<T>::value << endl;      //value就是回答真假值
        cout << "is_integral\t" << is_integral<T>::value << endl;
        cout << "is_floating_point\t" << is_floating_point<T>::value << endl;
        //若T为算术类型（即整数类型(包括char)或浮点数类型）value为true，对于任何其他类型，value为false
        cout << "is_arithmetic\t" << is_arithmetic<T>::value << endl;    //arithmetic: 算术、算法
        cout << "is_signed\t" << is_signed<T>::value << endl;
        cout << "is_unsigned\t" << is_unsigned<T>::value << endl;
        cout << "is_const\t" << is_const<T>::value << endl;    //在这个示例中，T永远不会是const类型
        cout << "is_const<const T>\t" << is_const<const T>::value << endl; 
        cout << "is_volatile\t" << is_volatile<T>::value << endl;
        cout << "is_class\t" << is_class<T>::value << endl;
        cout << "is_function\t" << is_function<T>::value << endl;
        cout << "is_reference\t" << is_reference<T>::value << endl;
        cout << "is_lvalue_reference\t" << is_lvalue_reference<T>::value << endl;
        cout << "is_rvalue_reference\t" << is_rvalue_reference<T>::value << endl;
        cout << "is_pointer\t" << is_pointer<T>::value << endl;
        cout << "is_member_pointer\t" << is_member_pointer<T>::value << endl;
        cout << "is_member_object_pointer\t" << is_member_object_pointer<T>::value << endl;
        cout << "is_member_function_pointer\t" << is_member_function_pointer<T>::value << endl;
        cout << "is_fundamental\t" << is_fundamental<T>::value << endl;      //基础类型

        //标识T是否是标量类型的特征类。标量类型是一种类型，它具有内置的加法运算符功能，并且没有重载
        cout << "is_scalar\t" << is_scalar<T>::value << endl;

        //is_object: Trait class that identifies whether T is an object type. An object type is a type with storage 
        //associated to it, which includes all types except functions, references and void.
        cout << "is_object\t" << is_object<T>::value << endl;

        //判断T是否是复合类型(即: 数组、函数、对象指针、函数指针、成员对象指针、成员函数指针、引用、类、联合或枚举),是则value=true，对于其他类型value=false
        cout << "is_compound\t" << is_compound<T>::value << endl;           //compound: 复合的     

        cout << "is_standard_layout\t" << is_standard_layout<T>::value << endl;
        cout << "is_pod\t" << is_pod<T>::value << endl;         //pod: Plain Old Data(普通旧数据类型，是c++的一种数据类型概念)
        cout << "is_literal_type\t" << is_literal_type<T>::value << endl;
        cout << "is_empty\t" << is_empty<T>::value << endl;
        //polymorphic: 多态的，A polymorphic class is a class that declares or inherits a virtual function
        cout << "is_polymorphic\t" << is_polymorphic<T>::value << endl; 
        cout << "is_abstract\t" << is_abstract<T>::value << endl;
        cout << "has_virtual_destructor\t" << has_virtual_destructor<T>::value << endl;      //有虚析构函数
        cout << "is_default_constructible\t" << is_default_constructible<T>::value << endl;   //默认构造
        cout << "is_copy_constructible\t" << is_copy_constructible<T>::value << endl;      //拷贝构造
        cout << "is_move_constructible\t" << is_move_constructible<T>::value << endl;      //移动构造
        cout << "is_copy_assignable\t" << is_copy_assignable<T>::value << endl;         //拷贝赋值
        cout << "is_move_assignable\t" << is_move_assignable<T>::value << endl;         //移动赋值
        cout << "is_destructible\t" << is_destructible<T>::value << endl; 
        cout << "is_trivial\t" << is_trivial<T>::value << endl; 
        cout << "is_trivially_destructible\t" << is_trivially_destructible<T>::value << endl; 
        cout << "is_nothrow_default_constructible\t" << is_nothrow_default_constructible<T>::value << endl; 
        cout << "is_nothrow_copy_constructible\t" << is_nothrow_copy_constructible<T>::value << endl;
        cout << "is_nothrow_move_constructible\t" << is_nothrow_move_constructible<T>::value << endl;
        cout << "is_nothrow_copy_assignable\t" << is_nothrow_copy_assignable<T>::value << endl; 
        cout << "is_nothrow_move_assignable\t" << is_nothrow_move_assignable<T>::value << endl; 
    }

    void test_is_arithmetic()
    {
        class A{ };
        cout << "\ntest_is_arithmetic..........\n";

        cout << "A\t" << is_arithmetic<A>::value << '\n';
        cout << "bool\t" << is_arithmetic<bool>::value << '\n';
        cout << "int\t" << is_arithmetic<int>::value << '\n';
        cout << "const int\t" << is_arithmetic<const int>::value << '\n';
        cout << "int&\t" << is_arithmetic<int&>::value << '\n';
        cout << "int*\t" << is_arithmetic<int*>::value << '\n';
        cout << "float\t" << is_arithmetic<float>::value << '\n';
        cout << "const float\t" << is_arithmetic<const float>::value << '\n';
        cout << "float&\t" << is_arithmetic<float&>::value << '\n';
        cout << "float*\t" << is_arithmetic<float*>::value << '\n';
        cout << "char\t" << is_arithmetic<char>::value << '\n';
        cout << "const char\t" << is_arithmetic<const char>::value << '\n';
        cout << "char&\t" << is_arithmetic<char&>::value << '\n';
        cout << "char*\t" << is_arithmetic<char*>::value << '\n';
    }

    void tets_is_pointer_or_reference()
    {
        cout << "\ntest_is_pointer..........\n";
        cout << "double\t" << is_pointer<double>::value << '\n';
        cout << "double*\t" << is_pointer<double*>::value << '\n';

        cout << "\ntest_is_reference..........\n";
        cout << "double\t" << is_reference<double>::value << '\n';
        cout << "double&\t" << is_reference<double&>::value << '\n';
    }
}


//----------------------------------------------------------------
#include <cstdlib>    //rand() and RAND_MAX
namespace jjxx{

    /*
        该函数用来选择容器
    */
    void test_container()
    {
        int choice;
        long value;  
     
        srand(time(NULL));
    
        cout << "\n\ntest_containers()......... \n";
        cout << "select: \n";
        cout << "       (1)array (2)vector (3)list (4)forward_list (5)deque (6)multiset \n";
        cout << "       (7)multimap (8)unordered_multiset (9)unordered_multimap (10)set \n";
        cout << "       (11)map (12)unordered_set (13)unordered_map (14)stack (15)queue (16)sizeof\n"; 
        cout << " (2),(3),(5),(6),(8) will test also moveable elements. \n"; 
        cin >> choice;
        if ( choice != 1 && choice != 16) {    //1 ==> array, use ASIZE
            cout << "how many elements: ";
            cin >> value;         
        }
    
        switch (choice) 
        {
            case 1 :    jj01::test_array();     
                        break;
            case 2 :    jj02::test_vector(value);   
                        //jj02::test_vector_with_move(value);   
                        break;      
            case 3 :    jj03::test_list(value);
                        break;      
            case 4 :    jj04::test_forward_list(value); 
                        break;      
            case 5 :    jj05::test_deque(value);        
                        break;      
            case 6 :    jj06::test_multiset(value); 
                        break;      
            case 7 :    jj07::test_multimap(value); 
                        break;          
            case 8 :    jj08::test_unordered_multiset(value);       
                        break;      
            case 9 :    jj09::test_unordered_multimap(value);   
                        break;  
            case 10:    jj10::test_set(value);    
                        break;                      
            case 11 :   jj11::test_map(value);  
                        break;          
            case 12 :   jj12::test_unordered_set(value);        
                        break;      
            case 13 :   jj13::test_unordered_map(value);
                        break;          
            case 14 :   jj14::test_stack(value);        
                        break;      
            case 15 :   jj15::test_queue(value);    
                        break; 
            case 16 :   jj16::test_sizeof();    
                        break;                                                              
            default: 
                        break;      
        }
    }
}

int main(int argc, char const *argv[])
{
    class Foo
    {
        private:
            int d1, d2;
    };

    class Goo
    {
        private:
            int d1, d2;
        public:
            ~Goo(){ };
    };

    class Zoo
    {
        private:
            int d1, d2;
        public:
            Zoo(int i1, int i2): d1(i1), d2(i2){ }    //当写了一个构造函数时，编译器就不会给类一个默认的构造函数
            Zoo(const Zoo&) = delete;                 //拷贝构造=delete表明不存在拷贝构造函数
            Zoo(const Zoo&&);

            Zoo& operator=(const Zoo&);               //拷贝赋值
            Zoo& operator=(const Zoo&&) = delete;     //搬移赋值

            virtual ~Zoo(){ };   
    };

    jjxx::test_container(); 

    jj17::test_accumulate();
    jj18::test_for_each();
    jj19::test_sort();
    jj20::test_iterator_category();
    jj21::test_Rb_tree();
    jj22::test_istream_ostream_iterator();
    jj23::test_hash_table();
    jj24::test_tuple();

    cout << "\nselect test traits function: \n";
    cout << "       (1)test_traits_output(int(2)) (2)test_traits_output(char('a')) (3)test_traits_output(\"12345\")\n";
    cout << "       (4)test_traits_output(string(\"12345\")) (5)test_traits_output(double(2.345)) (6)test_traits_output(Foo())\n";
    cout << "       (7)test_traits_output(Goo()) (8)test_traits_output(Zoo(3, 4)) (9)test_is_arithmetic() (10)tets_is_pointer_or_reference() \n";

    int choice;
    cin >> choice;
    switch(choice)
    {
        case 1: jj25::test_traits_output(int(2));     //int(1): 是临时变量
                break;
        case 2: jj25::test_traits_output(char('a'));     
                break;
        case 3: jj25::test_traits_output("12345");     
                break;
        case 4: jj25::test_traits_output(string("12345"));     
                break;
        case 5: jj25::test_traits_output(double(2.345));     
                break;
        case 6: jj25::test_traits_output(Foo());     //使用默认构造函数
                break;
        case 7: jj25::test_traits_output(Goo());     //使用默认构造函数
                break;
        case 8: jj25::test_traits_output(Zoo(3, 4));     
                break;
        case 9: jj25::test_is_arithmetic();     
                break;
        case 10: jj25::tets_is_pointer_or_reference();     
                break;
        default: 
                break;
        /*
            想要测试其他数据类型，可以继续添加
        */
    }
    return 0;
}
