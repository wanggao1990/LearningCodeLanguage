#pragma once

#include <iostream>

/**
 * \brief ���ӳ�������
 *
 *  ��һȺ����ժ��һ������,����ÿ�춼�Ե�ǰ���ӵ�һ�����ٶ��һ��.
 *  ,���˵�10���ֻ����һ������.�ö��ַ���ʵ�����ԭ����Ⱥ���ӹ�ժ
 *  �˶��ٸ����ӡ�
 *
 *  Ҫ��1)�����������ݽṹʵ��������⣻2)������ʽ���ݽṹʵ����
 *  ����⣻3)���õݹ�ʵ��������⡣
 *
 *
 *  ˼·3��
 *   f(10) = 1;
 *   f(n) = f(n-1) - [ f(n-1)/2 + 1] = 1/2 * f(n-1) - 1;
 *
 *   ����֪ f(n-1) = 2f(n) + 1 �� f(10) = 1 ���f(1)
 *
 *
 *  ˼·2��
 *    ��f(n-1) = 2f(n) + 1��
 *    �� f(n-2) = 2f(n-1) + 1 = 4f(n)+3,   f(n-3) = 2f(n-2)+1 = 8f(n) + 7, ....
 *    �õ�  f(n - t) =  2^t * f(n) + (2^t - 1) = 2^t*(f(n) + 1) -1
 *
 *    ��֪ f(10) =1, ��f(1),  ��ô��n=10��t=9,  ��  f(1) = f(10-9) = 2^9 + 2^9 - 1 = 2^10 -1 = 1023
 *  
 *   
 */

class MonkeyPeach
{
public:

    int countRecursive(int day)
    {
        if (day == 10){
            return 1;
        }
        else{
            return  2 * countRecursive(day + 1) + 1;
        } 
    }

    int countLink()
    {
        int t = 9, f10 = 1;
        int f1 = std::pow(2, t)* (f10 + 1) - 1;
        return f1;
    }

    int countArray()
    {
        std::array<int, 10>  dayPeachs;
        dayPeachs[9] = 1;

        for (int i = 9; i > 0; i--)
            dayPeachs[i - 1] = 2 * dayPeachs[i] + 1;

        return dayPeachs[0];
    }
   

    static int Test()
    {
        auto instanse = MonkeyPeach();
       // int res = instanse.countRecursive(1);
      //  int res = instanse.countArray();
        int res = instanse.countLink();


        printf("%d\n", res);
        return res;
    }

protected:

private:

};
