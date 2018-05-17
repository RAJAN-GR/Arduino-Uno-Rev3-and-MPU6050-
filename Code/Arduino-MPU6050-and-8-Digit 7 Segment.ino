#include <Wire.h>
#include <MPU6050.h>
#include <math.h>
/* Include the HCMAX7219 and SPI library */
#include <HCMAX7219.h>
#include "SPI.h"

/* Set the LOAD (CS) digital pin number*/
#define LOAD 10 
/* Create an instance of the library */
HCMAX7219 HCMAX7219(LOAD);


MPU6050 mpu;
void setup() 
{
  Serial.begin(9600);
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}


void loop()
{
    int Meteres = 0;
    int angle = angle_in_degree();

    switch(angle)
    {
      case 79:                    
          Meteres = 180;
          break;
      case 80:                    
          Meteres = 180;
          break;
      case 81:
          Meteres = 180;
          break;
      
      case 76:
          Meteres = 450;
          break;
      case 77:
          Meteres = 450;
              break;
      case 78:
          Meteres = 450;
          break;
      
      case 72:
          Meteres = 350;
          break;
      case 73:
          Meteres = 350;
          break;
      case 74:
          Meteres = 350;
          break;
      
      case 67:
          Meteres = 400;
          break;
      case 68:
          Meteres = 400;
          break;
      case 69:
          Meteres = 400;
          break;
      
      case 62:
          Meteres = 450;
          break;
      case 63:
          Meteres = 450;
          break;
      case 64:
          Meteres = 450;
          break;
      
      case 56:
         Meteres = 550;
            break;
      case 57:
         Meteres = 550;
          break;
      case 58:
          Meteres = 550;
          break;
      
      case 46:
          Meteres = 600;
          break;
      case 45:
          Meteres = 600;
              break;
      case 44:
          Meteres = 600;
          break;
      
      case 31:
          Meteres = 550;
          break;
      case 32:
          Meteres = 550;
          break;
      case 33:
          Meteres = 550;
          break;
      
      case 21:
          Meteres = 450;
          break;
      case 22:
          Meteres = 450;
          break;
      case 23:
          Meteres = 450;
          break;
      
      default:
          Meteres = 0;
    }

    // Print in Serial Monitor.
    Serial.print("angle = ");
    Serial.print(angle);
    Serial.print(" Meteres  = "); Serial.println(Meteres);
    Serial.print("\n");

    // Print on 7sigmentd 8 digit.
    /* Clear the output buffer */
    HCMAX7219.Clear();
    /* Write some text to the output buffer */
    HCMAX7219.print7Seg(angle,8);
    HCMAX7219.print7Seg("A", 5);
    HCMAX7219.print7Seg(Meteres, 4);
    HCMAX7219.print7Seg("L", 1);
    /* Send the output buffer to the display */
    HCMAX7219.Refresh();
    
    //delay(20);
}



int angle_in_degree()
{
    Vector normAccel = mpu.readNormalizeAccel();
    int num_samples = 10; // take the average of multiple samples
    float sum = 0.0f;
    
    for (int i=0; i < num_samples; i++)
    {
        float z = normAccel.ZAxis; // +z is up from the top of the pcb
        float y = normAccel.YAxis; // +y is lengthwise to the right
        
        //float angle = atan2(z, y) * 180.0f / M_PI;  // angle will be between -360 and 360 degrees
        float angle = atan2(y, z) * 180.0f / M_PI;  // angle will be between -360 and 360 degrees
        sum += angle;
        delay(15);
    } 
    
    float average = round(sum / num_samples);
    return(average);  
}
