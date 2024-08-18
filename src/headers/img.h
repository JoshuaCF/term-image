#pragma once

struct Pixel {
	unsigned char r, g, b;
};

struct Image {
	unsigned int width, height;
	struct Pixel* data;
};

void freeImage(struct Image* img);
void drawImage(struct Image img);
