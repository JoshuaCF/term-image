#pragma once

// Returns zero on success, non-zero on failure
int loadPPM(const char* filename, struct Image* imageOut);
