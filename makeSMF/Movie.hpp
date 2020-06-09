#pragma once


#ifndef   MOVIE_HPP
#define   MOVIE_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "Setting.hpp"

using namespace cv;
using namespace std;


class Movie
{
private:
	VideoCapture cap;//動画を読み込むためのバッファ
	Setting set;//設定管理のクラスのインスタンス
	Mat img;//画像用のバッファ、動画から１フレームずつ取り出す
	int max_frame;
	int cur_frame_num = 0;//現在読み込んでいるフレーム

public:
	Movie();
	~Movie();

	Mat Get_Next_Frame();

	inline int Get_Width() {
		return cap.get(CAP_PROP_FRAME_WIDTH);
	}

	inline int Get_FPS() {
		return cap.get(CAP_PROP_FPS);
	}

	inline int Get_Max_Frame() {
		return this->max_frame;
	}

	inline int Cur_Frame_Num() {
		return this->cur_frame_num;
	}

	inline Setting Get_Set() {
		return set;
	}


};

#endif // MOVIE_HPP
