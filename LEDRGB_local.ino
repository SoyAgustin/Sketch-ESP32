#define LED_R 14
#define LED_G 27
#define LED_B 12
#define PIN_BUTTON 33

int led_status = 0; //cual es el color en el que vamos a encender el led

//Debouncing (evitar el rebote del botón)
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200; //tiempo entre que se puede detectar la presión del botón

void IRAM_ATTR isr_button(){
  //millis() devuelve la cantidad de milisegundos desde que el programa inició
  //1s=1000ms
  if( (millis() - lastDebounceTime) > debounceDelay ){
    led_status++;
    if( led_status >=8) led_status = 0;
    //se puede usar el operador ternario (?:) led_status = (led_status >=7) ? 0 : led_status+1;
    lastDebounceTime = millis();
    }
  }
  
void setup() {
  //botón
  pinMode(PIN_BUTTON, INPUT);
  attachInterrupt(PIN_BUTTON, isr_button, RISING);

  //Led
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  //casos según el número de veces que presionamos el botón
  switch(led_status){
    case 1://Rojo
      digitalWrite(LED_R, LOW); //enciende rojo
      digitalWrite(LED_G, HIGH); //apaga verde
      digitalWrite(LED_B, HIGH); //apaga azul
    break;
    
    case 2://Verde
      digitalWrite(LED_R, HIGH); //apaga rojo
      digitalWrite(LED_G, LOW); //enciende verde
      digitalWrite(LED_B, HIGH); //apaga azul
    break;

    case 3://Azul
      digitalWrite(LED_R, HIGH); //apaga rojo
      digitalWrite(LED_G, HIGH); //apaga verde
      digitalWrite(LED_B, LOW); //enciende azul
    break;

    case 4://Cyan
      digitalWrite(LED_R, HIGH); //apaga rojo
      digitalWrite(LED_G, LOW); //enciende verde
      digitalWrite(LED_B, LOW); //enciende azul
    break;

    case 5://Amarillo
      digitalWrite(LED_R, LOW); //enciende rojo
      digitalWrite(LED_G, LOW); //enciende verde
      digitalWrite(LED_B, HIGH); //apaga azul
    break;

    case 6://Magenta
      digitalWrite(LED_R, LOW); //enciende rojo
      digitalWrite(LED_G, HIGH); //apaga verde
      digitalWrite(LED_B, LOW); //enciende azul
    break;

    case 7://Blanco
      digitalWrite(LED_R, LOW); //enciende rojo
      digitalWrite(LED_G, LOW); //enciende verde
      digitalWrite(LED_B, LOW); //enciende azul
    break;

    default://apagado
      digitalWrite(LED_R, HIGH); //apaga rojo
      digitalWrite(LED_G, HIGH); //apaga verde
      digitalWrite(LED_B, HIGH); //apaga azul
    break;
    }

}
