#include "Movie.hpp"

Movie::Movie()
{


	/*if (!(this->cap.open(this->set.Get_Input_Path()))) {
		cout << "�t�@�C���I�[�v�����s" << endl;
		return;
	}*/


	cout << "��͂������t�@�C����D&D���ăG���^�[�������Ă�������" << endl;
	String str;
	cin >> str;

	if (!(this->cap.open(str))) {
		cout << "�t�@�C���I�[�v�����s" << endl;
		exit(1);
	}

	
	//�I�[�v���ł������̃`�F�b�N���������Ă�
	this->set.Set_Prog(cap.get(CAP_PROP_FRAME_WIDTH));
	this->max_frame = cap.get(CAP_PROP_FRAME_COUNT);

	//�����ŃI�t�Z�b�g����΂�
	for (int i = 0; i < this->Get_FPS()*this->Get_Set().Get_Offset(); i++) {
		if (cur_frame_num < max_frame) {
			cap >> img;
		}
	}

}

Movie::~Movie()
{
}

Mat Movie::Get_Next_Frame()
{
	if (cur_frame_num < max_frame) {
		cap >> img;
	}

	return this->img;
}
