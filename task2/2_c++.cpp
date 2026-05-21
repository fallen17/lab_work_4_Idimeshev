#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool duplic_digs(int n) {
    int counts[10] = {0};
    int temp = abs(n);
    while (temp > 0) {
        int digit = temp % 10;
        counts[digit]++;
        if (counts[digit] >= 2) return true;
        temp /= 10;
    }
    return false;
}

void print_vec(const vector<int>& vec, const string& label) {
    cout << label << ": ";
    for (int x : vec) cout << x << " ";
    cout << endl;
}

void gen_arrays(int n, vector<int>& arr1, vector<int>& arr2, knuth_b& gen) {
    uniform_int_distribution<> dist(10, 100);
    for (int i = 0; i < n; i++) {
        arr1[i] = dist(gen);
        arr2[i] = dist(gen);
    }
    cout << "\n--- Task 1: Initial Arrays ---" << endl;
    print_vec(arr1, "arr1");
    print_vec(arr2, "arr2");
}

void display_prime(const vector<int>& arr1, const vector<int>& arr2) {
    cout << "\n--- Task 2: Primes in range [10, 70] ---" << endl;
    auto printFiltered = [](const vector<int>& vec, const string& name) {
        cout << name << ": ";
        for (int x : vec) {
            if (x >= 10 && x <= 70 && is_prime(x)) cout << x << " ";
        }
        cout << endl;
    };
    printFiltered(arr1, "From arr1");
    printFiltered(arr2, "From arr2");
}

void sort_arrs(vector<int>& arr1, vector<int>& arr2) {
    sort(arr1.begin(), arr1.end(), greater<int>());
    sort(arr2.begin(), arr2.end());
    cout << "\n--- Task 3: Sorted Arrays ---" << endl;
    print_vec(arr1, "arr1 (descending)");
    print_vec(arr2, "arr2 (ascending)");
}

void swap_elems(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size();
    for (int i = 0; (2 * i + 1) < n && (2 * i) < n; i++) {
        swap(arr1[2 * i + 1], arr2[2 * i]);
    }
    cout << "\n--- Task 4: After swapping arr1[odd] with arr2[even] ---" << endl;
    print_vec(arr1, "arr1");
    print_vec(arr2, "arr2");
}

void proc_duplicate(int n, knuth_b& gen) {
    uniform_int_distribution<> dist(10000, 20000);
    vector<int> arr3(n);
    for (int i = 0; i < n; i++) {
        arr3[i] = dist(gen);
    }
    
    cout << "\n--- Task 5: New Array [10000, 20000] ---" << endl;
    print_vec(arr3, "arr3");

    vector<int> result;
    for (int x : arr3) {
        if (duplic_digs(x)) {
            result.push_back(x);
        }
    }
    print_vec(result, "Numbers with matching digits");
}

int main() {
    random_device rd;
    knuth_b gen(rd());

    int n;
    cout << "Enter n for tasks 1-4 (n >= 10): ";
    cin >> n;
    if (n < 10) n = 10;

    int n2;
    cout << "\nEnter n2 for task 5 (n >= 15): ";
    cin >> n2;
    if (n2 < 15) n2 = 15;

    vector<int> arr1(n), arr2(n);

    gen_arrays(n, arr1, arr2, gen);
    display_prime(arr1, arr2);
    sort_arrs(arr1, arr2);
    swap_elems(arr1, arr2);
    proc_duplicate(n2, gen);

    return 0;
}