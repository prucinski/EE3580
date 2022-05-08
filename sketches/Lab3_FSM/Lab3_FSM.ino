int button;
int led;
int buzzer;
int thermistor;

//counting to show temperature.
int counter;

//analysing button clicks
int previousButton = 1;
int currentButton;


enum {IDLE, TEST, ALERT, ALARM, ALARM_COOL} state;
long int lastPressedTime;
int thermistorRead;
int thermistorThreshhold;
bool litUp = true;
bool firstPressed = false;

//yet again I am reusing code from previous labs, for circular arrays.
long int timestampArray[10];
bool testEventArray[10];
int currentIndex = 0;
bool isCircular = false;


void setup() {
  // put your setup code here, to run once:
  // PB1 (pin 9) - button. PB0 (pin 8) - LED. 
  //PD5 (pin 5) - BUZZER. ADC0 (A0) - thermistor.
  buzzer = 5;
  led = 8;
  button = 9;
  thermistor = A0;

  //pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  //no need for pinMode for thermistor 

  //for testing purposes
  thermistorThreshhold = 540;
  state = IDLE;
  Serial.begin(9600);

}
//record an alarm event.
void sendLog(bool type){
  if(currentIndex ==10){
      currentIndex=0;
      //if is circular, we have to keep that in mind when we're printing.
      isCircular = true;
    }
  timestampArray[currentIndex] = millis();
  testEventArray[currentIndex] = type;
  currentIndex+=1;
}

//check if a button was pressed.
boolean buttonPressed(){
  currentButton = digitalRead(button);
  //transition on falling edge
  if(currentButton - previousButton < 0){
    previousButton = currentButton;
    return true;
  }
  previousButton = currentButton;
  return false;  
}

//print the last 10 events.
void printLog(){
  if(isCircular){
    for(int i =0; i < 10; i++){
      currentIndex+=1;
      Serial.print(timestampArray[currentIndex-1]);
      Serial.print(":  ");
      if(testEventArray[currentIndex -1]){
        Serial.print("ALARM");
      }
      else{
        Serial.print("TEST");
      }
      Serial.print(" | ");

      if(currentIndex == 10){
        currentIndex = 0;
      }
      }
      Serial.println("");
    }
    //Array is not circular. Print as usual.
    else{
      for(int i =0; i < currentIndex; i++){
        Serial.print(timestampArray[i]);
        Serial.print(":  ");
        if(testEventArray[i]){
          Serial.print("ALARM");
        }
        else{
          Serial.print("TEST");
        }
        Serial.print(" | ");
      }
      Serial.println("");   
    }
}

void update_fsa(){
  //check state every 500ms. Needs button to be held up to 500ms.
  delay(500);
  thermistorRead = analogRead(thermistor);

  if(counter%10 == 0){
    //Serial.println(thermistorRead);
    Serial.print("Current temperature is: ");
    long int thermistorVal = 1024000/thermistorRead -1000;
    int temp = -1*thermistorVal/40 + 50;
    Serial.println(temp);
  }
  counter+=1;
  
  switch(state){
    case IDLE:
      digitalWrite(led, HIGH);
      noTone(buzzer);
      if(thermistorRead > thermistorThreshhold){
        state = ALERT;
      }
      else if(buttonPressed()){
        state = TEST;
      }
      break;
      
    case TEST:
      //run this only on entering the state.
      if(!firstPressed){
        firstPressed = !firstPressed;
        //For test purposes, we treat it as an "ALARM" event
        Serial.println("Sending TEST log");
        sendLog(false);
        printLog();
        lastPressedTime = millis();
      }
      digitalWrite(led, HIGH);
      tone(buzzer, 100);
      //10 seconds
      if(millis() - lastPressedTime > 10000){
        state = IDLE;
        //reset firstPressed variable.
        firstPressed = !firstPressed;
      }
      break;
      
    case ALERT:
      if(!firstPressed){
        firstPressed = !firstPressed;
        //record every ALERT event.
        Serial.println("Sending ALERT log");
        sendLog(true);
        lastPressedTime = millis();
      }
      digitalWrite(led, HIGH);
      if(thermistorRead < thermistorThreshhold){
        state = IDLE;
        firstPressed = !firstPressed;
      }
      //2 seconds before alert
      else if(millis() - lastPressedTime > 2000){
        state = ALARM;
        firstPressed = !firstPressed;
      }
    
      break;
    //alternate.  
    
    case ALARM:
      litUp = !litUp;
      if(!firstPressed){
        firstPressed = !firstPressed;
        lastPressedTime = millis();
      }
      digitalWrite(led, litUp);
      //arbitrary values. 
      if(litUp){
        tone(buzzer, 200);
      }
      else{
        tone(buzzer, 100);
      }
      if(buttonPressed()){
        state = IDLE;
        firstPressed = !firstPressed;
      }
      //10 minutes
      if(millis() - lastPressedTime > 600000){
        state = ALARM_COOL;
        firstPressed = !firstPressed;
      }
      break;
      
    case ALARM_COOL:
      litUp = !litUp;
      digitalWrite(led, litUp);
      noTone(buzzer);
      if(buttonPressed()){
        state = IDLE;
      }
      break;
      
  }
}

void loop() {
  update_fsa();
}
