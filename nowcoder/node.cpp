#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;


struct ListNode{        //链表节点的结构
    int val; 
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

struct TreeNode{       //二叉树节点的结构
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};


class Tree_solution{
public:
    /*
        二叉树，求根节点至某节点路径(实现)
    */
    void path_to_node(TreeNode *root, vector<TreeNode*> &path, vector<TreeNode*> &res,
                    TreeNode *search, int &flag){
        /*
            path: 临时存放路径
            res: 根节点至search节点路径
            search: 要寻找的节点
            flag: 标志位，0:没找到节点， 1: 找到节点
        */
        if(!root || flag){   //节点为空或者找到则return
            return;
        }
        path.push_back(root);
        if(root == search){
            flag = 1;
            res = path;
        }
        path_to_node(root->left, path, res, search, flag);
        path_to_node(root->right, path, res, search, flag);
        path.pop_back();  //回溯
    }

    /*
        二叉树(Binary Tree)的最近公共祖先
        找到p, q两个节点的最近公共祖先
    */
    TreeNode* lowestCommonAncestor_1(TreeNode *root, TreeNode *p, TreeNode *q){
        vector<TreeNode*> path;      //暂时存储路径
        vector<TreeNode*> node_p_path;
        vector<TreeNode*> node_q_path;
        int flag = 0;
        path_to_node(root, path, node_p_path, p, flag);
        path.clear();
        flag = 0;
        path_to_node(root, path, node_q_path, q, flag);
        
        int path_len = node_p_path.size() < node_q_path.size()? node_p_path.size(): node_q_path.size();

        TreeNode *res = NULL;
        for(int i = 0; i < path_len; i++){
            if(node_p_path[i]->val == node_q_path[i]->val){
                res = node_p_path[i];
            }
        }
        return res;
    }

    /*
        二叉搜索树(BST)的最近公共祖先
        找到p, q两个节点的最近公共祖先
    */
    TreeNode* lowestCommonAncestor_2(TreeNode *root, TreeNode *p, TreeNode *q){
        int root_val = root->val;
        int p_val = p->val;
        int q_val = q->val;

        if(p_val < root_val && q_val < root_val){
            return lowestCommonAncestor_2(root->left, p, q);
        }else if(p_val > root_val && q_val > root_val){
            return lowestCommonAncestor_2(root->right, p, q);
        }else{
            return root;
        }
    }

    /*
        二叉树的前序遍历（非递归）
    */
    vector<int> preorder(TreeNode *root){
        vector<int> res;
        stack<TreeNode*> stack;

        if(!root)
            return res;
        stack.push(root);
        while(!stack.empty()){
            TreeNode *cur = stack.top();
            stack.pop();
            res.push_back(cur->val);

            if(cur->right)
                stack.push(cur->right);
            if(cur->left)
                stack.push(cur->left);
        }
        return res;
    }

    /*
        二叉树的后序遍历（非递归）
    */
    vector<int> postorder(TreeNode *root){
        vector<int> res;
        stack<TreeNode*> stack;
        if(!root){
            return res;
        }

        stack.push(root);
        while(!stack.empty()){
            TreeNode *node = stack.top();
            stack.pop();
            res.push_back(node->val);

            if(node->left){
                stack.push(node->left);
            }
            if(node->right){
                stack.push(node->right);
            }
        }
        return res;
    }

