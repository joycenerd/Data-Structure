# Arrays and Structures

## Arrays, Structures and Unions

### Arrays

* `*plist[5]`: five pointers to integers

* Pointers to array
```c
int list[5]={1,2,3,4,5};
int *plist;
plist=list;
for(int i=0;i<5;i++) printf("%d ",*(plist+i));
```
The output of the example above will be 1 2 3 4 5. `plist=list` means giving plist the first address of list, list is an array, so plist will have the list whole array, because it got it’s first address.

`*(plist+i)` : value of i in the address

`plist+i`: the address of pointer after i location from the beginning location

* Two Dimensional Arrays
We want to construct a two dimensional array using memory allocation.
```c
int **makeMatrix(int row,int col){
	int **x;
	int i;
	x=malloc(row*sizeof(*x));
	for(i=0;i<row;i++) x[i]=malloc(col*sizeof(**x));
	return x;
}
```
Malloc is always a pointer. Because it is two-dimensional so we define our array of pointer to be `**x`.

* Unions
Definition: A union declaration is similar to a structure, but the fields of a union must share their memory space. This means that only one field of the union is “active” at any given time.
```c
typedef struct sexType{
	enum tagField{female,male}sex;
	union{
		bool children;
		bool beard;
	}u;
};
```
If the sex is female then will enter children information, otherwise male then will enter beard information.

## Polynomials
We want to do two polynomials addition. We got two method. First, using array, and second using structure. They both has their own advantages and disadvantages.

* **Method 1: Array**
Array is implemented by consecutive memory, so no matter we need the space or not we need to specify it all. If the polynomial is dense, like the exponential isn’t two sparse, then using array is a good option,  since array is easy for implementation. Array’s disadvantages is wasting space when sparse. Ex: A(X)=2X^1000+1, although it’s only two elements but the exponential is 1000, we need a `arr[1001]` to put our polynomial.
```c
int arr[num];
arr[exp]=arr[coef];
```
This is how we store our polynomial.
```c
for(i=N-1;i>=0;i--){
        if(poly[0][i]!=0 && poly[1][i]!=0) ans[i]=poly[0][i]+poly[1][i];
        else if(poly[0][i]!=0 && poly[1][i]==0) ans[i]=poly[0][i];
        else if(poly[0][i]==0 && poly[1][i]!=0) ans[i]=poly[1][i];
    }
```
The addition is pretty simple for array. If the index is the same then we add it together.

* **Method 2: Structure**
Structure method is required if the polynomial is sparse so it won’t waste space. We only use space which have value in the specific degree. The  addition may be a bit complicated because it isn’t consecutive memory, we need to check everything by ourselves.
```c
typedef struct{
	int exp;
	int	coef;
}Poly[N];
```
This is how we specify our polynomial using structure
```c
int start1=0,start2=0;
while(start1<end1 && start2<end2){
        if(poly[0][start1].exp==poly[1][start2].exp){
            ans[count].exp=poly[0][start1].exp;
            ans[count].coef=poly[0][start1].coef+poly[1][start2].coef;
            count++;start1++;start2++;
        }
        else if(poly[0][start1].exp>poly[1][start2].exp){
            ans[count].exp=poly[0][start1].exp;
            ans[count].coef=poly[0][start1].coef;
            count++;start1++;
        }
        else{
            ans[count].exp=poly[1][start2].exp;
            ans[count].coef=poly[1][start2].coef;
            count++;start2++;
        }
    }
    while(start1<end1){
        ans[count].exp=poly[0][start1].exp;
        ans[count].coef=poly[0][start1].coef;
        count++;start1++;
    }
    while(start2<end2){
        ans[count].exp=poly[1][start2].exp;
        ans[count].coef=poly[1][start2].coef;
        count++;start2++;
    }
```
The addition of structure method is complicated we need to use 4 index `start1,end1,start2,end2` to check where is the addition going now.

