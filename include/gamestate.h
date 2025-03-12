typedef struct s_gamestate
{
	int			active_color;		// WHITE / BLACK
	int			en_passant;			// Current en_passant square (0-63)
	int			castling;			// Castling perms
	int			half_move_clock;	// half moves made since last pawn push / piece capture
	int			fullmove_number;	// 1 fullmove == both sides moved once
	unsigned long		zobrist_key;		// Updated each move
	int			score_value;		// Value of current position
	int			ps_value[2];		// Piece Square Table value for WHITE / BLACK
	struct move *completed_move;	// Move that has been played in the current turn
}				t_gamestate;
