#include "MidiController.hpp"

MidiController::MidiController()
{
	pMIDIData = MIDIData_Create(MIDIDATA_FORMAT0, 1, MIDIDATA_TPQNBASE, 120);
	if (pMIDIData == NULL) {
		printf("MIDI�f�[�^�̐����Ɏ��s���܂����B\n");
		
	}
	/* �ŏ��̃g���b�N�ւ̃|�C���^���擾 */
	pMIDITrack = MIDIData_GetFirstTrack(pMIDIData);

	/* �C�x���g��}�� */
	MIDITrack_InsertTrackName(pMIDITrack, 0, "��"); /* �^�C�g�� */
	MIDITrack_InsertTempo(pMIDITrack, 0, 60000000 / 120); /* 120BPM */
	MIDITrack_InsertProgramChange(pMIDITrack, 0, 0, 0); /* Piano1 */


}