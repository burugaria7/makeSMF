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

	//デルタタイム計算用
	int time_record = 0;


public:
	SMFwriter();

	void Regist_Head();
	void Note_On(double time,int key);
	void Note_Off(double time, int key);
	void Test();

	template<class... A> int sum(A... args) {
		int s = 0;
		for (int i : std::initializer_list<int>{ args... }) {
			s += i;
		}
		return s;
	}

};

