const int MIN_PRESSURE = 0;
const int MAX_PRESSURE = 1023;

void creativeMode() {
  int currentPressure = analogRead(INPUT_FSR_PIN);

  int mappedValue = map(currentPressure, MIN_PRESSURE, MAX_PRESSURE, 0, 255);

  int hueValue = mappedValue;

  setColorHSV(hueValue, 255, 255);
}

void setColorHSV(int hue, int saturation, int value) {
  float h = hue / 255.0; // Convert hue to 0-1 range
  float s = saturation / 255.0; // Convert saturation to 0-1 range
  float v = value / 255.0; // Convert value to 0-1 range

  int hi = floor(h * 6);
  float f = h * 6 - hi;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (hi) {
    case 0:
      setColor(v * 255, t*255, p*255);
      break;
    case 1:
      setColor(q * 255, v*255, p*255);
      break;
    case 2:
      setColor(p * 255, v*255, t*255);
      break;
    case 3:
      setColor(p * 255, q*255, v*255);
      break;
    case 4:
      setColor(t * 255, p*255, v*255);
      break;
    default:
      setColor(v * 255, p*255, q*255);
      break;
  }
}