/*
 *  Exemplo de Acelerômetro analógico conectado nas entradas AD do Arduino controlando servo
 *  Envia pela serial: timespamp + valores lidos X, Y + valor remapeado e filtrado(Kalman) controle servo 0-180graus 
 * 
 *  uso: 
 *    - Acelerômetro eixos X e Y conectados nas entradas A0 e A1 do Arduio e servo alimentação (5V) e pino 9
 *  
 *  
 *  
 *  by Marcelo Campos - Garoa HC
 *  Rev.0 - Nov/16
 * 
*/

#include <Kalman_Filter.h>
#include <Servo.h>

Servo my_Servo;

Kalman_Filter Kalman_Filter_i1;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Init Ok");
  
  my_Servo.attach(9);
  
  Kalman_Filter_i1.kalman_init();  
}

void loop() 
{
  int val_x, val_y, val_graus;
  float kalman_returned, z_measured;
     
  while(1)
  {
    val_x = analogRead(A0);
    val_y = analogRead(A1);

    kalman_returned = Kalman_Filter_i1.kalman_filter( val_x ) ; 
  
    
    val_graus = map((int)kalman_returned, 110, 600, 180, 0);  

    Serial.print(millis());
    Serial.print(", ");
    Serial.print(val_x);
    Serial.print(", ");
    Serial.print(val_y);
    Serial.print(", ");
    Serial.print(val_graus);
    
    Serial.println();

    my_Servo.write(val_graus);
    
  }
  
}
