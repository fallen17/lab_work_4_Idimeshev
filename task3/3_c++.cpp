#include <iostream>
#include <cstdint>

using namespace std;

uint32_t xorshift32(uint32_t& x) {
    x ^= (x << 13);
    x ^= (x >> 17);
    x ^= (x << 5);
    return x;
}

int main() {
    uint32_t seed = 123456789;
    int N = 5;                 

    cout << "seed " << seed << endl;
    cout << "printing " << N << " generated numbers:" << endl;

    uint32_t currentState = seed;
    cout << currentState << " ";

    for (int i = 1; i < N; ++i) {
        cout << xorshift32(currentState) << " ";
    }
    
    cout << endl;
    return 0;
}