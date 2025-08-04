// Outputs
int led1 = 13; // gaasi
int led2 = 12; // vesi
int led3 = 8;  // madal temp
int led4 = 7;  // k2rg temp
int buzz = 3;  // alarmi jaoks

// Inputs
int nupp = 4;

// Analogs
int vesi = A0;
int temp = A1;
int gas = A2;

// Status variables
int a = 0; // vesi
int b = 0; // gaas
int c = 0; // temp
int alarm = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(buzz, OUTPUT);
  pinMode(nupp, INPUT);

  Serial.begin(9600);
}

void loop() {
  int nup = digitalRead(nupp);

  // Read sensor analog inputs every loop
  int vesilug = analogRead(vesi);
  int templug = analogRead(temp);
  int gaslug = analogRead(gas);

  // Update status variables with returned values
  a = waterlevel(vesilug, led2);
  b = gased(gaslug, led1)-3;
  c = temperature(templug, led3, led4);

  alarm = a + b + c;

  if (alarm <= 2) {
    switcher(nup, a, b, c);
    if (alarm >= 1) {
      buzzing(buzz);
    }
  } else {
    blingbling(led1, led2, led3, led4);
    switcher(nup, a, b, c);
    buzzing(buzz);
  }
}

int gased(int x, int y) {
  if (x > 400) {
    digitalWrite(y, HIGH);
    delay(1000);
    digitalWrite(y, LOW);
    delay(1000);
    return 1;
  } else {
    digitalWrite(y, LOW);
    return 0;
  }
}

int waterlevel(int x, int y) {
  if (x < 400 || x > 900) {
    digitalWrite(y, HIGH);
    delay(1000);
    digitalWrite(y, LOW);
    delay(1000);
    return 1;
  } else {
    digitalWrite(y, LOW);
    return 0;
  }
}

int temperature(int x, int y, int z) {
  if (x < 760) {
    digitalWrite(z, LOW);
    digitalWrite(y, HIGH);
    delay(1000);
    digitalWrite(y, LOW);
    delay(1000);
    return 1;
  } else if (x > 860) {
    digitalWrite(y, LOW);
    digitalWrite(z, HIGH);
    delay(1000);
    digitalWrite(z, LOW);
    delay(1000);
    return 1;
  } else {
    digitalWrite(y, LOW);
    digitalWrite(z, LOW);
    return 0;
  }
}

void blingbling(int x, int y, int z, int w) {
  digitalWrite(x, HIGH);
  digitalWrite(y, HIGH);
  digitalWrite(z, HIGH);
  digitalWrite(w, HIGH);
  delay(1000);
  digitalWrite(x, LOW);
  digitalWrite(y, LOW);
  digitalWrite(z, LOW);
  digitalWrite(w, LOW);
  delay(1000);
}

void buzzing(int x) {
  tone(x, 3000); // 3kHz alarm
  delay(1000);
  noTone(x);
  delay(500);
}

void switcher(int x, int y, int z, int w) {
  // This function seems a bit unclear in purpose; here's an example to toggle all alarms off/on with the button:
  if (x == HIGH) {  // If button pressed
    if (w == 1) {   // If alarms active
      // Reset all alarms
      a = 0;
      b = 0;
      c = 0;
    } else {
      // Set all alarms active
      a = 1;
      b = 1;
      c = 1;
    }
    delay(1000); // debounce delay
  }
}