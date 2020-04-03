#pragma once

#include <sstream>
#include <optional>
#include <ncurses.h>
#include "BoardView.hpp"

class NcursesBoardView final : public BoardView {
    int cursorX = 0, cursorY = 0;
public:
    NcursesBoardView();
    std::optional<Position> retrieveNextPosition() override;
    void drawField(const vector<vector<CellContent> > &field) override;
    void printGameInfo(std::optional<Player> nextPlayer, GameState gameState) override;
    void printError(const std::string &s) override;
    ~NcursesBoardView() override;
};