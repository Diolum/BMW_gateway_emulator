  #include <IbusTrx.h>
  #include <DiagTrx.h>
  unsigned int messageSource = 0;
  unsigned int messageDestination = 0;
  unsigned int messageLength = 0;
  unsigned int messageCommand = 0;
  unsigned int message = 0;
  unsigned int DmessageSource = 0;
  unsigned int DmessageDestination = 0;
  unsigned int DmessageLength = 0;
  unsigned int DmessageCommand = 0;
  unsigned int Dmessage = 0;
  IbusTrx ibusTrx;
  DiagTrx diagTrx;
  uint8_t IbusOut[150];//Fail over 150. Why?!!!!
  int IbusOutMessLenght = 0;
  uint8_t DiagOut[150];//Fail over 150. Why?!!!!
  int DiagOutMessLenght = 0;


void setup(){
    ibusTrx.begin(Serial);
    diagTrx.begin(Serial1);
}

void loop() {
  bool messageWaiting = ibusTrx.available();
  bool DiagmessageWaiting = diagTrx.available();
  if (messageWaiting) {
    IbusMessage message = ibusTrx.readMessage();
    if (message.destination()==0x3F){
      DiagOut [0] = message.source();
      DiagOut [1] = message.length() + 1;
      for (int i = 0; i < (message.length() - 2); i++) {
        DiagOut [2+i] =  message.b(i);
      }
      diagTrx.write(DiagOut); 
    }
  }
  if (DiagmessageWaiting) {
    DiagMessage message = diagTrx.readMessage();
    IbusOut [0] = 0x3F; 
    IbusOut [1] = message.dlength() - 1;
    IbusOut [2] = message.ddestination();
    for (int i = 0; i < (message.dlength()); i++) {
    IbusOut [3+i] =  message.b(i+2);
    }
    ibusTrx.write(IbusOut); 
  }
}