## Sparse Matrices
Sparse matrix: non-zero elements are small. An nxn matrix may be stored as an nxn array, but this takes O(n^2) space. Sparse matrices may be mapped into a 1D array so that a mapping function can be used to locate an element quickly; the space required by the 1D array is less than that required by an nxn array.
* Structured sparse matrix: The non-zero element may have some regular pattern
* Unstructured sparse matrix: the non-zero element have no regular pattern, the appearance are random. 

EX: Web analysis

  ![](Arrays%20and%20Structures/page34image3813856.png) 
Authority page: page that has many links to it. Hub page: links to many authority page.

### Representations

* use triple <row, column, value> -> only storing non-zero elements
* store triple within row by row -> with ascending order first sort row and then column
![](Arrays%20and%20Structures/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202018-09-26%20%E4%B8%8A%E5%8D%8810.13.30.png)
a[0] : <total row, total column, total nonzero term>
```c
typedef struct{
    int row;
    int col;
    int val;
}Matrix;

Matrix matrix[N];

matrix[0].row=6;matrix[0].col=6;matrix[0].val=8;
int count=1;
for(i=0;i<6;i++){
    for(j=0;j<6;j++){
        if(a[i][j]!=0){
            matrix[count].row=i;
            matrix[count].col=j;
            matrix[count].val=a[i][j];
            count++;
        }
    }
}
```

### Transpose a Matrix

The definition of transpose matrix is changing the value of row to column and the column to row, that is `a[i][j]->a[j][i]`. 
* Transposing a sparse matrix: for each row in <i, j, value> and store it in element <j, i, value> of the transpose
* Difficulty: Where to put <j, i,  value>?

* **Method 1: Scan all the elements**
Move elements down very often -> first, for all elements in column j, place element <i, j, value> in element <j, i, value>. The disadvantage of this method is that we will need to scan the array “column” times, and the array has “total nonzero term elements” => Time Complexity O (columns*total nonzero term elements)
```c
// doing transpose
void doTranspose(int pos,int cur){
    transpose[cur].row=matrix[pos].col;
    transpose[cur].col=matrix[pos].row;
    transpose[cur].val=matrix[pos].val;
}

// Scan the array
    doTranspose(0,0);
    int cur=1;
    for(i=0;i<matrix[0].col;i++){
        for(j=1;j<matrix[0].val;j++){
            if(matrix[j].col==i){
                doTranspose(j,cur);
                cur++;
            }
        }
    }
```

* **Method 2: fast transpose**
Determine the number of elements in each column of the original matrix -> determine the starting positions of each row in the transpose matrix. 
![](Arrays%20and%20Structures/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202018-09-26%20%E4%B8%8B%E5%8D%889.07.06.png)
為每個index留位子，這樣只要掃一遍原sparse matrix就知道每個元素在transpose後要放的位子了。Time complexity of fast transpose is O (columns+ total nonzero elements). Although it’s faster than method 1, but the cost for this is additional row_terms and starting_pos arrays are required.
```c
for(i=1;i<=matrix[0].val;i++) rec[matrix[i].col][0]++;
    rec[0][1]=1;
    for(i=1;i<matrix[0].row;i++) rec[i][1]=rec[i-1][0]+rec[i-1][1];
    for(i=1;i<=matrix[0].val;i++){
        doTranspose(i,rec[matrix[i].col][1]);
        rec[matrix[i].col][1]++;
    }
    doTranspose(0,0);
```
`rex[][0]`: recording my row_terms, `rec[][1]`: recording my starting position

### Sparse Matrix Multiplication

Definition of matrix multiplication: C=A x B, if C is m x n, then A must be m x k and B must be k x n, so that A’s column must equal to B’s row.  We will compute the transpose of B to make the calculation much easier (check A’s column compare to B transpose’s column if the value in that location isn’t 0) . 
```c
int apos=1,bpos=1;
    int multi[N][N]={0};
    while(apos<=matrixa[0].val){
        while(bpos<=transposeb[0].val){
            if(matrixa[apos].col==transposeb[bpos].col){
                multi[matrixa[apos].row][transposeb[bpos].row]+=matrixa[apos].val*transposeb[bpos].val;
            }
            bpos++;
        }
        bpos=1;
        apos++;
    }
```
Using `após`as the position of the index of running through `matrixa`, and `bpos`as `transposeb`, if the column of a and b is the same then multiply the value and add it to the `multi` matrix in position of `[rowa][row_transposeb]`.

