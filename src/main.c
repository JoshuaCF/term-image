#include <stdio.h>
#include <stdlib.h>

#include "img.h"
#include "ppm.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Provide a single .ppm file as an argument\n");
		return 1;
	}

	struct Image testImage;
	int status = loadPPM(argv[1], &testImage);
	if (status != 0) return status;

	drawImage(testImage);

	freeImage(&testImage);
	return 0;
}
