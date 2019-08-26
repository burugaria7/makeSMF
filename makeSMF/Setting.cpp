#include "Setting.hpp"

Setting::Setting()
{
	//‚Æ‚è‚ ‚¦‚¸‚±‚±‚ÅÝ’èA‚»‚Ì‚¤‚¿ˆø”‚©‚ç‚à‚ç‚¤‚æ‚¤‚ÉH
	this->input_path = "C:\\Users\\Retasu\\Documents\\Github\\makeSMF\\videos\\cho720.mp4";
	this->Get_Offset = 0;
	this->Get_Resol = 5;
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
