#include <stdlib.h>
#include <stdio.h>

struct Pixel {
	unsigned char r, g, b;
};

struct Image {
	unsigned int width, height;
	struct Pixel* data;
};
void freeImage(struct Image* img) {
	free(img->data);
}
void drawImage(struct Image img) {
	printf("\n");
	for (unsigned int y = 0; y < img.height; y++) {
		for (unsigned int x = 0; x < img.width; x++) {
			struct Pixel curPixel = img.data[y*img.width + x];
			printf("\e[38;2;%hhu;%hhu;%hhum█", curPixel.r, curPixel.g, curPixel.b);
		}
		printf("\n");
	}
}

int main() {
	struct Image testImage = {};
	testImage.width = 10;
	testImage.height = 10;
	struct Pixel* imageData = malloc(testImage.width * testImage.height * sizeof(struct Pixel));
	testImage.data = imageData;

	for (unsigned int y = 0; y < testImage.height; y++) {
		for (unsigned int x = 0; x < testImage.width; x++) {
			imageData[y*testImage.width + x] = (struct Pixel) { 127, 255, 80 };
		}
	}

	drawImage(testImage);

	freeImage(&testImage);
	return 0;
}
