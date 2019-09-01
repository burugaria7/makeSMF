#include "Movie.hpp"

Movie::Movie()
{
	this->cap.open(this->set.Get_Input_Path());
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