    /*
        二叉树的中序遍历（非递归）
    */
    vector<int> inorder(TreeNode *root){
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode* cur = root;

        while(cur || !s.empty()){
            while(cur){
                s.push(cur);
                cur = cur->left;
            }

            cur = s.top();
            s.pop();
            res.push_back(cur->val);
            cur = cur->right;
        }
        return res;
    }

 
    /*
        二叉树的层次遍历
    */
    vector<vector<int> > level_order(TreeNode *root){
        queue<TreeNode*> que;      //使用队列
        vector<vector<int> > res;

        if(!root){   //root为空，直接返回
            return res;
        }

        que.push(root);
        int depth = 0;
        while (!que.empty()){
            vector<int> temp;
            res.push_back(temp);

            int que_len = que.size();
            for(int i = 0; i < que_len; i++){
                TreeNode *node = que.front();
                que.pop();
                res[depth].push_back(node->val);

                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            depth++;
        }
        return res; 
    }

    /*
        二叉树的锯齿形层次遍历:
        输入:
            3
           / \
          9  20
             / \
            15  7
        
        输出:
            [
                [3],
                [20, 9],
                [15, 7]
            ]
    */
    vector<vector<int> > zigzagLevelOrder(TreeNode* root){
       //与上一题一样，这题遇到depth为奇数的情况，翻转一下vec;
       vector<vector<int> > res;
       queue<TreeNode*> que;

       if(!root)
            return res;

        que.push(root);
        int depth = 0;
        while(!que.empty()){
            vector<int> temp;
            res.push_back(temp);

            int que_len = que.size();
            for(int i = 0; i < que_len; i++){
                TreeNode* node = que.front();
                temp.push_back(node->val);
                que.pop();

                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);

                if((depth % 2) == 1)
                    reverse(temp.begin(), temp.end());
            }
            depth++;
        } 

        for(int i = 0; i < res.size(); i++){
            if(i % 2 == 1)
                reverse(res[i].begin(), res[i].end());
        }
        return res;
   }

   /*
        二叉树的最大深度
        递归解法
   */
    int maxDepth_1(TreeNode* root){
        if(!root)
            return 0;
        int maxLeft = maxDepth_1(root->left);
        int maxRight = maxDepth_1(root->right);
        return 1 + max(maxLeft, maxRight);
  }

    int maxDepth_2(TreeNode* root){
        stack<pair<TreeNode*, int> > s;     //栈中的元素为节点与深度的键值对

        if(root)
            s.push(pair<TreeNode*, int>(root, 1));
     
        int depth = 0;
        while(!s.empty()){
            pair<TreeNode*, int> cur = s.top();
            s.pop();
            TreeNode* node = cur.first;
            int cur_depth = cur.second;

            if(node){
                depth = max(depth, cur_depth);
                if(node->left) s.push(pair<TreeNode*, int>(node->left, cur_depth + 1));
                if(node->right) s.push(pair<TreeNode*, int>(node->right, cur_depth + 1));
            }
        }
        return depth;
    }

    /*
        二叉树的最小深度
    */
    int minDepth(TreeNode* root){
        if(root == NULL) return 0;

        int minLeft = minDepth(root->left);
        int minRight = minDepth(root->right);
        
        //1.如果左孩子和右孩子有为空的情况，直接返回m1+m2+1(m1和m2中有一个为0)
        //2.如果都不为空，返回较小深度+1
        return root->left == NULL || root->right == NULL? minLeft + minRight + 1: 1 + min(minLeft, minRight);
    }

