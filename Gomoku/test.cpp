#include "game.h"

#include <ctime>


using namespace std;


int main(int argc, char** argv) { // the optional console arguments is a path to a logged game file for debug purposes
	srand(unsigned(time(nullptr))); // initialize random number generator

	bool player_starts = false; // ai starts the first game
	printf("hello");
    bit_board a = bit_board();
}