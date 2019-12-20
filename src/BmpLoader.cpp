#include "BmpLoader.h"
#include <stdio.h>
#include <iostream>

BmpLoader::BmpLoader()
{
    const char* filename="cubo1.bmp";
    FILE *file=0;
    file=fopen(filename,"rb");
    if(!file)
        std::cout<<"Imagen no encontrada"<<std::endl;
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,file);
    if(bfh.bfType != 0x4D42)
        std::cout<<"No es un formato Bitmap"<<std::endl;

    fread(&bih,sizeof(BITMAPINFOHEADER),1,file);
    if(bih.biSizeImage==0)
        bih.biSizeImage=bih.biHeight*bih.biWidth*3;

    textureDataImg = new unsigned char [bih.biSizeImage];
    fseek(file,bfh.bfOffBits,SEEK_SET);
    fread(textureDataImg,1,bih.biSizeImage,file);

    textureData = new unsigned char [bih.biSizeImage];
    fseek(file,bfh.bfOffBits,SEEK_SET);
    fread(textureData,1,bih.biSizeImage,file);

    unsigned char temp, ant, deb, sig;

    temp = textureData[0];

    cont=0;
    for (int i=0; i<bih.biSizeImage-w ;i+=3){
        temp = textureDataImg[i];
        deb = textureDataImg[i+w];
        if(abs(int(temp)-int(deb))>tol){
            textureData[i]=(unsigned char)0;
            textureData[i+1]=(unsigned char)0;
            textureData[i+2]=(unsigned char)0;
            if(minimLim < i/w && i/w<maximLim && minimLim<(i%w)/3 && (i%w)/3 <maximLim){
                f[cont]=double(i/w);
                c[cont]=double((i%w)/3);
                if(f[cont]>maximf){
                    maximf=f[cont];
                }
                if(f[cont]<minimf){
                    minimf=f[cont];
                }
                if(c[cont]>maximc){
                    maximc=c[cont];
                }
                if(c[cont]<minimc){
                    minimc=c[cont];
                }
                //std::cout<<f[cont]<<" "<<c[cont] <<std::endl;
                cont++;
            }

        }else{
            textureData[i]=(unsigned char)255;
            textureData[i+1]=(unsigned char)255;
            textureData[i+2]=(unsigned char)255;
        }
    }
    for (int i=3; i<bih.biSizeImage-3;i+=3){
        temp = textureDataImg[i];
        sig = textureDataImg[i+3];
        if(abs(int(temp)-int(sig))>tol ){
            textureData[i]=(unsigned char)0;
            textureData[i+1]=(unsigned char)0;
            textureData[i+2]=(unsigned char)0;
            if(minimLim<i/w && i/w<maximLim && minimLim<(i%w)/3 && (i%w)/3 <maximLim){
                f[cont]=double(i/w);
                c[cont]=double((i%w)/3);
                if(f[cont]>maximf){
                    maximf=f[cont];
                }
                if(f[cont]<minimf){
                    minimf=f[cont];
                }
                if(c[cont]>maximc){
                    maximc=c[cont];
                }
                if(c[cont]<minimc){
                    minimc=c[cont];
                }
                //std::cout<<f[cont]<<" "<<c[cont] <<std::endl;
                cont++;
            }
        }else{
            //textureData[i]=(unsigned char)255;
            //textureData[i+1]=(unsigned char)255;
            //textureData[i+2]=(unsigned char)255;
        }
    }
    std::cout<< cont <<std::endl;
    std::cout<<minimf<<" "<<maximf <<" "<<minimc<<" "<<maximc <<std::endl;
    for(int i=0;i<cont;i++){
        f[i]=f[i]-minimf;
        c[i]=c[i]-minimc;
    }

    maximf=maximf-minimf;
    maximc=maximc-minimc;
    minimf=0;
    minimc=0;
    std::cout<<minimf<<" "<<maximf <<" "<<minimc<<" "<<maximc <<std::endl;
    for(int i=0;i<cont;i++){
        f[i]=(f[i]-(maximf/2))/(maximf/2);
        c[i]=(c[i]-(maximc/2))/(maximc/2);
        std::cout<<f[i]<<" "<<c[i] <<std::endl;
    }

    iWidth=bih.biWidth;
    iHeight=bih.biHeight;
}
void BmpLoader::print(){
    while(textureData){
        std::cout<<*textureData<<std::endl;
    }
}
BmpLoader::~BmpLoader(){
    delete [] textureData;
}

