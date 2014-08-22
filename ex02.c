#define LED_PIN 13
#define BUT_UP_PIN  2
#define BUT_DOWN_PIN 8
#define stepy 100
#define min_fr 100
#define max_fr 2000
#define start_fr 1000
#define button_fr 500
#define button1_fr 200
#define button2_fr button1_fr
#define buttonboth_fr 100
int fr;
int start;
/*
int button_timer = 0;
int button1_timer = 0;
int button2_timer = 0;
int buttonboth_timer = 0;
int blink_timer = 0;
*/
int timers[] = {0,0,0,0,0};
int timers_count = 5;
#define button_timer timers[0]
#define button1_timer timers[1]
#define button2_timer timers[2]
#define buttonboth_timer timers[3]
#define blink_timer timers[4]

int led;
int enabled = 1;

int pressed_down = 0;
int pressed_up = 0;

#define timer(a,b,c) if((a) >= (b)) \
      { \
         (a) = 0; \
         c; \
      } \

#define bound(a,b,c) if((a)<(b)){(a) = (b);} \
		     if((a)>(c)){(a) = (c);}


int  ispressed_up = 0; 
int  ispressed_down = 0; 
void setup () {
    pinMode(LED_PIN, OUTPUT);       // Enable pin 13 for digital output
    pinMode(BUT_UP_PIN, INPUT);        // Enable pin  2 for digital input
    pinMode(BUT_DOWN_PIN, INPUT);
    digitalWrite(BUT_DOWN_PIN,1);
    digitalWrite(BUT_UP_PIN,1);
    start = millis();
    led = 0;
    fr = start_fr;
}
 
void loop () {
    

    if(enabled){ 
    timer(button_timer,button_fr,button())
    timer(buttonboth_timer,buttonboth_fr, F_button_both())
    timer(button1_timer,button1_fr, F_button_up())
    timer(button2_timer,button2_fr, F_button_down())
    bound(fr,min_fr,max_fr)
    

    timer(blink_timer,fr,blink())
    
    
    if(!digitalRead(BUT_UP_PIN)) 
        pressed_up = 1;
    if(!digitalRead(BUT_DOWN_PIN))
        pressed_down = 1; 
    }
    

    
    
    int dt = millis() - start;
    
    int i;
    for(i=0;i<timers_count;i++){
      timers[i] =+ dt;
    }
    /*
    button1_timer += dt;
    button2_timer += dt;
    buttonboth_timer += dt;
    blink_timer += dt;
    button_timer += dt;
    */
    start += dt;
}

void blink(){
      digitalWrite(LED_PIN,led);
      led = !led;
}
void F_button_both(){
      if(ispressed_up && ispressed_down){ 
	enabled = 0; 
        digitalWrite(LED_PIN,1); 
  } 
  
}
void F_button_up(){
  if(pressed_up){
     fr += stepy;
       ispressed_up = 1; 
  }
    pressed_up = 0;
}
void F_button_down(){
  if(pressed_down){
	fr -= stepy;
  ispressed_down = 1; 
  }
  pressed_down = 0;

}
void button(){
  ispressed_up = 0; 
  ispressed_down = 0; 
}
