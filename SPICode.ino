
//khai báo chân Master
#define SCLK_M 2 
#define MOSI_M 3
#define MISO_M 4 
#define SS_M 5   
//khai báo chân Slave
#define SCLK_S 8 
#define MOSI_S 9 
#define MISO_S 10
#define SS_S 11


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Master
  pinMode(SCLK_M, OUTPUT);
  pinMode(MOSI_M, OUTPUT);
  pinMode(MISO_M, INPUT);
  pinMode(SS_M, OUTPUT);
  //Slave
  pinMode(SCLK_S, INPUT);
  pinMode(MOSI_S, INPUT);
  pinMode(MISO_S, OUTPUT);
  pinMode(SS_S, INPUT);
  
}
// chương trình khởi tạo SPI
void SPI_Soft_init(){
  digitalWrite(SCLK_M, LOW);
  digitalWrite(MOSI_M, LOW); 
  digitalWrite(SS_M, HIGH);
}
// chương trình tạo 1 xung clock
void Clock(){
  digitalWrite(SCLK_M, HIGH);
  delay(300); 
  digitalWrite(SCLK_M, LOW);
  delay(300); 
}

// chương trình gửi 1 byte
void SPI_Soft_Transmit_Receive(uint8_t mData){ 
  uint8_t i = 0, x = 0, a=0x00, dataReceive=0x00; 
  digitalWrite(SS_M, LOW);  
  for(i = 0; i < 8; i++){ x = mData&0x80; // đưa bit cần truyền lên chân MOSI 
   if(x>0)  
   {
      digitalWrite(MOSI_M, HIGH);
   }

    else
   {
      digitalWrite(MOSI_M, LOW); 
   }
    Clock(); // phát 1 xung clock gửi dữ liệu đi   
    mData=mData<<1; // dịch dữ liệu cần gửi lên 1 bits  
    //Nhận dữ liệu từ Master
  if(digitalRead(MOSI_S)==LOW) 
  {
     a=0x00;
  }
 
  if(digitalRead(MOSI_S)==HIGH) 
  {
     a=0x01;
  } 
    dataReceive = dataReceive<<1;       // dịch dữ liệu lên 1 bit     
    dataReceive = dataReceive | a;
   Clock(); // phát 1 xung clock đọc bit tiếp theo 
  if(digitalRead(MOSI_S)==LOW) 
  {
     Serial.println("Tin hieu tren chan MOSI cua Slave nhan la: 0\n");   //In ra kiểm tra chân MOSI của Slave đã nhận đúng dữ liệu từ Master hay chưa   
         
  }
 
  if(digitalRead(MOSI_S)==HIGH) 
  {
     Serial.println("Tin hieu tren chan MOSI cua Slave nhan la: 1\n");  //In ra kiểm tra chân MOSI của Slave đã nhận đúng dữ liệu từ Master hay chưa 
        
  }

  }  
  digitalWrite(SS_M, HIGH);   //Đã truyền nhận xong,đưa chân SS lên mức 1
  Serial.println("Tin hieu tren Slave nhan ve kieu HEX"); 
  Serial.print(dataReceive, HEX);
  Serial.println("\n");
  if(digitalRead(SS_S)==HIGH) Serial.println("Da gui xong, Set chan SS len 1\n");


}

// chương trình nhận về 1 byte
/*uint8_t SPI_Soft_Receive(){  
  uint8_t data=0x00 ;
  uint8_t i=0,a=0x00;  

  while(i<8)
  {   

   if(digitalRead(MOSI_S)==HIGH)a=0x01;
   if(digitalRead(MOSI_S)==LOW)a=0x00;
 
    data = data<<1;       // dịch dữ liệu lên 1 bit     
    data = data | a;    //đọc chân MISO     
    Clock();    // phát một xung clock để đọc bit tiếp theo  

  }   

  return data;             // trả về dữ liệu đọc được 
}*/
void loop() {
  // put your main code here, to run repeatedly:
uint8_t mData = 0x0B;

SPI_Soft_init();// chương trình khởi tạo SPI
SPI_Soft_Transmit_Receive(mData);// chương trình gửi và nhận 1 byte
//Serial.println(SPI_Soft_Receive());
     


}
