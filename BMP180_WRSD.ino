//En este script vamos a leer valores en el sensor BMP180
//Y vamos a imprimirlos en el monitor serial
//Y después vamos a escribir esos valores en la tarjeta SD

#include <Adafruit_BMP085.h>
#include <SD.h>
#include <sd_defines.h>
#include <sd_diskio.h>

#define PIN_LED 32

//En ESP32 hay 3 formas para escribir en la tarjeta SD:
//FILE_APPEND, FILE_WRITE, FILE READ

Adafruit_BMP085 bmp; //de Adafruit creamos la variable readings
File readings; //Lo mismo pero para la tarjeta

char payload[50];// Datos para escribir en el serial y la tarjeta SD, lo vamos a usar en sprintf

void setup() {
  Serial.begin(115200);
  bmp.begin(0x77); //esta es la dirección en donde está conectado el sensor por I2C.
  SD.begin();//Inicializa SD
  pinMode(PIN_LED,OUTPUT);//Inicializamos el LED
  
}

void loop() {

  float temp, pres;

  temp = bmp.readTemperature();
  pres = bmp.readPressure();
  //sprintf(payload,"temp: %8.2f , press: %8.2f",temp,pres); //Futuro json
  sprintf(payload,"%8.2f,%8.2f",temp,pres);
  Serial.println(payload);
  
  digitalWrite(PIN_LED,HIGH);//Encendemos el LED antes de iniciar la escritura
    readings =SD.open("/readings.csv",FILE_APPEND);//Abre archivo
    readings.println(payload);//Escribe en readings.csv lo que hay en payload
    readings.close();//Cerramos el archivo
  digitalWrite(PIN_LED,LOW);//Apagamos el LED después de escribir
  
  
  delay(500);

}
