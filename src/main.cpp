#include <string.h>
#include "GameController.hpp"
#include "BoardView.hpp"
#include "StdioBoardView.hpp"
#include "NcursesBoardView.hpp"

int main(int argc, char *argv[]) {
    BoardView *view;
    if (argc > 1 && strcmp("curses", argv[1]) == 0) {
        view = new NcursesBoardView();
    }
    else {
        view = new StdioBoardView();
    }
    
    GameController gc(*view);

    GameMode gameMode = GameMode::Default;
    if (argc > 1 && strcmp("silent", argv[1]) == 0) {
        gameMode = GameMode::Silent;
    }

    gc.doGameCycle(gameMode);
    
    delete view;
    
    return 0;
}