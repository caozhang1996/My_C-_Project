#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


class Solution{
public:
    /*
        编写一个程序判断给定的数是否为丑数。

        丑数就是只包含质因数 2, 3, 5 的正整数。

        示例 1:

        输入: 6
        输出: true
        解释: 6 = 2 × 3

        示例 2:

        输入: 8
        输出: true
        解释: 8 = 2 × 2 × 2

        示例 3:

        输入: 14
        输出: false 
        解释: 14 不是丑数，因为它包含了另外一个质因数 7。

        说明：

            1 是丑数。
            输入不会超过 32 位有符号整数的范围: [−231,  231 − 1]。
    */
    bool isUgly(int num){
        if(num == 0){
            return false;
        }
        while(num != 1){
            if(num % 2 == 0){
                num /= 2;
            }else if(num % 3 == 0){
                num /= 3;
            }else if(num % 5 == 0){
                num /= 5;
            }else
            {
                return false;
            }
            
        }

        return true;
    }

    /*
        编写一个程序，找出第 n 个丑数。

        丑数就是只包含质因数 2, 3, 5 的正整数。

        示例:

        输入: n = 10
        输出: 12
        解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。

        说明:  

            1 是丑数。
            n 不超过1690。
    */
    int nthUglyNumber(int n){    //三指针法
        int res[n];
        res[0] = 1;

        //三个指针用于记录丑数的位置
        int i2 = 0, i3 = 0, i5 = 0;
        for(int i = 1; i < n; i++){
            int n2 = res[i2] * 2; 
            int n3 = res[i3] * 3;
            int n5 = res[i5] * 5;
            res[i] = min(n2, min(n3, n5));

            if(n2 == res[i]){
                i2++;
            }
            if(n3 == res[i]){
                i3++;
            }
            if(n5 == res[i]){
                i5++;
            }
        }
        return res[n - 1];
    }

    /*
        15、三数之和
        给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

        注意：答案中不可以包含重复的三元组。

        例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

        满足要求的三元组集合为：
        [
        [-1, 0, 1],
        [-1, -1, 2]
        ]
    */
    vector<vector<int> > three_sum(vector<int> &nums){
        //双指针
        sort(nums.begin(), nums.end());
        vector<vector<int> > res;

        if(nums.empty() || nums.size() < 3){ // nums为空或者长度小于3，返回res(为空)
            return res;
        }

        sort(nums.begin(), nums.end());   //先排序
        for(int i = 0; i < nums.size(); i++){
            int start = i + 1;
            int end = nums.size() - 1;

            if(nums[i] > 0){  //去重
                break;
            }

            if(i > 0 && nums[i] == nums[i - 1]){   //剪枝, 去重
                continue;
            }
            
            while(start < end){
                int sum = nums[i] + nums[start] + nums[end];
                if(sum == 0){
                    vector<int> temp;
                    temp.push_back(nums[i]), temp.push_back(nums[start]), temp.push_back(nums[end]);
                    res.push_back(temp);

                    while(start < end && nums[start] == nums[start + 1]) start++;  //剪枝，去重
                    while(start < end && nums[end] == nums[end - 1]) end--;  //剪枝，去重
                    start++;
                    end--;
                }else if(sum > 0){
                    end--;
                }else{
                    start++;
                }
            }
        }
        return res;
    } 

    /*
        402、移掉k位数字
        给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

        注意:

            num 的长度小于 10002 且 ≥ k。
            num 不会包含任何前导零。

        示例 1 :

        输入: num = "1432219", k = 3
        输出: "1219"
        解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。

        示例 2 :

        输入: num = "10200", k = 1
        输出: "200"
        解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。

        示例 3 :

        输入: num = "10", k = 2
        输出: "0"
        解释: 从原数字移除所有的数字，剩余为空就是0。

    */
   string removeKdigits(string& num, int k){
       vector<int> stack;
       string res = "";
       for(int i= 0; i < num.size(); i++){
           int number = num[i] - '0';
           while(stack.size() != 0 && stack[stack.size() - 1] > number && k > 0){
               stack.pop_back();
               k--;
           }
           if(number != 0 || stack.size() != 0){
               stack.push_back(number);
           }
       }
       while(stack.size() != 0 && k > 0){ //特殊的处理：当所有数字都扫描完成后，k仍然>0,例如：num=12345，k=3时
           stack.pop_back();
           k--;
       }
       for(int i = 0; i < stack.size(); i++){
           res += '0' + stack[i];
       }
       return res;
   }

    /*
        子集：
            给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

            说明：解集不能包含重复的子集。

            示例:

                输入: nums = [1,2,3]
                输出:
                [
                    [3],
                    [1],
                    [2],
                    [1,2,3],
                    [1,3],
                    [2,3],
                    [1,2],
                    []
                ]

    */
   vector<vector<int> > subsets(vector<int>& nums){
       vector<vector<int> > res;
       res.push_back({});   //先添加一个空集

        for(auto num: nums){
            int size = res.size();
            for(int i = 0; i < size; i++){
                vector<int> sub = res[i]; 
                sub.push_back(num);
                res.push_back(sub);
            }
        }
        return res;
   }

   /*
        字符串的所有子串
   */
  vector<string> allSubstring(string s){
      vector<string> res;
      if(s.size() == 0) return res;

      for(int i = 0; i < s.size(); i++){
          for(int j = 1; j < s.size() - 1; j++){
              res.push_back(s.substr(i, i + j));
          }
      }
  }

    /*
        除自身以外数组的乘积：
            给定长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

`       示例:

        输入: [1,2,3,4]
        输出: [24,12,8,6]
    */
    vector<int> productExceptSelf(vector<int>& nums){
        vector<int> res(nums.size(), 0);
        int product = 1;

        for(int i = 0; i < nums.size(); i++){
             res[i] = product;
             product *= nums[i];
        }

        product = 1;
        for(int i = nums.size() - 1; i >= 0; i--){
            res[i] *= product;
            product *= nums[i];
        }
        return res;
    }

    /*
        字母异位词分组：
            给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

        示例:

        输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
        输出:
        [
            ["ate","eat","tea"],
            ["nat","tan"],
            ["bat"]
        ]

    */

   vector<vector<string> > groupAnagrams(vector<string>& strs){
       map<string, vector<string> > hashmap;
       for(auto str: strs){
           string temp = str;
           sort(temp.begin(), temp.end());
       }

        vector<vector<string> > res(hashmap.size());
        int index = 0;
        for(auto i: hashmap){
            res[index] = i.second;
            index++;
        }
        return res;
   }
};

int main(){
    Solution s;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);

    vector<int> res = s.productExceptSelf(nums);

    for(int i = 0; i < res.size(); i++){
        cout << res[i] << endl;
    }
}


