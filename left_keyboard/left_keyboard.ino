#include <Encoder.h>
#include "HID-Project.h"

const byte ROWS = 5; // Read
const byte COLS = 7; // Write

const byte rowsPins[ROWS] = {15, 14, 16, 10, 9}; // up to down
const byte colsPins[COLS] = {2, 7, 8, 5, 6, 3, 4}; // left to right

unsigned int currentRow = 0;
unsigned int currentCol = 0;

bool functionActivated = false;

long currentRotary = -999;
Encoder rotary(A0, A1);

bool keyboardPressed[ROWS][COLS];

const KeyboardKeycode keyboard[ROWS][COLS] = {
  {KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6},
  {NULL, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T}, 
  {NULL, KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G},
  {NULL, KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B},
  {NULL, NULL, KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, NULL, KEY_SPACE }
};

const KeyboardKeycode funcKeyboard[ROWS][COLS] = {
  {KEY_TILDE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6},
  {NULL, KEY_TAB, NULL , NULL, NULL, NULL, NULL},
  {NULL, KEY_CAPS_LOCK, NULL, NULL, NULL, NULL, NULL}, 
  {NULL, KEY_LEFT_SHIFT, NULL, NULL, NULL, NULL, NULL},
  {NULL, KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_F24, NULL, NULL}
};


void readCurrentKey();
void nextKey();
void rotaryRead();

void setup() {
  for(int i = 0; i < ROWS; i++){
    pinMode(rowsPins[i], INPUT);
   }
  for(int i = 0; i < COLS; i++){
    pinMode(colsPins[i], OUTPUT);
  }
  BootKeyboard.begin();
  Consumer.begin();
}

void loop() {
  readCurrentKey();
  nextKey();
  rotaryRead();
  delay(1);
}

void rotaryRead(){
  long newRotary;
  newRotary = rotary.read() / 4;
  if(currentRotary == -999) currentRotary = newRotary;
  if(newRotary != currentRotary){
    if(newRotary > currentRotary){
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    currentRotary = newRotary;
  }
}


void writeKey(KeyboardKeycode key, int keyOn){
  if(currentRow == 4 && currentCol == 5) {
    functionActivated = keyOn == HIGH;
    return;
  }
  if(key != 0){
    if(keyOn && !keyboardPressed[currentRow][currentCol]){
      BootKeyboard.press(key);
      keyboardPressed[currentRow][currentCol] = true;
    } else if(!keyOn && keyboardPressed[currentRow][currentCol]){
      BootKeyboard.release(key);
      keyboardPressed[currentRow][currentCol] = false;
    }
  }
}

void readCurrentKey(){
  const int keyOn = digitalRead(rowsPins[currentRow]);
  KeyboardKeycode key;
 if(!functionActivated){
    key = keyboard[currentRow][currentCol];
 } else {
    key = funcKeyboard[currentRow][currentCol];
  }
  writeKey(key, keyOn);
}

void nextKey(){
  currentRow++;
  if(currentRow == ROWS){
    currentRow = 0;
    digitalWrite(colsPins[currentCol], LOW);
    delayMicroseconds(5);
    currentCol++;
    if(currentCol == COLS){
      currentCol = 0;
    }
    digitalWrite(colsPins[currentCol], HIGH);
  }
}
