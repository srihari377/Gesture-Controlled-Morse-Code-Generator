/*
  Gesture-Controlled Morse Code Generator
  ---------------------------------------
  REFERENCE IMPLEMENTATION

  Reconstructed from the documented project architecture.
  This is NOT the original source code.

  Hardware:
  - Arduino Uno
  - MPU6050 accelerometer/gyroscope
  - LED
  - Buzzer

  Function:
  - Short hand movement -> DOT (.)
  - Long hand movement  -> DASH (-)
  - Button/serial command -> finish the current Morse character
  - LED + buzzer -> feedback
*/

#include <Wire.h>

const int LED_PIN = 13;
const int BUZZER_PIN = 8;

// Optional push button for confirming a Morse character.
// Connect button between D2 and GND.
const int CONFIRM_PIN = 2;

const byte MPU_ADDR = 0x68;
const int16_t MOTION_THRESHOLD = 3500;
const unsigned long DOT_DASH_THRESHOLD = 350;
const unsigned long DEBOUNCE_TIME = 120;

bool movementActive = false;
unsigned long movementStart = 0;
unsigned long lastMovementTime = 0;
unsigned long lastConfirmTime = 0;

String morseCode = "";

void writeMPU(byte reg, byte data) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void readMPU(int16_t &ax, int16_t &ay, int16_t &az) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, (byte)6);

  ax = (Wire.read() << 8) | Wire.read();
  ay = (Wire.read() << 8) | Wire.read();
  az = (Wire.read() << 8) | Wire.read();
}

void feedback(unsigned int duration) {
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000);
  delay(duration);
  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN, LOW);
}

void addDot() {
  morseCode += ".";
  Serial.println("DOT -> .");
  feedback(100);
}

void addDash() {
  morseCode += "-";
  Serial.println("DASH -> -");
  feedback(250);
}

char decodeMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';
  return '?';
}

void decodeCurrentLetter() {
  if (morseCode.length() == 0) return;

  char letter = decodeMorse(morseCode);

  Serial.print("Morse: ");
  Serial.print(morseCode);
  Serial.print(" -> ");
  Serial.println(letter);

  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 1500);
  delay(120);
  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN, LOW);

  morseCode = "";
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(CONFIRM_PIN, INPUT_PULLUP);

  Wire.begin();

  // Wake MPU6050
  writeMPU(0x6B, 0x00);

  // Accelerometer ±2g
  writeMPU(0x1C, 0x00);

  Serial.println("================================");
  Serial.println("GESTURE MORSE CODE GENERATOR");
  Serial.println("================================");
  Serial.println("Short movement = DOT");
  Serial.println("Long movement  = DASH");
  Serial.println("Button press   = Decode character");
  Serial.println();
}

void loop() {
  int16_t ax, ay, az;
  readMPU(ax, ay, az);

  long motionValue = abs(ax) + abs(ay) + abs(az - 16384);
  unsigned long now = millis();

  // Detect the start of a hand movement.
  if (motionValue > MOTION_THRESHOLD &&
      !movementActive &&
      now - lastMovementTime > DEBOUNCE_TIME) {

    movementActive = true;
    movementStart = now;
    lastMovementTime = now;
  }

  // Detect the end of the movement and classify it.
  if (movementActive && motionValue < MOTION_THRESHOLD) {

    unsigned long duration = now - movementStart;

    if (duration < DOT_DASH_THRESHOLD) {
      addDot();
    } else {
      addDash();
    }

    movementActive = false;
    lastMovementTime = now;
  }

  // Confirm/decode the current Morse character.
  if (digitalRead(CONFIRM_PIN) == LOW &&
      now - lastConfirmTime > 300) {

    decodeCurrentLetter();
    lastConfirmTime = now;
  }

  delay(10);
}
