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


	//int n = 0x90;
	//// int�^ sizeof n �o�C�g (�ʏ�4�o�C�g) �̗̈�̐擪
	//// �A�h���X &n �� write �̈��� const char* �ɃL���X�g
	//fs.write((const char*)&n, sizeof n);

	this->Regist_Head();
	for (auto i : this->header_chunk) {
		fs.write((const char*)&i, 1);
		
	}


	fs.close();
	return;
}
