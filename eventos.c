/* Funções de registro: */
#ifndef NUMTIMER
#define NUMTIMER 8
#endif
#ifndef MAX_PIN
#define MAX_PIN 13
#endif
typedef void(*t_callback)(void);

typedef struct Button{
	int pin;
	int pullup;
	t_callback callback;
} button;

typedef struct Timer{
	int fr;
	int time;
	t_callback callback;
} timer;
//static:
    timer timers[NUMTIMER];
    int timer_num = 0;
    int button_num = 0;
    button buttons[MAX_PIN];
    int start;


void button_listen (int pin, int pullup,t_callback callback) {
   pinMode(pin,1);
   if(pullup) digitalWrite(pin,1);
// “pin” passado deve gerar notificações
   buttons[button_num].pin = pin;
   buttons[button_num].pullup = pullup;
   buttons[button_num].callback = callback;
   button_num++;
}

void timer_set (int ms,t_callback callback) {
timers[timer_num].fr = ms;
timers[timer_num].callback = callback;
timers[timer_num].time = 0;
timer_num++;
 // timer deve expirar após “ms” milisegundos
}



/* Programa principal: */
void setup () {
    start = millis();
    m_init();                 // inicialização do usuário
}

void loop () {
    int i;

    for(i=0;i<button_num;i++){
	int val = digitalRead(buttons[i].pin); 
	//if((buttons[i].pullup && !val)||(!buttons[i].pullup && val))
	if(buttons[i].pullup != val)
	{
		(*(buttons[i].callback))();
	}
    }
    for(i=0;i<timer_num;i++){
	if(timers[i].time >= timers[i].fr){
		timers[i].time = 0;
		(*(timers[i].callback))();
	}
    }
    int dt = millis() - start;
    for(i=0;i<timer_num;i++){
      timers[i].time =+ dt;
    }
    start += dt;
}