    /*
        相同的树
    
    */
    bool isSameTree(TreeNode* p, TreeNode* q){
        if(p == NULL && q == NULL) return true;
        if(p == NULL || q == NULL) return false;

        if(p->val != q->val)
            return false;
        
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
   
    /*
        将有序数组转换为二叉搜索树
    */
    TreeNode* sortedArrayToBST(vector<int>& nums){
        if(nums.size() == 0 || nums.empty())
            return NULL;
        return helper(nums, 0, nums.size() - 1);
    }

    /*
        二分找最大值
    */
    TreeNode* helper(vector<int>& nums, int left, int right){
        if(left > right)
            return NULL;
        
        int center = (left + right + 1) / 2;
        TreeNode *root = new TreeNode(nums[center]);

        root->left = helper(nums, left, center - 1);
        root->right = helper(nums, center + 1, right);
        return root; 
    }

    /*
        二叉树展开为链表
        
    */
    void flatten(TreeNode* root){

    }
    
    /*
        翻转二叉树
    */
    TreeNode* invertTree(TreeNode* root){   
        if(root == NULL)
            return NULL;    
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }

   /*
        二叉树的所有路径
        示例:
        输入:
          1
         / \
        2   3
         \
          5
        输出: ["1->2->5", "1->3"]
   */
    vector<string> binaryTreePaths(TreeNode* root){
        vector<string> res;
        dfs(root, res, "");
        return res;
    }

    void dfs(TreeNode* root, vector<string>& res, string path){   //一定要传引用!!!!!!!!!
        if(root == NULL)
            return;
        if(path.empty())
            path.append(to_string(root->val));
        else {
            path.append("->");
            path.append(to_string(root->val));
        }
            
        if((root->left == NULL) && (root->right == NULL)){
            res.push_back(path);
        }
            
        dfs(root->left, res, path);
        dfs(root->right, res, path);
    }

    /*
        两数之和：输入BST
        给定一个二叉搜索树和一个目标结果，如果BST中存在两个元素且它们的和等于给定的目标结果，则返回true，否者返回false。

        案例 1:

        输入: 
            5
           / \
          3   6
         / \   \
        2   4   7

        Target = 9
        输出: True
    */

    bool findTarget(TreeNode* root, int k){  //常见做法：中序遍历+双指针
        vector<int> nums;
        inorder(root, nums);

        int i = 0, j = nums.size() - 1;
        while(i < j){
            if(nums[i] + nums[j] == k)
                return true;
            else if(nums[i] + nums[j] > k)
                j--;
            else 
                i++;
        } 
        return false;
    }

    void inorder(TreeNode* root, vector<int>& nums){  //中序遍历的递归方法
        if(!root) return;
        inorder(root->left, nums);
        nums.push_back(root->val);
        inorder(root->right, nums);
    }

    /*
        合并二叉树：
        示例 1:

        输入: 
            Tree 1                     Tree 2                  
                 1                         2                             
                / \                       / \                            
               3   2                     1   3                        
              /                           \   \                      
             5                             4   7                  
        输出: 
        合并后的树:
                 3
                / \
               4   5
              / \   \ 
             5   4   7

        注意: 合并必须从两个树的根节点开始。
    */
    TreeNode* mergeTrees(TreeNode* p, TreeNode* q){  //合并的两棵树的深度必须相同
        if(!p) return NULL;
        if(!q) return NULL;

        TreeNode* root = new TreeNode(p->val + q->val);
        root->left = mergeTrees(p->left, q->left);
        root->right = mergeTrees(p->right, q->right);
        return root;
    }
};


class List_solution{
public:
    /*
        删除链表的倒数第N个节点
        给定一个链表: 1->2->3->4->5, 和 n = 2.
        当删除了倒数第二个节点后，链表变为 1->2->3->5.

        方法：使用两个指针，第一个先走n + 1步，然后second再走，两者始终保持n的距离
    */
    ListNode* removeNthFromEnd(ListNode* head, int n){
        ListNode* dummy = new ListNode(0);    //dummy节点防止   
        dummy->next = head;
        ListNode* first = dummy;
        ListNode* second = dummy;

        for(int i = 0; i < n + 1; i++){  //fisrt先移动n + 1步
            first = first->next;
        }
        while(first){
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        return dummy->next;
    }


    /*
        合并k个排序链表
        输入:
            [
            1->4->5,
            1->3->4,
            2->6
            ]
        输出: 1->1->2->3->4->4->5->6

        方法：将k*n个节点
    */
    static int comp (const void* a, const void* b){     //当 comp函数写在类外面时，不用申明为静态函数。
        return (*(ListNode *)a).val < (*(ListNode *)b).val;
    }

    ListNode* mergeKLists(vector<ListNode*> lists){

        vector<ListNode*> node_vec;
        for(int i = 0; i < lists.size(); i++){
            ListNode *head = lists[i];
            while(head != nullptr){
                node_vec.push_back(head);
                head = head->next;
            }
        }
        if(node_vec.size() == 0)    
            return NULL;
        
        sort(node_vec.begin(), node_vec.end(), comp);
        for(int i = 1; i < node_vec.size(); i++){
            node_vec[i - 1]->next = node_vec[i];
        }
        node_vec[node_vec.size() - 1]->next = NULL;
        return node_vec[0];
    }

    /*
        k个一组翻转链表 
        示例 :
            给定这个链表：1->2->3->4->5
            当 k = 2 时，应当返回: 2->1->4->3->5
            当 k = 3 时，应当返回: 3->2->1->4->5
    */
    ListNode* reverseKGroup(ListNode* head, int k){

    }

    /*
        两数相加
        示例：
            输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
            输出：7 -> 0 -> 8
            原因：342 + 465 = 807

    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;

        int carry = 0;
        while(l1 || l2){
            int sum = (!l1? 0: l1->val) + (!l2? 0: l2->val) + carry;

            cur->next = new ListNode(sum % 10);
            cur = cur->next;
            carry = sum / 10;

            l1 = !l1? l1: l1->next;
            l2 = !l2? l2: l2->next;
        }
        if(carry == 1)
            cur->next = new ListNode(carry);

        return dummy->next;
    }

    /*
        合并两个有序链表
            输入：1->2->4, 1->3->4
            输出：1->1->2->3->4->4
    */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;

        while(l1 && l2){    //两者都不为空指针时
            bool flag = l1->val < l2->val;
            cur->next = flag? l1: l2;
            cur = cur->next;

            l1 = flag? l1->next: l1;
            l2 = flag? l2: l2->next;
        }

        cur->next = l1 == NULL? l2: l1;
        return dummy->next;
    }

