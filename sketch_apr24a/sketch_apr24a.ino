#define CLK 18
#define DT  19
#define SW  21

volatile int lastState = 0;
volatile int encoderValue = 0;

void IRAM_ATTR readEncoder() {
  int MSB = digitalRead(CLK);
  int LSB = digitalRead(DT);

  int encoded = (MSB << 1) | LSB;
  int sum = (lastState << 2) | encoded;

  // правильные переходы (без шума)
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderValue++;

  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderValue--;

  lastState = encoded;
}

void setup() {
  Serial.begin(115200);

  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(CLK), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT), readEncoder, CHANGE);
}

void loop() {
  static int lastValue = 0;

  if (encoderValue != lastValue) {
    if (encoderValue > lastValue) {
      Serial.println("UP");
    } else {
      Serial.println("DOWN");
    }
    lastValue = encoderValue;
  }

  // кнопка (с антидребезгом)
  static unsigned long lastPress = 0;
  if (digitalRead(SW) == LOW && millis() - lastPress > 200) {
    Serial.println("MUTE");
    lastPress = millis();
  }
}