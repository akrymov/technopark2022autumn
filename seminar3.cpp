#include <iostream>
#include <vector>

int partition(int* arr, int l, int r) {
    int pivot_idx = l + (r - l) / 2;
    int pivot = arr[pivot_idx];

    std::swap(arr[pivot_idx], arr[r - 1]);

    int i = 0;
    int j = r - 1;
    while (i < j) {
        for(; arr[i] < pivot; ++i);
        while (!(arr[j] < pivot)) j--;

        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    std::swap(arr[i], arr[r - 1]);
    return i;
}

void kth_element(int* arr, int size, int k) {
    int l = 0;
    int r = size;
    while (l < r) {
        int m = partition(arr, l , r);
        if (m == k) {
            return;
        } else if (m < k) {
            l = m + 1;
        } else {
            r = m;
        }
    }
}


void count_sort_unstable(int* arr, int size, int R) {
    int* counter = new int[R];
    for (int i = 0; i < R; ++i) {
        counter[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        counter[arr[i]]++;
    }
    int arr_idx = 0;
    for (int counter_idx = 0; counter_idx < R; ++counter_idx) {
        while (counter[counter_idx] > 0) {
            arr[arr_idx++] = counter_idx;
            counter[counter_idx]--;
        }
    }
    delete[] counter;
}


void count_sort_stable(int* arr, int size, int R) {
    int* counter = new int[R];
    for (int i = 0; i < R; ++i) {
        counter[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        counter[arr[i]]++;
    }

    for (int i = 0; i < R - 1; ++i) {
        counter[i + 1] += counter[i];
    }

    int* tmp_arr = new int[size];
    for (int i = size - 1; i >= 0; --i) {
        tmp_arr[--counter[arr[i]]] = arr[i];
    }

    for (int i = 0; i < size; ++i) {
        arr[i] = tmp_arr[i];
    }

    delete[] tmp_arr;
    delete[] counter;
}


int main() {
    //1,2,3,4,5,,,
    std::vector<int> arr = {5,4,3,2,1,9,5,8,6,7};

    size_t k = 3;
    kth_element(&arr[0], arr.size(), k);
    kth_element(&arr[0], arr.size(), 0);

    std::cout << "kth_element: " << arr[0] << std::endl;
    std::cout << "kth_element: " << arr[k] << std::endl;

    count_sort_stable(&arr[0], arr.size(), 10);

    for (auto c : arr) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}
