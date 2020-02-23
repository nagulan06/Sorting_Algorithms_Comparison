// NAGULAN MANIVELAN
// NUID: 001347557
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<time.h>
using namespace std;
int moves, comps;
/////////////////INSERTION SORT
void ins_sort(int *a, int len)
{
    int key, j;
    for (int i=1; i<len; i++)  //Loop that travels through the entire array
    {
        key = a[i];
	j=i-1;
        while(j>=0 && a[j]>key)
        {
            comps = comps + 1;   // Before entering into the while loop, the elements are compared. So comps incremented.
            a[j+1] = a[j];
            moves = moves + 1;  // The element is moved in the previoud line.
            j-=1;
        }
        comps = comps + 1;   // Even when the while loop is not entered, a comparison would have happened for the condition to have failed.
	if(a[j+1]!=key)   // key is moved only if the value of a[i] has changed. If not, it's the best case scenario. This condition ensures we don't count move while reassigning the same variable..
		{
		moves = moves + 1;  //This move operation does not occur for the best case scenario
        a[j+1] = key;
		}
    }
}

/////////////////////HEAP SORT
int max_heapify(int *a, int i, int len)
{
    int largest,temp;
    int left = 2*i + 1;  // left child of the node i
    int right = 2*i + 2; // right child of the node i
        if ((a[left]>a[i]) && (left<len)) // finds the largest among left child and the node
        {
            comps = comps + 1;  // comparison is done to find the largest
            largest = left;
        }
        else
        {
            comps = comps + 1; // the comparison results to either the if block are the else block. So, comps is incremented here also
            largest = i;
        }
	comps = comps + 1;    // comparing the largest among the parent and the left with the right
        if ((a[right] > a[largest]) && (right<len))
        {
            largest = right;
        }
        if(largest != i)
        {
            temp = a[largest]; // if the largest value is not the parent, the parent node is swapped with the largest value
            moves = moves + 1;
            a[largest] = a[i];
            moves = moves + 1;
            a[i] = temp;
            moves = moves + 1;  // the swap operation consumes 3 moves
            max_heapify(a,largest, len); // now, max_heapify is repeated from the largest node until the leaf.
        }
    return(0);
}
void max_build(int *a, int len)  // this function builds a tree where the root will be the largest element
{
    int i = (len/2)-1;  // starting from the parent of the last leaf, max_heapify is called until the root.
    for(int x=i; x>=0; x--)
    {
        max_heapify(a,x,len);  // so, the root will have the largest value
    }
}
void heap_sort(int *a, int len)
{
    int temp, x=0;
    max_build(a,len);      // the given array is max_build to bring the largest element to the root of the array
    for(int y=len-1; y>=0; y--)
    {
        temp = a[y];            // once the largest element reaches the root, the root is swapped with the last leaf.
        moves = moves + 1;
        a[y]=a[0];
        moves = moves + 1;
        a[0] = temp;
        moves = moves + 1;     // the swap operation consumes 3 moves.
			       // the value of y starts from the last node and goes until the root. So, the entire heap is max_heapified.
        max_heapify(a,0,y);
    }
}
/////////////////////////QUICK SORT

int partition(int *a, int p, int r)
{
    int i= (p-1);
    int x = r;    // choose the last element of the array as the pivot
    for(int j=p; j<r; j++)  // p is the starting index and r is the last index. So, the loop is run from the start to the last.
    {
        comps = comps + 1; // everytime for loop is entered, a comparison is done. Based on it, 'if' block is entered or not entered.
        if(a[j]<=a[x])    // every element is compared eith the pivot.
        {
            i=i+1;
			if(a[i]!=a[j])  // This condition avoids reassigning variables to itself. -- This is not a part of the algorithm. This comparison is jsut to ensure proper moves count.
			{
				int temp = a[j];// if the element compared is lesser than the pivot, it is swapped with element with index i+1 (an element larger than the pivot)
				moves = moves + 1;
				a[j] = a[i];
				moves = moves + 1;
				a[i] = temp;
				moves = moves + 1;  // 3 moves for the swap
			}
        }
    }
	if(a[i+1]!=a[r]) // This is also not a part of the algorithm but ensures that we don't count reassignment of variables as a move
	{
		int temp = a[i+1];
		moves = moves + 1;
		a[i+1] = a[r];
		moves = moves + 1;    // finally the pivot is moves to the correct position by swapping it
		a[r] = temp;
		moves = moves + 1;
	}
    return(i+1);
}
void quick_sort(int *a, int p, int r)
{
    if(p<r)
    {
        int q = partition(a,p,r);  // this function returns a value. The elemnts to the left of the value will be lesser than it and those to the right will be larger than it. So, the array is basically partioned into two and an element at the middle
        quick_sort(a,p,q-1); // the left part of the array is again quick sorted recursively
        quick_sort(a,q+1,r); // the right part of the array is quick sorted
    }
}
/////////////CHECK FUNCTION
void check(int *a, int len)
{
//   this function checks if the elements in the passed array are sorted
  int cv = 0;
  for(int i=0; i<len-1; i++)
  {
    if(a[i]>a[i+1])            // even if any one of the element is lesser than its previous element, make cv =1 and print sorting failed
    {
      cv = 1;
      cout<<"\nSORTING FAILED  ";
      break;
    }
  }
  if (cv == 0)              // if cv!=0 , it would mean that the if block was never entered. So, the array is sorted.
      cout<<"\nSORTING SUCCESS  ";
}

