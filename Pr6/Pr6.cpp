#include <iostream>
using namespace std;
int* get_ptr() {
    int* x = new int(5);
    return x;
}
int main() {
    int* ptr = get_ptr();
    stdcout << *ptr;
    delete ptr;
    return 0;
}