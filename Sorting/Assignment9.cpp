//Grant Novota
//Assignment 9
//Hoenigman

#include <iostream>
#include <random>
#include <cstdio>
#include <ctime>

using namespace std;

int selectSortCount = 0;
int quickSortCount = 0;
int insertionSortCount = 0;
int bubbleSortCount = 0;
int shellSortCount = 0;

int selectSortLoopCount = 0;
int quickSortLoopCount = 0;
int shellSortLoopCount = 0;

void quickSort(int arr[], int left, int right) {
    quickSortLoopCount++;
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
            quickSortCount++;
        }
    }
    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

void selectSort(int arr[], int n) {

  int counter = 0;
  int index_min_value;
  int temp;
  for (int i=0; i<n-1; i++) {
        selectSortLoopCount++;
  // outer loop tracks the sorted portion of the list
    index_min_value = i; //set index_min_value to the current index of array
    for (int j=i+1; j < n; j++) // inner loop finds the next smallest value
    {
      if (arr[j] < arr[index_min_value])
        index_min_value = j;

    }
    if (index_min_value != i) {
      temp = arr[i];
      arr[i] = arr[index_min_value];
      arr[index_min_value] = temp;
      selectSortCount++;
    }
  }
}

void insertionSort (int arr[], int length) {
  int j, temp;
  for (int i = 0; i < length; i++)  {
      j = i;
      while (j > 0 && arr[j] < arr[j-1])
      { // move elements over until find the position for next element
        temp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = temp;
        j--;
        insertionSortCount++;
      }
  }
}

void shellSort(int arr[], int length)
{
    int temp;
    for(int gap = length/2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < length; i++)
        {
            shellSortLoopCount++;
            for(int j = i-gap; j >= 0 && arr[j] > arr[j+gap]; j-=gap)
            {
                temp = arr[j];
                arr[j] = arr[j+gap];
                arr[j+gap] = temp;
                shellSortCount++;
            }
        }
    }
}

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}
void bubbleSort(int arr[], int n) {

  int i, j;
  int counter = 0;
  for (i = 0; i < n-1; i++) {// Last i elements are already in place
    for (j = 0; j < n-i-1; j++){
      if (arr[j] > arr[j+1]){
        swap(&arr[j], &arr[j+1]);
        bubbleSortCount++;
      }
    }
  }
}


