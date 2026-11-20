/* odd_even.c - CSCI291 Lab 4, Task 1 */

#include <stdio.h>
#define MAX 20

/* Iterative */
void partition_iterative(int arr[], int size)
{
    int left = 0; /* moves right, looking for an even number */
    int right = size - 1; /* moves left, looking for an odd number */
    int temp;
    while (left < right) {
        while (left < right && arr[left] % 2 != 0) 
            left++;
        while (left < right && arr[right] % 2 == 0) 
            right--;
        if (left < right) { /* even on left, odd on right */
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
} 

/* Recursive */
void partition_recursive(int arr[], int left, int right)
{
    int temp;
    if (left >= right) /* base case: pointers met or crossed */
        return;
    if (arr[left] % 2 != 0) { /* left element is odd: skip it */
        partition_recursive(arr, left + 1, right);
        return;
    }
    if (arr[right] % 2 == 0) { /* right element is even: skip it */
        partition_recursive(arr, left, right - 1);
        return;
    }
    temp = arr[left]; /* even on left, odd on right: swap */
    arr[left] = arr[right];
    arr[right] = temp;
    partition_recursive(arr, left + 1, right - 1);
}

static void print_array(const char *label, const int arr[], int size)
{
    int i;
    printf("%-12s: [", label);
    for (i = 0; i < size; i++)
    printf("%s%d", i ? ", " : "", arr[i]);
    printf("]\n");
}

static void run_test(const char *name, const int src[], int size)
{
    int a[MAX], b[MAX], i;
    for (i = 0; i < size; i++) { 
        a[i] = src[i]; b[i] = src[i]; \
    }
    printf("--- %s ---\n", name);
    print_array("Original", src, size);
    partition_iterative(a, size);
    print_array("Iterative", a, size);
    partition_recursive(b, 0, size - 1);
    print_array("Recursive", b, size);
    printf("\n");
}

int main(void) {
    int t1[] = {12, 7, 4, 9, 2, 15, 8, 3};
    int t2[] = {1, 3, 5, 7, 9};
    int t3[] = {2, 4, 6, 8};
    int t4[] = {10, 21, -3, 6, -8, 5, 0, 11};
    int t5[] = {4};
    run_test("Test 1: mixed", t1, 8);
    run_test("Test 2: all odd", t2, 5);
    run_test("Test 3: all even", t3, 4);
    run_test("Test 4: negatives and zero", t4, 8);
    run_test("Test 5: single element", t5, 1);
    run_test("Test 6: empty array", t5, 0);
    return 0;
}
