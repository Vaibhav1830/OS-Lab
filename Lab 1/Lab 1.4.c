#include <stdio.h>

int main() {
    int n, count = 0;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n], freq[n];

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        freq[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (freq[i] == 0) continue;
        int duplicateCount = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                duplicateCount++;
                freq[j] = 0;
            }
        }
        if (duplicateCount > 1) {
            count++;
        }
    }

    printf("Total number of duplicate elements: %d\n", count);

    return 0;
}
