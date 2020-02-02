#include "SMF.h"

//The example shows the way to obtain the MIDI code of "Twinkle twinkle little star" song

compass adios = {4,4}; //Compass 4/4

SMF twinkle(adios,60); //Create an SMF object to make the operations

hexArray code; //Create an hexArray for save the result MIDI code

void setup() {
	Serial.begin(9600);

  	twinkle.setInstrument(0,grandPiano); //Set the channel 0 as a piano

//---------Set the notes that compose the song---------------
  	twinkle.addNote(0,0,C4,quarter,standard);
  	twinkle.addNote(0,0,C4,quarter,standard);

  	twinkle.addNote(0,0,G4,quarter,standard);
  	twinkle.addNote(0,0,G4,quarter,standard);

  	twinkle.addNote(0,0,A4,quarter,standard);
  	twinkle.addNote(0,0,A4,quarter,standard);

  	twinkle.addNote(0,0,G4,half,standard);

  	twinkle.addNote(0,0,F4,quarter,standard);
  	twinkle.addNote(0,0,F4,quarter,standard);

  	twinkle.addNote(0,0,E4,quarter,standard);
  	twinkle.addNote(0,0,E4,quarter,standard);

  	twinkle.addNote(0,0,D4,quarter,standard);
  	twinkle.addNote(0,0,D4,quarter,standard);

  	twinkle.addNote(0,0,C4,half,standard);
//-----------------------------------------------------

  	code = twinkle.getFileCode(); //Get the MIDI code

  	for(int i=0; i< code.num; i++){
  	    Serial.println(code.array[i],HEX);
  	}
}

void loop() {
  // put your main code here, to run repeatedly:
}