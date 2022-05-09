#include "class.cpp"

int main() {
    Sudoku board;

    std::cout << ((board.scan(0,0)) ? "Victory!" : "Problem.");

    return 0;
}
