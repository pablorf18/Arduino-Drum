#include <MIDI.h> 
MIDI_CREATE_DEFAULT_INSTANCE();

//analog inputs
const int Pad1 = A0;
const int Pad2 = A1;
const int Pad3 = A2;
const int Pad4 = A3;
const int Pad5 = A4;
const int Pad6 = A5;
const int Pad7 = A6;
const int Pad8 = A7;

//digital input
const int hitHat = 8;

//volume threshold variable, being used to determine
//if user stikes the drum pad
const int volumeThreshold = 150;

//variables for volume magnitude of each drum pad
int Drum1_val = 0;
int Drum2_val = 0;
int Drum3_val = 0;
int Drum4_val = 0;
int Drum5_val = 0;
int Drum6_val = 0;
int Drum7_val = 0;
int Drum8_val = 0;

int signalTest5 = 0;

//midi mapping - addictive drums mapping
byte snareDrum = 38;
byte kick = 36; 
byte hihatClosed = 48;
byte crash = 77;
byte hihatOpened = 55;
byte lowTom = 68;
byte highTom = 72;
byte ride = 60;
byte crash2 = 79;

float transform = 127.0/1023.0;

void setup()
{
  MIDI.begin(4);
  //starts serial communication between arduino na serial USB port
  Serial.begin(115200); 
  pinMode(hitHat, INPUT);
}

void loop()
{ 
  /*1st pad*/
  //checks if magnitude of analoginput is higher than volumeThreshold
  Drum1_val= analogRead(Pad1);
  if(Drum1_val >= volumeThreshold-70) 
  {
    //sets the velocity
    int velocity = Drum1_val * transform;
    if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;

    //sends midi signal over USB serial port
    MIDI.sendNoteOn(highTom, velocity, 1);
    MIDI.sendNoteOff(highTom, 0, 1);
  }

  /*2nd pad*/
  Drum2_val = analogRead(Pad2);
  if(Drum2_val >= volumeThreshold-50) 
  { 
   int velocity = (transform * Drum2_val);
      
   if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;  
      
    MIDI.sendNoteOn(snareDrum, velocity, 1);
    MIDI.sendNoteOff(snareDrum, 0, 1);
  }

  /*3rd pad*/
  Drum3_val = analogRead(Pad3);
  if(analogRead(Pad3) >= volumeThreshold-50) 
  {
   
   int hitHatValue = 0;
   int velocity = Drum3_val * transform;
   
   if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;

    hitHatValue = digitalRead(hitHat);  // read input value
    if (hitHatValue == HIGH) 
    {
      MIDI.sendNoteOn(hihatOpened, velocity, 1);
      MIDI.sendNoteOff(hihatOpened, 0, 1);
      //Serial.print("open");
    } 
    else 
    {
      MIDI.sendNoteOn(hihatClosed, velocity, 1);
      MIDI.sendNoteOff(hihatClosed, 0, 1);
      //Serial.print("closed");
    }
  }

  /*4th pad*/
  Drum4_val= analogRead(Pad4);
  if(analogRead(Pad4) >= 500) 
  {
   
   int velocity = Drum4_val * transform;
   
   if(velocity > 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;  
      
    MIDI.sendNoteOn(crash, velocity, 1);
    MIDI.sendNoteOff(crash, 0, 1);
  }

  /*5th pad*/
  Drum5_val = analogRead(Pad5);
  if(analogRead(Pad5) >= 250) 
  {
   int velocity = Drum5_val * transform; 
   
   if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;   
       
    MIDI.sendNoteOn(kick, velocity, 1);
    MIDI.sendNoteOff(kick, 0, 1);
  }

    /*6th pad*/
  Drum6_val = analogRead(Pad6);
  if(analogRead(Pad6) >= volumeThreshold-70) 
  {
 
   int velocity = Drum6_val * transform; 
   if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;   
       
    MIDI.sendNoteOn(lowTom, velocity, 1);
    MIDI.sendNoteOff(lowTom, 0, 1);
  }

  /*7th pad*/
  Drum7_val = analogRead(Pad7);
  if(analogRead(Pad7) >= volumeThreshold-70) 
  {
 
   int velocity = Drum7_val * transform; 
   if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;   
       
    MIDI.sendNoteOn(ride, velocity, 1);
    MIDI.sendNoteOff(ride, 0, 1);
  }

    /*8th pad*/
  Drum8_val= analogRead(Pad8);
  if(analogRead(Pad8) >= 500) 
  {
   
   int velocity = Drum8_val * transform;
   
   if(velocity > 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;  
      
    MIDI.sendNoteOn(crash2, velocity, 1);
    MIDI.sendNoteOff(crash2, 0, 1);
  }
}
