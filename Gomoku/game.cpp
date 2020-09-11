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

	while(true) {
		
		coords next_move;

		// if human is on move, read his next move and place it on board
		if(human_on_move_) {
		    next_move = coords(7, 8);
		}
		// if computer is on move, calculate his next move and place it on board
		else {
			next_move = engine_->get_response();
			if (next_move.is_out_of_board() || !board_.is_empty(next_move)) throw std::runtime_error("engine played incorrect move");
			printf("AI select: %s\n", next_move.to_string().c_str());
            if(move_counter_ > 0){
                exit(0);
            }
		}
        board_.place_move(next_move, current_player_);
        change_player();
        engine_->set_next_move(next_move);

		last_move_ = next_move;
		++move_counter_;
	}
}

