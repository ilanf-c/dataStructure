#include "Insert_sort.h"
#include <stdio.h>
#include <stdlib.h>

/* helper: check if array is sorted (indices 1 to n-1) */
static int is_sorted(int *a, int n) {
    for (int i = 1; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) return 0;
    }
    return 1;
}

/* helper: copy array */
static void copy_array(int *dst, int *src, int n) {
    for (int i = 0; i < n; ++i) dst[i] = src[i];
}

int testInsertSort(){
    printf("\n**TEST[testInsertSort]**\n");
    int res = 0;
    
    /* Test data: array with sentinel at index 0, data at indices 1..8 */
    int n = 9;
    int test_data[] = {0, 5, 2, 8, 1, 9, 3, 6, 4}; /* sentinel=0, data=5,2,8,1,9,3,6,4 */
    int expected_sorted[] = {0, 1, 2, 3, 4, 5, 6, 8, 9};
    
    /* Test insert_sort */
    int *a1 = malloc(sizeof(int) * n);
    if (!a1) return 1;
    copy_array(a1, test_data, n);
    insert_sort(a1, n);
    
    int sorted1 = is_sorted(a1, n);
    printf("insert_sort: sorted=%d\n", sorted1);
    if (!sorted1) {
        fprintf(stderr, "insert_sort failed\n");
        res = 1;
    }
    
    /* Test insert_binary_sort */
    int *a2 = malloc(sizeof(int) * n);
    if (!a2) { free(a1); return 1; }
    copy_array(a2, test_data, n);
    insert_binary_sort(a2, n);
    
    int sorted2 = is_sorted(a2, n);
    printf("insert_binary_sort: sorted=%d\n", sorted2);
    if (!sorted2) {
        fprintf(stderr, "insert_binary_sort failed\n");
        res = 1;
    }
    
    /* Test shell_sort */
    int *a3 = malloc(sizeof(int) * n);
    if (!a3) { free(a1); free(a2); return 1; }
    copy_array(a3, test_data, n);
    shell_sort(a3, n);
    
    int sorted3 = is_sorted(a3, n);
    printf("shell_sort: sorted=%d\n", sorted3);
    if (!sorted3) {
        fprintf(stderr, "shell_sort failed\n");
        res = 1;
    }
    
    /* cleanup */
    free(a1);
    free(a2);
    free(a3);
    
    if (res == 0) printf("Insert sort tests passed\n");
    return res;
}
