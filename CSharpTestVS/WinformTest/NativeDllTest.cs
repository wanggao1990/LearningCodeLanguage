
using System.Runtime.InteropServices;


namespace WinformTest
{
    class NativeDllTest
    {

        // c++的导出函数符号可以用dumpbin /exports xxx.lib查看 
        [DllImport("../../../Debug/NativeDll.dll", EntryPoint = "?fnNativeDll@@YAHXZ")]
        private static extern int fnNativeDll();


        public void testNativeFunc()
        {
            System.Console.WriteLine("%d", fnNativeDll());
        }
    }
}
