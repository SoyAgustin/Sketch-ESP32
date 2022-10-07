//Una estructura es un tipo de datos hecho por otro tipo de datos

struct Button{ 
  //generamos un nuevo tipo de variable que se llama botón
  //conformada por otras 3 variables.
  
  const int PIN;
  int numTimesButtonPressed;
  bool pressed;
  bool bStatus; //el último estado en el que estuvo el botón
}; //lleva ;

//Inicializamos la variable button1 que es de tupo Button (arriba la creamos)
Button button1 ={33,0,false,false};
//Es equivalente a declarar  una variable como de toda la vida sólo que con parámetros personalizados

//IRAM_ATTR hace que se ejecute en la memoria RAM por que queremos que sea lo más rápido posible
//void IRAM_ATTR 'nombre de la función'

void IRAM_ATTR isr_button(){
  button1.numTimesButtonPressed +=1; //incremento en 1 el número de veces que sea presionado
  button1.pressed = true;
  button1.bStatus = button1.bStatus ^ 1; //el operador XOR en c es ^ , el operador  XOR con un 1 devuelve el primero pero negado.
}

void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN,INPUT);
  
  //Generamos una instrucción para la interrupción con attachInterrupt()
  //Como argumentos tenemos: La variable, La función o instrucciones a ejecutar, Modo
  //Modo: LOW, HIGH, CHANGE, FALLING, RISING
  
  attachInterrupt(button1.PIN, isr_button,RISING);

}

void loop() {

  if(button1.bStatus == true){
    Serial.printf("El botón se ha presionado %u veces \n",button1.numTimesButtonPressed);
  }else{
    Serial.print("bStatus: ");
    Serial.println(button1.bStatus);
  }
  
}
