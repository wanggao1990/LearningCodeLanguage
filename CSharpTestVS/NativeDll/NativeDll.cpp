// NativeDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "NativeDll.h"


// 这是导出函数的一个示例。
NATIVEDLL_API int fnNativeDll()
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 NativeDll.h
CNativeDll::CNativeDll()
{
    return;
}

#ifdef _WIN64
void CNativeDll::grayScale(uint8_t * pSrc, int channel, int width, int height, uint8_t ** pDst)
{
    FILE *pFile = fopen("log.txt", "w");
    fprintf(pFile,
            "input dat: \n"
            "  pSrc  %p,    channle %d, width %d, height %d\n"
            "  ppDst %p,   pDst %p\n",
            pSrc, channel, width, height, pDst, *pDst
    );
    fclose(pFile);

    int inStride = 0;  //4字节对齐
    int outStride = (width + 3) / 4 * 4;

    cv::Mat gray;
    if(pDst != nullptr) {
        gray = cv::Mat(height, outStride, CV_8UC1, *pDst);
    }
    else {
        gray = cv::Mat(height, outStride, CV_8UC1);
        pDst = &(gray.data);
    }

    if(channel == 3) {

        inStride = (width*channel + 3) / 4 * 4;

        for(int i = 0; i < height; i++) {
            cv::Mat rgbRow(1, width, CV_8UC3, pSrc);
            cv::Mat grayRow(1, width, CV_8UC1, gray.ptr<char>(i));
            cv::cvtColor(rgbRow, grayRow, cv::COLOR_BGR2GRAY);
            pSrc += inStride;
        }


    }
}
#endif