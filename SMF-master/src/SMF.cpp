/*
SMF.h - Library for make Standar MIDI Files
Created by Kevin A. Martinez, January 10, 2018.
*/
#include <Arduino.h>
#include "SMF.h"


/*------------------------------------------------------- 
@Initialize the file@

compass->numerator 		<byte>
compass->denominator 	<byte>

timeSignature <compass>
tempoPerQuarter <int> :The number of quarter notes per each second
----------------------------------------------------------*/
SMF::SMF(compass timeSignature, uint32_t tempoPerQuarter){

	uint8_t realDenom = 1;
	uint8_t comp = 2;
	uint8_t convert[4];

	_instruments.num=0;
	_instruments.array = new uint8_t[1];

	_notes.num=0;
	_notes.array= new uint8_t[1];

	tempo = (tempoPerQuarter/60)*1000000;

	this -> _headerChunk[0] = 0x4D;
	this -> _headerChunk[1] = 0x54;
	this -> _headerChunk[2] = 0x68;
	this -> _headerChunk[3] = 0x64;
	this -> _headerChunk[4] = 0x00;
	this -> _headerChunk[5] = 0x00;
	this -> _headerChunk[6] = 0x00;
	this -> _headerChunk[7] = 0x06;
	this -> _headerChunk[8] = 0x00;
	this -> _headerChunk[9] = 0x00;
	this -> _headerChunk[10] = 0x00;
	this -> _headerChunk[11] = 0x01;
	this -> _headerChunk[12] = 0x00;
	this -> _headerChunk[13] = 0x60;

	this -> _trackChunk[0] = 0x4D;
	this -> _trackChunk[1] = 0x54;
	this -> _trackChunk[2] = 0x72;
	this -> _trackChunk[3] = 0x6B;

	this -> _end[0] = 0x00;
	this -> _end[1] = 0xFF;
	this -> _end[2] = 0x2F;
	this -> _end[3] = 0x00;

	this -> _timeSignature[0] = 0x00;
	this -> _timeSignature[1] = 0xFF;
	this -> _timeSignature[2] = 0x58;
	this -> _timeSignature[3] = 0x04;
	this -> _timeSignature[4] = 0x04;
	this -> _timeSignature[5] = 0x02;
	this -> _timeSignature[6] = 0x18;
	this -> _timeSignature[7] = 0x08;

	this -> _timeSignature[4] = timeSignature.numerator;

	if(timeSignature.denominator==1) _timeSignature[5]=0;
	else if(timeSignature.denominator==2) _timeSignature[5]=1;
	else if(timeSignature.denominator%2==0){

		do{
			comp *= 2;
			realDenom++;
		}while(comp < timeSignature.denominator && realDenom < 20);

		if(realDenom >= 20)_timeSignature[5]=2;
		else this -> _timeSignature[5]=realDenom;
	}

	this->_tempo[0] = 0x00;
	this->_tempo[1] = 0xFF;
	this->_tempo[2] = 0x51;
	this->_tempo[3] = 0x03;

	getHexCode(convert, tempo);
	this->_tempo[4] = convert[1];
	this->_tempo[5] = convert[2];
	this->_tempo[6] = convert[3];
}


/*------------------------------------------------------- 
@Assign an instrument to a channel@

Channel 	<byte>
Instrument 	<byte>	: the code of the MIDI instrument. **See the definitions on SMF.h
----------------------------------------------------------*/
void SMF::setInstrument(uint8_t channel, uint8_t instrument){
	if(_instruments.num==0)_instruments.array=new uint8_t[3];
	else{
		uint8_t aux[_instruments.num+3];
		copyBytes(aux, _instruments.array, 0, _instruments.num);
		delete(_instruments.array);
		_instruments.array=new uint8_t[_instruments.num+3];
		copyBytes(_instruments.array, aux, 0, _instruments.num+3);
	}
	_instruments.array[_instruments.num] = 0x00;
	_instruments.array[_instruments.num+1] = (channel & 0x0F) | 0xC0;
	_instruments.array[_instruments.num+2] = instrument;
	_instruments.num += 3;
}


