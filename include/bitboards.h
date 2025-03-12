typedef struct s_board
{
	unsigned long	pieces[2][6];	// pieces[COLOUR][PIECES]
	unsigned long	side[2];		// side[COLOUR]
	int		piece_list[64];	// piece_list[SQUARE]
}	t_board;

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
