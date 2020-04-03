#pragma once

#include <string>
#include <iostream>
#include <optional>
#include "Board.hpp"

class BoardView {
public:
    virtual std::optional<Position> retrieveNextPosition() = 0;
    virtual void drawField(const vector<vector<CellContent> > &field) = 0;
    virtual void printGameInfo(std::optional<Player> nextPlayer, GameState gameState) = 0;
    virtual void printError(const std::string &s) = 0;
    virtual ~BoardView() {};
};