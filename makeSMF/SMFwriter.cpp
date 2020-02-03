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

	VLQ_Converter(0x80000000);
	




	fs.close();
	return;
}

int SMFwriter::VLQ_Converter(long time)
{


	cout << "���͂́A" << time << "(10)" << endl;

	cout << "���͂́A0x" << hex << time << "(16)" << endl;

	std::stringstream ss;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//�����̃o�C�g�T�C�Y�w��A�v�Ďv�l
	ss << std::bitset<32>(time);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	string s;
	s = ss.str();

	int t = 18897;
	cout << "2�i��������ɕϊ�" << s << endl;

	int n;

	while (s.size() > 7) {

		if (s.size() < 8) {
			n = atoi(s.c_str());
		}
		else {
			n = stoi("1" + s.substr(s.size() - 8, 7));
			s.erase(s.size()-8, 7);
		}

		cout << "�Q�i���t���O�t���ɕϊ�" << n << endl;
	}


	//int n = std::atoi(s.c_str());

	return 0;
}
