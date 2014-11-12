button_start = {type = "button",id = 1,label = "start", clr_bg = "green"}
button_exit =  {type = "button",id = 2,label = "exit", clr_bg = "red"}
button_config =  {type = "button",id = 3, img_bg = "img/cog.png"}
initial_menu = {}
initial_menu.lay = {  {{type = "img",src = "img/mytitle.png"}}, 
                      {{},button_start,{}},
                      {button_exit,{},button_config}
                   }
                   
--[[
  ##TITULO##
    start
  exit   ©
--]]

main = {w = 800, h = 600, refresh_color="black"}

--[[
no .ceu:

load("config.lua")
// classe lui inicializa um estado sdl(uma janela e um renderer) e mantem um loop de flush e present. 
// emitindo ok entre eles. 
// ela espera um evento quit para terminar.
SDL_Renderer* ren;
var LUI main with 
  varname = "main";
  renderer_ptr = ren;
end;
var LUI_Panel menu with
  varname = "inital_menu";
end;
every main.ok do
  var int i = await menu.click;
  if i == 1 then 
    do Game;
  else/if i == 2 then
    do emit main.quit;
  else/if i == 3 then
    do Config;
  end
end

--]]
