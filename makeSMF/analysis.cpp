#include "Analysis.hpp"

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

	cout << "Set_Coodinates() 座標セット関数" << endl;

	//720p 88key
	if (movie.Get_Set().Get_Mode() == 2) {

		cout << "Mode = 720p 88 key" << endl;

		//white

		this->key_white_y = 665;

		for (int i = 0; i < 52; i++) {
			this->key_white_x[i] = (24.5 / 2.0) + i * 24.6;
		}

		//black

		this->key_black_y = 620;

		this->key_black_x[0] = 27;

		int k = 0;
		int def = 27;
		#define W_1 43;
		#define W_2 29;
		for (int i = 1; i < 36; i++) {
			switch (k){
			case 0:
				def += W_1;
				break;
			case 1:
				def += W_2;
				break;
			case 2:
				def += W_1;
				break;
			case 3:
				def += W_2;
				break;
			case 4:
				def += W_2;
				k = -1;
				break;
			}
			k++;
			this->key_black_x[i] = def;
		}
	}
	this->Check_Coodinates();
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

	double fps = movie.Get_FPS();

	for (;;frame = movie.Get_Next_Frame()) {
		
		if (frame.empty()) break;
		this->Check_Key();
		cv::imshow("movie", frame);
		if ((char)cv::waitKey((int)1000 / fps) >= 0) break;
	}
}

void Analysis::Check_Coodinates()
{

	cout << "Check_Coodinates() 座標チェック関数" << endl;

	cv::namedWindow("movie", cv::WINDOW_AUTOSIZE);

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

	cv::imshow("movie", frame);

	cv::waitKey(0);
}

bool Analysis::Change_Color_w(int sum)
{
	int def_sum = def_w_clrB + def_w_clrG + def_w_clrR;

	if (abs(sum - def_sum) > 100) { //ここの値は調整してね
		return true;//色が変わってるね！
	}else{
		return false;
	}
}

bool Analysis::Change_Color_b(int sum)
{

	int def_sum = def_b_clrB + def_b_clrG + def_b_clrR;

	if (abs(sum - def_sum) > 100) { //ここの値は調整してね
		return true;//色が変わってるね！
	}
	else {
		return false;
	}
}

void Analysis::Check_Key()
{

	int x, y;

	//C5_31_W

	x = key_white_x[31];
	y = key_white_y;

	if (this->key_event[31] == false) {
		if (Change_Color_w(Get_Color_Sum(x, y))){
			cout <<"C5 on"<<endl;
			key_event[31] = true;
		}
	}else {
		if (!Change_Color_w(Get_Color_Sum(x, y))) {
			cout << "C5 off" << endl;
			key_event[31] = false;
		}
	}

}

int Analysis::Get_Color_Sum(int x, int y)
{
	int b = frame.at<Vec3b>(y, x)[0];
	int g = frame.at<Vec3b>(y, x)[1];
	int r = frame.at<Vec3b>(y, x)[2];
	return b + g + r;
}
