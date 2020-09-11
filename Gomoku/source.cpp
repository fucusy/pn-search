#include "game.h"

#include <ctime>


using namespace std;


int main(int argc, char** argv) { // the optional console arguments is a path to a logged game file for debug purposes
	srand(unsigned(time(nullptr))); // initialize random number generator

	bool player_starts = false; // ai starts the first game	
	while(true) {
		game g(player_starts); // create a game
		if (argc > 1) g.init(argv[1]); // load a saved game board if requested
		g.run(); // start the game

		player_starts = !player_starts; // change the player who starts
	}
}