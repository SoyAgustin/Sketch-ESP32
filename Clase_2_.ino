//Declaramos los pines en donde van a estar el LDR y el transistor
//podemos usar tambien macros para definir variables
//#define pin_LDR 34 (sin punto y coma)

const int pin_LDR=34;
#define PIN_LM35 35

void setup() {
  Serial.begin(9600); //algo como bits por segundo, son 9600 baudios
  //el ESP32 funciona por defecto en 115200
}

void loop() {

  //LDR:
  
  //int m= analogRead(pin_LDR); //lee la informacion del pin de la fotoresistencia y la guardamos en m.
  //Serial.println(m);//lo imprime en la pantalla
  //delay(100);
  
////////////////////////////////////////////////////////////////////////////////////////

  //LM35:
  
  float T; //Declaramos la variable T como la temperatura del LM35
  int n = analogRead(PIN_LM35); // Guardamos la lectura del LM35 en la variable n
  T=n/10; //
  Serial.println(T);
  delay(100);
  
}
