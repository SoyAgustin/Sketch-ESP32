const int PWM_PIN_LED = 32;
const int BUTTON_PIN = 33;

//variables para PWM
const int PWM_CHANNEL = 0; 
const int PWM_FREQ = 10000; //en Hz
const int PWM_RESOLUTION = 8; //resolución en bits

//variables para la señal de onda
int waveform = 0;
float t; //tiempo que ha transcurrido dentro de nuestro ciclo
float dutyCycle = 0;//ciclo de trabajo (el tiempo que está encedido)

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN,INPUT_PULLDOWN);

  //Iniciamos configuración PWM (ledc)
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN_LED, PWM_CHANNEL);

}

void loop() {

  //Polling al botón (si presionamos el botón)
  if(digitalRead(BUTTON_PIN)){
  //generamos una señal en forma de onda 
  waveform++; //aumenta en una unidad
  if(waveform > 7){
    waveform = 0;
    }
    Serial.println(waveform);
    delay(500);
  }
   t++;
   if(t >= 256){
    t=0;
    }
  
//Usamos un switch para cada caso de pulsación.
  switch(waveform){
    //dutyCycle es un valor entre [0,1], es el porcentaje de trabajo

    //formas de onda constantes
    case 0:
      dutyCycle = 0;
    break;
    
    case 1:
      dutyCycle = 0.3;
    break;
      
    case 2:
      dutyCycle = 0.5;
    break;
      
    case 3:
      dutyCycle = 0.8;
    break;
      
    case 4:
      dutyCycle = 1;
    break;
      //formas de onda variables
    case 5:
      dutyCycle = (t+0.1)/256;
      delay(2.5);
    break;
      
    case 6:
      dutyCycle = 0.5*sin(2*PI*t/256)+0.5;
      delay(0.5);
    break;

    case 7:
      dutyCycle = pow(2.71828, ((t/255)-1)*2);
      delay(4);
    break;
    }

  Serial.println(dutyCycle*100);

  //Ahora 'mandamos' estas formas al LED

  ledcWrite(PWM_CHANNEL,dutyCycle*255);

}
