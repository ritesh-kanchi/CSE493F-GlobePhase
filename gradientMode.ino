void gradientMode() {
  // photocell info
  int photocellVal = analogRead(PHOTOCELL_INPUT_PIN);
  int ledVal = map(photocellVal, MIN_PHOTOCELL_VAL, MAX_PHOTOCELL_VAL, 0, 255);
  ledVal = constrain(ledVal, 0, 255);
  Serial.print(photocellVal);
  Serial.print(",");
  Serial.println(ledVal);

  // rgb info
  _rgbLedValues[_curFadingUpColor] += FADE_STEP;
  _rgbLedValues[_curFadingDownColor] -= FADE_STEP;

  if(_rgbLedValues[_curFadingUpColor] > MAX_COLOR_VALUE){
    _rgbLedValues[_curFadingUpColor] = MAX_COLOR_VALUE;
    _curFadingUpColor = (RGB)((int)_curFadingUpColor + 1);

    if(_curFadingUpColor > (int)BLUE){
      _curFadingUpColor = RED;
    }
  }

  if(_rgbLedValues[_curFadingDownColor] < 0){
    _rgbLedValues[_curFadingDownColor] = 0;
    _curFadingDownColor = (RGB)((int)_curFadingDownColor + 1);

    if(_curFadingDownColor > (int)BLUE){
      _curFadingDownColor = RED;
    }
  }

  float dimmer = ledVal / 255.0;

  // Set the color and then delay
  setColor(_rgbLedValues[RED]*dimmer, _rgbLedValues[GREEN]*dimmer, _rgbLedValues[BLUE]*dimmer);
}