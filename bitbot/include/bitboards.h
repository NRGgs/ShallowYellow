
#ifndef BITBOARDS_H
#define BITBOARDS_H

#include "gamestate.h"

const typedef enum e_colour
{
	C_WHITE,
	C_BLACK,
}	e_colour;

const typedef enum e_bitpiece
{
	BP_KING,
	BP_QUEEN,
	BP_ROOK,
	BP_BISHOP,
	BP_KNIGHT,
	BP_PAWN,
	BP_NONE,
}	e_bitpiece;

typedef struct	zob_hashes
{
	unsigned long	piece_hashes[2][6][64];
	unsigned long	castling_hashes[16];
	unsigned long	side_hashes[2];
	unsigned long	en_passant_hashes[17];
}					zob_hashes;

typedef struct move {
	/* the square the piece is moving from.                                  */
	int from_square;

	/* the square the piece is moving to.                                    */
	int to_square;

	/* the type of piece that is being promoted to, if any.                  */
	int promotion_type;

	int	captured_piece;
	/*
	1 bit  for capture (bool)
	3 bits for captured piece type
	3 bits for piece type
	8 bits for to_square
	8 bits for from_square
	3 bits for promotion type
	*/
}	t_move;

typedef struct s_gamestate
{
	int					active_color;		// WHITE / BLACK
	int					en_passant;			// Current en_passant square (0-63)
	int					castling;			// Castling perms
	int					half_move_clock;	// half moves made since last pawn push / piece capture
	int					fullmove_number;	// 1 fullmove == both sides moved once
	unsigned long		zobrist_key;		// Updated each move
	int					score_value;		// Value of current position
	int					ps_value[2];		// Piece Square Table value for WHITE / BLACK
	t_move		 		completed_move;		// Move that has been played in the current turn
}						t_gamestate;

typedef struct s_history
{
	t_gamestate		states[2048];
	int				current;
}	t_history;

typedef struct s_board
{
	unsigned long	pieces[2][6];	// pieces[COLOUR][PIECES]
	unsigned long	side[2];		// side[COLOUR]
	int				piece_list[64];	// piece_list[SQUARE]
	t_gamestate		state;
	zob_hashes		*hashes;
	int 			***table;
	t_history		history;
}	t_board;


void	init_board(t_board *board);
void	init_piece_list(t_board *board);
void	remove_piece(t_board *board, int color, int piece, int square);
void	place_piece(t_board *board, int color, int piece, int square);
void	add_history(t_board *board);
void	undo_state(t_board *board);

#endif
