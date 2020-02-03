#include "SMFwriter.hpp"

SMFwriter::SMFwriter()
{
}

void SMFwriter::Regist_Head()
{
	//チャンクタイプ(4byte)
	header_chunk.push_back(0x4D);
	header_chunk.push_back(0x54);
	header_chunk.push_back(0x68);
	header_chunk.push_back(0x64);

	//データ長(4byte)
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x06);

	//フォーマット(2byte)
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x00);

	//トラック数(2byte)
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x01);
	
	//時間単位
	//以下の設定でトラックを
	//トラックをミリセカンド・ベースにできるらしい
	header_chunk.push_back(0xE2);
	header_chunk.push_back(0x50);

}

void SMFwriter::Note_On(double time, int key)
{
	int delta = time_record - time;


	

	//次の計算用に保存しておく
	time_record = time; 
}

void SMFwriter::Note_Off(double time, int key)
{
}

void SMFwriter::Test()
{
	fstream fs;

	fs.open("output.bin", ios::out | ios::binary);
	if (!fs.is_open()) {
		return;
	}

	//cout << "SUUUUM 0x" << hex << sum(0x80) << endl;
	//cout << "SUUUUM 0x" << hex << sum(0x20) << endl;
	//int n = 0x90;
	//// int型 sizeof n バイト (通常4バイト) の領域の先頭
	//// アドレス &n を write の引数 const char* にキャスト
	//fs.write((const char*)&n, sizeof n);

	this->Regist_Head();
	for (auto i : this->header_chunk) {
		fs.write((const char*)&i, 1);
		
	}



	//Variable-length quantity 可変長数値表現のテスト＾

	VLQ_Converter(0x08000000);
	




	fs.close();
	return;
}

vector<long> SMFwriter::VLQ_Converter(long time)
{


	//cout << "入力は、" << time << "(10)" << endl;

	//cout << "入力は、0x" << hex << time << "(16)" << endl;

	std::stringstream ss;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//ここのバイトサイズ指定、要再思考
	ss << std::bitset<32>(time);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	string s;
	s = ss.str();

	vector<long> n_long;

	//cout << "2進数文字列に変換" << s << endl;

	string s_;

	if (s.size() > 7) {
		//n = stoi("0" + s.substr(s.size() - 8, 7));
		s_ = "0" + s.substr(s.size() - 7, 7);
		n_long.push_back(binToUInt(s_));
		s.erase(s.size() - 7, 7);
	}
	else {
		s_ = s;
		n_long.push_back(binToUInt(s_));
	}


	while (s.size() > 7) {

		s_ = "1" + s.substr(s.size() - 7, 7);
		n_long.push_back(binToUInt(s_));
		s.erase(s.size()-7, 7);
		
	}


	//cout << "２進数フラグ付きに変換 cout " << s_ << endl;

	std::reverse(n_long.begin(), n_long.end());

	//for (auto i : n_long) {
	//	cout << "HEX" << hex << i << endl;
	//}

	
	return n_long;
}


