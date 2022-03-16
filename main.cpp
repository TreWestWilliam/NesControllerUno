#include <Arduino.h>
#include <FastLED.h>

int clk = 4;
int latch = 6;
int data= 8;

bool a = false;
bool b = false;
bool start = false;
bool select = false;
int pad = 0;

int red= 2;
int yellow = 3;
int green = 11;
int blue = 12;

int pos = 60;
CRGB color = CRGB(0,255,0);

#define STRIP_SIZE 120
CRGB leds [STRIP_SIZE];


void setup() {
  // put your setup code here, to run once:

  //Begin serial output
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, 7>(leds, 120);

  pinMode(data, INPUT);//Getting our data input
  pinMode(clk, OUTPUT); // Clock output
  pinMode(latch, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);

  
}

void printBin(byte inByte) 
//if you try print 00011101 you will get 1101 as the leading zeros don't print
//this prints a bin number with all the leading zeros and a space between nibbles
{
  for (int b = 7; b >= 4; b--) {
      Serial.print(bitRead(inByte, b));  
      Serial.print(" "); 
      }
  for (int b = 3; b >= 0; b--) {
      Serial.print(bitRead(inByte, b));  //now prints:  0001 1101
  }
  Serial.println(); //needs a CR at end
}

bool interpretInput(int num) 
{
  if (num == 0) {return true;};
  return false;
}

void loop() {
  // put your main code here, to run repeatedly:
  //Getting data from the 4021

  pad = 0;
  Serial.println("\nOut:");
  digitalWrite(latch, LOW);
  digitalWrite(latch,HIGH);
  int readable =  digitalRead(data);
  Serial.print(readable);
  a = interpretInput(readable);
  Serial.print(" ");
  digitalWrite(latch, LOW);
  for (int i = 1; i < 8; i++ ) 
  {
    digitalWrite(clk, HIGH);
    int readable =  digitalRead(data);
    digitalWrite(clk, LOW);
    Serial.print(readable);
    switch(i) 
    {
      case 1: b = interpretInput(readable); break;
      case 2: select = interpretInput(readable); break;
      case 3: start = interpretInput(readable); break;
      case 4: if (readable == 0) {pad = 1;} break;
      case 5: if (readable == 0) {pad = 2;} break;
      case 6: if (readable == 0) {pad = 3;} break;
      case 7: if (readable == 0) {pad = 4;} break;
    }
    delay(10);
    Serial.print(" ");
  }

  if (pad == 1) 
  {
    pos++;
  }
  else if ( pad == 2) 
  {
    pos--;
  } else if (pad == 3) 
  {
    if (color == CRGB(0,255,0)) 
    {
      color = CRGB(0,0,255);
    } 
    else if (color == CRGB(0,0,255)) 
    {color = CRGB(255,0,0);}
    else if (color == CRGB(255,0,0)) {color = CRGB(0,255,0);}
    else { CRGB::White;}
  } else if (pad == 4) 
  {
    if (color == CRGB(0,255,0)) 
    {
      color = CRGB(255,0,0);
    } 
    else if (color == CRGB(0,0,255)) 
    {color = CRGB(0,255,0);}
    else if (color == CRGB(255,0,0)) {color = CRGB(0,0,255);}
    else { CRGB::White;}
  }

  if (a) 
  {
    digitalWrite(blue,HIGH);
    Serial.print("A");
  }
  else 
  {
    digitalWrite(blue,LOW);
  }

  if (b) 
   {
    digitalWrite(green,HIGH);
  }
  else 
  {
    digitalWrite(green,LOW);
  }

  if (select) 
   {
    digitalWrite(yellow,HIGH);
  }
  else 
  {
    digitalWrite(yellow,LOW);
  }  
  if (start)
   {
    digitalWrite(red,HIGH);
  }
  else 
  {
    digitalWrite(red,LOW);
  }

  for (int i = 0; i <STRIP_SIZE; i++) 
  {
    leds[i] = CRGB::Black;
  }

  leds[pos] = color;
  FastLED.show();
  //byte incoming = shiftIn(dataIn,clockIn,LSBFIRST);

  //incoming = incoming >> 4;

  //printBin(incoming);

}

