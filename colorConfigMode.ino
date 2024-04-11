int colors[12][3] = {
  {255, 0, 0},
  {255, 127, 0},
  {255, 255, 0},
  {127, 255, 0},
  {0, 255, 0},
  {0, 255, 127},
  {0, 255, 255},
  {0, 127, 255},
  {0, 0, 255},
  {127, 0, 255},
  {255, 0, 255},
  {255, 0, 127}}; // needed for mode 2

void colorConfigMode() {
  int potVal = analogRead(ROTARY_INPUT_PIN);
  int index = map(potVal, 0, 1023, 0, 12);
  setColor(colors[index][0], colors[index][1], colors[index][2]);
}