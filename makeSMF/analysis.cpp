﻿#include "Analysis.hpp"


Analysis::Analysis()
{

	cout << "Analysisコンストラクタ呼び出し" << endl;
	this->Set_Coodinates();
	this->Set_Color();

	for (int i = 0; i < 88; i++) {
		this->key_event[i] = false;
	}
}

void Analysis::Set_Coodinates()
{

	//ここに鍵盤を探す処理を書く
	/*bool mikke = true;
	while (mikke) {

	}*/

	frame = movie.Get_Next_Frame();



	cv::Mat gray_img;
	// グレースケールに変換する
	cvtColor(frame, gray_img, cv::COLOR_BGR2GRAY);

	// 画像を平滑化する
	double sigmaX = 1.0;
	double sigmaY = 1.0;
	UMat destination;
	GaussianBlur(gray_img, destination, Size(5, 5), sigmaX, sigmaY);

	cv::Mat canny_img;
	cv::Canny(destination, canny_img, 50, 110);

	//cv::Mat img_(2, 1, CV_8UC3), canny_img;
	//cv::Mat img_;

	int length = this->movie.Get_Width();

	int tate = 600;

	//int r_ = this->Get_Color_r(0, tate, img_);
	//int g_ = this->Get_Color_g(0, tate, img_);
	//int b_ = this->Get_Color_b(0, tate, img_);
	int wb = this->Get_WB(0, tate, canny_img);

	vector<int> xxx;

	for (int i = 1; i < canny_img.cols; i++) {
		//cv::circle(frame, cv::Point(i, tate), 3, cv::Scalar(0, 200, 0), 3, 4);
		/*int rr = this->Get_Color_r(i, tate, img_);
		int gg = this->Get_Color_g(i, tate, img_);
		int bb = this->Get_Color_b(i, tate, img_);*/
		int wb_ = this->Get_WB(i, tate, canny_img);
		cout << "WB:" << wb << " ";
		//cout << "R;" << rr << "G:" << gg << "B:" << bb << endl;

		//cv::circle(frame, cv::Point(i, tate), 3, cv::Scalar(0, 200, 0), 3, 4);

		if (Change_Color(wb, 0, 0, wb_, 0, 0)) {
			wb = wb_;
			xxx.push_back(i);
		}

	}


	cout << "" << endl;

	int fla = 1;
	cv::Mat mat_ = frame;
	cv::circle(mat_, cv::Point(30, tate), 3, cv::Scalar(0, 200, 0), 3, 4);

	for (auto xx : xxx) {
		cout << "X:" << xx << " ";

		if (fla == 1) {
			cv::circle(mat_, cv::Point(xx, tate + 10), 3, cv::Scalar(0, 200, 0), 3, 4);
		}
		else {
			cv::circle(mat_, cv::Point(xx, tate), 3, cv::Scalar(0, 200, 0), 3, 4);
		}

		fla *= -1;
	}

	cout << "" << endl;


	//cv::imshow("座標チェック", canny_img);
	cv::imshow("座標チェック", mat_);

	cv::waitKey(0);

	cv::destroyAllWindows();


	//this->Check_Coodinates();
}

void Analysis::Set_Color()
{
	cout << "Set_Color() デフォルトカラー取得関数" << endl;

	this->def_w_clrB = frame.at<Vec3b>(key_white_y, key_white_x[0])[0];
	this->def_w_clrG = frame.at<Vec3b>(key_white_y, key_white_x[0])[1];
	this->def_w_clrR = frame.at<Vec3b>(key_white_y, key_white_x[0])[2];

	this->def_b_clrB = frame.at<Vec3b>(key_black_y, key_black_x[0])[0];
	this->def_b_clrG = frame.at<Vec3b>(key_black_y, key_black_x[0])[1];
	this->def_b_clrR = frame.at<Vec3b>(key_black_y, key_black_x[0])[2];

	cout << "B:" << def_w_clrB << ",G:" << def_w_clrG << ",R:" << def_w_clrR << endl;
	cout << "B:" << def_b_clrB << ",G:" << def_b_clrG << ",R:" << def_b_clrR << endl;

}

void Analysis::Analyze()
{

	const static double fps = movie.Get_FPS();

	int frame_count = 1;

	for (;; frame = movie.Get_Next_Frame()) {

		if (frame.empty()) break;

		this->Check_Key();//ここでキーイベントをアップデート

		double time_now = ((double)frame_count / fps);

		//同時発音数が一定以下でイベント本登録
		if (str.size() > 0 && str.size() < 30) {

			cout << std::to_string(time_now) << endl;

			this->str_ += std::to_string(time_now);
			this->str_ += "ms";
			this->str_ += str;
			this->str_ += "\n";
			//cout << str.size() << endl;;
		}

		str = "";

		frame_count++;
		this->first_key = 0;
		this->active_key_sum = 0;
		cv::imshow("movie", frame);

		//ここのコメントアウトはずすと動画速度になる
		if ((char)cv::waitKey((int)1000 / fps) >= 0) break;
	}

	//最後にファイルに書き出し
	this->Output_txt();
	smf.Test();
}

