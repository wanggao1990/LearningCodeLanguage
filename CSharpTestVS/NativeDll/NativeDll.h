// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NATIVEDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NATIVEDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef NATIVEDLL_EXPORTS
#define NATIVEDLL_API __declspec(dllexport)
#else
#define NATIVEDLL_API __declspec(dllimport)
#endif

#ifdef  _WIN64
#include "opencv2\opencv.hpp"
#endif // _WIN64



// �����Ǵ� NativeDll.dll ������
class NATIVEDLL_API CNativeDll {
public:
	CNativeDll();
	// TODO:  �ڴ�������ķ�����
	
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
