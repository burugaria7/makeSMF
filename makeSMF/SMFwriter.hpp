#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

class SMFwriter
{

private:

	vector<int> manuscript;
	vector<int> header_chunk;
	vector<int> track_chunk;

	//�f���^�^�C���v�Z�p
	int time_record = 0;


public:
	SMFwriter();

	void Regist_Head();
	void Test();

};

