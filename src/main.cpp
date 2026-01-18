#include <Arduino.h>
#include "pins.h"

#ifdef DEBUG
  #define DEBUG_PRINT(...)  Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTLN(...)
#endif

enum class State : uint8_t {
  STATE_START,
  STATE_INIT_PINS,
  STATE_INIT_FS,
  STATE_INIT_SERIAL,
  STATE_READY,
  STATE_ERROR
};


void initializePins() {
  pinMode(pin_led_blue, INPUT);
  pinMode(pin_led_red, OUTPUT);
  digitalWrite(pin_led_blue, LOW);
  digitalWrite(pin_led_red, LOW);
}

void initializeFilesystem() {
  // Placeholder for filesystem initialization code
}

void initializeSerial() {
  Serial.begin(115200);
  Serial.flush();
  Serial.println();
}

void setup() {
  State state = State::STATE_START;

  DEBUG_PRINTLN("Starting setup...");
  bool initialized = false;

  while(!initialized) {
    switch (state) {
      case State::STATE_START:
        state = State::STATE_INIT_PINS;
        break;
      case State::STATE_INIT_PINS:
        initializePins();

        DEBUG_PRINTLN("Pins initialized.");
        state = State::STATE_INIT_FS;
        break;
      case State::STATE_INIT_FS:
        initializeFilesystem();
        DEBUG_PRINTLN("Filesystem initialized.");
        state = State::STATE_INIT_SERIAL;
        break;
      case State::STATE_INIT_SERIAL:
        // Initialize serial communication
        initializeSerial();
        DEBUG_PRINTLN("Serial initialized.");
        initialized = true; // Exit loop after successful initialization
        state = State::STATE_READY;
        break;
      case State::STATE_ERROR:
        DEBUG_PRINTLN("Error occurred during initialization.");
        initialized = true; // Exit loop on error
        break;
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
}

