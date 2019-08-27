#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string> 

#include "Setting.hpp";
#include "Movie.hpp";

using namespace cv;
using namespace std;

int main()
{

	Movie movie;

	//string path = "C:\\Users\\Retasu\\Documents\\Github\\makeSMF\\videos\\cho720.mp4";

	cv::namedWindow("movie", cv::WINDOW_AUTOSIZE);
	//cv::VideoCapture cap;
	//cap.open(path);
	//if (!movie.Get_Next_Frame.isOpened()) {
	//	cout << "path error\n" << endl;
	//	return -1;
	//}

	double fps = movie.Get_FPS();

	cv::Mat frame;
	for (;;) {
		frame = movie.Get_Next_Frame();
		if (frame.empty()) break;
		cv::imshow("movie", frame);
		if ((char)cv::waitKey((int)1000 / fps) >= 0) break;
	}
}