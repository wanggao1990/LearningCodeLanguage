using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;


namespace WinformTest
{
    class NativeDllTest
    {

        // c++的导出函数符号可以用vs命令行 dumpbin /exports xxx.lib/dll 查看 
        //[DllImport("../../../Debug/NativeDll.dll", EntryPoint = "?fnNativeDll@@YAHXZ")]    // AnyCPU
        // 若自己的动态库包含了其他库,一定要放入运行目录下。
        #region 简单函数
        [DllImport("E:/GitRepository/LearningCodeLanguage/CSharpTestVS/x64/Debug/NativeDll.dll", EntryPoint = "?fnNativeDll@@YAHXZ")]         // x64   MDd
        private static extern int fnNativeDll();

        public void testNativeFunc()
        {
            System.Console.WriteLine("%d", fnNativeDll());
        }
        #endregion


        #region 类构造

        [DllImport("E:/GitRepository/LearningCodeLanguage/CSharpTestVS/x64/Debug/NativeDll.dll", EntryPoint = "?GetInstance@CNativeDll@@SAPEAXXZ")]
        private static extern IntPtr GetInstance();

        [DllImport("E:/GitRepository/LearningCodeLanguage/CSharpTestVS/x64/Debug/NativeDll.dll", EntryPoint = "?GrayScale@CNativeDll@@SAXPEAXPEAEHHHPEAPEAE@Z")] 
        private static extern void GrayScale(IntPtr instance, IntPtr pSrc, int channel, int width, int height, ref IntPtr pDst);

        #endregion


        #region 类静态方法
        // [DllImport("../../../Debug/NativeDll.dll", EntryPoint = "?grayScale@CNativeDll@@SAXPEAEHHHPEAPEAE@Z")]
        [DllImport("E:/GitRepository/LearningCodeLanguage/CSharpTestVS/x64/Debug/NativeDll.dll", EntryPoint = "?grayScale@CNativeDll@@SAXPEAEHHHPEAPEAE@Z")]  // 有 static 声明
        private static extern void grayScale(IntPtr pSrc, int channel, int width, int height, ref IntPtr pDst);
        #endregion



        public void grayScale(Bitmap srcBitmap, out Bitmap dstBitmap)
        {
            if (srcBitmap.PixelFormat == PixelFormat.Format8bppIndexed)
            {
                dstBitmap = null;
                return;
            }

            BitmapData srcBmpData = srcBitmap.LockBits(new Rectangle(0, 0, srcBitmap.Width, srcBitmap.Height), ImageLockMode.ReadOnly, srcBitmap.PixelFormat);


            Bitmap resBitmap = new Bitmap( srcBmpData.Width, srcBmpData.Height, PixelFormat.Format8bppIndexed);
            BitmapData resBmpData = resBitmap.LockBits(new Rectangle(0, 0, resBitmap.Width, resBitmap.Height), ImageLockMode.WriteOnly, resBitmap.PixelFormat);

            // bmp 需要4字节对齐
            System.IntPtr dstPtr = resBmpData.Scan0;

            // NativeDllTest.grayScale(srcBmpData.Scan0, 3, srcBitmap.Width, srcBmpData.Height, ref dstPtr);  // static 方法调用

            IntPtr instance = GetInstance();
            GrayScale(instance, srcBmpData.Scan0, 3, srcBitmap.Width, srcBmpData.Height, ref dstPtr); 

            srcBitmap.UnlockBits(srcBmpData);
            resBitmap.UnlockBits(resBmpData);

            // 创建索引表
            ColorPalette palette = resBitmap.Palette;
            for (int i = 0; i < palette.Entries.Length; i++)
            {
                palette.Entries[i] = Color.FromArgb(i, i, i);
            }
            resBitmap.Palette = palette;

            dstBitmap = resBitmap;
        }
    }
}
