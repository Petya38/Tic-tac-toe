#include "NcursesBoardView.hpp"

NcursesBoardView::NcursesBoardView() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    move(13, 0);
    printw("=======================\nUse arrows to select the cell then press space.\nPress x to exit.");
}

std::optional<Position> NcursesBoardView::retrieveNextPosition() {
    move(cursorY, cursorX);
    refresh();
    int inputChar;
    do {
        inputChar = getch();
        switch(inputChar) {
            case KEY_UP:
                if (cursorY > 0) {
                    cursorY--;
                }
                break;
            case KEY_DOWN:
                if (cursorY + 1 < static_cast<int>(BOARDSIZE)) {
                    cursorY++;
                }
                break;
            case KEY_LEFT:
                if (cursorX > 0) {
                    cursorX--;
                }
                break;
            case KEY_RIGHT:
                if (cursorX + 1 < static_cast<int>(BOARDSIZE)) {
                    cursorX++;
                }
                break;
        }
        move(cursorY, cursorX);
        refresh();
    } while (inputChar != ' ' && inputChar != 'x');
    int x = cursorX;
    int y = cursorY;
    if (inputChar == 'x') {
        x = y = -1;
    }
    return std::optional<Position>({x, y});
}

void NcursesBoardView::drawField(const vector<vector<CellContent> > &field) {
    move(0, 0);
    std::stringstream ss;
    for (const auto &line : field) {
        for (const auto &player : line) {
            ss << player;
        }
        ss << '\n';
    }
    printw(ss.str().c_str());
    refresh();
}

void NcursesBoardView::printGameInfo(std::optional<Player> nextPlayer, GameState gameState) {
    std::stringstream ss;
    move(11, 0);
    if (gameState == GameState::in_progress) {
        assert(nextPlayer);
        ss << *nextPlayer << " move.";
        printw(ss.str().c_str());
        refresh();
    }
    else {
        ss << gameState << "\n" << "Press any key to exit.";
        clrtoeol();
        printw(ss.str().c_str());
        refresh();
        getch();
    }
}

void NcursesBoardView::printError(const std::string &s) {
    (void)(s);
}

NcursesBoardView::~NcursesBoardView() {
    endwin();
}