#include <bits/stdc++.h>

using namespace std;

template <typename T, typename Compare = less<>>   // C++14 起支持透明比较器
void merge(vector<T>& a, int l, int mid, int r, vector<T>& tmp, Compare cmp = Compare{}) {
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
        tmp[k++] = cmp(a[i], a[j]) ? a[i++] : a[j++];
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r)   tmp[k++] = a[j++];
    for (i = 0; i < k; ++i) a[l + i] = tmp[i];
}

template <typename T, typename Compare = less<>>
void mergeSort(vector<T>& a, int l, int r, vector<T>& tmp, Compare cmp = Compare{}) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSort(a, l, mid, tmp, cmp);
    mergeSort(a, mid + 1, r, tmp, cmp);
    merge(a, l, mid, r, tmp, cmp);
}

template <typename T, typename Compare = less<>>
void mergeSort_(vector<T>& a, Compare cmp = Compare{}) {
    if (a.empty()) return;
    vector<T> tmp(a.size());
    mergeSort(a, 0, (int)a.size() - 1, tmp, cmp);
}



