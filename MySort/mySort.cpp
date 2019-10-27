#include <iostream>
using namespace std;


class Solution{
public:
    /*
        冒泡排序
    */
    void bubbleSort(int* p, int size){
        for(int i = 0; i < size - 1; i++){
            for(int j = 0; j < size - 1 - i; j++){
                if(p[j + 1] < p[j]){
                    int temp = p[j + 1];
                    p[j + 1] = p[j];
                    p[j] = temp; 
                }
            }
        }
    }

    /*
        选择排序
    */
   void selectSort(int* p, int size){
       for(int i = 0; i < size - 1; i++){
           int t = i;
           for(int j = i + 1; j < size; j++){
               if(p[t] > p[j])
                    t = j;
           }
           if(t != i){
               int temp = p[t];
               p[t] = p[i];
               p[i] = temp;
           }
       }
   }

   /*
        插入排序
        将数组分为已经排好的顺序的和未排好顺序的
        3 6 7 4 2 1 5： 要将4 2 1 5插入到前面的顺序中
   */
  void insertSort(int* p, int size){
      int j;
      for(int i = 1; i < size; i++){
          int key = p[i];
          for(j = i; j > 0 && key < p[j - 1]; j--){
              p[j] = p[j - 1];
          }
          p[j] = key;
      }
  }

    /*
      快速排序
      算法思想：将大于基准数的数字放在其右边，小于基准数的数字放在其左边
    */
   void quickSort(int* p, int left, int right){
       if(left > right)
            return;
        int base = p[left];
        int i = left;
        int j = right;

        while(i < j){
            while(i < j && p[j] >= base)
                j--;
            while(i < j && p[i] <= base)
                i++;
            int temp = p[i];    //将两个不符合的元素互换位置
            p[i] = p[j];
            p[j] = temp;
        }
        p[left] = p[i];
        p[i] = base;

        quickSort(p, left, i - 1);    //递归
        quickSort(p, j + 1, right);
   }

    /*
        归并排序
    */
    void mergeSort(int* p, int size){  //重载
        int tempArray[size];
        mergeSort(p, tempArray, 0, size - 1);
    }

    /*
        堆排序

    */
    void heapSort(){
        
    }

private:
    void mergeSort(int* p, int* tempArray, int left, int right){
        if(left < right){
            int center = (left + right) / 2;
            mergeSort(p, tempArray, left, center);
            mergeSort(p, tempArray, center + 1, right);
            merge(p, tempArray, left, center + 1, right);
        }
    }

    void merge(int* p, int* tempArray, int leftPos, int rightPos, int rightEnd){
        int leftEnd = rightPos - 1;
        int numElements = rightEnd - leftPos + 1;
        int tempPos = leftPos;

        while(leftPos <= leftEnd && rightPos <= rightEnd){
            if(p[leftPos] <= p[rightPos])
                tempArray[tempPos++] = p[leftPos++];
            else
                tempArray[tempPos++] = p[rightPos++];
        }

        while(leftPos <= leftEnd)
            tempArray[tempPos++] = p[leftPos++];
        while(rightPos <= rightEnd)
            tempArray[tempPos++] = p[rightPos++];

        for(int i = 0; i < numElements; i++, rightEnd--){ //将tempArray倒回到原数组
            p[rightEnd] = tempArray[rightEnd];
        }
    }
};



int main(int argc, char const *argv[])
{   

    int nums[] = {1, 3, -1, 2, -10, 2, 8, -2};
    
    Solution s;

    s.mergeSort(nums, sizeof(nums)/sizeof(int));
    for(auto num: nums){
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
