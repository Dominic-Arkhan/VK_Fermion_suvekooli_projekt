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

int a = 0;
int b = 0;
int c = 0;

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


  int alarm = a + b + c;

  if (alarm < 2) {
    switcher(nup, a, b, c, alarm);
    a = gased(gaslug, led1);
    b = waterlevel(vesilug, led2);
    c = temperature(templug, led3, led4);
    Serial.println("// ?res? //");
  } else {
    Serial.print(" Error ");
    blingbling(led1, led2, led3, led4);
    switcher(nup, a, b, c, alarm);
    buzzing(buzz);
    Serial.println("// ?res? //");
  }
}

int gased(int x, int y) {
  delay(1000);
    Serial.print("G");
    Serial.print(x);
    Serial.print(" ");
  if (x > 400 || x < 300) {
    digitalWrite(y, HIGH);
    digitalWrite(y, LOW);
    return 1;
  } else {
    digitalWrite(y, LOW);
    return 0;
  }

}

int waterlevel(int x, int y) {
    Serial.print("ML");
    Serial.print(x);
    Serial.print("  ");
  if (x < 450 || x > 800) {
    digitalWrite(y, HIGH);
    buzzing(buzz);
    digitalWrite(y, LOW);
    return 1;
  } else {
    digitalWrite(y, LOW);
    return 0;
  }

}

int temperature(int x, int y, int z) {
  Serial.print("T");
    Serial.print(x);
    Serial.print(" ///// ");
  if (x < 400) {
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
}

void buzzing(int x) {
  tone(x, 3000); // 3kHz alarm
  delay(1000);
  noTone(x);
}

void switcher(int x, int &y, int &z, int &w, int sup) { //muuda alarmist mitte alarmi ja vastupidi
  Serial.print(" state of gas: ");
  Serial.print(y);
  Serial.print(" state of water: ");
  Serial.print(z);
  Serial.print(" state of temp: ");
  Serial.print(w);
  Serial.print(" ");
  if ( x == HIGH) {  
    if (sup >= 2) {   
    
      y = 0;
      z = 0;
      w = 0;
    } else {
     
      y = 1;
      z = 1;
      w = 1;
    }
  }
  delay(1000); 
}
