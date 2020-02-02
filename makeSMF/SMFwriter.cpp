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


	//int n = 0x90;
	//// int型 sizeof n バイト (通常4バイト) の領域の先頭
	//// アドレス &n を write の引数 const char* にキャスト
	//fs.write((const char*)&n, sizeof n);

	this->Regist_Head();
	for (auto i : this->header_chunk) {
		fs.write((const char*)&i, 1);
		
	}


	fs.close();
	return;
}
