#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string> 

#include "Analysis.hpp";

using namespace cv;
using namespace std;

int main()
{

	Analysis analysis;

	//analysis.Check_Coodinates();

	analysis.Analyze();
	
}