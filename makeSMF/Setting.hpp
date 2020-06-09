#pragma once

#ifndef   SETTING_HPP
#define   SETTING_HPP

#include <string> 
#include <iostream>

using namespace std;

class Setting
{
	private:
		string input_path;
		//string output_path; //とりあえずデフォルトルートパスで実装しましょ
		int offset = 0; //まんまオフセット
		int progressive; //480p 720p 1080p とかとか
		int resolution; //分解能
		//int key;//鍵盤数

		/*	
		mode番号-内容
		0-manual 画像を表示してクリックで設定
		1-480 88
		2-720 88
		3-1080 88
		などよくある設定を作成
		*/
		int mode; 

	public:
		Setting();
		Setting(int offset, int resol);
		~Setting();

		inline string Get_Input_Path() {
			return this->input_path;
		}

		inline int Get_Offset() {
			return this->offset;
		}

		inline int Get_Prog() {
			return this->progressive;
		}

		inline int Get_Resol() {
			return this->resolution;
		}

		inline void Set_Prog(int prog) {
			this->progressive = prog;
		}

		inline int Get_Mode() {
			return this->mode;
		}
};

#endif // SETTING_HPP
