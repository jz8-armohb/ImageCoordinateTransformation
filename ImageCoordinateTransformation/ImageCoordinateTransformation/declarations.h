#pragma once
/* Global variables */
extern int w;
extern int h;
extern int wDst;
extern int hDst;

/* Function declarations */
void Rotation(unsigned char* oriBuff, unsigned char* dstBuff, double degree);
void Scaling(unsigned char* oriBuff, unsigned char* dstBuff, double factor);