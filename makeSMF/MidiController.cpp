#include "MidiController.hpp"

MidiController::MidiController()
{
	midifile.addTimbre(track, 0, channel, instr);
}

MidiController::~MidiController()
{
	midifile.sortTracks();  // Need to sort tracks since added events are
						   // appended to track in random tick order.
	string filename = "smf.mid";
	if (filename.empty()) {
		//options.getBoolean("hex")
		if (true) midifile.writeHex(cout);
		else cout << midifile;
	}
	else
		midifile.write(filename);
}

void MidiController::noteOn(int time, int key)
{
	midifile.addNoteOn(track, time, channel, key, 0);
}

void MidiController::noteOff(int time, int key)
{
	midifile.addNoteOff(track, time, channel, key);
}

void MidiController::test()
{
}
