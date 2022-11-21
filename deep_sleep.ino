//En deep_sleep no se guardan las variables, sólo las que están dentro del RTC
//agregando a una varibale local RTC_DATA_ATTR hacemos que se guarde en la memoria del RTC
RTC_DATA_ATTR int bootCount = 0; 

#define uS_TO_S_FACTOR 1000000  //Factor de conversion de us a s
#define TIME_TO_SLEEP 5         //Tiempo durante el que lo queremos dormir 
#define LED_PIN 32              //LED
#define BUTTON_PIN 33           //botón

//En deep_sleep cuando se enciende, se carga todo desde el setup
//por eso se incrementa la variable bootCount desde el setup y no del loop
void setup() {
  Serial.begin(115200);
  delay(500);
  
  pinMode(LED_PIN, OUTPUT);
  
  bootCount++;
  Serial.println("Número de veces iniciado " +String(bootCount));

  print_wakeup_reason();
  //Configuracion Deep Sleep
  //(gpio_num_t) convertimos a la variable que necesita
  //otra solución es con GPIO_NUM_33 que es el numero del pin en donde esta el boton
  
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, HIGH); //Despierta por una señal externa (botón)
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*uS_TO_S_FACTOR); //10 segundos para despertar (por timer)
  Serial.println("Configurando ESP32 para dormir por " + String(TIME_TO_SLEEP) + " segundos.");

  if (bootCount%2 == 0){
  Serial.println("ESP32 se va a dormir ahora.");
  esp_deep_sleep_start();
  }
  else {Serial.println("Esta línea se imprime en reinicios impares");}
}

void loop() {
  //Nunca se va a ejecutar lo que está en el loop por que el deep sleep inicia en el setup
  delay(5);

  digitalWrite(LED_PIN,LOW);
  //Usando esp_light_sleep_start() inicia el modo ligth_sleep
  esp_light_sleep_start(); //Se va a quedar en light sleep hasta que no le digamos lo contrario

  digitalWrite(LED_PIN, HIGH);
  delay(500);
  
  print_wakeup_reason();
}

//-----------------------------------------------------------------------------------------
//Función que vamos a usar despues para ver cual fue la razon para despertar
void print_wakeup_reason(){
  //Se usa un tipo de dato especial de la librería para dormir 
  //esp_sleep_wakeup_cause_t (esa t al final significa type)
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Inicio causado por señal en el RTC_IO (periféricos del RTC)");
    break;

    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Inicio causado por señal en el RTC_CNTL (controlador del RTC)");
    break;

    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Inicio causado por señal en un timer");
    break;

    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Inicio causado por señal en un pin touch (botón del ESP32)");
    break;

    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Inicio causado por señal lanzada por el ULP(ultralow) Croprocessor");
    break;

    default:
      Serial.printf("El inicio no fue causado por ninguna razón conocida: %d \n", wakeup_reason);
    break;
    }
}
//-----------------------------------------------------------------------------------------
