#include "Test.hpp"
#include "BoardTest.hpp"

int main() {
    BoardTest bt;
    bt.runAllTests();
    return Test::showFinalResult();
}