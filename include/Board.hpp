#pragma once

#include <cstddef>
#include <vector>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <optional>

static const size_t BOARDSIZE = 10;

using std::vector;

enum class GameState {
    in_progress,
    Win_X,
    Win_O,
    Draw
};
std::ostream& operator<<(std::ostream &os, const GameState &gameState);

enum class CellContent
{
    X,
    O,
    None
};
std::ostream& operator<<(std::ostream &os, const CellContent &cellContent);

enum class Player {
    X,
    O
};
std::ostream& operator<<(std::ostream &os, const Player &player);

struct Position
{
    int x, y;
};
bool operator==(const Position &pos, const Position &other);
Position operator*(const Position &pos, int k);
Position operator+(const Position &pos, Position &anotherPos);

class Board final {
public:
    explicit Board();
    bool canMove(const Position &pos) const;
    void move(const Position &pos);
    GameState getState() const;
    std::optional<Player> getNextPlayer() const;
    const vector<vector<CellContent> > &getField() const;
private:
    std::optional<Player> nextPlayer = Player::O;
    vector<vector<CellContent> > field;
    bool isInsideField(const Position &pos) const;
    bool OnLine5(const Position &pos, const Position &dPos) const;
    const Position Directions[4] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}};
};