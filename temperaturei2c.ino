
#include <math.h>
#include <Wire.h>

#define ADDRESS 0b1001111

float max = -1000;
float min = 1000;

void setup ( void ) 
{
    Serial.begin(9600);
    Wire.begin();
}

float readTemperature ( void )
{
    int temp = Wire.read() << 8; /* MSB  */
    temp += Wire.read();         /* LSB  */

        /*
         * Data   | Shift | Resolution
         * 8 bit  |   8   | 1.0C
         * 9 bit  |   7   | 0.5C
         * 10 bit |   6   | 0.25C
         * 11 bit |   5   | 0.125C
         * 12 bit |   4   | 0.0625C
         * 13 bit |   3   | 0.03125C
         */
    return (float)(temp >> 3) * 0.03125; 
}

float getTemperature (int address)
{
    Wire.requestFrom(address,2);
    if (Wire.available() > 1){
        return readTemperature();
    }
}

float maxMin (float temp)
{
    if (temp > max){
        max = temp;
    }
    if (temp < min){
        min = temp;
    }
    return temp;
}

void SerialPrint (float temp, int precision)
{
    Serial.print("\"");
    Serial.print(temp,precision);
    Serial.print(",");
    Serial.print(max,precision);
    Serial.print(",");
    Serial.print(min,precision);
    Serial.println("\"");
}


void loop ( void )
{
   
    SerialPrint(maxMin(getTemperature(ADDRESS)),5);
    delay (500);
}
