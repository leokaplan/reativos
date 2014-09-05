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
#include "eventos.c"
int fr;
int led;
int enabled = 1;

int pressed_down = 0;
int pressed_up = 0;

#define bound(a,b,c) if((a)<(b)){(a) = (b);} \
		     if((a)>(c)){(a) = (c);}


int  ispressed_up = 0; 
int  ispressed_down = 0; 
void button_down(){
	pressed_down = 1;
}

void button_up(){
	pressed_up = 1;
}

void blink(){
      digitalWrite(LED_PIN,led);
      led = !led;
      timer_set(fr,blink);
}
void F_button_both(){
      if(ispressed_up && ispressed_down){ 
	enabled = 0; 
        digitalWrite(LED_PIN,1); 
  } 
  if(enabled) 
    timer_set(buttonboth_fr, &F_button_both);

}
void F_button_up(){
  if(pressed_up){
     fr += stepy; 
     bound(fr,min_fr,max_fr)
     ispressed_up = 1; 
  }
    pressed_up = 0;
 if(enabled) 
    timer_set(button1_fr, &F_button_up);

}
void F_button_down(){
  if(pressed_down){
      fr -= stepy;
      bound(fr,min_fr,max_fr)
      ispressed_down = 1; 
  }
  pressed_down = 0;
if(enabled) 
    timer_set(button2_fr, &F_button_down);

}
void F_button(){
  ispressed_up = 0; 
  ispressed_down = 0; 
if(enabled) 
    timer_set(button_fr,&F_button);
}
void init () {
    pinMode(LED_PIN, OUTPUT);
    button_listen(BUT_UP_PIN,1,button_up);
    button_listen(BUT_DOWN_PIN,1,button_down);
    led = 0;
    fr = start_fr;
    bound(fr,min_fr,max_fr)

    timer_set(fr,blink);
    timer_set(buttonboth_fr,&F_button_both);
    timer_set(button2_fr,&F_button_down);
    timer_set(button1_fr,&F_button_up);
    timer_set(button_fr,&F_button);
    
}


