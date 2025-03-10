#ifndef TYPES_H
#define TYPES_H

#define SUCCESS (signed char)0
#define FAILURE (signed char)-1

#define NO_COLOR (signed char)-1
#define NO_TYPE (signed char)-1
#define NO_PIECE (signed char)-1
#define NO_FILE (signed char)-1
#define NO_RANK (signed char)-1
#define NO_SQUARE (signed char)-1

#define FILE_A (signed char)0
#define FILE_B (signed char)1
#define FILE_C (signed char)2
#define FILE_D (signed char)3
#define FILE_E (signed char)4
#define FILE_F (signed char)5
#define FILE_G (signed char)6
#define FILE_H (signed char)7

#define RANK_1 (signed char)0
#define RANK_2 (signed char)1
#define RANK_3 (signed char)2
#define RANK_4 (signed char)3
#define RANK_5 (signed char)4
#define RANK_6 (signed char)5
#define RANK_7 (signed char)6
#define RANK_8 (signed char)7

#define WHITE (signed char)0
#define BLACK (signed char)1

#define PAWN (signed char)0
#define KNIGHT (signed char)1
#define BISHOP (signed char)2
#define ROOK (signed char)3
#define QUEEN (signed char)4
#define KING (signed char)5

#define KING_SIDE (signed char)1
#define QUEEN_SIDE (signed char)2

/* returns the square with the given file and rank.                          */
#define SQUARE(file, rank) ((rank) * (signed char)8 + (file))

/* returns the file of the given square.                                     */
#define FILE(square) ((square) % (signed char)8)

/* returns the rank of the given square.                                     */
#define RANK(square) ((square) / (signed char)8)

/* returns the piece with the given color and type.                          */
#define PIECE(color, type) ((type) * (signed char)2 + (color))

/* returns the color of the given piece.                                     */
#define COLOR(piece) ((piece) % (signed char)2)

/* returns the type of the given piece.                                      */
#define TYPE(piece) ((piece) / (signed char)2)

/* returns the rank from the perspective of the given color.                 */
#define RELATIVE(rank, color) ((color) == WHITE ? (rank) : (signed char)7 - (rank))

#endif
