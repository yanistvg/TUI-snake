#include "./libs/headers/main.h"

int main(int argc, char **argv) {
	int size[2] = {0, 0}; // screen size

	if (getTermSize(size) == _YG_FAIL_GET_SCREEN_SIZE_)
		exitCodeWithError("Fail to get screen size", _YG_FAIL_GET_SCREEN_SIZE_);

	drawMainGameScreen(size);

	return _YG_SUCCESS_;
}
