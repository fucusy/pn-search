#include "game.h"


using namespace std;


// initializes moves from a file
void game::init(const string& filename) {
	auto ifs = ifstream(filename);

	string word;
	while(ifs >> word) {
		coords next_move; 
		if (!coords::try_parse(word, next_move)) throw runtime_error(word + " is invalid, coordinates expected");

		board_.place_move(next_move, current_player_);
		change_player();
		engine_->set_next_move(next_move);
	}
}

// starts the game
void game::run() {

	ui_->render(board_); // render the initial board

	while(true) {
		
		coords next_move;

		// if human is on move, read his next move and place it on board
		if(human_on_move_) {
			if(move_counter_ == 0) next_move = ui_->read_next_move(board_, "it's your turn");
			else next_move = ui_->read_next_move(board_, "AI played " + last_move_.to_string() + ", it's your turn");
		}
		// if computer is on move, calculate his next move and place it on board
		else {
			next_move = engine_->get_response();
			if (next_move.is_out_of_board() || !board_.is_empty(next_move)) throw std::runtime_error("engine played incorrect move");
		}
        board_.place_move(next_move, current_player_);
        change_player();
        engine_->set_next_move(next_move);

		last_move_ = next_move;
		++move_counter_;

		if (board_.is_winning(next_move)) {
			ui_->show_winning_screen(board_, !human_on_move_);
			return;
		} else {
			ui_->render(board_, last_move_);
		}
	}
}

