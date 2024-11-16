#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge Sort algo
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
        
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Quick Sort algo
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function for performance comparison
int main() {
    int n;

    // User input for array size
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n], arr_copy[n];

    // User input for array elements
    printf("Enter %d elements of the array:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i]; // Copy for fair comparison
    }

    // Measure time for Merge Sort
    clock_t start_merge = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end_merge = clock();
    double time_merge = ((double)(end_merge - start_merge)) / CLOCKS_PER_SEC;

    // Measure time for Quick Sort
    clock_t start_quick = clock();
    quickSort(arr_copy, 0, n - 1);
    clock_t end_quick = clock();
    double time_quick = ((double)(end_quick - start_quick)) / CLOCKS_PER_SEC;

    // Output the sorted arrays
    printf("\nSorted array using Merge Sort:\n");
    printArray(arr, n);

    printf("Sorted array using Quick Sort:\n");
    printArray(arr_copy, n);

    // Output the time taken by each algorithm
    printf("\nMerge Sort Time: %.6f seconds\n", time_merge);
    printf("Quick Sort Time: %.6f seconds\n", time_quick);

    return 0;
}
