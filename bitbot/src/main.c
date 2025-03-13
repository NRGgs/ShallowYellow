#include "../include/perft.h"
#include "../include/uci.h"

#include <stdlib.h>

#define PERFT 0

int main(void) {
#if PERFT
	perft_run();
#else
	uci_run("ShallowYellow", "ShallowYellow");
#endif

	return EXIT_SUCCESS;
}
