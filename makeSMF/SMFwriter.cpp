#include "SMFwriter.hpp"

SMFwriter::SMFwriter()
{
}

void SMFwriter::Regist_Head()
{
	//�`�����N�^�C�v(4byte)
	header_chunk.push_back(0x4D);
	header_chunk.push_back(0x54);
	header_chunk.push_back(0x68);
	header_chunk.push_back(0x64);

	//�f�[�^��(4byte)
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x06);

	//�t�H�[�}�b�g(2byte)
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x00);

	//�g���b�N��(2byte)
	header_chunk.push_back(0x00);
	header_chunk.push_back(0x01);
	
	//���ԒP��
	//�ȉ��̐ݒ�Ńg���b�N��
	//�g���b�N���~���Z�J���h�E�x�[�X�ɂł���炵��
	header_chunk.push_back(0xE2);
	header_chunk.push_back(0x50);

}

void SMFwriter::Note_On(double time, int key)
{
	int delta = time_record - time;


	

	//���̌v�Z�p�ɕۑ����Ă���
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

	//cout << "SUUUUM 0x" << hex << sum(0x80) << endl;
	//cout << "SUUUUM 0x" << hex << sum(0x20) << endl;
	//int n = 0x90;
	//// int�^ sizeof n �o�C�g (�ʏ�4�o�C�g) �̗̈�̐擪
	//// �A�h���X &n �� write �̈��� const char* �ɃL���X�g
	//fs.write((const char*)&n, sizeof n);

	this->Regist_Head();
	for (auto i : this->header_chunk) {
		fs.write((const char*)&i, 1);
		
	}



	//Variable-length quantity �ϒ����l�\���̃e�X�g�O

	VLQ_Converter(0x08000000);
	




	fs.close();
	return;
}

vector<long> SMFwriter::VLQ_Converter(long time)
{


	//cout << "���͂́A" << time << "(10)" << endl;

	//cout << "���͂́A0x" << hex << time << "(16)" << endl;

	std::stringstream ss;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//�����̃o�C�g�T�C�Y�w��A�v�Ďv�l
	ss << std::bitset<32>(time);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	string s;
	s = ss.str();

	vector<long> n_long;

	//cout << "2�i��������ɕϊ�" << s << endl;

	string s_;

	if (s.size() > 7) {
		//n = stoi("0" + s.substr(s.size() - 8, 7));
		s_ = "0" + s.substr(s.size() - 7, 7);
		n_long.push_back(binToUInt(s_));
		s.erase(s.size() - 7, 7);
	}
	else {
		s_ = s;
		n_long.push_back(binToUInt(s_));
	}


	while (s.size() > 7) {

		s_ = "1" + s.substr(s.size() - 7, 7);
		n_long.push_back(binToUInt(s_));
		s.erase(s.size()-7, 7);
		
	}


	//cout << "�Q�i���t���O�t���ɕϊ� cout " << s_ << endl;

	std::reverse(n_long.begin(), n_long.end());

	//for (auto i : n_long) {
	//	cout << "HEX" << hex << i << endl;
	//}

	
	return n_long;
}


