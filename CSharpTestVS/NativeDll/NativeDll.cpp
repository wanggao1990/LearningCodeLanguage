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
