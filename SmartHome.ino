/*
                            Chương trình chính

Mở thư mục Code Nháp -> mở file Wind_Speed_TEST -> run code và khảo sát tốc độ gió,
từ đó lấy được mốc "rpm" và thay vào "rpm_maxValue" ở dưới đây. Các phần còn lại
TUYỆT ĐỐI không được thay đổi gì!
*/


int rpm_maxValue = 500; //----> Thay



//-----------------------KHONG THAY DOI PHAN NAY------------------------------------//
const int encoder = 2;
const int waterSensor_1 = 12;
const int rainSensor = 8;
const int relay = 10;
const int waterSensor_2 = A4;
const int buzzer = 11;

const int IN_3 = 6; //PWM
const int IN_4 = 7;

//Varialble
unsigned long previousTime = millis();
float count = 0;
uint8_t lastVal = 0;

int getRPM(){
  const int timeWait = 1000; //Thoi gian cho la 1(s)
  float rpm = 0;
  if ((millis() - previousTime) >= timeWait){
    previousTime = millis();
    /*Vi du:
      - Ta nhan duoc count la 60 (60 xung)
      - Disk co 20 lo => 1 (s) disk quay 3 vong de tao 60 xung
      ==> RPM = so_vong x 60 (60s = 1p)
    */
    rpm = (count/20)*60;
    count = 0; //reset lai bien count cho lan dem moi
  }
  return rpm;
}
void blink(){
  digitalWrite(buzzer, 1);
  delay(200);
  digitalWrite(buzzer, 0);
  delay(200);
  digitalWrite(buzzer, 1);
  delay(200);
  digitalWrite(buzzer, 0);
  delay(200);
  digitalWrite(buzzer, 1);
  delay(200);
  digitalWrite(buzzer, 0);
  delay(200);
  digitalWrite(buzzer, 1);
  delay(200);
  digitalWrite(buzzer, 0);
  delay(200);
}
void count_EI(){
  count++;
}
void pump(){
    while (digitalRead(waterSensor_1) == 0){
      digitalWrite(relay, 0);
    }
    digitalWrite(relay, 1);
}
void open(){
  //Dong
  if (lastVal == 1){
   
  }else{
    digitalWrite(IN_4, 0);
    analogWrite(IN_3, 255-109);
    delay(100);
    digitalWrite(IN_4, 0);
    analogWrite(IN_3, 0);
    lastVal = 1;
  }
}
void close(){
  //Mo
  if (lastVal == 0){
    
  }else{
    digitalWrite(IN_4, 1);
    analogWrite(IN_3, 139);
    delay(130);
    digitalWrite(IN_4, 0);
    analogWrite(IN_3, 0);
    lastVal = 0;
  }
}
void setup(){

  pinMode(waterSensor_1, INPUT);
  pinMode(waterSensor_2, INPUT);
  pinMode(rainSensor, INPUT_PULLUP);
  pinMode(encoder, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, 0);
  digitalWrite(relay, 1);

  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  //Dem so lo tren disk, 0 la ngat ngoai cua board UNO tuong duong voi D2
  //Khi dien ap o chan 2 la 1 thi se dem = dem +1
  attachInterrupt(0, count_EI, RISING);
}
void loop(){
  if (analogRead(waterSensor_2) > 100){
    blink();
  }else if(analogRead(waterSensor_2) > 800){
    digitalWrite(buzzer, 1);
  }else{
    digitalWrite(buzzer, 0);
  }
  if (getRPM() > rpm_maxValue){
    close();
    pump();
  }
  digitalWrite(relay, 1);
  digitalWrite(buzzer, 0);

  if (digitalRead(rainSensor) == 0){
    close();
    delay(500);
  }else{
    open();
  }
}
//------------------------------------------------------------------------------//