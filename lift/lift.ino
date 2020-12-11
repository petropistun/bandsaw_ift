
/////////// Copyright © 2008 DesuraNET. All rights reserved. /////////////

  Project     : Bandsaw Lift
  Description :
     automatic lift for bandsaw

  Created On: 11/12/2020
  Created By: Petro Pistun <mailto:petropistun@gmail.com>
//////////////////////////////////////////////////////////////////////////


#define sleep delay
#define pinLeft  2 
#define pinRight 3

#define OPTO 6

#define LEFT_RIGHT_BUTTON 4


int buttonState = 0, opto_state = 0, opto_state2 = 0, opto_delay = 0;
int delay_Pin = A5; 
bool action = false;

void stopRun();

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(9600);
  
  pinMode(pinLeft, OUTPUT);
  pinMode(pinRight , OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(OPTO, INPUT);
  digitalWrite(OPTO, HIGH);
  pinMode(LEFT_RIGHT_BUTTON, INPUT);
  
  sleep(300);

  stopRun();
  pinMode(LED_BUILTIN, HIGH);

  Serial.println("started");
  Serial.println(LED_BUILTIN);
  
}

void stopRun()
{
  digitalWrite(pinLeft, LOW);
  digitalWrite(pinRight, LOW);
}

void LeftRun()
{
  digitalWrite(pinLeft, HIGH);
  digitalWrite(pinRight, LOW);
}

void RightRun()
{
  digitalWrite(pinLeft, LOW);
  digitalWrite(pinRight, HIGH);
}

// the loop function runs over and over again forever
void loop() {

  //read opto
  opto_state = digitalRead(OPTO);


  //read button
  action = false;
  pinMode(LEFT_RIGHT_BUTTON, HIGH);
  sleep(10);
  buttonState = digitalRead(LEFT_RIGHT_BUTTON);
  
  if (buttonState == 1){
      LeftRun();
      action = true;
      Serial.println("left");
  }

  pinMode(LEFT_RIGHT_BUTTON, LOW);
  sleep(10);
  buttonState = digitalRead(LEFT_RIGHT_BUTTON);

  if (buttonState == 0){
      RightRun();
      action = true;
      Serial.println("Right");
  }

  if (! action )
  {
    stopRun();
    
  }
  //////////////


  //read opto
  opto_delay = 510/*reverse*/ - analogRead(delay_Pin) / 2 + 30;
  sleep(20);
  opto_state2 = digitalRead(OPTO);

  if (opto_state == 0 && opto_state2 == 1)
  {
    
    LeftRun();
    sleep(opto_delay);
    stopRun();
    opto_state = 1;
    opto_state2 = 0;
  }
  
}