   /*
        相交链表：
            编写一个程序，找到两个单链表相交的起始节点

   */
   ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
       //双指针
       if(headA == NULL || headB == NULL) return NULL;
       ListNode* p1 = headA, *p2 = headB;
    
        while(p1 != p2){
            p1 = p1 == NULL? headB: p1->next;
            p2 = p2 == NULL? headA: p2->next;
        }
        return p1;
   }

   /*
        旋转链表：
            给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

            示例 1:

            输入: 1->2->3->4->5->NULL, k = 2
            输出: 4->5->1->2->3->NULL
            解释:
            向右旋转 1 步: 5->1->2->3->4->NULL
            向右旋转 2 步: 4->5->1->2->3->NULL

            示例 2:

            输入: 0->1->2->NULL, k = 4
            输出: 2->0->1->NULL
            解释:
            向右旋转 1 步: 2->0->1->NULL
            向右旋转 2 步: 1->2->0->NULL
            向右旋转 3 步: 0->1->2->NULL
            向右旋转 4 步: 2->0->1->NULL

   */
    ListNode* roateRight(ListNode* head, int k){
        if(head == NULL) return NULL;
        if(head->next == NULL) return head;

        int len = 1;
        ListNode* old_tail = head; 
        while(old_tail->next != NULL){
            old_tail = old_tail->next;
            len++;
        }
        old_tail->next = head;   //形成环形链表

        ListNode* new_tail = head;
        for(int i = 0; i < len - k%len - 1; i++){
            new_tail = new_tail->next;
        }
        ListNode* new_head = new_tail->next;
        new_tail->next = NULL;

        return new_head;
    }

    /*
        排序链表：
            在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

            示例 1:

            输入: 4->2->1->3
            输出: 1->2->3->4

            示例 2:

            输入: -1->5->3->4->0
            输出: -1->0->3->4->5
    */
   ListNode* sortList(ListNode* head){
       if(!head || !head->next)  return head;

       ListNode* slow = head;
       ListNode* fast = head;
       ListNode* temp;

       while(fast != NULL && fast->next != NULL){
           temp = slow;
           slow = slow->next;
           fast = fast->next->next;
       }
       temp->next = NULL;
       ListNode* l = sortList(head);
       ListNode* r = sortList(slow);
       return mergeSort(l, r);
   }

