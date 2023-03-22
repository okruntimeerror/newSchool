#include <stdio.h>

int main() {
    int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int n = sizeof(arr) / sizeof(arr[0]);
    int swaps[n];

    for (int i = 0; i < n; i++) {
        swaps[i] = 0;
    }

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                
                swaps[j]++;
                swaps[j + 1]++;
            }
        }
    }

    
    for (int i = 0; i < n; i++) {
        printf("Index %d: %d swaps\n", i, swaps[i]);
    }

    return 0;
}
