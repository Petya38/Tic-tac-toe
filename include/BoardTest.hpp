#pragma once

#include "Test.hpp"
#include "Board.hpp"

class BoardTest : public Test {
private:
    void testGetNextPlayer1();
    void testGetNextPlayer2();
    void testGetNextPlayer3();
    void testGetNextPlayer4();
    void testMove1();
    void testMove2();
    void testMove3();
    void testMove4();
    void testMove5();
    void testInProgress();
    void testWinHorizontal();
    void testWinVertical();
    void testWinDiagonal1();
    void testWinDiagonal2();
    void testWinX();
    void testWinO();
    void testDraw();
    void testGetField1();
    void testGetField2();
    void testGetField3();
public:
    void runAllTests() override;
};