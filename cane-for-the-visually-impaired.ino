#include <Ultrasonic.h>

// Define os pinos utilizados
#define pin_trigger 4
#define pin_echo 5
#define pin_vibration 3
 
// Inicializa o sensor nos pinos definidos
Ultrasonic ultrasonic(pin_trigger, pin_echo);
 
void setup()
{
  // Define velocidade da comunicação serial
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  // Define modo do pino o motor de vibração
  pinMode(pin_vibration, OUTPUT);
}
 
void loop()
{
  //Le as informacoes do sensor em cm
  
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  // exbindo no serial monitor a distância atual
  Serial.print(" - Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print("\n");
  delay(1000);

  // Limite max da distância para realizar a leitura é 150cm, mas podendo ser ajustado
  if(cmMsec < 150) {

    // define os intervalos inversamente proporcionais da distancia para com o tempo de vibração
    // quanto maior a distância menor o tempo de vibração
    // warning: o menor valor é 10cm pois valores menores podem ter erro de leitura e falha na interpretação do sensor
    int val = map(cmMsec, 10, 150, 1000, 300);
    
    digitalWrite(pin_vibration, HIGH);
    
    // exbindo no serial monitor o delay atual
    Serial.print("time: ");
    Serial.print(val);
    Serial.print("\n");
    
    delay(val);
    digitalWrite(pin_vibration, LOW);
  }
}
