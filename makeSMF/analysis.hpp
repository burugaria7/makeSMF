#pragma once

#ifndef ANALYSIS_HPP
#define	ANALYSIS_HPP

#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Movie.hpp"

class Analysis
{

	private:
		int key_white_x[52];
		int key_white_y;
		int key_black_x[36];
		int key_black_y;

		//bool key_flag[88];

		Movie movie;

		cv::Mat frame;

		int def_w_clrB;
		int def_w_clrG;
		int def_w_clrR;

		int def_b_clrB;
		int def_b_clrG;
		int def_b_clrR;

		bool key_event[88];


	public:
		
		Analysis();
		void Set_Coodinates();
		void Set_Color();
		void Analyze();
		void Check_Coodinates();

		//明らかに色が変わったかチェックする
		//明らかに色が変わっていたらtrue
		bool Change_Color_w(int b,int g,int r);
		bool Change_Color_b(int b, int g, int r);

		void Check_Key();
		int Get_Color_b(int x,int y);
		int Get_Color_g(int x, int y);
		int Get_Color_r(int x, int y);

};


#endif //ANALYSIS_HPP