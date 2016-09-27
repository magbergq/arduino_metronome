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

const int firstDigit = 12;
const int secondDigit = 9;
const int thirdDigit = 8;

/* prototype of method calls to be scheduled */
void setNumber(int numberToDisplay, int ordinalNumberOfDigit);

Scheduler scheduler;
Task updateFirstDigit();
Task updateSecondDigit();
Task updateThirdDigit();

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

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

  //Serial.begin(9600);  
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
    
    int test = 995;
    int thirdNumber = test % 10;
    int secondNumber = test % 100 / 10;
    int firstNumber = test % 1000 / 100;

    setNumber(firstNumber, firstDigit);
    delayMicroseconds(250);
    setNumber(secondNumber, secondDigit);
    delayMicroseconds(250);
    setNumber(thirdNumber, thirdDigit);
    delayMicroseconds(250);
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

    digitalWrite(ordinalNumberOfDigit, LOW);
}

