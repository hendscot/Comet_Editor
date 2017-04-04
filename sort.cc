#include <iostream>
#include <ctime>
#include <cstdlib>

void PrintArray    (int*, const int);
void FillRand      (int*, const int);
void BubbleSort    (int*, const int);
void SelectionSort (int*, const int);

int main (int argc, char* argv[]) {
    const int SIZE = 50;
    srand (time(NULL));
    int* randArray = new int [SIZE];
    std::cout << "BUBBLE SORT" << std::endl;
    FillRand   (randArray, SIZE);
    PrintArray (randArray, SIZE);
    BubbleSort (randArray, SIZE);
    PrintArray (randArray, SIZE);

    std::cout << "SELECTION SORT" << std::endl;
    FillRand   (randArray, SIZE);
    PrintArray (randArray, SIZE);
    SelectionSort (randArray, SIZE);
    PrintArray (randArray, SIZE);

    std::cout << "INSERTION SORT" << std::endl;
    FillRand   (randArray, SIZE);
    PrintArray (randArray, SIZE);
    SelectionSort (randArray, SIZE);
    PrintArray (randArray, SIZE);
}

void PrintArray (int* arr, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void FillRand (int* arr, const int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (rand () % 500 + 1);
    }
}

void BubbleSort (int* arr, const int size) {
    bool swapped;
    int temp;
    do {
        swapped = false;
        for (int i = 1; i < size; i++) {
            if (arr[i] < arr[i-1]) {
                temp = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

void SelectionSort (int* arr, const int size) {
    int min, temp;
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void InsertionSort (int* arr, const int size) {
    int xtrac;
    for (int i = 1; i < size; i++) {
        xtrac = arr[i];
        for (int j = i - 1; i >= 0; j--) {
            if (arr[j] > xtrac) 
                arr[j + 1] = arr[j];
            else {
                arr[j] = xtrac;
                break;
            }
        }
    }
}