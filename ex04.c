#include <SDL2/SDL.h>
#include <assert.h>


int mouseVSsquare(SDL_Rect* r, int x, int y){
	if(x>r->x && x<(r->x+r->w)) 
		if(y>r->y && y<(r->y+r->h))
			return 1;
	return 0; 
}

void movesquare(SDL_Rect* r, int step,int minx,int maxx,int miny,int maxy,int* mov){
		int t_mov = *mov;
		if(t_mov % 2 == 0){
			if(t_mov > 1)r->x -= step;
			else r->x += step;
		} 
		if(t_mov % 2 != 0){
			if(t_mov > 1)r->y -= step;
			else r->y += step;
		}
		if(r->x <= minx || r->x >= maxx){		
			if(r->y <= miny || r->y >= maxy){
				if(*mov == 3) *mov = 0; 
				else *mov = t_mov+1;
			}
		}	
}
int main (int argc, char* args[])
{
    /* INITIALIZATION */

    int err = SDL_Init(SDL_INIT_EVERYTHING);
    assert(err == 0);

    SDL_Window* window = SDL_CreateWindow("Hello World!",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            640, 480, SDL_WINDOW_SHOWN
                         );
    assert(window != NULL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    assert(renderer != NULL);

    /* EXECUTION */
#define r1minx 200
#define r1miny 200
#define r1maxx (r1minx+50)
#define r1maxy (r1miny+50)

#define r2minx 300
#define r2miny 300
#define r2maxx (r2minx+50)
#define r2maxy (r2miny+50)

#define step1 1
#define step2 1

#define fr 10
    SDL_Rect r1 = { r1minx,r1miny, 50, 50 };
    SDL_Rect r2 = { r2minx,r2miny, 50, 50 };
    int mov1 = 0;
    int mov2 = 0;
    SDL_Event e;
    int state1 = 1;
    int state2 = 1;
    int i = 0;
    int timer1 = 0;
    int start = SDL_GetTicks();
    while (1)
    {
        SDL_PollEvent(&e);

        if (e.type == SDL_QUIT) {
            break;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
		SDL_MouseButtonEvent* me = (SDL_MouseButtonEvent*) &e;
		if(mouseVSsquare(&r1,me->x,me->y)){
		 state1 = !state1;
		}          
		if(mouseVSsquare(&r2,me->x,me->y)){
		 state2 = !state2;
		}          
        }

	int dt = SDL_GetTicks() - start;
        if(timer1>fr){
		if(state1) movesquare(&r1, step1,r1minx,r1maxx,r1miny,r1maxy,&mov1);
        	if(state2) movesquare(&r2, step2,r2minx,r2maxx,r2miny,r2maxy,&mov2);
        	timer1 = 0;
		i++;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderFillRect(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 0xFF,0xFF*sin(3.14*i/180),0x48,0x00);
        SDL_RenderFillRect(renderer, &r1);

        SDL_SetRenderDrawColor(renderer,0xFF*sin(3.14*i/180),0xFF,0x48,0x00);
        SDL_RenderFillRect(renderer, &r2);
        
	SDL_RenderPresent(renderer);
		
	timer1 += dt;
	start += dt;
    }

    /* FINALIZATION */

    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}
