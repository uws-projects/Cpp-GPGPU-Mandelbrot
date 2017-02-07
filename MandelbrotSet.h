#pragma once
#include "Util.h"

struct Pixel { unsigned char r, g, b; };

class MandelbrotSet
{
private:
	Pixel *setOnHost;			// the Mandelbrot set on the host RAM
	Pixel *setOnDevice;			// the Mandelbrot set on the device RAM

	int width = 4096;
	int height = 4096;

	void init();

public:
	MandelbrotSet();
	MandelbrotSet(int width, int height);
	~MandelbrotSet();

	Pixel *getHostReference() { return setOnHost; }
	Pixel *getDeviceReference() { return setOnDevice; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	void fetch();

	inline void saveAs(char* fileName) {
		fetch();

		FILE *fp = fopen(fileName, "w");
		fprintf(fp, "P6\n%d %d\n255\n", width, height);
		for (int i = height - 1; i >= 0; i--) {
			fwrite(setOnHost + i * width, 1, width * sizeof(Pixel), fp);
		}
		fclose(fp);
	}
};

