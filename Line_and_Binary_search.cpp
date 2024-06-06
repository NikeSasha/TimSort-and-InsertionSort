#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

int line_search(const vector<int>& the_array, int item, int start, int end) {
    for (int i = start; i < end; i++) {
        if (the_array[i] == item) {
            return i;
        }
    }
    return -1;
}

int binary_search(const vector<int>& the_array, int item, int start, int end) {
    if (start == end) {
        if (the_array[start] >= item) {
            return start;
        }
        else {
            return start + 1;
        }
    }
    if (start > end) {
        return start;
    }

    int mid = (start + end) / 2;
    if (the_array[mid] < item) {
        return binary_search(the_array, item, mid + 1, end);
    }
    else if (the_array[mid] > item) {
        return binary_search(the_array, item, start, mid - 1);
    }
    else {
        return mid;
    }
}

void mass(vector <int>& vec, int n) {
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        vec[i] = i + 1;
    }
    sort(vec.begin(), vec.end());
}

int main(){
    vector <int> vec;
    mass(vec, 1000000);
    chrono::duration <double> time;
    auto start = chrono::steady_clock::now();
    int bsearch = binary_search(vec, 500005, 0, 999999);
    auto end = chrono::steady_clock::now();
    time = end - start;
    cout << "bin_search result: " << bsearch << "\n";
    cout << "time " << time.count() << "\n";

    start = chrono::steady_clock::now();
    int lsearch = line_search(vec, 500005, 0, 999999);
    end = chrono::steady_clock::now();
    time = end - start;
    cout << "line search result: " << lsearch << "\n";
    cout << "time " << time.count() << "\n";
}