/* Depending on your configuration, change the following variables:
 * -CAPACITOR_VALUE   ---> Capacitor value in Farad
 * -RESISTOR_VALUE   ---> Resistor value in Ohm
 * -bitDigitalPins[]   ---> digital pins that write the value
 * -bitAnalogPins[]   ---> analog pins that read the charge
 * -writeValues[]   ---> The value you want to write
 * -bits[x]   ---> x is the number of bits in your configuration
 */

const double CAPACITOR_VALUE = 10E-6; //value in Farad (exponential notation)
const double RESISTOR_VALUE = 1E3;  //value in Ohm (exponential notation)

const double WRITE_TIME = 5*CAPACITOR_VALUE*RESISTOR_VALUE*1E6;  //timing in microseconds. 5 times t = RC to charge to 99% of the supplied voltage
const double REFRESH_TIME = 2*CAPACITOR_VALUE*RESISTOR_VALUE*1E6;  //timing in microseconds. The refresh doesn't need to fully charge the capacitor, but only maintain a high enough charge

int bitDigitalPins[] = {2, 3, 4};  //digital pins connected to the single bits. The order is important
int bitAnalogPins[] = {A0, A1, A2};
int writeValues[] = {1, 0, 1};  //initial values to write to the RAM. The order is the one in the pin array

int bitNumber = sizeof(bitDigitalPins)/sizeof(int);

int bitLeftToWrite = 0;  //wait until every bit has finished writing or refreshing. If > 0, it means that it is still writing or refreshing
int bitLeftToRefresh = 0;
boolean canRead = false;  //can't read while writing or refreshing

class BitHandler{  //class that handles every bit, particularly timings
  private:
    int pin;  //digital pin
    int analogPin;
    int index;  //index in the arrays
    
    boolean isRefreshing = false;  //determine the status of the single bit. Needed to initiate the procedures only once
    boolean isWriting = false;
    boolean isErasing = false;
    
    unsigned long bitTiming = 0;  //timer dedicated to the single bit. Needed to simulate a sort of multithreading

  public:
    BitHandler(){ //necessary creation of default constructor
      pin = 0;
      analogPin = A0;
      index = 0;
    }

    BitHandler(int _index){
      index = _index;
      pin = bitDigitalPins[index];
      analogPin = bitAnalogPins[index];
    }

    void writeBit(){
       
      if((!isWriting)&&(bitLeftToWrite >= bitNumber-index)){  //if it isn't already writing this bit or at least a bit in the array, abilitate writing.
        pinMode(pin, OUTPUT);  //close the circuit
        digitalWrite(pin, LOW);

        bitLeftToRefresh = 0;  //every refresh is stopped
          
        eraseBitValue();  //erase bit values. Every bit needs to go to 0
          
        if(micros()-bitTiming > WRITE_TIME){  //if the erase time is passed. Erase time is equal to write time
          isErasing = false;
          bitTiming = micros();  //timer to decide when to stop writing
          isWriting = true;
  
          int value = writeValues[index];  //set pin write status only one time
            
          if(value == 1){  //default value is LOW
            digitalWrite(pin, HIGH);
          }
        }
      }
  
      if(isWriting){
        writeValue();
      }
    }

    void refreshBit(){
      
      if((!isRefreshing)&&(bitLeftToRefresh >= bitNumber-index)){  //if it isn't already refreshing this bit or at least a bit in the array, abilitate refreshing
  
        pinMode(pin, OUTPUT);  //close the circuit
        digitalWrite(pin, LOW);
        
        bitTiming = micros();  //timer to decide when to stop refreshing
        isRefreshing = true;  
        
        int chargeValue = analogRead(analogPin);//set pin write status only one time
  
        if(chargeValue > 500){  //default value is LOW
          digitalWrite(pin, HIGH);
        }
      }
  
      if(isRefreshing){
        refresh();
      }
    }

    int readBit(){

      int chargeValue = analogRead(analogPin);

      if(chargeValue > 500){  //a capacitor is considered charged if it's read charge is above 500
        return 1;
      }else{
        return 0;
      }
    }

    int getPin(){
      return pin;
    }

    int getAnalogPin(){
      return analogPin;
    }

    int getIndex(){
      return index;
    }

  private:
    void eraseBitValue(){
      if(!isErasing){  //start the erasing process
        bitTiming = micros();
        isErasing = true;
      }
    }
  
    void writeValue(){  //function to stop writing the bit (bit write started before)         
      if(micros() - bitTiming > WRITE_TIME){
        digitalWrite(pin, LOW);  //writing has ended
        isWriting = false;  //the single bit is not writing
        bitLeftToWrite--;
      
        pinMode(pin, INPUT);  //open circuit to slow down discharge
      }
      
    }

    void refresh(){  //function to stop refreshing the bit (bit refresh started before)
      if(micros() - bitTiming > REFRESH_TIME){
        digitalWrite(pin, LOW);  //refreshing has ended
        isRefreshing = false;  //the single bit is not refreshing
        
        bitLeftToRefresh--;

        pinMode(pin, INPUT);  //open circuit to slow down discharge
      }
      
    }
};

BitHandler bits[3];  //create bits objects. Change the size depending on how many bits do you have

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < bitNumber; i++){  //for every bit create bit object
    bits[i] = BitHandler(i);
  }
  pinMode(12, INPUT);  //button
  bitLeftToWrite = bitNumber;  //write at first
}

void loop() {
  writeRAM();
  refreshRAM();
  
  if(digitalRead(12) == HIGH){  //press the button to read what is written on the RAM
    readRAM();
  }
}

void refreshRAM(){
  
  if(bitLeftToRefresh > 0){
    for(int i = 0; i < bitNumber; i++){  //for every bit run the refresh function
      bits[i].refreshBit();
    }
  }

  for(int i = 0; i < bitNumber; i++){  //decide if at least a bit needs refresh
    if((analogRead(bits[i].getAnalogPin()) < 700)&&(analogRead(bits[i].getAnalogPin()) > 500)){  //if the capacitor charge is too low but it is not a 0
      if((bitLeftToWrite == 0)&&(bitLeftToRefresh == 0)){  //if it isn't already writing or refreshing
        bitLeftToRefresh = bitNumber;
      }
    }
  }
}

void readRAM(){
  if(canRead){
    for(int i = 0; i < bitNumber; i++){  //read the value of every bit
        int bitValueRead = bits[i].readBit();
        Serial.print(bitValueRead);
      }
  
    Serial.println("");
  }
}

void writeRAM(){
  if(bitLeftToWrite > 0){
    canRead = false;  //the only time it can't read is while writing
    for(int i = 0; i < bitNumber; i++){  //for every bit run the write function
      bits[i].writeBit();
    }
  }else{
    canRead = true;
  }
}
