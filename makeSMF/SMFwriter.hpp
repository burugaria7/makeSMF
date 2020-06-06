#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdarg.h>
#include <sstream> // std::stringstream
#include <bitset>  // std::bitset<N>
#include <stdlib.h>
#include <string>
#include <cstdlib>

using namespace std;

class SMFwriter
{

private:

	vector<int> manuscript;
	vector<int> header_chunk;
	vector<int> track_chunk;

	//デルタタイム計算用
	int time_record = 0;

	//実データのデータ長計測
	int track_sum = 0;


public:
	SMFwriter();

	void Regist_Head();
	void Note_On(double time,int key);
	void Note_Off(double time, int key);
	void Test();


	vector<long> VLQ_Converter(long time);

	unsigned int binToUInt(const std::string& str)
	{
		//cout << "STRRR" << str << endl;
		unsigned int val = 0;
		for (int i = 0; i < (int)str.size(); ++i) {
			switch (str[i]) {
			case '0':
				val *= 2;
				break;
			case '1':
				val = val * 2 + 1;
				break;
			}
		}
		return val;
	}

	/* 4バイトlong型整数値を可変長整数値に変換し、書き込んだバイト数を返す(最大5バイト)。 */
	static long LongToVariable(long lValue, unsigned char* pData) {
		unsigned long ulValue = (unsigned long)lValue;
		if (0 <= ulValue && ulValue < 128) {
			*pData = (unsigned char)ulValue;
			return 1;
		}
		else if (128 <= ulValue && ulValue < 16384) {
			*pData = (unsigned char)(((ulValue & 0x3F80) >> 7) | 0x80);
			*(pData + 1) = (unsigned char)(ulValue & 0x007F);
			return 2;
		}
		else if (16384 <= ulValue && ulValue < 2097152) {
			*pData = (unsigned char)(((ulValue & 0x1FC000) >> 14) | 0x80);
			*(pData + 1) = (unsigned char)(((ulValue & 0x003F80) >> 7) | 0x80);
			*(pData + 2) = (unsigned char)(ulValue & 0x00007F);
			return 3;
		}
		else if (2097152 <= ulValue && ulValue < 268435456) {
			*pData = (unsigned char)(((ulValue & 0x0FE00000) >> 21) | 0x80);
			*(pData + 1) = (unsigned char)(((ulValue & 0x001FC000) >> 14) | 0x80);
			*(pData + 2) = (unsigned char)(((ulValue & 0x00003F80) >> 7) | 0x80);
			*(pData + 3) = (unsigned char)(ulValue & 0x0000007F);
			return 4;
		}
		else if (268435456 <= ulValue) {
			*(pData + 0) = (unsigned char)(((ulValue & 0xF0000000) >> 28) | 0x80);
			*(pData + 1) = (unsigned char)(((ulValue & 0x0FE00000) >> 21) | 0x80);
			*(pData + 2) = (unsigned char)(((ulValue & 0x001FC000) >> 14) | 0x80);
			*(pData + 3) = (unsigned char)(((ulValue & 0x00003F80) >> 7) | 0x80);
			*(pData + 4) = (unsigned char)(ulValue & 0x0000007F);
			return 5;
		}
		*pData = 0;
		return 0;
	}

};

