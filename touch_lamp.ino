// Define the touch and LED pins
const int touchPin = T0; // Use touch pin T0 (GPIO 4) - change if needed
const int ledPin = 16;   // LED PWM pin (use a PWM-capable pin)

// Variables for brightness and touch detection
int brightness = 0;      // Start brightness at 0%
int touchThreshold = 40; // Adjust this threshold based on your touch sensitivity
bool touchDetected = false; // State to track if touch has been detected

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read touch sensor value
  int touchValue = touchRead(touchPin);

  // Check if the touch sensor is triggered
  if (touchValue < touchThreshold && !touchDetected) {
    // Set flag to avoid multiple triggers
    touchDetected = true;
    
    // Increase brightness by 25% with each touch
    brightness += 64; // 25% of 255 (PWM max value)
    
    // If brightness exceeds 100%, reset to 0 (LED off)
    if (brightness > 255) {
      brightness = 0;
    }
    
    // Set LED brightness
    analogWrite(ledPin, brightness);

    // Delay to debounce touch
    delay(100);
  }

  // Reset touchDetected flag once the touch is no longer detected
  if (touchValue >= touchThreshold) {
    touchDetected = false;
  }
}
