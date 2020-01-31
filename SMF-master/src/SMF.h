/*
SMF.h - Library for make Standar MIDI Files
Created by Kevin A. Martinez, January 10, 2018.
*/
#ifndef SMF_h
#define SMF_h

#include <Arduino.h>

//Notes definition
#define C2 	0x24
#define C2s	0x25
#define D2 	0x26
#define D2s 0x27
#define E2 	0x28
#define F2 	0x29
#define F2s	0x2A
#define G2	0x2B
#define G2s	0x2C
#define A2	0x2D//110Hz
#define A2s	0x2E
#define B2	0x2F

#define C3 	0x30
#define C3s	0x31
#define D3 	0x32
#define D3s 0x33
#define E3 	0x34
#define F3 	0x35
#define F3s	0x36
#define G3	0x37
#define G3s	0x38
#define A3	0x39//220Hz
#define A3s	0x3A
#define B3	0x3B

//Central C
#define C4 	0x3C//261.63Hz
#define C4s	0x3D
#define D4 	0x3E
#define D4s 0x3F
#define E4 	0x40
#define F4 	0x41
#define F4s	0x42
#define G4	0x43
#define G4s	0x44
#define A4	0x45//440Hz
#define A4s	0x46
#define B4	0x47

#define C5 	0x48
#define C5s	0x49
#define D5 	0x4A
#define D5s 0x4B
#define E5 	0x4C
#define F5 	0x4D
#define F5s	0x4E
#define G5	0x4F
#define G5s	0x50
#define A5	0x51//880Hz
#define A5s	0x52
#define B5	0x53

#define C6 	0x54
#define C6s	0x55
#define D6 	0x56
#define D6s 0x57
#define E6 	0x58
#define F6 	0x59
#define F6s	0x5A
#define G6	0x5B
#define G6s	0x5C
#define A6	0x5D//1750Hz
#define A6s	0x5E
#define B6	0x5F


//Velocity definitions
#define ppp	0x01
#define pp	0x15
#define p	0x29
#define mp	0x3D
#define mf	0x43
#define f	0x57
#define ff	0x6B
#define fff 0x7F
#define standard 0x40

//figures definition
#define whole 		0x10
#define half 		0x08
#define quarter 	0x04
#define eighth 		0x02
#define sixteenth 	0x01

//instruments definition
#define grandPiano	0x00
#define organ 		0x10
#define bass		0x20
#define guitar		0x18

struct compass
{
	uint8_t numerator;
	uint8_t denominator;
};

struct hexArray
{
	uint32_t num;
	uint8_t* array;
};

class SMF
{
	public:
		//-------------For user use---------------------
		SMF(compass timeSignature, uint32_t tempoPerQuarter);
		void setInstrument(uint8_t channel, uint8_t instrument);
		void addNote(uint8_t channel,uint32_t silence, uint8_t note, uint8_t figure, uint8_t velocity);
		void noteOn(uint8_t channel, uint32_t deltaTime, uint8_t note, uint8_t velocity);
		void noteOff(uint8_t channel, uint32_t deltaTime, uint8_t note, uint8_t velocity);
		hexArray getFileCode();
		//----------------------------------------------
	private:
		void getHexCode(uint8_t* target,uint32_t value);
		void getVariableLength(uint8_t target[4], uint32_t value);
		bool copyBytes(uint8_t* destiny, uint8_t source[], uint32_t offset, uint32_t numElements);
		hexArray _notes;
		hexArray _instruments;
		uint8_t _headerChunk[14];
		uint8_t _trackChunk[8];
		uint8_t _end[4];
		uint32_t tempo;
		uint8_t _timeSignature[8];
		uint8_t _tempo[7];
};

#endif