#include <GameController.hpp>

GameController::GameController(BoardView &boardView_) : boardView(boardView_) {}

void GameController::doGameCycle(GameMode gameMode) {
    Board board;
    while (board.getState() == GameState::in_progress) {
        std::optional<Position> pos;
        if (gameMode != GameMode::Silent) {
            boardView.drawField(board.getField());
        }
        while (true) {
            boardView.printGameInfo(board.getNextPlayer(), board.getState());
            pos = boardView.retrieveNextPosition();
            if (pos && pos == forceEndGamePos) {
                return;
            }
            if (pos && board.canMove(*pos)) {
                break;
            }
            else {
                boardView.printError("Bad move!");
            }
        }
        board.move(*pos);
    }
    boardView.drawField(board.getField());
    boardView.printGameInfo(board.getNextPlayer(), board.getState());  
}
