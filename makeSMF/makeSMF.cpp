#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cv::namedWindow("movie", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;
	cap.open("C:\\Users\\Retasu\\Documents\\Github\\makeSMF\\videos\\cho720.mp4");
	if (!cap.isOpened()) {
		cout << "path error\n" << endl;
		return -1;
	}

	double fps = cap.get(cv::CAP_PROP_FPS);

	cv::Mat frame;
	for (;;) {
		cap >> frame;
		if (frame.empty()) break;
		cv::imshow("movie", frame);
		if ((char)cv::waitKey((int)1000 / fps) >= 0) break;
	}
}