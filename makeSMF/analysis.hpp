﻿#pragma once

#ifndef ANALYSIS_HPP
#define	ANALYSIS_HPP

#include <stdlib.h>
#include<fstream>
#include<string>
#include <iostream>
#include <sstream>
#include <algorithm>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//#include <MIDIData.h>

#include "Movie.hpp"
#include "SMFwriter.hpp"
//#include "MidiController.hpp"

using namespace std;
using namespace cv;

class Analysis
{

private:

	//マウス入力用のパラメータ
	struct mouseParam {
		int x;
		int y;
		int event;
		int flags;
	};

	mouseParam mouseEvent;

	//色がどれくらい変わったら変化したと
	//認識するか
	const static int threshold = 50;

	int ikiti = 10;

	std::ostringstream pos_msec;

	vector<int> key_xx;

	int key_white_x[52];
	int key_white_y;
	int key_black_x[36];
	int key_black_y;

	int key_x[88];

	//画面変更の時のご検知対策
	//変化量が多すぎると、
	//書き出ししない
	//フラグみたいな使い方
	int active_key_sum = 0;

	int first_key = 0;


	Movie movie;

	SMFwriter smf;

	cv::Mat frame;

	int def_w_clrB;
	int def_w_clrG;
	int def_w_clrR;

	int def_b_clrB;
	int def_b_clrG;
	int def_b_clrR;

	//bool key_w_event[52];
	//bool key_b_event[36];

	bool key_event[88];

	bool key_active[88];

	//１フレーム分を保持
	string str = "";

	//その1フレーム分に問題がなければ、
	//書き込み
	string str_ = "";



public:

	Analysis();
	void Set_Coodinates();
	void Set_Color();
	void Analyze();
	void Check_Coodinates();

	//明らかに色が変わったかチェックする
	//明らかに色が変わっていたらtrue
	bool Change_Color_w(int b, int g, int r);
	bool Change_Color_b(int b, int g, int r);
	bool Change_Color(int r, int g, int b, int r_, int g_, int b_);

	void Check_Key();
	int Get_Color_b(int x, int y);
	int Get_Color_g(int x, int y);
	int Get_Color_r(int x, int y);

	int Get_Color_b(int x, int y, cv::Mat mat);
	int Get_Color_g(int x, int y, cv::Mat mat);
	int Get_Color_r(int x, int y, cv::Mat mat);

	int Get_WB(int x, int y, cv::Mat mat);

	bool True_White(int n);

	void Register_Event(int key, int event);

	void Output_txt();



};


#endif ANALYSIS_HPP