## String

### String Matching

* **Method 1 straightforward solution**
1. Algorithm: simple string matching
2. Input: main string, and matching pattern, and the pattern is assumed to be nonempty
3. Output: return the value of the first index where the pattern match in main string begin, or output -1 if no match for the pattern is found.
```c
 for(i=0;i<lens-lenp+1;i++){
        if(strncmp(mainstring+i,pattern,lenp)==0){
            printf("starting index: %d\n",i);
            flag=1;
            break;
        }
    }
    if(flag==0) printf("Pattern not found\n");
```
Find all the possibilities is the main string compare with the pattern if they were the same.

* **Method 2 KMP**
KMP is a string matching algorithm which complete with two phases. Phase1: generate an array to indicate the moving direction. Phase2: make use of the array to move and match string.
![](Arrays%20and%20Structures/page61image3808480.png) 
This is the perspective of the KMP algorithm. To move forward pattern more than one step at a time to speed up the finding time. Apparently, if we find the repeat part of the head of the pattern, then we can move our pattern to that part to find if it’s matching.

	* Failure Function
	Definition:
failure_array=![](Arrays%20and%20Structures/page63image3809824.png) 
![](Arrays%20and%20Structures/page63image3809600.png) 
The step of finding failure function if in the following:
![](Arrays%20and%20Structures/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202018-09-27%20%E4%B8%8B%E5%8D%887.51.20.png)
![](Arrays%20and%20Structures/%E8%9E%A2%E5%B9%95%E5%BF%AB%E7%85%A7%202018-09-27%20%E4%B8%8B%E5%8D%887.52.39.png)
```c
int failure[N];
failure[0] = 0;
char head = string[0];
for (i = 1; i < len; i++) {
    if (failure[i - 1] == 0) {
        if (string[i] == head) failure[i] = 1;
        else failure[i] = 0;
    }
    else {
        j = i - 1;
        int index = 0;
        while (j >= 1) {
            if (failure[j] == 1) {
                index = j;
                break;
            }
            j--;
        }
        int count;
        count = i - index + 1;
        if (strncmp(string + 0, string + index, count) == 0) failure[i] = count;
        else {
            int flag = 0;
            for (j = index + 1; j < i; j++) {
                if (string[j] == head) {
                    count = i - j + 1;
                    if (strncmp(string, string + j, count) == 0) {
                        failure[i] = count;
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag == 0) {
                if (string[i] == head) failure[i] = 1;
                else failure[i] = 0;
            }
        }
    }
}
```
從failure value=1開始算到現在這個元素比較最開始的重複區段，如果有重複就將前一個failure value+1 assign給這個元素。如果從1開始是找不到的，就從那個1的位置往後找如果是和最開始一樣的字母去比較有沒有和最開始重複的區段，如果有就從那個位置算到這裡的間隔數為此元素的failure value，如果還是沒有，那這個元素的failure value就是0了。

	* The KMP matcher
	After finding the failure function (array), then we use the array to do 		matching compare with the main string. 
		1. If the head element doesn’t match -> the pattern shift one position to the right.
		2. If their are some elements are match form the head element, then find from what index does it doesn’t match. Suppose it doesn’t match in index 2, from failure function -> `f[index-1]`: then we find the value in index 1 and minus one, and this will be the step count that the pattern will shift to the right. 
```c
i=0;j=0;
while(i<lent && j<lens){
    if(test[i]==string[j]){
        i++;j++;
    }
    else if(j==0) i++;
    else{
        i+=failure[j-1]   ;
        j=0;
    }
}
if(j==lens) printf("%lu\n",i-lens);
else printf("-1\n");	
```




#data structure#
