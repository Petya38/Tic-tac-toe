#pragma once

#include <optional>
#include "Board.hpp"
#include "BoardView.hpp"

static constexpr Position forceEndGamePos = {-1, -1};

enum class GameMode {
    Default,
    Silent
};

class GameController final {
    BoardView &boardView;
public:
    void doGameCycle(GameMode gameMode = GameMode::Default);
    GameController(BoardView &boardView_);
};