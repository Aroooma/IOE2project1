
#define Echo 7 // Echo回声脚
#define Trig 6 //  Trig 触发脚
int Front_Distance = 0;//

#define BREZZE 3
#define motor 4

//const int dis_bound=
unsigned long timer1 = 0;
unsigned long timer2 = 0;
bool flag1=true;
bool flag2=true;
bool flag3=true;
bool flag4=true;
bool flag5=true;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);  // start serial for output
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
  pinMode(BREZZE,OUTPUT);
  pinMode(motor,OUTPUT);
  timer1 = millis();
}

void loop() {
Front_Distance = 10*Distance_test();

if ((Front_Distance > 800 && Front_Distance < 1000) && flag1)
{
flag1=false;
tone(BREZZE,850);
digitalWrite(motor,HIGH);
timer1 = millis();
}
else if ((Front_Distance > 600 && Front_Distance < 800) && flag2)
{     
flag2=false;
tone(BREZZE,850);
digitalWrite(motor,HIGH);
timer1 = millis();
}
else if ((Front_Distance > 400 && Front_Distance < 600) && flag3)
{
flag3=false;
tone(BREZZE,850);
digitalWrite(motor,HIGH);
timer1 = millis();
}else if ( Front_Distance < 400 && flag4)
{
flag4=false;
tone(BREZZE,850);
digitalWrite(motor,HIGH);
timer1 = millis();
timer2=millis();
}
if (!flag1){
if ((millis()-timer1) >1000){
noTone(BREZZE); 
digitalWrite(motor,LOW);
flag1=true;
}
}
if (!flag2){
if ((millis()-timer1) >500){
noTone(BREZZE); 
digitalWrite(motor,LOW);
flag2=true;
}
}
if (!flag3){
if ((millis()-timer1) >200){
noTone(BREZZE); 
digitalWrite(motor,LOW);
flag3=true;
}

}
if (!flag4){
if ((millis()-timer1) >50){
noTone(BREZZE); 
digitalWrite(motor,LOW);
flag4=true;
}

}
delay(100);
}

float Distance_test()   // 量出前方距离 
{
  digitalWrite(Trig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  Serial.print("Distance:");      //输出距离（单位：厘米）
  Serial.println(Fdistance);         //显示距离
  //Distance = Fdistance;
  return Fdistance;
}  
