//main_simd.c

#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include "sm4_simd_sbox.h"
int main() {
    // 01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10
    unsigned char key[16 * 8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab,
                                 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98,
                                 0x76, 0x54, 0x32, 0x10 };

    // 01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10
    // 00 00 ... 00
    unsigned char in[16 * 8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
    SM4_Key sm4_key;

 
    double run_time;
    LARGE_INTEGER time_start;	//开始时间
    LARGE_INTEGER time_over;	//结束时间
    double dqFreq;		//计时器频率
    LARGE_INTEGER f;	//计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    QueryPerformanceCounter(&time_start);	//计时开始


    SM4_KeyInit(key, &sm4_key);
    for(int i=0;i<2000;i++)
    SM4_Encrypt_x8(in, in, sm4_key);


    QueryPerformanceCounter(&time_over);	//计时结束
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
    printf("\nrun_time：%fus\n", run_time);
   
    system("pause");
    return 0;
}
