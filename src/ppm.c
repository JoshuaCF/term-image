#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "img.h"

void skipWhitespace(FILE* file) {
	char curChar;
	do {
		fread(&curChar, 1, 1, file);
	} while(
		curChar == ' ' ||
		curChar == '\t' ||
		curChar == '\r' ||
		curChar == '\n'
	);
	fseek(file, -1, SEEK_CUR);
}

void skipLine(FILE* file) {
	char curChar;
	do {
		fread(&curChar, 1, 1, file);
	} while(
		curChar != '\n'
	);
}

void skipComments(FILE* file) {
	char curChar;
	while(1) {
		fread(&curChar, 1, 1, file);
		if (curChar == '#') skipLine(file);
		else break;
	}
	fseek(file, -1, SEEK_CUR);
}

int loadPPM(const char* filename, struct Image* imageOut) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) return 1;

	// Check magic number
	char magicNum[3];
	magicNum[2] = '\0';
	fread(magicNum, 1, 2, file);
	if (strcmp(magicNum, "P6") != 0) return 2;
	skipComments(file);

	// Skip whitespace
	skipWhitespace(file);
	skipComments(file);
	// Read width
	unsigned int width;
	if (fscanf(file, "%u", &width) != 1) return 3;
	skipComments(file);
	// Skip whitespace
	skipWhitespace(file);
	skipComments(file);
	// Read height
	unsigned int height;
	if (fscanf(file, "%u", &height) != 1) return 4;
	skipComments(file);
	// Skip whitespace
	skipWhitespace(file);
	skipComments(file);
	// Read maximum color value
	unsigned int maxColorValue;
	if (fscanf(file, "%u", &maxColorValue) != 1) return 5;
	if (maxColorValue != 255) return 6; // Don't want to deal with it rn
	skipComments(file);
	// Skip next character (should be whitespace)
	fseek(file, 1, SEEK_CUR);
	skipComments(file);
	// Initialize image
	imageOut->width = width;
	imageOut->height = height;
	imageOut->data = malloc(width * height * sizeof(struct Pixel));
	// Read color data
	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			fread(&imageOut->data[y*width + x].r, 1, 1, file);
			fread(&imageOut->data[y*width + x].g, 1, 1, file);
			fread(&imageOut->data[y*width + x].b, 1, 1, file);
		}
	}
	
	// Convert to linear?

	fclose(file);
	return 0;
}
