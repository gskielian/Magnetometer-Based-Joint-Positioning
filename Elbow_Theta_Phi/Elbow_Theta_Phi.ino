#include <Wire.h> //arduino i2c library
#define i2c_addr 0x1E

//TODO add register names here
//note, I like binary format over hex, but is this so wrong?

//CRA registers
#define DO_75HZ 0b00011100
#define AVERAGE_8 0b01100000

int x,y,z;

void setup() {
  // Serial and I2c bus setup
  Serial.begin(115200);
  Wire.begin();

  //HMC setup
  average8();
  gain(0x08); // 3-bit gain, so 2^3 = 8 is the highest value
  //continuousMeasurementMode(); //only needs to be set once
}

void loop() {
  singleMeasurementMode(); //device goes into low-power mode between measurements, until this is called again
  delay(6); //we must wait at least 6ms or monitor DRDY hardware interrupt pin
  read6bytes();
}


//Register Helpers


//set single measurement mode -- low-pwr mode entered between measurements
void singleMeasurementMode() {
  send2Bytes(0x02, 0x01);
}

//set continuous measurement mode -- faster than sngle measurement mode, I haven't tested how much faster yet
void continuousMeasurementMode() {
  send2Bytes(0x02, 0x00);
}


//sets gain for all channels, input must be between 1->8
void gain(byte gain) {
  send2Bytes(0x01, gain << 5); //shift 5 bytes left, as leftmost 3 registers are the targets
}

//TODO needs a better name, as we also use this for setting the data output rate
void average8() {
  send2Bytes(0x00, AVERAGE_8 | DO_75HZ); //average 8 samples before data is output, data output rate of 75Hz
}


//wire-wrapper functions (rofl, wire-wrapper...)

void send2Bytes(byte x, byte y) {
  Wire.beginTransmission(i2c_addr);
  Wire.write(x);
  Wire.write(y);
  Wire.endTransmission();
}

//right now we print these but need not
void read6bytes() {
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(i2c_addr,0x06);
  if(0x06 <= Wire.available()){
    x = Wire.read()<<8; //x's msb
    x |= Wire.read(); //x's lsb
    y = Wire.read()<<8; //y's msb
    y |= Wire.read(); //y's lsb
    z = Wire.read()<<8; //z's msb
    z |= Wire.read(); //z's lsb
  }

  //I like the adafruit style arduino prints
  Serial.print("x = "); Serial.print(x);
  Serial.print("  y = "); Serial.print(y);
  Serial.print("  z = "); Serial.println(z);

  delay(16); //approximately 60Hz, far within our 75Hz data output rate envelope
}
