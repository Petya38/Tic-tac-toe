#include <Board.hpp>

std::ostream& operator<<(std::ostream &os, const GameState &gameState) {
    switch(gameState) {
    case GameState::in_progress:
        os << "In progress..";
        break;
    case GameState::Win_X:
        os << "X wins!";
        break;
    case GameState::Win_O:
        os << "O wins!";
        break;
    case GameState::Draw:
        os << "Draw.";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const CellContent &cellContent) {
    switch (cellContent) {
    case CellContent::None:
        os << '.';
        break;
    case CellContent::X:
        os << 'X';
        break;
    case CellContent::O:
        os << 'O';
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const Player &player) {
    switch(player) {
    case Player::X:
        os << 'X';
        break;
    case Player::O:
        os << 'O';
        break;
    }
    return os;
}

bool operator==(const Position &pos, const Position &other) {
    return pos.x == other.x && pos.y == other.y;
}

Position operator*(const Position &pos, int k) {
    return {pos.x * k, pos.y * k};
}
Position operator+(const Position &pos, const Position &anotherPos) {
    return {pos.x + anotherPos.x, pos.y + anotherPos.y};
}

Board::Board() : field(BOARDSIZE, vector<CellContent>(BOARDSIZE, CellContent::None)) {}

bool Board::isInsideField(const Position &pos) const {
    return 0 <= pos.x && 0 <= pos.y && pos.x < static_cast<int>(BOARDSIZE) && pos.y < static_cast<int>(BOARDSIZE);
}

bool Board::OnLine5(const Position &pos, const Position &dPos) const {
    if (!isInsideField(pos)) {
        return false;
    }
    for (size_t i = 1; i < 5; i++) {
        Position pos_ = pos + dPos * i;
        if (!isInsideField(pos_) || field[pos.y][pos.x] != field[pos_.y][pos_.x]) {
            return false;
        }
    }
    return true;
}

bool Board::canMove(const Position &pos) const {
    return isInsideField(pos) && field[pos.y][pos.x] == CellContent::None;
}

void Board::move(const Position &pos) {
    assert(canMove(pos));
    assert(nextPlayer);
    field[pos.y][pos.x] = static_cast<CellContent>(*nextPlayer);
    if (getState() == GameState::in_progress) {
        if (nextPlayer == Player::X) {
            nextPlayer = Player::O;
        }
        else {
            nextPlayer = Player::X;
        }
    }
    else {
        nextPlayer = std::nullopt;
    }
}

GameState Board::getState() const {
    // здесь можно было бы использовать mutable, но эта функция всего 1 раз вызывается повторно, а её реализация тогда заментно усложнится
    bool game_in_progress = false;
    for (size_t i = 0; i < BOARDSIZE; i++) {
        for (size_t j = 0; j < BOARDSIZE; j++) {
            Position pos = {static_cast<int>(j), static_cast<int>(i)};
            if (field[i][j] != CellContent::None && 
                    (
                    OnLine5(pos, Directions[0]) || 
                    OnLine5(pos, Directions[1]) || 
                    OnLine5(pos, Directions[2]) ||
                    OnLine5(pos, Directions[3])
                    )
                ) {
                if (field[i][j] == CellContent::X) {
                    return GameState::Win_X;
                }
                else {
                    return GameState::Win_O;
                }
            }

            if (field[i][j] == CellContent::None) {
                game_in_progress = true;
            }
        }
    }
    if (game_in_progress) {
        return GameState::in_progress;
    }
    else {
        return GameState::Draw;
    }
}

std::optional<Player> Board::getNextPlayer() const {
    return nextPlayer;
}

const vector<vector<CellContent> > &Board::getField() const {
    return field;
}