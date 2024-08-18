#include <stdio.h>
#include <stdlib.h>

#include "img.h"
#include "ppm.h"

int main() {
	struct Image testImage;
	int status = loadPPM("resources/ColorHead.ppm", &testImage);
	if (status != 0) return status;

	drawImage(testImage);

	freeImage(&testImage);
	return 0;
}
