#include "Setting.hpp"

Setting::Setting()
{
	//�Ƃ肠���������Őݒ�A���̂�������������炤�悤�ɁH
	this->input_path = "C:\\Users\\Retasu\\Documents\\Github\\makeSMF\\videos\\cho720.mp4";
	this->offset = 3;//�Ƃ肠����(s)�A(ms)�ɂ��邩��
	this->resolution = 5;
	this->mode = 2;
}

Setting::Setting(string path, int offset, int resol)
{
	this->input_path = path;
	this->offset = offset;
	this->resolution = resol;
}

Setting::~Setting()
{
}
