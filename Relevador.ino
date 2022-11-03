#define PIN_REL 15 //pin del relevador
#define PIN_BUTTON 33 //pin del botón

//----------
//Debouncing 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200; //tiempo de 
int button_status = 0;

void IRAM_ATTR isr_button(){  
  //millis() devuelve la cantidad de milisegundos desde que el programa inició
  if( (millis() - lastDebounceTime) > debounceDelay ){
    button_status++;
    
    if( button_status == 2) button_status = 0;
    
    lastDebounceTime = millis();
    }
    
  }
//----------


void setup() {
 Serial.begin(115200);
 //Botón
 pinMode(PIN_BUTTON, INPUT);
 pinMode(PIN_REL, OUTPUT);
 attachInterrupt(PIN_BUTTON, isr_button, RISING);
}

void loop() {
 if(button_status == 0){
  digitalWrite(PIN_REL, HIGH);
  }
  else{
    digitalWrite(PIN_REL, LOW);
    }
}
