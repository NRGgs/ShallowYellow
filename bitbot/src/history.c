#include "../include/bitboards.h"
#include "../include/move.h"

int jehovah(int old);

void	add_history(t_board *board)
{
	board->history.states[board->history.current++] = board->state;
}

void	undo_state(t_board *board)
{
	board->state = board->history.states[--board->history.current];
	int	jesus = board->state.completed_move.captured_piece;
	int piece = board->piece_list[board->state.completed_move.to_square];
	board->state.active_color ^= 1;
	remove_piece(board, board->state.active_color, piece, board->state.completed_move.to_square);
	place_piece(board, board->state.active_color, piece, board->state.completed_move.from_square);
	if (board->state.completed_move.captured_piece != BP_NONE)
		place_piece(board, board->state.active_color ^ 1, jehovah(jesus), board->state.completed_move.to_square);
}
