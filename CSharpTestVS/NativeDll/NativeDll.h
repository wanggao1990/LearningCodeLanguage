// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 NATIVEDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// NATIVEDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef NATIVEDLL_EXPORTS
#define NATIVEDLL_API __declspec(dllexport)
#else
#define NATIVEDLL_API __declspec(dllimport)
#endif

#ifdef  _WIN64
#include "opencv2\opencv.hpp"
#endif // _WIN64



// 此类是从 NativeDll.dll 导出的
class NATIVEDLL_API CNativeDll {
public:
	CNativeDll();
	// TODO:  在此添加您的方法。
	
    static void* GetInstance()
    {
        static CNativeDll instace = CNativeDll();
        return &instace;
    }

    static void GrayScale(void *instance, uint8_t* pSrc, int channel, int width, int height, uint8_t** pDst)
    {
        ((CNativeDll*)instance)->grayScale(pSrc, channel, width, height, pDst);
    }


#ifdef  _WIN64
    static void grayScale(uint8_t* pSrc, int channel, int width, int height, uint8_t** pDst);
#endif // _WIN64

};


NATIVEDLL_API int fnNativeDll();
