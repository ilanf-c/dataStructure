#include "Insert_sort.h"

void insert_sort(int *a, int n){
    for(int i = 2; i<n; ++i){
        a[0] = a[i];
        int j;
        for(j = i-1; j>0 && a[0]<a[j]; --j){
            a[j+1] = a[j];
        }
        a[j+1] = a[0];
    }
}

void insert_binary_sort(int *a, int n){
    for(int i = 2; i<n; ++i){
        a[0] = a[i];
        int l = 1, h = i-1;
        while(l<=h){
            int mid = (l+h)/2;
            if (a[0] > a[mid]) l = mid + 1;
            else h = mid - 1;
        }
        for(int j = i-1; j>=l; --j){
            a[j+1] = a[j];
        }
        a[l] = a[0];
    }
}

void shell_sort(int *a, int n){
    for(int d = n/2; d>=1; d = d/2){
        for(int i = d+1; i<n; ++i){
            a[0] = a[i];
            int j;
            for(j = i-d; j>0 && a[0]<a[j]; j-=d){
                a[j+d] = a[j];
            }
            a[j+d] = a[0];
        }
    }
}

