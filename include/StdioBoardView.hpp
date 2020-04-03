#pragma once

#include <optional>
#include <sstream>
#include "BoardView.hpp"

class StdioBoardView final : public BoardView {
public:
    std::optional<Position> retrieveNextPosition() override;
    void drawField(const vector<vector<CellContent> > &field) override;
    void printGameInfo(std::optional<Player> nextPlayer, GameState gameState) override;
    void printError(const std::string &s) override;
    ~StdioBoardView() override = default;
};