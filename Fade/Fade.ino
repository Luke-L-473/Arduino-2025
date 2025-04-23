int blueled = 9;       // PWM pin for blue LED
int redled = 10;       // PWM pin for red LED

int blueBrightness = 0;     // Current brightness of blue LED
int redBrightness = 255;    // Start red LED at full brightness for staggered effect

int blueFadeAmount = 5;     // Amount to fade blue LED by
int redFadeAmount = -5;     // Fade red LED in opposite direction

void setup() {
  pinMode(blueled, OUTPUT);
  pinMode(redled, OUTPUT);
}

void loop() {
  // Update LED brightness
  analogWrite(blueled, blueBrightness);
  analogWrite(redled, redBrightness);

  // Change brightness values for next loop
  blueBrightness += blueFadeAmount;
  redBrightness += redFadeAmount;

  // Reverse fading direction at bounds for blue LED
  if (blueBrightness <= 0 || blueBrightness >= 255) {
    blueFadeAmount = -blueFadeAmount;
  }

  // Reverse fading direction at bounds for red LED
  if (redBrightness <= 0 || redBrightness >= 255) {
    redFadeAmount = -redFadeAmount;
  }

  delay(30);  // Delay to see the dimming effect
}
