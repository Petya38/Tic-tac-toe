#include "Test.hpp"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    if (!expr) {
        std::cout << "In " << filename << " on line " << lineNum << " in " << func << std::endl;
        failedNum++;
    }
    Test::totalNum++;
} 

bool Test::showFinalResult() {
    std::cout << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Test cases: " << Test::totalNum << " | ";
    std::cout << Test::totalNum - Test::failedNum << " passed | ";
    std::cout << Test::failedNum << " failed" << std::endl; 
    std::cout << "Status: ";
    if (Test::failedNum == 0) {
        std::cout << "SUCCESS!";
    }
    else {
        std::cout << "FAILED!";
    }
    std::cout << std::endl;
    return Test::failedNum == 0;
}
