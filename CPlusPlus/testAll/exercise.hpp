#pragma once

#include <iostream>

/**
 * \brief 猴子吃桃问题
 *
 *  有一群猴子摘了一堆桃子,他们每天都吃当前桃子的一半且再多吃一个.
 *  ,到了第10天就只余下一个桃子.用多种方法实现求出原来这群猴子共摘
 *  了多少个桃子。
 *
 *  要求：1)采用数组数据结构实现上述求解；2)采用链式数据结构实现上
 *  述求解；3)采用递归实现上述求解。
 *
 *
 *  思路3：
 *   f(10) = 1;
 *   f(n) = f(n-1) - [ f(n-1)/2 + 1] = 1/2 * f(n-1) - 1;
 *
 *   即已知 f(n-1) = 2f(n) + 1 ， f(10) = 1 求解f(1)
 *
 *
 *  思路2：
 *    由f(n-1) = 2f(n) + 1，
 *    有 f(n-2) = 2f(n-1) + 1 = 4f(n)+3,   f(n-3) = 2f(n-2)+1 = 8f(n) + 7, ....
 *    得到  f(n - t) =  2^t * f(n) + (2^t - 1) = 2^t*(f(n) + 1) -1
 *
 *    已知 f(10) =1, 求f(1),  那么令n=10，t=9,  有  f(1) = f(10-9) = 2^9 + 2^9 - 1 = 2^10 -1 = 1023
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
