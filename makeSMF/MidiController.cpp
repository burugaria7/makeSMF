#include "MidiController.hpp"

MidiController::MidiController()
{
	//pMIDIData = MIDIData_Create(MIDIDATA_FORMAT0, 1, MIDIDATA_TPQNBASE, 120);
	//if (pMIDIData == NULL) {
	//	printf("MIDIデータの生成に失敗しました。\n");
	//	
	//}
	///* 最初のトラックへのポインタを取得 */
	//pMIDITrack = MIDIData_GetFirstTrack(pMIDIData);

	//const wchar_t wch[1] = { 'a'};

	///* イベントを挿入 */
	//MIDITrack_InsertTrackName(pMIDITrack, 0, wch); /* タイトル */
	//MIDITrack_InsertTempo(pMIDITrack, 0, 60000000 / 120); /* 120BPM */
	//MIDITrack_InsertProgramChange(pMIDITrack, 0, 0, 0); /* Piano1 */


}

MidiController::~MidiController()
{
	///* エンドオブトラックイベントを挿入 */
	//MIDITrack_InsertEndofTrack(pMIDITrack, 1920);

	//const wchar_t wch[5] = {'a','.','m','i','d'};

	///* MIDIデータを保存 */
	//MIDIData_SaveAsSMF(pMIDIData, wch);
	///* MIDIデータをメモリ上から削除 */
	//MIDIData_Delete(pMIDIData);
	//pMIDIData = NULL;
}
