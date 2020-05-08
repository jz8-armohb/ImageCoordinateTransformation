#include <iostream>
#include "declarations.h"
using namespace std;

int main(int argc, char* argv[]) {
	FILE* oriImgPtr;
	FILE* dstImgPtr;
	const char* oriImgName = argv[1];
	const char* dstImgName = argv[2];

	/* Open the files */
    if (fopen_s(&oriImgPtr, oriImgName, "rb") == 0) {
        cout << "Successfully opened \"" << oriImgName << "\".\n";
    } else {
        cout << "Failed to open \"" << oriImgName << "\".\n";
        exit(-1);
    }
    if (fopen_s(&dstImgPtr, dstImgName, "wb") == 0) {
        cout << "Successfully opened \"" << dstImgName << "\".\n";
    } else {
        cout << "Failed to open \"" << dstImgName << "\".\n";
        exit(-1);
    }

    /* Space allocation */
    cout << "Rotated image size: " << wDst << " by " << hDst << "." << endl;
    unsigned char* oriYBuff = new unsigned char[w * h];
    unsigned char* dstYBuff = new unsigned char[wDst * hDst];
    unsigned char* dstUBuff = new unsigned char[wDst * hDst / 4];
    unsigned char* dstVBuff = new unsigned char[wDst * hDst / 4];

    /* Read Y component into the buffer */
    fread(oriYBuff, sizeof(unsigned char), w * h, oriImgPtr);

    /* Rotation */
    ImgRotation(oriYBuff, dstYBuff, 30);

    /* Write transformed pixel data into a file */
    fwrite(dstYBuff, sizeof(unsigned char), wDst * hDst, dstImgPtr);
    memset(dstUBuff, 128, wDst * hDst / 4 * sizeof(unsigned char));
    memset(dstVBuff, 128, wDst * hDst / 4 * sizeof(unsigned char));
    fwrite(dstUBuff, sizeof(unsigned char), wDst * hDst / 4, dstImgPtr);
    fwrite(dstUBuff, sizeof(unsigned char), wDst * hDst / 4, dstImgPtr);

    fclose(oriImgPtr);
    fclose(dstImgPtr);
    delete[]oriYBuff;
    delete[]dstYBuff;
    delete[]dstUBuff;
    delete[]dstVBuff;
}