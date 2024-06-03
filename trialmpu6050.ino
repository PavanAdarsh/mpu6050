#include<Wire.h>
const int slaveadd=0x68;
long int aX,aY,aZ,gX,gY,gZ,temp;
int dt=2000;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  //reset when code runs each time
  Wire.beginTransmission(slaveadd);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  /*
  configuration of accelerometer range from datasheet:(write to 0x1C)
  -default is +-2g, that corresponds to 0x00 for bits 4 and 3, i.e. 000(00)000;
  -for +-4g, 000(01)000=0x08;
  -for+-8g, 000(10)000=0x10;
  -for+-16g, 000(11)000=0x18;
  configuration of gyroscope range from datasheet: (write to 0x1B)
  -default is 250/s, corresponds to 0x00;
  -500=0x08,1000=0x10,2000=0x18;
  */
}

void loop()
{
  Wire.beginTransmission(slaveadd);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(slaveadd,14,true);//all registers are next to one another, so we can read all values in one request
  aX = Wire.read()<<8 | Wire.read(); //reads from 0x3B,0x3C, adds both to get 16-bit number
  aY = Wire.read()<<8 | Wire.read(); //reads from 0x3D,0x3E
  aZ = Wire.read()<<8 | Wire.read(); //reads from 0x3F,0x40

  temp = Wire.read()<<8 | Wire.read(); //reads from 0x41,0x42
  
  gX = Wire.read()<<8 | Wire.read(); //reads from 0x43,0x44
  gY = Wire.read()<<8 | Wire.read(); //reads from 0x45,0x46
  gZ = Wire.read()<<8 | Wire.read(); //reads from 0x47,0x48

  //printing
  Serial.print("AX:");
  Serial.print(aX);
  Serial.print(" AY:");
  Serial.print(aY);
  Serial.print(" AZ:");
  Serial.print(aZ);

  Serial.print("  Temp:");
  Serial.print((temp/340.0)+36.53); //from datasheet

  Serial.print("  GX:");
  Serial.print(gX);
  Serial.print(" GY:");
  Serial.print(gY);
  Serial.print(" GZ:");
  Serial.print(gZ);
  Serial.println(" ");


  delay(dt);
}