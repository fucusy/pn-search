#ifndef COORDS_H
#define COORDS_H


#include "parameters.h"

#include <cstdlib>
#include <string>


// values 0-15 are sufficient, but bounds of +-5 units are needed in order to check extreme situations 
// such as handling requests that are out of the board - that's wht a signed integer is needed
using coord = int_fast8_t;

enum figure : uint_fast8_t {
	OUTSIDE = 0, BLACK = 1, WHITE = 2, NONE = 3
};

enum direction : uint_fast8_t {
	HORIZONTAL, VERTICAL, DIAGONAL, ANTI_DIAGONAL
};

// represents position on board
struct coords;

// represents offset / relative position
using coords_offset = coords;



/* COORDS
 *
 * A simple structure representing the 2D coordinates on the game board.
 * 
 * In addition to absolute positions, reletive positions (sementicaly defined as coords_offset) are
 * represented by this structure as well.
 * 
 */

struct coords {
	coord x, y;

	coords() : coords(INCORRECT_POSITION) {}
	coords(coord x, coord y) : x(x), y(y) {}
	std::string to_string() const { return char('a' + x) + std::to_string(y + 1); }
	bool is_out_of_board() const { return x < 0 || x >= constants::BOARD_SIZE || y < 0 || y >= constants::BOARD_SIZE; }
	coords operator +(coords_offset pos) const { return coords(x + pos.x, y + pos.y); }
	coords operator -(coords_offset pos) const { return coords(x - pos.x, y - pos.y); }
	coords operator *(coord a) const { return coords(a*x, a*y); }
	bool operator ==(coords other) const { return x == other.x && y == other.y; }
	bool operator !=(coords other) const { return x != other.x || y != other.y; }

	static coords get_random() { return coords(std::rand() % constants::BOARD_SIZE, std::rand() % constants::BOARD_SIZE); }

	// parses $input into $output; returns TRUE if parsing position into $output was successful, otherwise returns FALSE
	static bool try_parse(const std::string& input, coords& output);					

	// "unit" vectors of horizontal, vertical, diagonal and anti-diagonal direction
	static const coords_offset DIRECTIONS[4];
	static const coords INCORRECT_POSITION;

	// allows coords to be used as a key in hash tables
	struct hasher {
		std::size_t operator()(coords pos) const {
			return (std::hash<coord>()(pos.x) * 397) ^ std::hash<coord>()(pos.y);
		}
	};
};

#endif