//1초동안 최소밝기 - 최대밝기 - 최소밝기 사이에서 밝기가 triangle패턴으로 변화하는 코드
//period와 duty를 설정 가능
//duty = 밝기
//period = led의 밝기가 변하는 주기

#define LED 7
#define Interval 5

int duty = 0; //초기 밝기 0으로 설정
int duty_var = 1; //초기 밝기 변화량 1로 설정
int period = 10000; //초기 주기 10ms로 설정
unsigned long timer; //타이머 설정

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  timer = millis() + Interval; //초기시간 설정
}

void loop() {
  for(int i = 0; i < 10; i++){    
    while(duty < 100){
      while(millis() < timer){
        digitalWrite(LED, 0);
        delayMicroseconds(period * duty / 100.0);
        digitalWrite(LED, 1);
        delayMicroseconds(period * (100 - duty) / 100.0);
      }
      duty = set_duty(duty);
      timer = timer + Interval;
    }
    duty_var *= -1;
    while(duty > 0){
      while(millis() < timer){
        digitalWrite(LED, 0);
        delayMicroseconds(period * duty / 100.0);
        digitalWrite(LED, 1);
        delayMicroseconds(period * (100 - duty) / 100.0);
      }
      duty = set_duty(duty);
      timer = timer + Interval;
    }
    duty_var *= -1;
  }
  period = set_period(period);
}

int set_period(int period){
  period = period / 10;
  return period;
}

int set_duty(int duty){
  duty += duty_var;
  return duty;
}
