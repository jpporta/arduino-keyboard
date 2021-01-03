//#include "HID-Project.h"

const byte ROWS = 5; // Read
const byte COLS = 8; // Write

const byte rowsPins[ROWS] = {10, 11, 12, 13, 14}; // up to down
const byte colsPins[COLS] = {2, 3, 4, 5, 6, 7, 8, 9}; // left to right

unsigned int currentRow = 0;
unsigned int currentCol = 0;

bool functionActivated = false;

bool keyboardPressed[ROWS][COLS];

const KeyboardKeycode keyboard[ROWS][COLS] = {
  {KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, NULL},
  {KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH}, 
  {KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_ENTER, NULL},
  {KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT, NULL, NULL},
  {KEY_SPACE, KEY_RIGHT_ALT, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_RIGHT_CTRL, NULL}
};

const KeyboardKeycode funcKeyboard[ROWS][COLS] = {
  {KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_BACKSPACE, NULL},
  {KEY_PRINTSCREEN, KEY_SCROLL_LOCK, KEY_PAUSE, NULL, NULL, NULL, NULL, NULL}, 
  {KEY_INSERT, KEY_HOME, KEY_PAGE_UP, NULL, NULL, NULL, NULL, NULL},
  {NULL, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, NULL, NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};


void readCurrentKey();
void nextKey();
void writeKey( int keyOn);

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < ROWS; i++){
    pinMode(rowsPins[i], INPUT);
   }
  for(int i = 0; i < COLS; i++){
    pinMode(colsPins[i], OUTPUT);
  }
  //BootKeyboard.begin();
}

void loop() {
  readCurrentKey();
  nextKey();
  delay(1);
}

void writeKey(int keyOn){
  if(keyOn){
    Serial.print(currentCol);
    Serial.println(currentRow);
  }
  return;
//  if(currentRow == 4 && currentCol == 5) {
//    functionActivated = keyOn == HIGH;
//    return;
//  }
//  if(key != 0){
//    if(keyOn && !keyboardPressed[currentRow][currentCol]){
//      //BootKeyboard.press(key);
//      keyboardPressed[currentRow][currentCol] = true;
//    } else if(!keyOn && keyboardPressed[currentRow][currentCol]){
//      //BootKeyboard.release(key);
//      keyboardPressed[currentRow][currentCol] = false;
//    }
//  }
}

void readCurrentKey(){
  const int keyOn = digitalRead(rowsPins[currentRow]);
//  KeyboardKeycode key;
// if(!functionActivated){
//    key = keyboard[currentRow][currentCol];
// } else {
//    key = funcKeyboard[currentRow][currentCol];
//  }
  writeKey(keyOn);
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
