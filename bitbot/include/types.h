#ifndef TYPES_H
#define TYPES_H

#define SUCCESS (int)0
#define FAILURE (int)-1

#define NO_COLOR (int)-1
#define NO_TYPE (int)-1
#define NO_PIECE (int)-1
#define NO_FILE (int)-1
#define NO_RANK (int)-1
#define NO_SQUARE (int)-1

#define FILE_A (int)0
#define FILE_B (int)1
#define FILE_C (int)2
#define FILE_D (int)3
#define FILE_E (int)4
#define FILE_F (int)5
#define FILE_G (int)6
#define FILE_H (int)7

#define RANK_1 (int)0
#define RANK_2 (int)1
#define RANK_3 (int)2
#define RANK_4 (int)3
#define RANK_5 (int)4
#define RANK_6 (int)5
#define RANK_7 (int)6
#define RANK_8 (int)7

#define WHITE (int)0
#define BLACK (int)1

#define PAWN (int)0
#define KNIGHT (int)1
#define BISHOP (int)2
#define ROOK (int)3
#define QUEEN (int)4
#define KING (int)5

#define KING_SIDE (int)1
#define QUEEN_SIDE (int)2

/* returns the square with the given file and rank.                          */
#define SQUARE(file, rank) ((rank) * (int)8 + (file))

/* returns the file of the given square.                                     */
#define FILE(square) ((square) % (int)8)

/* returns the rank of the given square.                                     */
#define RANK(square) ((square) / (int)8)

/* returns the piece with the given color and type.                          */
#define PIECE(color, type) ((type) * (int)2 + (color))

/* returns the color of the given piece.                                     */
#define COLOR(piece) ((piece) % (int)2)

/* returns the type of the given piece.                                      */
#define TYPE(piece) ((piece) / (int)2)

/* returns the rank from the perspective of the given color.                 */
#define RELATIVE(rank, color) ((color) == WHITE ? (rank) : (int)7 - (rank))

#define RELATIVESQUARE(square, piece) (SQUARE(FILE(square), RELATIVE(RANK(square), COLOR(piece))))
#define BB_RELATIVESQUARE(square, color) (SQUARE(FILE(square), RELATIVE(RANK(square), color)))

#define GET_ENPASSANT_SQUARE(color, square) ((color == C_WHITE) ? square % 16 : square % 32 + 8)

#endif
