#include "MIDIUSB.h"

int noteDelta = 0;
int timeDivision = 16;
int mainNote = 60;
int mainVelocity = 70;
int mainTempo = 350;
int mainChannel = 0;

const int minorPentatonicScale[] = {-12, -9, -8, -5, -2, 0, 3, 4, 7, 10, 12};
const int majorPentatonicScale[] = {-12, -10, -8, -5, -3, 0, 2, 4, 7, 9, 12};
const int EgyptianPentatonicScale[] = {-12, -10, -7, -5, -2, 0, 2, 5, 7, 10, 12};
const int bluesMinorPentatonicScale[] = {-12, -9, -7, -4, -2, 0, 3, 5, 8, 10, 12};
const int bluesMajorPentatonicScale[] = {-12, -10, -7, -5, -3, 0, 2, 5, 7, 9, 12};
int scaleType = 0;
int numberOfScaleTypes = 6;

const int majorTriadChord[] = {0, 4, 7};
const int majorSixthChord[] = {0, 4, 7, 9};
const int dominantSeventhChord[] = {0, 4, 7, 10};
const int majorSeventhChord[] = {0, 4, 7, 11};
const int augmentedTriad[] = {0, 4, 8};
const int augmentedSeventhChord[] = {0, 4, 8, 10};
const int minorTriad[] = {0, 3, 7};
const int minorSixthChord[] = {0, 3, 7, 9};
const int minorSeventhChord[] = {0, 3, 7, 10};
const int minorMajorSeventhChord[] = {0, 3, 7, 11};
const int diminishedTriadChord[] = {0, 3, 6};
const int diminishedSeventhChord[] = {0, 3, 6, 9};
const int halfDiminishedSeventhChord[] = {0, 3, 6, 10};
int chordType = 0;
int numberOfChordTypes = 13;

int upperThreshold = 90;
int lowerThreshold = 20;
long nextNoteIteration = 0;


void setup() {
  // Seed the random() function with a value from analog
  // input 4.
  randomSeed(analogRead(4));
  
  // Send an "all notes off" command to each channel.
//  for (int i = 0; i < 16; i++){
//    MidiUSB.sendMIDI((0xB0 + i), 0x78, 0x00);
//  }
}

void loop() {
  if (millis() >= nextNoteIteration){
    // Stop the last note
    noteOff(mainChannel, mainNote, mainVelocity);
    // Generate the next note.
    noteDelta = random(0, 12);
    // Check to see that the note will be within the prescribed range.
    noteDelta = maintainNoteLimits(mainNote, noteDelta, scaleType, numberOfScaleTypes, lowerThreshold, upperThreshold);
    // Change the mainNote variable according to the selected scale.
    mainNote = mainNote + (calculateScale(noteDelta, scaleType, numberOfScaleTypes));
    // Play the note, wait, then go back to the beginning of the loop()
    noteOn(mainChannel, mainNote, mainVelocity);
    Serial.print("Note:\t");
    Serial.print(mainChannel);
    Serial.print("\t");
    Serial.print(mainNote);
    Serial.print("\t");
    Serial.print(mainVelocity);
    Serial.print("\n");
    nextNoteIteration = millis() + (mainTempo - mainNote);
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
