void setup() {
  // put your setup code here, to run once:

}
int t=0;
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,1);
delay(t);
digitalWrite(12,1);
delay(t);
digitalWrite(13,0);
delay(t);
digitalWrite(12,0);
delay(t);
t-=1;
if(t<0)
t=100;
}
