#include <iostream>
#include <vector>

int main() {
    std::vector<int> tape(30000, 0);
    int ptr = 0;

    std::cout << (char)tape[ptr];
    tape[ptr] += 29;
    std::cout << (char)tape[ptr];
    tape[ptr] += 7;
    std::cout << (char)tape[ptr];
    std::cout << (char)tape[ptr];
    tape[ptr] += 3;
    std::cout << (char)tape[ptr];

    return 0;
}