#include "MidiController.hpp"

MidiController::MidiController()
{
	//pMIDIData = MIDIData_Create(MIDIDATA_FORMAT0, 1, MIDIDATA_TPQNBASE, 120);
	//if (pMIDIData == NULL) {
	//	printf("MIDI�f�[�^�̐����Ɏ��s���܂����B\n");
	//	
	//}
	///* �ŏ��̃g���b�N�ւ̃|�C���^���擾 */
	//pMIDITrack = MIDIData_GetFirstTrack(pMIDIData);

	//const wchar_t wch[1] = { 'a'};

	///* �C�x���g��}�� */
	//MIDITrack_InsertTrackName(pMIDITrack, 0, wch); /* �^�C�g�� */
	//MIDITrack_InsertTempo(pMIDITrack, 0, 60000000 / 120); /* 120BPM */
	//MIDITrack_InsertProgramChange(pMIDITrack, 0, 0, 0); /* Piano1 */


}

MidiController::~MidiController()
{
	///* �G���h�I�u�g���b�N�C�x���g��}�� */
	//MIDITrack_InsertEndofTrack(pMIDITrack, 1920);

	//const wchar_t wch[5] = {'a','.','m','i','d'};

	///* MIDI�f�[�^��ۑ� */
	//MIDIData_SaveAsSMF(pMIDIData, wch);
	///* MIDI�f�[�^���������ォ��폜 */
	//MIDIData_Delete(pMIDIData);
	//pMIDIData = NULL;
}
