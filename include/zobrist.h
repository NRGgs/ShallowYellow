typedef struct	zob_hashes
{
	unsigned long	piece_hashes[2][6][64];
	unsigned long	castling_hashes[16];
	unsigned long	side_hashes[2];
	unsigned long	en_passant_hashes[17];
}			zob_hashes;