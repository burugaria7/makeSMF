#include "Setting.hpp"

Setting::Setting()
{
	//とりあえずここで設定、そのうち引数からもらうように？
	this->input_path = "C:\\Users\\Retasu\\Documents\\Github\\makeSMF\\videos\\cho720.mp4";
	//this->input_path = "C:\\Users\\Retasu\\Documents\\Github\\makeSMF\\videos\\from the new world.mp4";
	this->offset = 3;//とりあえず(s)、(ms)にするかも
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
