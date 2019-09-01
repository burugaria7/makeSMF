#include "Analysis.hpp"

Analysis::Analysis()
{
	this->Set_Coodinates();
}

void Analysis::Set_Coodinates()
{

	//720p 88key
	if (movie.Get_Set().Get_Mode() == 2) {

		//white

		this->key_white_y = 680;

		for (int i = 0; i < 52; i++) {
			this->key_white_x[i] = (24.5 / 2.0) * (i + 1);
		}

		//black

		this->key_black_y = 620;

		for (int i = 0; i < 36; i++) {
			
		}

	}

}

void Analysis::Analyze()
{

	cv::namedWindow("movie", cv::WINDOW_AUTOSIZE);

	double fps = movie.Get_FPS();

	cv::Mat frame;
	for (;;) {
		frame = movie.Get_Next_Frame();
		if (frame.empty()) break;
		cv::imshow("movie", frame);
		if ((char)cv::waitKey((int)1000 / fps) >= 0) break;
	}
}
