//---------------AI HELP----------------

const int echo = 18, trig = 8;

const int digs[4]  = {9, 10, 11, 12};      // digit select pins (LOW = digit ON)
const int digis[7] = {4, 5, 6, 7, 15, 16, 17}; // szegmens pinek (a,b,c,d,e,f,g)

const int digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

int digitValues[4] = {0,0,0,0};

unsigned long lastCountTime = 0;
const unsigned long countInterval = 100;

unsigned long lastMuxTime = 0;
const unsigned long muxInterval = 3;
int activeDigit = 0;

unsigned long lastDistTime = 0;
const unsigned long distInterval = 60; // ne mérjünk gyakrabban, mint kb. 60 ms-enként

int currentNumber = 0;

void setup(){
  for(int i = 0; i < 7; i++){
    pinMode(digis[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++){
    pinMode(digs[i], OUTPUT);
    digitalWrite(digs[i], HIGH);
  }

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);

  splitNumber(currentNumber);

  Serial.begin(9600);
}

void splitNumber(int num){
  int n = num % 10000;
  for(int i = 3; i >= 0; i--){
    digitValues[i] = n % 10;
    n /= 10;
  }
}

void showDigit(int index){
  for(int j = 0; j < 4; j++){
    digitalWrite(digs[j], HIGH);
  }

  int value = digitValues[index];

  for(int seg = 0; seg < 7; seg++){
    digitalWrite(digis[seg], digits[value][seg]);
  }

  digitalWrite(digs[index], LOW);
}

long measureDistance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 20000); // 20 ms timeout -> nem fagy be, ha nincs visszaverődés
  if(duration == 0) return -1; // nincs érvényes mérés (timeout)

  long distance = duration * 0.034 / 2;
  return distance;
}

int pre_dist = 10000;

void loop(){
  unsigned long now = millis();

  // --- Szám léptetése ---
  /*if(now - lastCountTime >= countInterval){
    lastCountTime = now;
    currentNumber++;
    if(currentNumber > 9999) currentNumber = 0;
    splitNumber(currentNumber);
  }*/
  
  

  // --- Multiplexálás ---
  if(now - lastMuxTime >= muxInterval){
    lastMuxTime = now;
    showDigit(activeDigit);
    activeDigit++;
    if(activeDigit > 3) activeDigit = 0;
  }

  // --- Távolságmérés ritkábban, nem minden loop-ban ---
  if(now - lastDistTime >= distInterval){
    lastDistTime = now;
    long distance = measureDistance();
    if(distance >= 0){
      Serial.println(distance);
      if(distance < 15 && abs(pre_dist-distance) > 10){
        currentNumber++;
        splitNumber(currentNumber);
      }
      pre_dist = distance;
    }
  }
}
