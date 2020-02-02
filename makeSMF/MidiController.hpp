#pragma once

#ifndef MIDI_CONTROLLER_HPP
#define	MIDI_CONTROLLER_HPP

#include <stdio.h>
#include <iostream>
#include <locale.h>
#include <tchar.h>
#include <MidiFile.h>

using namespace std;
using namespace smf;

class MidiController
{
private:

	MidiFile midifile;
	int track = 0;
	int channel = 0;
	int instr = 0;

public:
	MidiController();
	~MidiController();

	void noteOn(int time,int key);
	void noteOff(int time, int key);

	void test();

};

#endif MIDI_CONTROLLER_HPP