#include "MidiController.hpp"

MidiController::MidiController()
{
	pMIDIData = MIDIData_Create(MIDIDATA_FORMAT0, 1, MIDIDATA_TPQNBASE, 120);
	if (pMIDIData == NULL) {
		printf("MIDIデータの生成に失敗しました。\n");
		
	}
	/* 最初のトラックへのポインタを取得 */
	pMIDITrack = MIDIData_GetFirstTrack(pMIDIData);

	/* イベントを挿入 */
	MIDITrack_InsertTrackName(pMIDITrack, 0, "あ"); /* タイトル */
	MIDITrack_InsertTempo(pMIDITrack, 0, 60000000 / 120); /* 120BPM */
	MIDITrack_InsertProgramChange(pMIDITrack, 0, 0, 0); /* Piano1 */


}