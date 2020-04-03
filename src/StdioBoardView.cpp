#include "StdioBoardView.hpp"

std::optional<Position> StdioBoardView::retrieveNextPosition() {
    std::optional<Position> pos;
    std::cin.exceptions(std::istream::failbit | std::istream::badbit);
    try {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream strStream(line);
        std::vector<std::string> tokens;
        std::string token;
        while (strStream >> token) {
            tokens.push_back(token);
        }
        if (tokens.size() != 2) {
            throw 0;
        }
        pos = {std::stoi(tokens[1]), std::stoi(tokens[0])};
    }
    catch (...) {
        pos = std::nullopt;
    }
    return pos;
}

void StdioBoardView::drawField(const vector<vector<CellContent> > &field) {
    std::cout.exceptions(std::ostream::failbit | std::ostream::badbit);
    try {
        std::cout << std::endl;
        for (const auto &line : field) {
            for (const auto &player : line) {
                std::cout << player;
            }
            std::cout << '\n';
        }
        std::cout << std::flush;
    }
    catch (std::ostream::failure e) {
        std::cerr << "Write error" << std::endl;
        exit(-1);
    }
}

void StdioBoardView::printGameInfo(std::optional<Player> nextPlayer, GameState gameState) {
    if (gameState == GameState::in_progress) {
        assert(nextPlayer);
        std::cout << *nextPlayer << " move: " << std::flush;
        assert(!std::cout.fail());
    }
    else {
        std::cout << gameState << std::endl;
        assert(!std::cout.fail());
    }
}

void StdioBoardView::printError(const std::string &s) {
    std::cout << s << std::endl;
    assert(!std::cout.fail());
}