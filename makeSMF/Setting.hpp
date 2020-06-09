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
		//int key;//���Ր�

		/*	
		mode�ԍ�-���e
		0-manual �摜��\�����ăN���b�N�Őݒ�
		1-480 88
		2-720 88
		3-1080 88
		�Ȃǂ悭����ݒ���쐬
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
