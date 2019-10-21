#pragma once

#ifndef MIDI_CONTROLLER_HPP
#define	MIDI_CONTROLLER_HPP

#include <MIDIData.h>
#include <stdio.h>
#include <locale.h>

class MidiController
{
private:
	MIDIData* pMIDIData;
	MIDITrack* pMIDITrack;

public:
	MidiController();

};

#endif MIDI_CONTROLLER_HPP