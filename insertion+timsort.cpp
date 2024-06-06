#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
const int RUN = 32;

int binary_search(const vector<int>& the_array, int item, int start, int end) {
    if (start == end) {
        if (the_array[start] > item) {
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

int binary_search_spad(const vector<int>& the_array, int item, int start, int end) {
    if (start == end) {
        if (the_array[start] > item) {
            return start + 1;
        }
        else {
            return start;
        }
    }
    if (start > end) {//
        return start;
    }

    int mid = (start + end) / 2;
    if (item < the_array[mid]) {
        return binary_search_spad(the_array, item, mid + 1, end);
    }
    else if (item > the_array[mid]) {
        return binary_search_spad(the_array, item, start, mid - 1);
    }
    else {
        return mid;
    }
}

vector<int> merge(const vector<int>& left, const vector<int>& right) {
    vector<int> result;
    auto it1 = left.begin();
    auto it2 = right.begin();

    //cout << "CHECK: " << left[start_it1 - left.begin()] << " " << left[0] << "\n";

    while (it1 != left.end() && it2 != right.end()) {
        if (*it1 < *it2) {
            result.push_back(*it1);
            ++it1;
        }
        else {
            result.push_back(*it2);
            ++it2;
        }
    }

    while (it1 != left.end()) {
        result.push_back(*it1);
        ++it1;
    }

    while (it2 != right.end()) {
        result.push_back(*it2);
        ++it2;
    }

    return result;
}

vector<int> timsort(vector<int>& the_array, chrono::duration <double>& time) {
    vector<vector<int>> runs;
    int l = the_array.size();

    auto start = chrono::steady_clock::now();

    for (int j = 0; j < l; j += RUN) {
        vector<int> new_run = { the_array[j], the_array[j + 1] };
        if (new_run[0] < new_run[1]) {
            for (int i = 2; i < min(RUN, l - j); ++i) {
                if (new_run[i - 1] <= the_array[j + i]) {
                    new_run.push_back(the_array[j + i]);
                }
                else {
                    int value = the_array[j + i];
                    int pos = binary_search(new_run, value, 0, i - 1);
                    new_run.insert(new_run.begin() + pos, value);
                }
            }

            runs.push_back(new_run);
            new_run.clear();
        }
        else {
            for (int i = 2; i < min(RUN, l - j); ++i) {
                if (new_run[i - 1] >= the_array[j + i]) {
                    new_run.push_back(the_array[j + i]);
                }
                else {
                    int value = the_array[j + i];
                    int pos = binary_search_spad(new_run, value, 0, i - 1);
                    new_run.insert(new_run.begin() + pos, value);
                }
            }

            vector <int> reverse(min(RUN, l - j));
            for (int i = 0; i < min(RUN, l - j); i++) {
                reverse[i] = new_run[min(RUN, l - j) - i - 1];
            }
            for (int i = 0; i < min(RUN, l - j); i++) {
                new_run[i] = reverse[i];
            }

            runs.push_back(new_run);
            new_run.clear();
        }
    }

    vector<int> sorted_array;
    for (auto& run : runs) {
        sorted_array = merge(sorted_array, run);
    }

    auto end = chrono::steady_clock::now();
    time = end - start;

    return sorted_array;
}

void output(vector <int>& sorted_array) {
    for (auto& val : sorted_array) {
        cout << val << " ";
    }
    cout << "\n\n\n";
}

void generateWorstTim(vector <int>& the_array, int quan) {
    the_array[0] = rand() % quan + 1;
    the_array[1] = rand() % quan + 1;
    for (int i = 2; i < quan; i++) {
        if (the_array[i - 2] < the_array[i - 1]) {
            the_array[i] = (rand() % the_array[i - 1]) % quan;
        }
        else {
            the_array[i] = rand() % quan + the_array[i - 1];
        }
    }
}

void generateWorstIns(vector <int>& the_array, int quan) {
    for (int i = 0; i < quan; i++) {
        the_array[i] = (rand() % quan + 1);
    }
    sort(the_array.begin(), the_array.end(), greater<int>());
}

void generateAvgIns(vector <int>& the_array, int quan) {
    for (int i = 0; i < quan; i++) {
        the_array[i] = (rand() % quan + 1);
    }
}

void generateAvgTim(vector <int>& the_array, int quan) {
    for (int i = 0; i < quan; i++) {
        the_array[i] = (rand() % quan + 1);
    }
    int a;
    for (int i = 0; i < 10; i++) {
        a = rand() % (quan - 50);
        sort(the_array.begin() + a, the_array.begin() + a + quan/200);
    }
}

void generateBest(vector <int>& the_array, int quan) {
    for (int i = 0; i < quan; i++) {
        the_array[i] = (rand() % quan + 1);
    }
    sort(the_array.begin(), the_array.end());
}

void insertionSort(vector<int>& array, chrono::duration <double>& time) {
    auto start = chrono::steady_clock::now();
    int size = array.size();
    for (int step = 1; step < size; step++) {
        int key = array[step];
        int j = step - 1;
        while (j >= 0 and key < array[j]) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
    auto end = chrono::steady_clock::now();
    time = end - start;
}

void tentimes(int ch) {
    chrono::duration <double> time;
    int n = 80000;
    for (int var = 0; var < 10; var++) {
        srand(var);
        vector<int> the_array(n), copy(n);

        if (ch == 1) {
            generateWorstTim(the_array, n);
        }
        else if (ch == 2) {
            generateAvgTim(the_array, n);
        }
        else if (ch == 3) {
            generateBest(the_array, n);
        }
        else if (ch == 4) {
            generateWorstIns(the_array, n);
        }
        else if (ch == 5) {
            generateAvgIns(the_array, n);
        }

        copy = the_array;

        copy = timsort(copy, time);
        cout << "Time: " << time.count() << "\n";
        //output(copy);

        copy = the_array;

        insertionSort(copy, time);
        cout << "Time: " << time.count() << "\n";
        
        //output(copy);
    }
}


int main() {
    tentimes(5);

    /*= { 15, 16, 17, 18, 19, 20, 30, 29, 28, 27, 26, 25,
                           24, 23, 21, 22, 1, 2, 3, 4, 5, 6, 7, 8, 9, 14, 13,
                           12, 11, 10, 31, 32, 33, 35, 34 }*/



    //output(the_array);

    /*the_array.resize(20000);
    //generate(the_array, 20000);
    //output(the_array);

    //the_array.resize(40000);
    //generate(the_array, 40000);
    //output(the_array);

    //the_array.resize(80000);
    //generate(the_array, 80000);
    //output(the_array);

    //the_array.resize(100000);
    //generate(the_array, 100000);
    //output(the_array);

    the_array.resize(500000);
    generate(the_array, 500000);
    output(the_array);*/

    return 0;
}