   /*
        两两交换链表中的节点:
            给定 1->2->3->4, 你应该返回 2->1->4->3 
    */
   ListNode* swapParis(ListNode* head){
       if(!head) return head;

       ListNode* dummy = new ListNode(0);
       dummy->next = head;
       ListNode* cur = dummy;

       while(cur->next && cur->next->next){
           ListNode* p1 = cur->next;
           ListNode* p2 = cur->next->next;
           cur->next = p1->next;
           p1->next = p2->next;
           p2->next = p1;
           cur = p1;
       }
       return dummy->next;
   }

    /*
        反转链表：

    */
   ListNode* reverseList(ListNode* head){
       if(head == nullptr) return NULL;

        ListNode *dummyNode = new ListNode(0);
        dummyNode->next = head;
        while(head != NULL && head->next != NULL){
            ListNode *cur = head->next;
            head->next = cur->next;
            cur->next = dummyNode->next;
            dummyNode->next = cur;
        }
        return dummyNode->next;
   }

   /*
        奇偶链表：
            给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，
            而不是节点的值的奇偶性。

            请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。

            示例 1:

            输入: 1->2->3->4->5->NULL
            输出: 1->3->5->2->4->NULL



            示例 2:

            输入: 2->1->3->5->6->4->7->NULL 
            输出: 2->3->6->7->1->5->4->NULL

   */
  ListNode* oddEvenList(ListNode* head){
      if(!head) return head;

      ListNode* odd = head;
      ListNode* even = head->next;
      ListNode* evenHead = even;

      while (even || even->next){
          odd = even->next;
          odd = odd->next;
          even = odd->next;
          even = even->next;
      }
      odd->next = evenHead;
      return head;
  }


private:
    ListNode* mergeSort(ListNode* l, ListNode* r){
        /*
            l,r要是排好序的链表
        */
        if(l == NULL) return r;
        if(r == NULL) return l;

        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;

        while(l && r){
            if(l->val <= r->val){
                cur->next = l;
                cur = cur->next;
                l = l->next;
            }else{
                cur->next = r;
                cur = cur->next;
                r = r->next;
            }
        }
        if(l){
            cur->next = l;
        }
        if(r){
            cur->next = r;
        }

        return dummy->next;
    }
};


int main(int argc, char const *argv[])
{   
    // /*
    //     二叉树结构:
    //            6
    //           / \
    //          2   8
    //         / \ / \
    //        0  4 7  9
    //          / \
    //         3   5
    // */
    // TreeNode a(6), b(2), c(8), d(0), e(4), f(7), g(9), h(3), i(5);
    // a.left = &b, a.right = &c;
    // b.left = &d, b.right = &e;
    // c.left = &f, c.right = &g;
    // e.left = &h, e.right = &i;


    // /*
    //     二叉树结构:
    //         2
    //        / \
    //       1   3
    //        \   \
    //         4   7
    // */
    // TreeNode node_1(2), node_2(1), node_3(3), node_4(4), node_5(7);
    // node_1.left = &node_2, node_1.right = &node_3;
    // node_2.right = &node_4, node_3.right = &node_5;

    

    /*
        链表结构:
            3->7->2->1->2->1
    */
    ListNode l1_0(3), l1_1(7), l1_2(2),l1_3(1),l1_4(2), l1_5(1);
    l1_0.next = &l1_1, l1_1.next = &l1_2, l1_2.next = &l1_3;
    l1_3.next = &l1_4, l1_4.next = &l1_5;

    /*
        链表结构:
            4->4->5
    */
    ListNode l2_0(4), l2_1(4),l2_2(5);
    l2_0.next = &l2_1, l2_1.next = &l2_2;

    /*
        链表结构:
            1->3->4
    */
    ListNode l3_0(1), l3_1(3), l3_2(4);
    l3_0.next = &l3_1, l3_1.next = &l3_2;

    List_solution l_s;
    ListNode* res = l_s.swapParis(&l1_0);
    while(res != NULL){
        cout << res->val << "->";
        res = res->next;
    }
}
