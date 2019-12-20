#ifndef BMPLOADER_H
#define BMPLOADER_H

#include <windows.h>

class BmpLoader
{
    public:
        unsigned char* textureDataImg;
        unsigned char* textureData;
        int iWidth,iHeight;
        const int tol=12;
        double f[200000];
        double c[200000];
        int minimLim = 200;
        int maximLim =1200;
        double minimf=5000;
        double maximf=0;
        double minimc=5000;
        double maximc=0;
        int w=4320;
        double t=1339;
        int cont;
        BmpLoader();
        void print();
        ~BmpLoader();
    private:
        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;
};

#endif
