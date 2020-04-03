#include "BoardTest.hpp"

void BoardTest::testGetNextPlayer1() {
    Board b;
    DO_CHECK(b.getNextPlayer() == Player::O);
}

void BoardTest::testGetNextPlayer2() {
    Board b;
    b.move({0, 0});
    DO_CHECK(b.getNextPlayer() == Player::X);
}

void BoardTest::testGetNextPlayer3() {
    Board b;
    b.move({0, 0});
    b.move({1, 1});
    DO_CHECK(b.getNextPlayer() == Player::O);
}

void BoardTest::testGetNextPlayer4() {
    Board b;
    for (size_t i = 3; i < 7; i++) {
        b.move({static_cast<int>(i), 0});
        b.move({static_cast<int>(i), 1});
    }
    b.move({7, 0});
    DO_CHECK(!b.getNextPlayer());
}

void BoardTest::testMove1() {
    Board b;
    b.move({0, 0});
    DO_CHECK(!b.canMove({0, 0}));
}

void BoardTest::testMove2() {
    Board b;
    b.move({0, 0});
    DO_CHECK(b.canMove({1, 1}));
}

void BoardTest::testMove3() {
    Board b;
    DO_CHECK(!b.canMove({-3, -3}));
}

void BoardTest::testMove4() {
    Board b;
    DO_CHECK(b.canMove({9, 9}));
}

void BoardTest::testMove5() {
    Board b;
    DO_CHECK(!b.canMove({0, 10}));
}

void BoardTest::testInProgress() {
    Board b;
    for (size_t i = 0; i < 10; i++) {
        b.move({0, static_cast<int>(i)});
    }
    b.move({1, 0});
    b.move({4, 5});
    b.move({5, 5});
    DO_CHECK(b.getState() == GameState::in_progress);
}

void BoardTest::testWinHorizontal() {
    Board b;
    for (size_t i = 3; i < 7; i++) {
        b.move({static_cast<int>(i), 0});
        b.move({static_cast<int>(i), 1});
    }
    b.move({7, 0});
    DO_CHECK(b.getState() == GameState::Win_O);
}

void BoardTest::testWinVertical() {
    Board b;
    for (size_t i = 3; i < 7; i++) {
        b.move({0, static_cast<int>(i)});
        b.move({1, static_cast<int>(i)});
    }
    b.move({0, 7});
    DO_CHECK(b.getState() == GameState::Win_O);
}

void BoardTest::testWinDiagonal1() {
    Board b;
    for (size_t i = 0; i < 5; i++) {
        b.move({2 * static_cast<int>(i), 0});
        b.move({static_cast<int>(i) + 2, static_cast<int>(i) + 2});
    }
    DO_CHECK(b.getState() == GameState::Win_X);
}

void BoardTest::testWinDiagonal2() {
    Board b;
    for (size_t i = 0; i < 5; i++) {
        b.move({2 * static_cast<int>(i), 0});
        b.move({static_cast<int>(i) + 2, 8 - static_cast<int>(i)});
    }
    DO_CHECK(b.getState() == GameState::Win_X);
}

void BoardTest::testWinX() {
    Board b;
    for (size_t i = 0; i < 5; i++) {
        b.move({2 * static_cast<int>(i), 9});
        b.move({static_cast<int>(i), 0});
    }
    DO_CHECK(b.getState() == GameState::Win_X);
}

void BoardTest::testWinO() {
    Board b;
    for (size_t i = 0; i < 4; i++) {
        b.move({0, static_cast<int>(i)});
        b.move({1, static_cast<int>(i)});
    }
    b.move({0, 4});
    DO_CHECK(b.getState() == GameState::Win_O);
}

void BoardTest::testDraw() {
    Board b;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            if (i < 4) {
                b.move({static_cast<int>(j), static_cast<int>(i)});
            }
            else if (i < 7) {
                b.move({(static_cast<int>(j) + 1) % 10, static_cast<int>(i)});
            }
            else {
                b.move({(static_cast<int>(j) + 2) % 10, static_cast<int>(i)});
            }
        }
    }
    DO_CHECK(b.getState() == GameState::Draw);
}

void BoardTest::testGetField1() {
    Board b;
    vector<vector<CellContent> > v(BOARDSIZE, vector<CellContent>(BOARDSIZE, CellContent::None));
    DO_CHECK(b.getField() == v);
}

void BoardTest::testGetField2() {
    Board b;
    vector<vector<CellContent> > v(BOARDSIZE, vector<CellContent>(BOARDSIZE, CellContent::None));
    
    b.move({0, 0});
    v[0][0] = CellContent::O;

    b.move({3, 3});
    v[3][3] = CellContent::X;

    b.move({8, 9});
    v[9][8] = CellContent::O;

    b.move({1, 1});
    v[1][1] = CellContent::X;

    DO_CHECK(b.getField() == v);
}

void BoardTest::testGetField3() {
    Board b;
    vector<vector<CellContent> > v(BOARDSIZE, vector<CellContent>(BOARDSIZE, CellContent::None));
    
    for (size_t i = 0; i < 5; i++) {
        b.move({2 * static_cast<int>(i), 0});
        v[0][2 * i] = CellContent::O;
        
        b.move({static_cast<int>(i), 1});
        v[1][i] = CellContent::X;
    }

    DO_CHECK(b.getField() == v);
}

void BoardTest::runAllTests() {
    testGetNextPlayer1();
    testGetNextPlayer2();
    testGetNextPlayer3();
    testGetNextPlayer4();
    testMove1();
    testMove2();
    testMove3();
    testMove4();
    testMove5();
    testInProgress();
    testWinHorizontal();
    testWinVertical();
    testWinDiagonal1();
    testWinDiagonal2();
    testWinX();
    testWinO();
    testDraw();
    testGetField1();
    testGetField2();
    testGetField3();
}