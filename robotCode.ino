const int line1Pin = 65;    //7.0
const int line2Pin = 48;    //7.1
const int line3Pin = 64;    //7.2
const int line4Pin = 47;    //7.3
const int line5Pin = 52;    //7.4
const int line6Pin = 68;    //7.5
const int line7Pin = 53;    //7.6
const int line8Pin = 69;    //7.7

int rightPins[] = {line8Pin,line7Pin,line6Pin,line5Pin};
int leftPins[] = {line1Pin,line2Pin,line3Pin,line4Pin};

//int i = 0;


const int leftSLPPin = 31;  //3.7
const int rightSLPPin = 11; //3.6

const int leftDIRPin = 14;  //1.7
const int rightDIRPin = 15; //1.6

const int rightPWMPin = 40;  //2.7
const int leftPWMPin = 39; //2.6


//TUNING VARIBLES
const int speed = 30; //base speed
const int ltuning = 0; //how fast the left wheel should turn
const int rtuning = 0; //how fast the right wheel should turn
const int readLeft_delay = 80; //delay between sensor write and sensor read on left set of sensors
const int readRight_delay = 80; //delay between sensor write and sensor read on right set of sensors
const int rightWheelRuntime = 2; //how long the right wheel runs before checking sensors again
const int leftWheelRuntime = 2; //how long the left wheel runs before checking sensors again

bool readRight();
bool readLeft();


void setup() {
  // put your setup code here, to run once:
  pinMode(leftSLPPin, OUTPUT);
  pinMode(rightSLPPin, OUTPUT);
  
  pinMode(leftDIRPin, OUTPUT);
  pinMode(rightDIRPin, OUTPUT);

  pinMode(leftPWMPin, OUTPUT);
  pinMode(rightPWMPin, OUTPUT);

  digitalWrite(leftDIRPin, 1);
  digitalWrite(leftSLPPin, 1);
  digitalWrite(rightDIRPin, 1);
  digitalWrite(rightSLPPin, 1);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 
  //turn left by spinning right wheel and keeping left still
  analogWrite(rightPWMPin, speed+ltuning);
  analogWrite(leftPWMPin, 0);  
  while(readRight()==0){
    delay(rightWheelRuntime);
  }
  //turn right by spinning left wheel and keeping right still
  analogWrite(rightPWMPin, 0);
  analogWrite(leftPWMPin, speed+rtuning);  
  while(readLeft()==0){
    delay(leftWheelRuntime);
  }
  
}

bool readRight(){
  for (int i=0; i<4; i++){
    pinMode(rightPins[i],OUTPUT);
    digitalWrite(rightPins[i],1);
    pinMode(rightPins[i],INPUT);
  }
//  pinMode(line8Pin,OUTPUT);
//  pinMode(line7Pin,OUTPUT);
//  pinMode(line6Pin,OUTPUT);
//  pinMode(line5Pin,OUTPUT);

//  digitalWrite(line8Pin,1);
//  digitalWrite(line7Pin,1);
//  pinMode(line8Pin,INPUT);
//  pinMode(line7Pin,INPUT);
  delay(readRight_delay);
  bool res = (digitalRead(rightPins[0])==1) || (digitalRead(rightPins[1])==1) || (digitalRead(rightPins[2])==1) || (digitalRead(rightPins[3])==1);
//  Serial.print("line8Pin:");
//  Serial.println(digitalRead(line8Pin));
//  Serial.print("line7Pin:");
//  Serial.println(digitalRead(line7Pin));
//  Serial.print("res:");
//  Serial.println(res);
//  Serial.println(res==1 ? "right sensor triggered" : "nope, still turning right");
  return res;
}

bool readLeft(){
    for (int i=0; i<4; i++){
    pinMode(leftPins[i],OUTPUT);
    digitalWrite(leftPins[i],1);
    pinMode(leftPins[i],INPUT);
  }

//  pinMode(line1Pin,OUTPUT);
//  pinMode(line2Pin,OUTPUT);

//  digitalWrite(line1Pin,1);
//  digitalWrite(line2Pin,1);

//  pinMode(line1Pin,INPUT);
//  pinMode(line2Pin,INPUT);

  delay(readLeft_delay);
  bool res = (digitalRead(leftPins[0])==1) || (digitalRead(leftPins[1])==1) || (digitalRead(leftPins[2])==1) || (digitalRead(leftPins[3])==1);
//  Serial.print("line1Pin:");
//  Serial.println(digitalRead(line1Pin));
//  Serial.print("line2Pin:");
//  Serial.println(digitalRead(line2Pin));
//  Serial.print("res:");
//  Serial.println(res);

//  Serial.println(res==1 ? "left sensor triggered" : "nope, still turning left");
  return res;
}
