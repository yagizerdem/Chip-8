#include <mmintrin.h>
#include <SDL_timer.h>
#include <unistd.h>

#include  "emulator.h"
#include "screen.h"
#include  "stdbool.h"
#include <time.h>

int main(int argc, char **argv)
{
	srand(time(NULL));

	if (argc != 2) {
		printf("You did not enter program file.\n");
		exit(1);
	}

	char* programFile = argv[1];
	start(programFile);

	return 0;
}