/*------------------------------------------------------- 
@Add a note to a channel@
**this function only supports consecutive not simultaneous notes

Channel <byte>
Silence <byte>	: the time (expressed in musical figures) since the last note on the channel. For no silence put 0. **See the dfinitions on SMF.h
Note 	<byte>	: the note **See the definitions on  SMF.h
Fgure 	<byte>	: the duration of the note (expressed in musical figures). **See the dfinitions on SMF.h
Velocity <byte>	: the release velocity of the note **See the definitions on  SMF.h
----------------------------------------------------------*/
void SMF::addNote(uint8_t channel, uint32_t silence, uint8_t note, uint8_t figure, uint8_t velocity){
	this->noteOn(channel,((this->tempo/1000)/4)*silence,note,velocity);
	this->noteOff(channel,((this->tempo/1000)/4)*figure,note,velocity);
}


/*------------------------------------------------------- 
@Start a note@

Channel 	<byte>
DeltaTime  	<int>	: the time since the last noteOn or noteOff **in milliseconds
Note 		<byte>	: the note **See the definitions on  SMF.h
Velocity 	<byte>	: the release velocity of the note **See the definitions on  SMF.h
----------------------------------------------------------*/
void SMF::noteOn(uint8_t channel, uint32_t deltaTime, uint8_t note, uint8_t velocity){
	uint32_t delta = ( deltaTime * 1000)/(tempo/96);
	uint8_t variable[4];
	getVariableLength(variable, delta);
	uint8_t cont=0;
	uint8_t i, j=0;
	for(i=0; i < 3; i++)if(variable[i]!=0)cont++;
	cont++;
	if(_notes.num==0)_notes.array=new uint8_t[cont+3];
	else{
		uint8_t aux[_notes.num+cont+3];
		copyBytes(aux, _notes.array, 0, _notes.num);
		delete(_notes.array);
		_notes.array=new uint8_t[_notes.num+cont+3];
		copyBytes(_notes.array, aux, 0, _notes.num+cont+3);
	}

	for(i=0; i<3; i++){
		if(variable[i]!=0){
			_notes.array[_notes.num+j]=variable[i];
			j++;
		}
	}
	_notes.array[_notes.num+cont-1]=variable[3];

	_notes.array[_notes.num + cont] = (channel & 0x0F) | 0x90;
	_notes.array[_notes.num + cont+1] = note;
	_notes.array[_notes.num + cont+2] = velocity;
	_notes.num += cont+3;
}


/*------------------------------------------------------- 
@Stop a note@

Channel 	<byte>
DeltaTime  	<int>	: the time since the last noteOn or noteOff **in milliseconds
Note 		<byte>	: the note **See the definitions on  SMF.h
Velocity 	<byte>	: the release velocity of the note **See the definitions on  SMF.h
----------------------------------------------------------*/
void SMF::noteOff(uint8_t channel, uint32_t deltaTime, uint8_t note, uint8_t velocity){
	uint32_t delta = ( deltaTime * 1000)/(tempo/96);
	uint8_t variable[4];
	getVariableLength(variable, delta);
	uint8_t cont=0;
	uint8_t i, j=0;
	for(i=0; i < 3; i++)if(variable[i]!=0)cont++;
	cont++;
	if(_notes.num==0)_notes.array=new uint8_t[cont+3];
	else{
		uint8_t aux[_notes.num+cont+3];
		copyBytes(aux, _notes.array, 0, _notes.num);
		delete(_notes.array);
		_notes.array=new uint8_t[_notes.num+cont+3];
		copyBytes(_notes.array, aux, 0, _notes.num+cont+3);
	}

	for(i=0; i<3; i++){
		if(variable[i]!=0){
			_notes.array[_notes.num+j]=variable[i];
			j++;
		}
	}
	_notes.array[_notes.num+cont-1]=variable[3];

	_notes.array[_notes.num + cont] = (channel & 0x0F) | 0x80;
	_notes.array[_notes.num + cont+1] = note;
	_notes.array[_notes.num + cont+2] = velocity;
	_notes.num += cont+3;
}