void Analysis::Check_Coodinates()
{

	cout << "Check_Coodinates() 座標チェック関数" << endl;

	//cv::namedWindow("座標チェック", cv::WINDOW_AUTOSIZE);

	double fps = movie.Get_FPS();

	frame = movie.Get_Next_Frame();

	for (const auto& e : this->key_white_x) {
		cout << e << endl;
		cv::circle(frame, cv::Point(e, this->key_white_y), 3, cv::Scalar(0, 0, 200), 3, 4);
	}

	for (const auto& e : this->key_black_x) {
		cout << e << endl;
		cv::circle(frame, cv::Point(e, this->key_black_y), 3, cv::Scalar(0, 200, 0), 3, 4);
	}

	int i = 0;
	for (const auto& e : this->key_x) {
		cout << i << "^" << e;
		cv::circle(frame, cv::Point(e, this->key_black_y + 30), 3, cv::Scalar(255, 255, 0), 3, 4);
		i += 1;
	}

	cv::imshow("座標チェック", frame);

	cv::waitKey(0);

	cv::destroyAllWindows();
}

bool Analysis::Change_Color_w(int b, int g, int r)
{
	int diff = abs(b - def_w_clrB)
		+ abs(g - def_w_clrG)
		+ abs(r - def_w_clrR);

	if (diff > threshold) {
		return true;//色が変わってるね！
	}
	else {
		return false;
	}
}

bool Analysis::Change_Color_b(int b, int g, int r)
{

	int diff = abs(b - def_b_clrB)
		+ abs(g - def_b_clrG)
		+ abs(r - def_b_clrR);

	if (diff > threshold) {
		return true;//色が変わってるね！
	}
	else {
		return false;
	}
}

bool Analysis::Change_Color(int r, int g, int b, int r_, int g_, int b_)
{
	int diff = abs(b - b_)
		+ abs(g - g_)
		+ abs(r - r_);

	if (diff > ikiti) {
		return true;//色が変わってるね！
	}
	else {
		return false;
	}

}


void Analysis::Check_Key()
{

	int x, y, key;

	for (key = 0; key < 88; key++) {
		x = key_x[key];
		if (True_White(key)) {
			y = key_white_y;
			if (this->key_event[key] == false) {
				if (Change_Color_w(
					Get_Color_b(x, y),
					Get_Color_g(x, y),
					Get_Color_r(x, y)))
				{
					cout << "[" << key << "W:on]" << endl;

					cv::circle(frame, cv::Point(x, y), 3, cv::Scalar(0, 0, 200), 3, 4);

					this->Register_Event(key, 1);
					key_event[key] = true;

				}
			}
			else {
				if (!Change_Color_w(
					Get_Color_b(x, y),
					Get_Color_g(x, y),
					Get_Color_r(x, y))) {
					cout << "[" << key << "W:off]" << endl;

					cv::circle(frame, cv::Point(x, y), 3, cv::Scalar(0, 200, 0), 3, 4);

					this->Register_Event(key, 0);
					key_event[key] = false;
				}
			}
		}
		else {
			y = key_black_y;
			if (this->key_event[key] == false) {
				if (Change_Color_b(
					Get_Color_b(x, y),
					Get_Color_g(x, y),
					Get_Color_r(x, y)))
				{
					cout << "[" << key << "B:on]" << endl;
					cv::circle(frame, cv::Point(x, y), 3, cv::Scalar(0, 0, 200), 3, 4);
					this->Register_Event(key, 1);
					key_event[key] = true;
				}
			}
			else {
				if (!Change_Color_b(
					Get_Color_b(x, y),
					Get_Color_g(x, y),
					Get_Color_r(x, y))) {
					cout << "[" << key << "B:off]" << endl;

					cv::circle(frame, cv::Point(x, y), 3, cv::Scalar(0, 200, 0), 3, 4);

					this->Register_Event(key, 0);
					key_event[key] = false;
				}
			}
		}
	}
}


int Analysis::Get_Color_b(int x, int y, cv::Mat mat)
{
	int b = mat.at<Vec3b>(y, x)[0];
	return b;
}

int Analysis::Get_Color_g(int x, int y, cv::Mat mat)
{
	int g = mat.at<Vec3b>(y, x)[1];
	return g;
}

int Analysis::Get_Color_r(int x, int y, cv::Mat mat)
{
	int r = mat.at<Vec3b>(y, x)[2];
	return r;
}

int Analysis::Get_WB(int x, int y, cv::Mat mat)
{
	int wb = mat.at<unsigned char>(y, x);
	return wb;
}

int Analysis::Get_Color_b(int x, int y)
{
	int b = frame.at<Vec3b>(y, x)[0];
	return b;
}

int Analysis::Get_Color_g(int x, int y)
{
	int g = frame.at<Vec3b>(y, x)[1];
	return g;
}

int Analysis::Get_Color_r(int x, int y)
{
	int r = frame.at<Vec3b>(y, x)[2];
	return r;
}

bool Analysis::True_White(int n)
{
	n += 9;
	int a = n % 12;
	switch (a)
	{
	case 0:
		return true;
	case 1:
		return false;
	case 2:
		return true;
	case 3:
		return false;
	case 4:
		return true;
	case 5:
		return true;
	case 6:
		return false;
	case 7:
		return true;
	case 8:
		return false;
	case 9:
		return true;
	case 10:
		return false;
	case 11:
		return true;

	default:
		break;
	}
}

void Analysis::Register_Event(int key, int event)
{

	//cout << "BBBBBBBBB" << endl;
	//cout << "Register_Event呼び出し" << endl;


	std::ostringstream key_;
	key_ << key;

	str += "-";
	str += to_string(event);
	str += key_.str();
	this->active_key_sum++;
}

void Analysis::Output_txt()
{
	ofstream outputfile("output.txt");
	outputfile << str_;
	outputfile.close();
}
