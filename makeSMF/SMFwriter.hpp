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

};