/*------------------------------------------------------- 
@Return an array with the result hexcode@

hexArray->array <byte*>	: The array with the codes
hexArray->num 	<int>	: The number of elements in the array 
----------------------------------------------------------*/
hexArray SMF::getFileCode(){
	uint32_t count;
	hexArray result;
	uint8_t size[4];
	count = sizeof(_timeSignature);
	count += sizeof(_tempo);
	count += sizeof(_end);
	count += _notes.num;
	count += _instruments.num;

	getHexCode(size, count);
	this->_trackChunk[4] = size[0];
	this->_trackChunk[5] = size[1];
	this->_trackChunk[6] = size[2];
	this->_trackChunk[7] = size[3];
	
	result.array=new uint8_t[18+count];

	copyBytes(result.array, this->_headerChunk, 0, sizeof(_headerChunk));
	count = sizeof(_headerChunk);

	copyBytes(result.array, this->_trackChunk, count, sizeof(_trackChunk));
	count += sizeof(_trackChunk);

	copyBytes(result.array, this->_timeSignature, count, sizeof(_timeSignature));
	count += sizeof(_timeSignature);

	copyBytes(result.array, this->_tempo, count, sizeof(_tempo));
	count += sizeof(_tempo);

	copyBytes(result.array, this->_instruments.array, count, _instruments.num);
	count += _instruments.num;

	copyBytes(result.array, _notes.array, count, _notes.num);
	count += _notes.num;

	copyBytes(result.array, _end, count, sizeof(_end));
	count += sizeof(_end);

	result.num = count;
	return result;
}


/*-------------------------------------------------------

						@-NOT FOR USERS-@

---------------------------------------------------------*/



/*------------------------------------------------------- 
@Get the equivalent hexadecimal of a number@

Target <byte[4]>: the destination of the hexadecimal value
Value  <int>	: the number to convert
----------------------------------------------------------*/
void SMF::getHexCode(uint8_t* target, uint32_t value){
	target[0] = value/16777216;
	target[1] = (value-(target[0]*16777216))/65536;
	target[2] = (value-(target[0]*16777216 + target[1]*65536))/256;
	target[3] = (value-(target[0]*16777216 + target[1]*65536 + target[2]*256));
}


/*------------------------------------------------------- 
@Convert the value into a variable length@

Target <byte[4]>: the destination of the variable lenght value
Value  <int>	: the number to convert
----------------------------------------------------------*/
void SMF::getVariableLength(uint8_t* target, uint32_t value){	
	target[0] = 0x00;
	target[1] = 0x00;
	target[2] = 0x00;
	target[3] = 0x00;


	if(value > 0x0FFFFFFF){ 
		target[0] = 0xFF;
		target[1] = 0xFF;
		target[2] = 0xFF;
		target[3] = 0x7F;
		return;
	}
	
	if (value < 128){
		target[3] = value;
		return;
	}

	for (int i = 3; i >= 0; --i)
	{
		target[i] = value & 0x7F;
		if(i<3)target[i]|=0x80;
		value >>= 7;
		if(value < 1) break;
	}
}

/*------------------------------------------------------- 
@Copy the bytes from source to target@

Target  <byte*>	: the destination of the variable lenght value
Source  <byte*>	: the number to convert
Offset 	<int>	: the target position to start copying
numElements <int>: the number of elements(bytes) to copy
----------------------------------------------------------*/
bool SMF::copyBytes(uint8_t* target, uint8_t* source, uint32_t offset, uint32_t numElements){
	uint32_t i,j;
		for(i=offset, j=0; j < numElements; i++, j++)target[i] = source[j];
		return true;
}