//////////////////////MAIN FUNCTION
int main()
{
    ofstream out;
    out.open("sort.txt");  // create and open a text file named sort.txt
    int len = 1000;
    srand(time(NULL));
    int x=10, y=6000;
  // nine arrays, 3 for each algorithm (worst, best and average case array)
    int bst_qsort[1000],avg_qsort[1000],wst_qsort[1000],bst_ins[1000],avg_ins[1000],wst_ins[1000],bst_heap[1000],avg_heap[1000],wst_heap[1000];
    for(int i=0; i<1000; i++)   // all the arrays are initialised in this loop.
    {
      bst_ins[i]= x;      // the best case array must consists of elements in ascending order starting from 0 incremented by 5
      bst_qsort[i]= x;
      bst_heap[i]= x;
      x = x + 5;
      wst_qsort[i] = y;  // worst case array stores elements in descending order begining from 6000, decremented by 5
      wst_ins[i] = y;
      wst_heap[i] = y;
      y = y-5;
      avg_ins[i] = rand()%100000;   // the average case array is filled with random numbers
      avg_heap[i] = avg_ins[i];
      avg_qsort[i] = avg_ins[i];
    }
    if (out.fail())
    {
        cerr << "Error: Could not open output file\n";    // if output file doesnt exist, prints error
        exit(1);
    }
   // initialize moves and comps to 0, call quick sort, check if the array has been sorted and then write the values to the created text file.
    out<<"\n\nBEST CASE QUICK SORT: ";
    moves = 0;
    comps = 0;
    quick_sort(bst_qsort,0,len-1);
    check(bst_qsort, len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;
// same is repeated for average case and worst case arrays
    out<<"\nAVERAGE CASE QUICK SORT: ";
    moves = 0;
    comps = 0;
    quick_sort(avg_qsort,0,len-1);
    check(avg_qsort, len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;

    out<<"\nWORST CASE QUICK SORT: ";
    moves = 0;
    comps = 0;
    quick_sort(wst_qsort,0,len-1);
    check(wst_qsort, len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;
    // initialize moves and comps to 0, call insertionquick sort, check if the array has been sorted and then write the values to the created text file.
    out<<"\n\nBEST CASE INSERTION SORT: ";
    moves = 0;
    comps = 0;
    ins_sort(bst_ins,len);
    check(bst_ins,len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;

    out<<"\nAVERAGE CASE INSERTION SORT: ";
    moves = 0;
    comps = 0;
    ins_sort(avg_ins,len);
    check(avg_ins,len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;

    out<<"\nWORST CASE INSERTION SORT: ";
    moves = 0;
    comps = 0;
    ins_sort(wst_ins,len);
    check(wst_ins,len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;
    // initialize moves and comps to 0, call heap sort, check if the array has been sorted and then write the values to the created text file
    out<<"\n\nBEST CASE HEAP SORT: ";
    moves = 0;
    comps = 0;
    heap_sort(bst_heap,len);
    check(bst_heap,len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;

    out<<"\nAVERAGE CASE HEAP SORT: ";
    moves = 0;
    comps = 0;
    heap_sort(avg_heap,len);
    check(avg_heap,len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;

    out<<"\nWORST CASE HEAP SORT: ";
    moves = 0;
    comps = 0;
    heap_sort(wst_heap,len);
    check(wst_heap,len);
    out<<"\nMOVES: "<<moves;
    out<<"\nCOMPARES: "<<comps;

	out.close();

    return 0;
}


