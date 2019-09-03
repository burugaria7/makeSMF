#pragma once

#ifndef ANALYSIS_HPP
#define	ANALYSIS_HPP

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

		bool key_flag[88];

		Movie movie;

		cv::Mat frame;

		int def_clr_B;
		int def_clr_G;
		int def_clr_R;


	public:
		
		Analysis();
		void Set_Coodinates();
		void Set_Color();
		void Analyze();
		void Check_Coodinates();

};


#endif //ANALYSIS_HPP