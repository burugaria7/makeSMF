#include "Analysis.hpp"


Analysis::Analysis()
{

	cout << "Analysisコンストラクタ呼び出し" << endl;
	this->Set_Coodinates();
	this->Set_Color();

	for (int i = 0; i < 52; i++) {
		this->key_w_event[i] = false;
	}
	for (int i = 0; i < 36; i++) {
		this->key_b_event[i] = false;
	}
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

		this->key_black_x[0] = 28.5;

		int k = 0;
		int def = 27;
		#define W_1 43.2;
		#define W_2 29.3;
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

	int num = 0;
	int white = 0;
	int black = 0;
	for (;num < 88;num++) {
		if (this->True_White(num)) {
			key_x[num] = key_white_x[white];
			white++;
			cout << num <<"w";
		}
		else {
			key_x[num] = key_black_x[black];
			black++;
			cout << num<< "b";
		}
	}

	cout << "" << endl;

	sort(key_x, key_x + 88);



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

	const static double fps = movie.Get_FPS();

	int frame_count = 1;

	for (;;frame = movie.Get_Next_Frame()) {
		
		if (frame.empty()) break;

		this->Check_Key();//ここでキーイベントをアップデート

		double time_now =((double)frame_count / fps);

		//同時発音数が一定以下でイベント本登録
		if (str.size() > 0&&str.size() < 30) { 

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


		if ((char)cv::waitKey((int)1000 / fps) >= 0) break;
	}

	//最後にファイルに書き出し
	this->Output_txt();
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

	int i = 0;
	for (const auto& e : this->key_x) {
		cout << i << "^" << e;
		cv::circle(frame, cv::Point(e, this->key_black_y + 30), 3, cv::Scalar(255, 255, 0), 3, 4);
		i += 1;
	}

	cv::imshow("movie", frame);

	cv::waitKey(0);
}

bool Analysis::Change_Color_w(int b, int g, int r)
{
	int diff = abs(b - def_w_clrB)
		+ abs(g - def_w_clrG)
		+ abs(r - def_w_clrR);

	if (diff > threshold) { 
		return true;//色が変わってるね！
	}else{
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

					this->Register_Event(key,1);
					key_event[key] = true;
					
				}
			}
			else {
				if (!Change_Color_w(
					Get_Color_b(x, y),
					Get_Color_g(x, y),
					Get_Color_r(x, y))) {
					cout << "[" << key << "W:off]" << endl;

					cv::circle(frame, cv::Point(x, y), 3, cv::Scalar(0,200, 0), 3, 4);
					
					this->Register_Event(key,0);
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
					this->Register_Event(key,1);
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

					this->Register_Event(key,0);
					key_event[key] = false;
				}
			}
		}
	}
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

void Analysis::Register_Event(int key,int event)
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

