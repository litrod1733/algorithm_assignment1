#include <iostream>
#include <cstring>
#include <ctime>
#define N 500000

using namespace std;

int arr[N];
int cmp_cnt = 0;
int swap_cnt = 0;

//삽입정렬 구현
void insertionSort(int Arr[], int size) {
  for(int i=0; i<size; i++) {
    int j=i;
    while(j >= 0 && Arr[j] > Arr[j+1]) {
      int tmp = Arr[j];
      Arr[j] = Arr[j+1];
      Arr[j+1] = tmp;
      j--;
      cmp_cnt++;
      swap_cnt++;
    }
  }
}

//합병정렬 구현
int sorted[N];

void merge(int Arr[], int left, int mid, int right) {
  int index1 = left;
  int index2 = mid+1;
  for(int i=left; i<=right; i++) {
    if(index1 > mid) {
      sorted[i] = Arr[index2];
      index2++;
      continue;
    }
    if(index2 > right) {
      sorted[i] = Arr[index1];
      index1++;
      continue;
    }
    if(Arr[index1] < Arr[index2]) {
      sorted[i] = Arr[index1];
      index1++;
      cmp_cnt++;
      swap_cnt++;
      continue;
    }
    if(Arr[index1] > Arr[index2]) {
      sorted[i] = Arr[index2];
      index2++;
      cmp_cnt++;
      swap_cnt++;
      continue;
    }
  }
  for(int i=left; i<=right; i++) {
    Arr[i] = sorted[i];
  }
}

void mergeSort(int Arr[], int left, int right) {
  if(left < right) {
    int mid = (left + right) / 2;
    mergeSort(Arr, left, mid);
    mergeSort(Arr, mid+1, right);
    merge(Arr, left, mid, right);
  }
}

//퀵정렬 구현
int getMedian(int Arr[], int left, int mid, int right) {
  if(Arr[left] > Arr[mid]) {
    if(Arr[mid] > Arr[right]) {
      cmp_cnt++;
      return mid;
    }
    else if(Arr[right] > Arr[left]) {
      cmp_cnt++;
      return left;
    }
    else {
      cmp_cnt++;
      return right;
    }
  }
  else if(Arr[left] > Arr[right]) {
    cmp_cnt++;
    return left;
  }
  else if(Arr[mid] > Arr[right]) {
    cmp_cnt++;
    return right;
  }
  else {
    cmp_cnt++;
    return mid;
  }
}

int partition(int Arr[], int left, int right) {
  int index1 = left+1;
  int index2 = right;
  int tmp;
  int pivot;
  int mid = (left + right) / 2;
  //왼쪽 끝 값, 오른쪽 끝 값, 중간 값을 비교해서 중앙값을 피벗으로 설정한다.
  pivot = getMedian(Arr, left, mid, right);
  //피벗에 위치한 값과 맨 왼쪽 자리에 위치한 값을 변경해준다.
  tmp = Arr[left];
  Arr[left] = Arr[pivot];
  Arr[pivot] = tmp;
  swap_cnt++;
  //피벗보다 작은 값은 왼쪽으로 큰 값은 오른쪽으로 스왑해준다.
  while(index1 <= index2) {
    if(Arr[index1] > Arr[left] && Arr[index2] < Arr[left]) {
      tmp = Arr[index1];
      Arr[index1] = Arr[index2];
      Arr[index2] = tmp;
      index1++;
      index2--;
      cmp_cnt++;
      swap_cnt++;
    }
    else if(Arr[index1] < Arr[left] && Arr[index2] < Arr[left]) {
      index1++;
      cmp_cnt++;
    }
    else if(Arr[index1] > Arr[left] && Arr[index2] > Arr[left]) {
      index2--;
      cmp_cnt++;
    }
    else {
      index1++;
      index2--;
      cmp_cnt++;
    }
  }
  tmp = Arr[left];
  Arr[left] = Arr[index1-1];
  Arr[index1-1] = tmp;
  swap_cnt++;
  pivot = index1 - 1;
  return pivot;
}

void quickSort(int Arr[], int left, int right) {
  if(left < right) {
    int pivot = partition(Arr, left, right);
    quickSort(Arr, left, pivot - 1);
    quickSort(Arr, pivot + 1, right);
  }
}

//힙정렬 구현
void maxHeapify(int Arr[], int size, int parent) {
  int left_child = parent*2 + 1;
  int right_child = parent*2 +2;
  int max_index;
  if(left_child <= size) {
    if (Arr[left_child] > Arr[parent]) {
      max_index = left_child;
      cmp_cnt++;
    }
    else {
      max_index = parent;
      cmp_cnt++;
    }
    if (right_child <= size && Arr[right_child] > Arr[max_index]) {
      max_index = right_child;
      cmp_cnt++;
    }
    if (max_index != parent) {
      int tmp = Arr[max_index];
      Arr[max_index] = Arr[parent];
      Arr[parent] = tmp;
      swap_cnt++;
      maxHeapify(Arr, size, max_index);
    }
  }
}

void buildMaxHeap(int Arr[], int size) {
  for(int i=(size-1)/2; i>=0; i--) {
    maxHeapify(Arr, size, i);
  }
}

void heapSort(int Arr[], int n) {
  int size = n;
  buildMaxHeap(Arr, n-1);
  for(int i=n; i>0; i--) {
    int temp = Arr[0];
    Arr[0] = Arr[i];
    Arr[i] = temp;
    swap_cnt++;
    size--;
    maxHeapify(Arr, size, 0);
  }
}


int main(int argc, char* argv[]) {
  //랜덤배열 생성

  //input.txt 파일에서 입력 받기
  for(int i=0; i<N; i++) {
    int n;
    scanf("%d", &n);
    arr[i] = n;
  }
  int arr_size = sizeof(arr)/sizeof(arr_size);
  //실행 시간 측정 시작
  time_t start;
  time_t end;
  start = time(NULL);
  //정렬 branch
  if(!strcmp(argv[1], "insertion")) {
    insertionSort(arr, arr_size);
  }
  else if(!strcmp(argv[1], "merge")) {
    mergeSort(arr, 0, arr_size-1);
  }
  else if(!strcmp(argv[1], "quick")) {
    quickSort(arr, 0, arr_size-1);
  }
  else if(!strcmp(argv[1], "heap")) {
    heapSort(arr, arr_size-1);
  }
  else {
    return -1;
  }
  //output.txt 파일로 출력하기
  for(int i=0; i<arr_size; i++) {
    printf("%d ",arr[i]);
  }
  end = time(NULL);
  printf("정렬에 걸린 시간 : %ld초\n", end-start);
  printf("비교 횟수 : %d번\n", cmp_cnt);
  printf("교환 횟수 : %d번\n", swap_cnt);
  return 0;
}
