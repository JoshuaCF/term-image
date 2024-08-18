#include "img.h"

#include <stdio.h>
#include <stdlib.h>

void freeImage(struct Image* img) {
	free(img->data);
}
void drawImage(struct Image img) {
	printf("\n");
	for (unsigned int y = 0; y < img.height; y += 2) {
		for (unsigned int x = 0; x < img.width; x++) {
			printf("\e[0m"); // reset
			struct Pixel curPixelTop = img.data[y*img.width + x];
			printf("\e[38;2;%hhu;%hhu;%hhum", curPixelTop.r, curPixelTop.g, curPixelTop.b);
			
			if (y+1 < img.height) {
				struct Pixel curPixelBottom = img.data[(y+1)*img.width + x];
				printf("\e[48;2;%hhu;%hhu;%hhum", curPixelBottom.r, curPixelBottom.g, curPixelBottom.b);
			}
			printf("▀");
		}
		printf("\e[0m\n");
	}
}
