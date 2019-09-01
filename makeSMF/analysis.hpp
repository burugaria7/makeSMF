#pragma once

#ifndef ANALYSIS_HPP
#define	ANALYSIS_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "Movie.hpp"

class analysis
{

	private:
		int key_white_x[52];
		int key_white_y[52];
		int key_black_x[36];
		int key_black_y[36];

		bool key_flag[88];

		Movie movie;

		//int default_color;

	public:

		void Set_Coodinates();


};


#endif //ANALYSIS_HPP