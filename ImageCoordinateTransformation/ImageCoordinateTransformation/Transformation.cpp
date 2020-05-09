#include <iostream>
#include "declarations.h"
#define PI 3.1416
using namespace std;

int w = 256;
int h = 256;
//int wDst = sqrt((double)w * w + (double)h * h);	// Assure enough space for rotation
int wDst = 2.5 * w;
int hDst = wDst;

unsigned char BilinInterplotation(unsigned char* oriBuff, int xInt, int yInt, double x, double y) {
	unsigned char temp 
		= oriBuff[yInt * w + xInt]           * (xInt + 1 - x) * (yInt + 1 - y)
		+ oriBuff[yInt * w + xInt + 1]       * (x - xInt)     * (yInt + 1 - y)
		+ oriBuff[(yInt + 1) * w + xInt]     * (xInt + 1 - x) * (y - yInt)
		+ oriBuff[(yInt + 1) * w + xInt + 1] * (x - xInt)     * (y - yInt);
	return temp;
}

void Rotation(unsigned char* oriBuff, unsigned char* dstBuff, double degree) {

	double rad = degree * PI / 180;	// Rotation angle in degree (clockwise)
	memset(dstBuff, 0, wDst * hDst * sizeof(unsigned char));	// Initialisation

	for (int i = 0; i < hDst; i++) {	// i for yDst (y')
		for (int j = 0; j < wDst; j++) {	// j for xDst (x')
			/* Compute the coordinates corresponding to each pixel in the destination buffer */
			double xOri = double(j - wDst / 2) * cos(rad) - double(i - hDst / 2) * sin(rad) + w / 2;
			double yOri = double(j - wDst / 2) * sin(rad) + double(i - hDst / 2) * cos(rad) + h / 2;
			int xOriInt = int(xOri);
			int yOriInt = int(yOri);

			/* Assignment & bilinear interplotation */
			if (xOriInt >= 0 && xOriInt <= w && yOriInt >=0 && yOriInt <= h) {
				dstBuff[i * wDst + j] = BilinInterplotation(oriBuff, xOriInt, yOriInt, xOri, yOri);
			}
		}
	}
}

void Scaling(unsigned char* oriBuff, unsigned char* dstBuff, double factor) {
	/**************************************************************************
	For upscaling, factor should be greater than 1, otherwise smaller than 1.
	**************************************************************************/

	memset(dstBuff, 0, wDst * hDst * sizeof(unsigned char));	// Initialisation

	for (int i = 0; i < hDst; i++) {	// i for yDst (y')
		for (int j = 0; j < wDst; j++) {	// j for xDst (x')
			/* Compute the coordinates corresponding to each pixel in the destination buffer */
			double xOri = 1 / factor * j;
			double yOri = 1 / factor * i;
			int xOriInt = int(xOri);
			int yOriInt = int(yOri);

			/* Assignment & bilinear interplotation */
			if (xOriInt >= 0 && xOriInt <= w && yOriInt >= 0 && yOriInt <= h) {
				dstBuff[i * wDst + j] = BilinInterplotation(oriBuff, xOriInt, yOriInt, xOri, yOri);
			}
		}
	}

}

//void ImgRotation(unsigned char* oriBuff, unsigned char* dstBuff, double degree) {
//	double rad = degree * PI / 180;	// Rotation angle in degree (clockwise)
//	memset(dstBuff, 0, wDst * hDst * sizeof(unsigned char));	// Initialisation
//
//	for (int i = 0; i < hDst; i++) {	// i for yDst (y')
//		for (int j = 0; j < wDst; j++) {	// j for xDst (x')
//			/* Compute the coordinates corresponding to each pixel in the destination buffer */
//			//int xOri = (double)j * cos(rad) - (double)i * sin(rad);
//			//int yOri = (double)j * sin(rad) + (double)i * cos(rad);
//			int xOri = double(j - wDst / 2) * cos(rad) - double(i - hDst / 2) * sin(rad) + w / 2;
//			int yOri = double(j - wDst / 2) * sin(rad) + double(i - hDst / 2) * cos(rad) + h / 2;
//
//			/* Assignment */
//			if (xOri >= 0 && xOri <= w && yOri >= 0 && yOri <= h) {
//				dstBuff[i * wDst + j] = oriBuff[yOri * w + xOri];
//			}
//		}
//	}
//}