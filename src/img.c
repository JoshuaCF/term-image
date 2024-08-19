#include "img.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void freeImage(struct Image* img) {
	free(img->data);
}

struct ImageCharacter {
	bool topHidden, bottomHidden;
	struct Color topColor, bottomColor;
};
void writeImageCharacter(struct ImageCharacter c) {
	printf("\e[0m"); // reset
	if (c.topHidden && c.bottomHidden) {
		printf(" ");
	} else if (c.bottomHidden) {
		printf("\e[38;2;%hhu;%hhu;%hhum", c.topColor.r, c.topColor.g, c.topColor.b);	
		printf("▀");
	} else if (c.topHidden) {
		printf("\e[38;2;%hhu;%hhu;%hhum", c.bottomColor.r, c.bottomColor.g, c.bottomColor.b);
		printf("▄");
	} else {
		printf("\e[38;2;%hhu;%hhu;%hhum", c.topColor.r, c.topColor.g, c.topColor.b);	
		printf("\e[48;2;%hhu;%hhu;%hhum", c.bottomColor.r, c.bottomColor.g, c.bottomColor.b);
		printf("▀");
	}
}

void drawImage(struct Image img) {
	printf("\n");
	for (unsigned int y = 0; y < img.height; y += 2) {
		for (unsigned int x = 0; x < img.width; x++) {
			struct ImageCharacter imgChar;
			imgChar.topHidden = true;
			imgChar.bottomHidden = true;

			struct Pixel curPixelTop = img.data[y*img.width + x];

			if (!curPixelTop.transparent) {
				imgChar.topHidden = false;
				imgChar.topColor = curPixelTop.col;
			}
			
			if (y+1 < img.height) {
				struct Pixel curPixelBottom = img.data[(y+1)*img.width + x];
				if (!curPixelBottom.transparent) {
					imgChar.bottomHidden = false;
					imgChar.bottomColor = curPixelBottom.col;
				}
			}
			writeImageCharacter(imgChar);
		}
		printf("\e[0m\n");
	}
}
