typedef struct s_bitboards
{
	long	pieces[2][6];	// pieces[COLOUR][PIECES]
	long	side[2];		// side[COLOUR]
}	t_bitboards;

const typedef enum e_bitpiece
{
	BP_KING,
	BP_QUEEN,
	BP_ROOK,
	BP_BISHOP,
	BP_KNIGHT,
	BP_PAWN,
	BP_NONE
}	e_bitpiece;
