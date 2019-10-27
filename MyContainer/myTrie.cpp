#include <iostream>
using namespace std;


/*
    实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。

    示例:

    Trie trie = new Trie();

    trie.insert("apple");
    trie.search("apple");   // 返回 true
    trie.search("app");     // 返回 false
    trie.startsWith("app"); // 返回 true
    trie.insert("app");   
    trie.search("app");     // 返回 true

*/

class Trie{    //字典树

public:
    /** Initialize your data structure here. */
    Trie() {
        isWord = false;
        for(int i = 0; i < 26; i++){
            child[i] = nullptr;
        }
    }

    ~Trie(){
        for(int i = 0; i < 26; i++){
            if(child[i] != nullptr)
                delete child[i];
        }
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* t = this;
        for(const char c: word){
            if(t->child[c - 'a'] == nullptr)
                t->child[c - 'a'] = new Trie();
            t = t->child[c - 'a'];
        }
        t->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* t = this;
        for(const char c: word){
            if(t->child[c - 'a'] == nullptr)
                return false;
            t = t->child[c - 'a'];
        }
        return t->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* t = this;
        for(const char c: prefix){
            if(t->child[c - 'a'] == nullptr)
                return false;
            t = t->child[c - 'a'];
        }
        return true;
    }

private:
    Trie* child[26];
    bool isWord;
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
