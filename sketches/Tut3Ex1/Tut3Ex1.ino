struct mystrings
{
  char str1[256];
  char str2[256];
  int len;
};
 void reverse(struct mystrings* ms);

void getstring(char* buffer)
{
   char c = 0;
   int i = 0;
   while (c != '\r')
   {
    if (Serial.available()) {
       c = Serial.read();
       buffer[i] = c;
       i++;
    }
   }
   buffer[i-1] = 0;
}

 void reverse(struct mystrings* ms){
  for(int i = 0; i < strlen(ms -> str1); i++){
    ms -> str2[ms -> len-i-1] = ms ->str1[i];
  }
  ms -> str2[ms->len] = '\0';
 }

bool gotString;

void setup() {
  Serial.begin(9600);
  char inputString[256];
  gotString = false;
  Serial.print("Starting execution...");

}

void loop() {
  mystrings myStruct;
  if(!gotString){
    getstring(myStruct.str1);
    gotString = true;
  }
  myStruct.len = strlen(myStruct.str1);
  Serial.println(myStruct.str1);
  delay(1000);

  mystrings *pointer_myStruct;
  pointer_myStruct = &myStruct;
  reverse(pointer_myStruct);
  Serial.println(myStruct.str2);
  
}
