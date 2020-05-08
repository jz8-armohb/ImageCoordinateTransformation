#include <iostream>
#include "declarations.h"
#define PI 3.1416
using namespace std;

int w = 256;
int h = 256;
//int wDst = sqrt((double)w * w + (double)h * h);	// Assure enough space for rotation
int wDst = 1000;
int hDst = wDst;

void ImgRotation(unsigned char* oriBuff, unsigned char* dstBuff, double degree) {
	double rad = degree * PI / 180;	// Rotation angle in degree (clockwise)
	memset(dstBuff, 0, wDst * hDst * sizeof(unsigned char));	// Initialisation

	for (int i = 0; i < hDst; i++) {	// i for yDst (y')
		for (int j = 0; j < wDst; j++) {	// j for xDst (x')
			/* Compute the coordinates corresponding to each pixel in the destination buffer */
			//int xOri = (double)j * cos(rad) - (double)i * sin(rad);
			//int yOri = (double)j * sin(rad) + (double)i * cos(rad);
			int xOri = double(j - wDst / 2) * cos(rad) - double(i - hDst / 2) * sin(rad) + w / 2;
			int yOri = double(j - wDst / 2) * sin(rad) + double(i - hDst / 2) * cos(rad) + h / 2;

			/* Assignment */
			if (xOri >= 0 && xOri <= w && yOri >=0 && yOri <= h) {
				dstBuff[i * wDst + j] = oriBuff[yOri * w + xOri];
			}
		}
	}

}