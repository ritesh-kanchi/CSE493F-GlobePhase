// input pins
const int MODE_SWITCH_BUTTON_INPUT_PIN = 8; // digital input - mode switcher
const int PHOTOCELL_INPUT_PIN = A0; // analog input - photo cell
const int ROTARY_INPUT_PIN = A5; // analog lo-fi input - potentiometer
const int INPUT_FSR_PIN = A2;

// output pins
const int RGB_RED_PIN = 9;
const int RGB_GREEN_PIN = 10;
const int RGB_BLUE_PIN = 11;

// global vars
int mode = 0; // 0 ~ mode 1, 1 ~ mode 2, 2 ~ mode 3

int modeSwitchVal = 1;
int lastModeSwitchVal = 1;

// photocell vars
const int MIN_PHOTOCELL_VAL = 200; 
const int MAX_PHOTOCELL_VAL = 800; 
const boolean PHOTOCELL_IS_R2_IN_VOLTAGE_DIVIDER = true; 

// rgb vars
enum RGB{
  RED,
  GREEN,
  BLUE,
  NUM_COLORS
};
const int MAX_COLOR_VALUE = 255;
int _rgbLedValues[] = {MAX_COLOR_VALUE, 0, 0}; // Red, Green, Blue
enum RGB _curFadingUpColor = GREEN;
enum RGB _curFadingDownColor = RED;
const int FADE_STEP = 5;  

void setup() {
  // input pin setup
  pinMode(MODE_SWITCH_BUTTON_INPUT_PIN, INPUT_PULLUP);
  pinMode(PHOTOCELL_INPUT_PIN, INPUT);
  pinMode(ROTARY_INPUT_PIN, INPUT_PULLUP);
  pinMode(INPUT_FSR_PIN, INPUT);

  // output pin setup
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);

  Serial.begin(9600);

  setColor(_rgbLedValues[RED], _rgbLedValues[GREEN], _rgbLedValues[BLUE]);
}

void loop() {

  // mode control
  modeSwitchVal = digitalRead(MODE_SWITCH_BUTTON_INPUT_PIN);

  // mode switch
  if(modeSwitchVal == 0 && lastModeSwitchVal == 1) {
    Serial.print("Moving from mode ");
    Serial.print(mode);
    mode = (mode + 1) % 3;
    Serial.print(" to mode ");
    Serial.println(mode);
  }

  lastModeSwitchVal = modeSwitchVal;

  if(mode == 0) {
    // mode 1: crossfading RGB LED with brightness inversely proportional to the light level
    Serial.println("In Mode 1");
    gradientMode();
  } else if (mode == 1) {
    // mode 2: configuring color with lo-fi input
    Serial.println("In Mode 2");
    colorConfigMode();
  } else {
    // mode 3: creative feature
    Serial.println("In Mode 3");
    creativeMode();
  }

  delay(100);
}