void printList(int arr[], int length){
  for (int i = 0; i<length; i++){
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}

int main(){
int *count = 0;
  //HINT: You should place a counter into each algorithm to see how many time each of them run. Then you can compare them easier.
  //You should use the given print statements for better organization.

  int myArray1[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray2[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray3[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray4[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray5[] = {12, 13, 5, 4, 7, 18, 9 };


  cout << endl;
  cout << " ======== Small array ======= " << endl;
  cout << endl;

  cout<<"My original small array is: "<<endl;
  printList(myArray1,7);

  //selectSort
  selectSort(myArray1,7);
  cout<<"When ordered with selectSort, after "<<selectSortCount<<" operations the result is: "<<endl;
  printList(myArray1,7);

  //insertionSort

  insertionSort(myArray2,7);
  cout<<"When ordered with insertionSort, after "<<insertionSortCount<<" operations the result is: "<<endl;
  printList(myArray2,7);

  //bubbleSort
  bubbleSort(myArray3,7);
  cout<<"When ordered with bubbleSort, after "<<bubbleSortCount<<" operations the result is: "<<endl;
  printList(myArray3,7);

  //quickSort
  quickSort(myArray4,0,6);
  cout<<"When ordered with quickSort, after "<<quickSortCount<<" operations the result is: "<<endl;
  printList(myArray4,7);

  //shellSort
  shellSort(myArray5, 7);
  cout<<"When ordered with shellSort, after "<<shellSortCount<<" operations the result is: "<<endl;
  printList(myArray5,7);

  cout << endl;
  cout << " ======== Large array ======= (1000)" << endl;
  cout << endl;

  int length = 1000;
  int *longArray1 = new int[length];
  int *longArray2 =  new int[length];
  int *longArray3 = new int[length];
  int *longArray4 = new int[length];
  int *longArray5 = new int[length];

  for(int x=0; x<length; x++)
  {
      int value = rand();
      longArray1[x] = value;
      longArray2[x] = value;
      longArray3[x] = value;
      longArray4[x] = value;
      longArray5[x] = value;
  }

  selectSortCount = 0;
  insertionSortCount = 0;
  bubbleSortCount = 0;
  quickSortCount = 0;
  shellSortCount = 0;

  selectSortLoopCount = 0;
  quickSortLoopCount = 0;
  shellSortLoopCount = 0;

  clock_t cl; //initializes a clock type
  double duration;
  cl = clock(); //starts the timer

  //selectSort
  selectSort(longArray1,length);
  cl = clock() - cl; //ends the timer
  duration = cl / (double) CLOCKS_PER_SEC; //ticks per second (seconds passed)

  cout<<"When ordered with selectSort, after "<<selectSortCount<<" swaps the result is: "<<endl;
  cout << "Time taken: " << duration << " seconds" << endl;
  cout << "Number of loops: " << selectSortLoopCount << endl;


  //insertionSort
  //cl = 0;
  //duration = 0;
  //cl = clock();
  //insertionSort(longArray2,length);
  //cl = clock() - cl;
  //duration = cl / (double) CLOCKS_PER_SEC;
  //cout<<endl<<"When ordered with insertionSort, after "<<insertionSortCount<<" swaps the result is: "<<endl;
  //cout << "Time taken: " << duration << " seconds" << endl;

  //bubbleSort
  //cl = 0;
  //duration = 0;
  //cl = clock();
  //bubbleSort(longArray3,length);
  //cl = clock() - cl;
  //duration = cl / (double) CLOCKS_PER_SEC;
  //cout<<endl<<"When ordered with bubbleSort, after "<<bubbleSortCount<<" swaps the result is: "<<endl;
  //cout << "Time taken: " << duration << " seconds" << endl;

  //quickSort
  cl = 0;
  duration = 0;
  cl = clock();
  quickSort(longArray4,0,length-1);
  cl = clock() - cl;
  duration = cl / (double) CLOCKS_PER_SEC;
  cout<<endl<<"When ordered with quickSort, after "<<quickSortCount<<" swaps the result is: "<<endl;
  cout << "Time taken: " << duration << " seconds" << endl;
  cout << "Number of loops: " << quickSortLoopCount << endl;

  //shellSort
  cl = 0;
  duration = 0;
  cl = clock();
  shellSort(longArray5, length);
  cl = clock() - cl;
  duration = cl / (double) CLOCKS_PER_SEC;
  cout<<endl<<"When ordered with shellSort, after "<<shellSortCount<<" swaps the result is: "<<endl;
  cout << "Time taken: " << duration << " seconds" << endl;
  cout << "Number of loops: " << shellSortLoopCount << endl;


  cout << endl;
  cout << " ======== Very Large array ======= (1,000,000)" << endl;
  cout << endl;

  length = 1000000;
  int *veryLongArray1 = new int[length];
  int *veryLongArray2 = new int[length];
  int *veryLongArray3 = new int[length];
  int *veryLongArray4 = new int[length];
  int *veryLongArray5 = new int[length];

  for(int x=0; x<length; x++)
  {
      int value = rand();
      veryLongArray1[x] = value;
      veryLongArray2[x] = value;
      veryLongArray3[x] = value;
      veryLongArray4[x] = value;
      veryLongArray5[x] = value;
  }

  selectSortCount = 0;
  insertionSortCount = 0;
  bubbleSortCount = 0;
  quickSortCount = 0;
  shellSortCount = 0;

  selectSortLoopCount = 0;
  quickSortLoopCount = 0;
  shellSortLoopCount = 0;

  //selectSort
  cl = 0;
  duration =0;
  cl = clock();
  selectSort(veryLongArray1,length);
  cl = clock() - cl; //ends the timer
  duration = cl / (double) CLOCKS_PER_SEC; //ticks per second (seconds passed)

  cout<<"When ordered with selectSort, after "<<selectSortCount<<" operations the result is: "<<endl;
  cout << "Time taken: " << duration << " seconds" << endl;
  cout << "Number of loops: " << selectSortLoopCount << endl;


  //insertionSort
  //cl = 0;
  //duration = 0;
  //cl = clock();
  //insertionSort(veryLongArray2,length);
  //cl = clock() - cl;
  //duration = cl / (double) CLOCKS_PER_SEC;
  //cout<<endl<<"When ordered with insertionSort, after "<<insertionSortCount<<" swaps the result is: "<<endl;
  //cout << "Time taken: " << duration << " seconds" << endl;

  //bubbleSort
  //cl = 0;
  //duration = 0;
  //cl = clock();
  //bubbleSort(veryLongArray3,length);
  //cl = clock() - cl;
  //duration = cl / (double) CLOCKS_PER_SEC;
  //cout<<endl<<"When ordered with bubbleSort, after "<<bubbleSortCount<<" operations the result is: "<<endl;
  //cout << "Time taken: " << duration << " seconds" << endl;

  //quickSort
  cl = 0;
  duration = 0;
  cl = clock();
  quickSort(veryLongArray4,0,length-1);
  cl = clock() - cl;
  duration = cl / (double) CLOCKS_PER_SEC;
  cout<<endl<<"When ordered with quickSort, after "<<quickSortCount<<" swaps the result is: "<<endl;
  cout << "Time taken: " << duration << " seconds" << endl;
  cout << "Number of loops: " << quickSortLoopCount << endl;

  //shellSort
  cl = 0;
  duration = 0;
  cl = clock();
  shellSort(veryLongArray5, length);
  cl = clock() - cl;
  duration = cl / (double) CLOCKS_PER_SEC;
  cout<<endl<<"When ordered with shellSort, after "<<shellSortCount<<" swaps the result is: "<<endl;
  cout << "Time taken: " << duration << " seconds" << endl;
  cout << "Number of loops: " << shellSortLoopCount << endl;

  return 0;
}
