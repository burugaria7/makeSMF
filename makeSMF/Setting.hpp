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
		//string output_path; //�Ƃ肠�����f�t�H���g���[�g�p�X�Ŏ������܂���
		int offset = 0; //�܂�܃I�t�Z�b�g
		int progressive; //480p 720p 1080p �Ƃ��Ƃ�
		int resolution; //����\

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
