#include <TaskScheduler.h>

/* Initial scratch for a 3 digit, 7 segment LED display driver */

const int anode1 = 6;
const int anode2 = 2;
const int anode3 = 3;
const int anode4 = 4;
const int anode5 = 5;
const int anode7 = 7;
const int anode10 = 10;
const int anode11 = 11;

const int E = 6;
const int D = 2;
const int DP = 3;
const int C = 4;
const int G = 5;
const int B = 7;
const int F = 10;
const int A = 11;

const int cathode8 = 8;
const int cathode9 = 9;
const int cathode12 = 12;

const int firstDigit = cathode12;
const int secondDigit = cathode9;
const int thirdDigit = cathode8;

long lastDPstateChangeMillis = 0;

/* Used to determine if the DPs should be on or off
   depending on state of the "beat cycle" */
bool isDPtoBeLit = true;

/* tempo in beats per minute */
byte tempo = 120;

/* prototype of method calls to be scheduled */
void updateFirstDigit();
void updateSecondDigit();
void updateThirdDigit();
void updateDPstate();

Scheduler scheduler;
Task updateFirst(1, TASK_FOREVER, &updateFirstDigit);
Task updateSecond(1, TASK_FOREVER, &updateSecondDigit);
Task updateThird(1, TASK_FOREVER, &updateThirdDigit);
Task updateDP(1, TASK_FOREVER, &updateDPstate);

void setup() {
  /* Set mode of anode and cathode pins */
  pinMode(anode1, OUTPUT);
  pinMode(anode2, OUTPUT);
  pinMode(anode3, OUTPUT);
  pinMode(anode4, OUTPUT);
  pinMode(anode5, OUTPUT);
  pinMode(anode7, OUTPUT);
  pinMode(anode10, OUTPUT);
  pinMode(anode11, OUTPUT);

  pinMode(cathode8, OUTPUT);
  pinMode(cathode9, OUTPUT);
  pinMode(cathode12, OUTPUT);

  resetAnodesCathodes();

  /* Insert display demo at for upstart */
  /* e.g. HEJ ... |_ |_ |_ ... _| _| _| ... */

  scheduler.init();
  scheduler.addTask(updateFirst);
  scheduler.addTask(updateSecond);
  scheduler.addTask(updateThird);
  scheduler.addTask(updateDP);

  updateFirst.enable();
  updateSecond.enable();
  updateThird.enable();
  updateDP.enable();
}

void resetAnodesCathodes() {
/* Initiate state of cathode pins so no current passes through*/
  digitalWrite(cathode8, HIGH);
  digitalWrite(cathode9, HIGH);
  digitalWrite(cathode12, HIGH);

  digitalWrite(anode1, LOW);
  digitalWrite(anode2, LOW);
  digitalWrite(anode3, LOW);
  digitalWrite(anode4, LOW);
  digitalWrite(anode5, LOW);
  digitalWrite(anode7, LOW);
  digitalWrite(anode10, LOW);
  digitalWrite(anode11, LOW);  
}

void loop() {
  scheduler.execute();
}

void updateFirstDigit() {
  int firstNumber = tempo % 1000 / 100;
  setNumber(firstNumber, firstDigit);
}

void updateSecondDigit() {
  int secondNumber = tempo % 100 / 10;
  setNumber(secondNumber, secondDigit);
}
void updateThirdDigit() {
  int thirdNumber = tempo % 10;
  setNumber(thirdNumber, thirdDigit);
}

void updateDPstate() {
  if (millis() - lastDPstateChangeMillis >= tempoToFrequencyInMillis(tempo)) {
    isDPtoBeLit = !isDPtoBeLit;
    lastDPstateChangeMillis = millis();
  }
}

void setNumber(int numberToDisplay, int ordinalNumberOfDigit) {

    resetAnodesCathodes();
    
    switch(numberToDisplay) {
      case 1:
        //Serial.print("Woohaaa!");
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;
      case 2:
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(G,HIGH);
        digitalWrite(E,HIGH);
        digitalWrite(D,HIGH);
        break;
      case 3:
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(D,HIGH);
        digitalWrite(G,HIGH);
        break;
      case 4:
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;
      case 5:
        digitalWrite(A,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(D,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;
      case 6:
        digitalWrite(A,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(D,HIGH);
        digitalWrite(E,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;
      case 7:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;
      case 8:
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(D,HIGH);
        digitalWrite(E,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;
      case 9:
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(D,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;
      case 0:
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(D,HIGH);
        digitalWrite(E,HIGH);
        digitalWrite(F,HIGH);
        break;
    }

    if (isDPtoBeLit) {
        digitalWrite(DP,HIGH);
      }

    digitalWrite(ordinalNumberOfDigit, LOW);
}

int tempoToFrequencyInMillis(int bpm) {
    /* 60 seconds in millis, divided by the tempo in BPM, divided by two
    gives the on/off time interval for tempo indicator */
    return 60000/bpm/2;
  }
