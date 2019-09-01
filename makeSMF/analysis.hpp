#pragma once

#ifndef ANALYSIS_HPP
#define	ANALYSIS_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

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

		//int default_color;

	public:
		
		Analysis();
		void Set_Coodinates();
		void Analyze();

};


#endif //ANALYSIS_HPP