const int motorPin = 8;
const int buttonPin = 2;
const int limitPin = 3;

const int dpPin = 4;
const int aPin = 11;
const int bPin = 12;
const int cPin = 5;
const int dPin = 6;
const int ePin = 7;
const int fPin = 10;
const int gPin = 9;

const int DEBOUNCE_DELAY = 200;
const int MOTOR_DELAY = 1000;

int now;
int motorState, lastMotorPressed, isMotorPressed;
int limitState, lastLimitPressed, isLimitPressed;
int stockAmount;

void clearDisplay() {
  digitalWrite(dpPin, HIGH);
  digitalWrite(aPin, LOW);
  digitalWrite(bPin, LOW);
  digitalWrite(cPin, LOW);
  digitalWrite(dPin, LOW);
  digitalWrite(ePin, LOW);
  digitalWrite(fPin, LOW);
  digitalWrite(gPin, LOW);
}

void display1() {
  clearDisplay();
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
}

void display2() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(dPin, HIGH);
}

void display3() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
}

void display4() {
  clearDisplay();
  digitalWrite(fPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(cPin, HIGH);
}

void display5() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
}

void display6() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, HIGH);
}

void display7() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
}

void display8() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
}

void display9() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(fPin, HIGH);
  digitalWrite(gPin, HIGH);
}

void display0() {
  clearDisplay();
  digitalWrite(aPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(cPin, HIGH);
  digitalWrite(dPin, HIGH);
  digitalWrite(ePin, HIGH);
  digitalWrite(fPin, HIGH);
}

void displayN(int n) {
  // Serial.print("Printing: ");
  // Serial.println(n);
  switch(n){
    case 0:
      display0();
      break;
    case 1:
      display1();
      break;
    case 2:
      display2();
      break;
    case 3:
      display3();
      break;
    case 4:
      display4();
      break;
    case 5:
      display5();
      break;
    case 6:
      display6();
      break;
    case 7:
      display7();
      break;
    case 8:
      display8();
      break;
    case 9:
      display9();
      break;
  }
}

void setup() {
  pinMode(motorPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(limitPin, INPUT_PULLUP);

  pinMode(dpPin, INPUT);
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(cPin, INPUT);
  pinMode(dPin, INPUT);
  pinMode(ePin, INPUT);
  pinMode(fPin, INPUT);
  pinMode(gPin, INPUT);
  Serial.begin(9600);

  analogWrite(motorPin, 255);
  digitalWrite(motorPin, LOW);

  lastLimitPressed = millis();
  isLimitPressed = false;
  stockAmount = 0;
}

void loop() {
  now = millis();
  if (now - lastLimitPressed > DEBOUNCE_DELAY) {
    limitState = digitalRead(limitPin);

    if(limitState == HIGH) {
      if (!isLimitPressed && stockAmount < 9) {
        isLimitPressed = true;
        stockAmount += 1;
        lastLimitPressed = now;
      }
    } else {
      if (isLimitPressed) {
        isLimitPressed = false;
        lastLimitPressed = now;
      }
    }
  }

  if (now - lastMotorPressed > MOTOR_DELAY) {
    motorState = digitalRead(buttonPin);
    if (motorState == LOW) {
      if (!isMotorPressed && stockAmount > 0) {
        digitalWrite(motorPin, HIGH);
        
        isMotorPressed = true;
        lastMotorPressed = now;
      }
    } else {
      if (isMotorPressed) {
        digitalWrite(motorPin, LOW);
        isMotorPressed = false;
        lastMotorPressed = now;
      }
    }
  }
  displayN(stockAmount);

}
