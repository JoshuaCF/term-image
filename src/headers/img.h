#pragma once

#include <stdbool.h>

struct Color {
	unsigned char r, g, b;
};

struct Pixel {
	struct Color col;
	bool transparent;
};

struct Image {
	unsigned int width, height;
	struct Pixel* data;
};

void freeImage(struct Image* img);
void drawImage(struct Image img);
