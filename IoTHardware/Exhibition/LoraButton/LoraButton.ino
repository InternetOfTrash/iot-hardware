  /*
MarvinLaptop

Basic controls of IoT Academy Marvin LoRa Development board through your Laptop

This version supports:
  - Sending LoRa uplink messages using ABP that are given as input from the serial port on your laptop
  - Blink three times when sending data
  - Power control to RN2483 module

Instructions:
  - Get the latest version of the Arduino software
  - In Arduino IDE select Arduino Leonardo and com port of your device
  - Please adjust ABP adresses and key below to match yours
*/
// Port to assign the type of lora data (any port can be used between 1 and 223)
int     set_port  = 1;
#define buttonOut A1
#define trigPin A2
#define echoPin A3
// Some standard ports that depend on the layout of the Marvin
long    defaultBaudRate = 57600;
int     reset_port = 5;
int     RN2483_power_port = 6;
int     led_port = 13;
int     buttonState = 0;

//*** Set parameters here BEGIN ---->
String  set_nwkskey = "BF7C020C8BF1468021894BFA37C6A0A3"; // Put your 32 hex char here
String  set_appskey = "1E3F4F48280CF8610EFCA33BD9FAAD90"; // Put your 32 hex char here
String  set_devaddr = "26011C0B"; // Put your 8 hex char here
//String  set_devEUI = "00ADA3B2C28049BE";
//*** <---- END Set parameters here

// Some global items
String reader = "";

/*
 * Setup() function is called when board is started. Marvin uses a serial connection to talk to your pc and a serial
 * connection to talk to the RN2483, these are both initialized in seperate functions. Also some Arduino port are 
 * initialized and a LED is called to blink when everything is done. 
 */
void setup() {
  InitializeSerials(defaultBaudRate);
  initializeRN2483(RN2483_power_port, reset_port);
  pinMode(led_port, OUTPUT); // Initialize LED port  
  pinMode(buttonOut,INPUT); // Initialize button
  blinky();
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  print_to_console("Payload?");
}

int valueFromUS= -2;
void GetData(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance >= 70|| distance <= 0){
      valueFromUS = -1;
  }
  else {
    int percentage = 65-distance;
    Serial.write(distance);
    int percentage2 = percentage*100;
    int percentage3 = percentage2/65;
    valueFromUS = percentage3;
  }
  
  
}
void loop() {
  read_data_from_LoRa_Mod();
  buttonState = digitalRead(buttonOut);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    GetData();
    reader = String(valueFromUS,HEX);
  
 

  if (reader.length() >0) {
    reader.replace("\r","");
    reader.replace("\n","");
    print_to_console("Read: " + reader);
    delay(1000);
    send_LoRa_data(set_port, reader);
    //blinky();
    //delay(5000);
    //read_data_from_LoRa_Mod();
    reader = "";
    //delay(1000);
    print_to_console("Payload?");
    
  }
  delay(30000);
}
}
void InitializeSerials(long baudrate)
{
  Serial.begin(baudrate);
  Serial1.begin(baudrate);
  delay(1000);
  print_to_console("Serial ports initialised");
}

void initializeRN2483(int pwr_port, int rst_port)
{
  //Enable power to the RN2483
  pinMode(pwr_port, OUTPUT);
  digitalWrite(pwr_port, HIGH);
  print_to_console("RN2483 Powered up");
  delay(1000);
  
  //Disable reset pin
  pinMode(rst_port, OUTPUT);
  digitalWrite(rst_port, HIGH);

  //Configure LoRa module
  send_LoRa_Command("sys factoryRESET");
  read_data_from_LoRa_Mod();


  send_LoRa_Command("mac set nwkskey " + set_nwkskey);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac set appskey " + set_appskey);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac set devaddr " + set_devaddr);
  read_data_from_LoRa_Mod();

  //For this commands some extra delay is needed.
  send_LoRa_Command("mac set adr on");
  //send_LoRa_Command("mac set dr 2"); //uncomment this line to fix the RN2483 on SF12 (dr=DataRate)
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac get dnctr"); //uncomment this line to fix the RN2483 on SF12 (dr=DataRate)
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac set rxdelay1 1000"); //uncomment this line to fix the RN2483 on SF12 (dr=DataRate)
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac set ar on");
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("radio set iqi on");
  delay(1000);
  read_data_from_LoRa_Mod();
  
  send_LoRa_Command("mac set rx2 3 869525000");
  delay(1000);
  read_data_from_LoRa_Mod();
  
  send_LoRa_Command("mac save");
  delay(1000);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("mac join abp");
  delay(1000);
  read_data_from_LoRa_Mod();
}

void print_to_console(String message)
{
  Serial.println(message);
}

void read_data_from_LoRa_Mod()
{
  if (Serial1.available()) {
    String inByte = Serial1.readString();
    Serial.println(inByte);
  }

}

void send_LoRa_Command(String cmd)
{
  print_to_console("Now sending: " + cmd);
  Serial1.println(cmd);
  delay(500);
}

void send_LoRa_data(int tx_port, String rawdata)
{
  send_LoRa_Command("mac tx uncnf " + String(tx_port) + String(" ") + rawdata);
}


void blinky()
{
  digitalWrite(led_port, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(led_port, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second
  digitalWrite(led_port, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(led_port, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

}


