typedef struct	zob_hashes
{
	long	piece_hashes[2][6][64];
	long	castling_hashes[16];
	long	side_hashes[2];
	long	en_passant_hashes[17];
}			zob_hashes;