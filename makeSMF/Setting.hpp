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

	public:
		Setting();
		Setting(string path,int offset, int resol);
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
};

#endif // SETTING_HPP
