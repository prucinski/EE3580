
char** strings;
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

 char** splitSentence(char* sentence){
  int wordCount = 0;
  int sentenceLength = strlen(sentence);
  //calculate no of words
  for(int i = 1; i < sentenceLength; i++){
    if (sentence[i] == ' ' && sentence[i-1] != ' '){
      wordCount++;
    }
  }
  //last word has no space
  wordCount++;
  //now we have the number of words.
  Serial.println(wordCount);

  //allocate memory for main array
  strings = (char**)malloc(sizeof(char*)*(wordCount+1));
  //strings = (char**)malloc((wordCount+1));?

  //now, we'll be dynamically allocating memory for strings
  int beginning = 0;
  int endChar = 1;
  for(int i = 0; i< wordCount; i++){
    while(endChar < sentenceLength){
      if(sentence[endChar] == ' ' && sentence[endChar-1] != ' '){        
        break;
      }
      endChar++;     
    }
    Serial.println(beginning);
    Serial.println(endChar);
    int k = 0;
    strings[i] = (char*) malloc(sizeof(char)*(endChar - beginning));
    for(int j = beginning; j < endChar; j++){
      strings[i][k] = sentence[j]; 
      k++;
    }
    Serial.println(' ');
    strings[i][endChar-beginning] = '\0';
    endChar++;
    beginning = endChar;
  }
  strings[wordCount] = '\0';
  Serial.println("END OF INSIDE FUNCTION");
  return strings;
 }

bool gotString;

void setup() {
  Serial.begin(9600);
  char inputString[256];
  gotString = false;
  Serial.print("Starting execution...");

}

void loop() {
  char myString[256];
  if(!gotString){
    getstring(myString);
    gotString = true;
    splitSentence(myString);
    int i = 0;
    while(strings[i]){
      Serial.println(strings[i]);
      i++;
    }
  }

  
}
