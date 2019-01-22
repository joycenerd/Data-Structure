# Introduction to Data Structures

### Abstract Data Type (ADT)
* data type specification (object & operation) is separated from representation
*  ADT is implementation independent

### Selection Sort
An unsorted array, from the first element of the array, find the minimum value of the rest array, compare with the first element, if it’s smaller, swap the two value. Now the first element is the smallest value of the array,                           continue from the second element, and repeat the process above until the last element, and the array is sorted
```c
void swap(int *num1, int *num2){
    int temp=*num1;
    *num1=*num2;
    *num2=temp;
}

int *sort(int list[],int number){
    int i=0;
    while(i<number){
        int j;
        int min=MIN;
        int min_index = 0;
        for(j=i+1;j<number;j++){
            if(list[j]<min){
                min=list[j];
                min_index=j;
        }
        if(list[min_index]<list[i]) 		 swap(&list[min_index],&list[i]);
        }
        i++;
    }
    return list;
}
```

### Binary Search

Binary Search is a common searching method, it is more efficient than linear search. First specify left bound to the first element of the sorted array and the right bound to the last element. Find the middle element in the area of the bounds. If the middle element is larger than the target than adjust the right bound to middle-1, if it’s smaller than adjust the left bound to middle+1, if it  is equal to than return its value. Careful left bound should always <= right bound. At last check the left bound value out of the loop if it’s not equal to the target than target is not found.
```c
int compare(int x,int y){
    if(x<y) return -1;
    else if(x==y) return 0;
    else return 1;
}

int BinarySearch(int list[],int target,int count){
    int left=0;
    int right=count-1;
    while(left<=right){
        int middle=(left+right)/2;
        switch(compare(list[middle],target)){
            case -1: left=middle+1;
                break;
            case 0: return middle;
            case 1: right=middle-1;
        }
    }
    if(list[left]==target) return left;
    else return -1;
}
```


### Selection Problem

* **Method 1**
We sort the whole list and select the k th largest element in the list
```c
int SelectionKth(int list[],int count,int k){
    return list[count-k];
}
```
* **Method 2**
We pick the first k elements put into a new array and sort by decrease order. Then compare the elements in the remaining list one by one to the new array, if it’s smaller than the new array than discard that element, otherwise change the new array’s element, and the new array’s element quantity should remain k all the time. At last return the last value of the new array.
```c
int SelectionII(int list[],int count,int k){
    int i;
    int temparray[k];
    for(i=0;i<k;i++) temparray[i]=list[i];
    int *sortarray;
    sortarray=sort(temparray,k);
    int reversearr[k];
    for(i=0;i<k;i++) reversearr[i] = *(sortarray+k-i-1);
    for(i=k;i<count;i++){
        if(list[i]<reversearr[k-1]) continue;
        int j;
        for(j=0;j<k;j++){
            int flag=0;
            if(list[i]>reversearr[j]){
                int temp=k-1;
                while(temp>j){
                    reversearr[temp]=reversearr[temp-1];
                    temp--;
                }
                reversearr[j]=list[i];
                flag=1;
            }
            if(flag) break;
        }
    }
    return reversearr[k-1];
}
```

### Recursive Multiplication

Like `a * b` can write in a recursive way: `a*(b-1)+a`
```c
int RecurMulti(int a, int b){
    if(b==1) return a;
    else return RecurMulti(a, b-1)+a;
}
```

### Recursive Permutation

Give a simple string, output all the permutations of the string. We swap two index at a time until all the combination has been found. We do it recursive way, called it every time after one swap so we can certain one index and swap the other two.
```c
void charSwap(char *char1, char *char2){
    char temp;
    temp=*char1;
    *char1=*char2;
    *char2=temp;
}
void RecurPerm(char *string,int left,int right){
    int i;
    if(left==right) printf("%s\n",string);
    else{
        for(i=left;i<=right;i++){
            charSwap(string+left, string+i);
            RecurPerm(string, left+1, right);
            charSwap(string+left, string+i);
        }
    }
}
```

We use pointer to pass the string to our function RecurPerm.
From the first index we swap two index and continue until the last element.

### Time Complexity

* Program Step: syntactically or semantically meaningful program segment whose execution time is independent of the instance characteristics. 

EX: Step count for matrix addtion
![](Introduction%20to%20Data%20Structures/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202018-09-22%20%E4%B8%8A%E5%8D%8811.26.26.png)
The total program step of the example above is 2rows x cols+**2rows**+1, so if the number of rows are larger than the number of columns then interchange the loop, so the program step will be smaller.

* It’s difficult to determine the exact step counts and also the exact step counts is not useful for comparison

* Big-O notation
f(n)=O(g(n)) iff ∃ positive const. c and n0, ∋ f(n) ≤ cg(n) ∀ n, n ≥ n0 , g(n) should be a least upper bound.
* Omega notation
f(n)=Ω(g(n)) iff ∃ positive const. c and n0, ∋ f(n) ≥ cg(n) ∀ n, n ≥ n0 , g(n) should be a most lower bound
* Theta notation
f(n)=Θ(g(n)) iff, ∃ positive constants c1,c2, and n0 ∋ c1g(n) ≤ f(n) ≤ 
c2g(n) ∀ n, n ≥ n0 , g(n) should be both lower bound and upper bound

* If T(N) is a polynomial of degree k, then T(N)=O(N^k)
* (logN)^k=O(N)

#data structure#
