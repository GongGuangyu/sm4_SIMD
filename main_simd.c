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
    LARGE_INTEGER time_start;	//��ʼʱ��
    LARGE_INTEGER time_over;	//����ʱ��
    double dqFreq;		//��ʱ��Ƶ��
    LARGE_INTEGER f;	//��ʱ��Ƶ��
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    QueryPerformanceCounter(&time_start);	//��ʱ��ʼ


    SM4_KeyInit(key, &sm4_key);
    for(int i=0;i<2000;i++)
    SM4_Encrypt_x8(in, in, sm4_key);


    QueryPerformanceCounter(&time_over);	//��ʱ����
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    //����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
    printf("\nrun_time��%fus\n", run_time);
   
    system("pause");
    return 0;
}
