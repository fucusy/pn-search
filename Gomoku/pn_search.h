#ifndef PN_SEARCH_H
#define PN_SEARCH_H

#include "bit_board.h"
#include "pn_node.h"
#include "abstract_engine.h"
#include "board_list_selector.h"
#include "zobrist_hash.h"
#include "transposition_table.h"

#include <stack>
#include <ratio>
#include <chrono>


/* PROOF-NUMBER SEARCH
 * 
 * Class implementing proof-number search as described in Searching for Solutions in Games and Artificial Intelligence
 * (http://digitalarchive.maastrichtuniversity.nl/fedora/get/guid:36b5cf0a-cf06-4602-afdb-1af04d65c23b/ASSET1)
 * 
 * It is basically a best-first search, where a node in the DAG to expand is selected by calculating the lower bound on 
 * the number of nodes that are needed to be expanded in order to proof a win in the game. The node with the lowest lower
 * bound is then selected.
 * 
 * When expanding the node, it is first checked, whether a node with equivalent state was already explored via a transposition
 * table, if it was, then it is just connected to the equavalent node's children.
 * Otherwise it is checked whether there is a win by continuous threats via dependency-based search.
 * If there is not, then the best moves (based on the overlap evaluation, selected via board_list_selector) are added as children.
 * 
 * The search continues as long as a win/lost isn't proven and the number of nodes doesn't exceed $SIZE_LIMIt_
 * 
 */

class pn_search : public abstract_engine {
public:
	pn_search() : move_number_(0) { player_ = current_player_ = WHITE; }

	// informs the engine that a new move was placed on board
	void set_next_move(coords pos) override;

	// engine returns his best response to actual board, doesn't update current state
	coords get_response() override;

private:
	// starts developing the tree
	void search();

	// selects the best answer to the last moves according to the searched tree
	coords select_next_move() const;

	// selects the node that will most likely end the search
	pn_node& select_most_proving();

	// adds children to the most-proving node
	void develop_node(pn_node& node);

	// updates actual state of the board
	void update_state(coords position);

	// restarts state of the board to the initial root value
	void restart_state();


	board_list_selector base_selector_; // selector corresponding to the root node
	board_list_selector selector_; // selector corresponding to the actual node
	figure player_; // figure corresponding to the actual node
	zobrist_hash hash_; // figure corresponding to the actual node; hash value for the root is 0
	std::stack<coords> position_history_; // stack of moves from root to the developed node

	transposition_table transposition_table_;
	pn_node root_;
	coords last_move_ = coords::INCORRECT_POSITION;

	size_t move_number_;


#if defined(_DEBUG) || defined(TEST)
	// traverses the search tree through command line 
	void debug(std::chrono::duration<double, std::milli> duration) const;
#endif
};

#endif