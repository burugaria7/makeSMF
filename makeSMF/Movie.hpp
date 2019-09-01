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
		VideoCapture cap;//�����ǂݍ��ނ��߂̃o�b�t�@
		Setting set;//�ݒ�Ǘ��̃N���X�̃C���X�^���X
		Mat img;//�摜�p�̃o�b�t�@�A���悩��P�t���[�������o��
		int max_frame;
		int cur_frame_num = 0;//���ݓǂݍ���ł���t���[��

	public:
		Movie();
		~Movie();

		Mat Get_Next_Frame();

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

