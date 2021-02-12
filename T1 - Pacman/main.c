#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//Dijkstra
typedef struct{
    int framePhantomWidth[4],framePhantomHeight[4];
    int texturePhantomWidth[4],texturePhantomHeight[4];
    bool olhos[4];
}phantomInfo;
//controlred


typedef struct _node_{
    int i,j;
    bool ispacman;
    struct _node_ *direct[4];
    struct _node_ *father;
}node;

typedef struct _nodepac_{
    node *key;
    struct _nodepac_ *next;
}nodepac;




//

SDL_Texture *LoadTexture(char filepath[40],SDL_Renderer *renderTarget){
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = SDL_LoadBMP(filepath);
    if(surface==NULL){
        printf("ERROR 1");
    }else{
        texture = SDL_CreateTextureFromSurface(renderTarget,surface);
        if(texture == NULL){
            printf("ERROR 2");
        }
    }
    SDL_FreeSurface(surface);
    return texture;
}
//funcoes
void acender(SDL_Rect*,SDL_Rect*,SDL_Rect*,SDL_Rect*,int,int,SDL_Event*);
void mapa(int);
void controlpacman(SDL_Event*,Mix_Chunk*,Mix_Chunk*,Mix_Chunk*);
void controlphantom(phantomInfo*,SDL_Event*);
void pacmanhome();
void phantomhome();
void pacfriend(SDL_Event*);
void restartgame(SDL_Event*);
void game();
void gameover();
void gamewin();
void acenderFimGame(SDL_Rect*,int,int,SDL_Event*,bool*);
void acenderGameWin(SDL_Rect*,SDL_Rect*,int,int,SDL_Event*,bool*);
int home();
void rec(node*,int,int,nodepac**);
void dir(int,int*,int*);
//variavel de saida (goQuit)
bool win = false;
bool space = true;
bool quit =false;
bool gotocor = false;
bool superonze = false;
bool tocar = true;
bool pilula_effect = false;
bool colisao =false;
bool fim = false;
//resposta da home , 1 - inicie o jogo,2 - tela de high score, 0 - feche o game
int returnhome=0;
//variaveis de evento de mouse sem clique
int mousex;
int mousey;
//variaveis de evento de mouse com clique
bool doubleClick=false;
//variavel de alternancia de cor
bool cor = false;
//variaveis do pacman
int vida =0;
int vidas = 3;
bool morreu = false;
bool inicio = false;  
int pontos = 0;
int fase = 0;
//direcao  fantasmas
int phandir[4] = {1};
int contpontosget = 0;
//variaveis globais
bool friend = false;
bool init = false;
int map[32][29];
int frameTime = 0;
int timePacman = 0;
SDL_Renderer * renderTarget = NULL;
SDL_Texture * item = NULL;
SDL_Texture * fruta[4] = {NULL};
SDL_Texture * pilula = NULL;
SDL_Texture * text = NULL;
SDL_Texture * phantomImage[4] = {NULL};
SDL_Rect pacmanPosition;
SDL_Rect phantomPosition[4];
SDL_Rect phantomRect[4];
SDL_Surface * textSurface = NULL;
Mix_Chunk *start_sound = NULL;
Mix_Chunk *eat_ghost = NULL;
Mix_Chunk *pilula_sound = NULL;
Mix_Chunk *death_sound = NULL;
SDL_Rect pacdead;
int pacmandirecao = 0;
int valor = 0;
int directpac=0;
bool frutas[4] = {false,false,false,false};
bool vidabonus = false;
//mapa red
int map_aux[32][29] = {0};
//

int directpac_ant = 0;

int main(){
    //bool pilula_efect = false;
    //carrega home por meio do goto
    //home:
   
    while(true){
         
        //home();
        if(!returnhome){
            home();
        }
        if(returnhome){
            quit = false;
            game();
        }
        if(quit)
            break;
    }
    //home();
    //gamewin();
    
    SDL_Quit();

    return 0;
  

    
}
void controlpacman(SDL_Event *event,Mix_Chunk *eatpontos,Mix_Chunk *pilula_sound,Mix_Chunk *eat_fruit){
    const int FPS = 60;

    
    int x=0,y=0;
        //event->key.repeat
        switch (event->type){
            case (SDL_KEYDOWN):
                switch (event->key.keysym.sym){
                    
                    case(SDLK_LEFT):             
                    
                        directpac=0;
                        //pacmandirecao =0;   
                    break;
                    case(SDLK_UP):
                      
                        directpac=1;
                        //pacmandirecao =1; 
                    break;  
                    case(SDLK_RIGHT):
                      
                        directpac=2;
                        //pacmandirecao =2;    
                    break;

                    case(SDLK_DOWN):
                     
                        directpac=3;
                        //pacmandirecao =3;    
                    break;


                }
            break;
            
                
        }
                if(directpac==0){
                    x = (pacmanPosition.x<=312.4)?(pacmanPosition.x+10)/24.8+1:pacmanPosition.x/24.8+1.2;
                    y = (pacmanPosition.y<=308.4)?(pacmanPosition.y-14.6)/22.6+0.9:pacmanPosition.y/22.6+0.4;
                }
                else if(directpac==1){
                    x = (pacmanPosition.x<=312.4)?(pacmanPosition.x+10)/24.8+0.6:pacmanPosition.x/24.8+0.9;
                    y = (pacmanPosition.y<=308.4)?(pacmanPosition.y-14.6)/22.6+1.4:pacmanPosition.y/22.6+1.1;
                }else if(directpac==2){
                    x = (pacmanPosition.x<=312.4)?(pacmanPosition.x+10)/24.8+0.1:pacmanPosition.x/24.8+0.1;
                    y = (pacmanPosition.y<=308.4)?(pacmanPosition.y-14.6)/22.6+0.9:pacmanPosition.y/22.6+0.4;
                }else if(directpac==3){
                    x = (pacmanPosition.x<=312.4)?(pacmanPosition.x+10)/24.8+0.6:pacmanPosition.x/24.8+0.9;
                    y = (pacmanPosition.y<=308.4)?(pacmanPosition.y-14.6)/22.6+0.2:pacmanPosition.y/22.6+0.2;
                }

                //movimentação do panman
            if(directpac==0 && map[y][x-1]==1){
                
                directpac=directpac_ant;
            }
            if(directpac==1 && map[y-1][x]==1){
               
                directpac=directpac_ant;
            }
            if(directpac==2 && map[y][x+1]==1){
                
                directpac=directpac_ant;
            }
            if(directpac==3 && map[y+1][x]==1){
                
                directpac=directpac_ant;
            }
           


      
            



            if(directpac==0 && map[y][x-1]!=1){
                
                directpac_ant = directpac;
                pacmandirecao = 0;
                pacmanPosition.x-=4;
                 if(pacmanPosition.x<0 && y==13){
                     pacmanPosition.x = 648;
                 }
                if(map[y][x]==2){
                    contpontosget++;
                    Mix_PlayChannel(-1,eatpontos,0);
                    
                    pontos+= 100;
                    map[y][x] = 0;
                }else if(map[y][x]==3){
                    
                    Mix_PlayChannel(-1,pilula_sound,3);
                    timePacman=0;
                    pilula_effect = true;
                    pontos+=200;
                    map[y][x]=0;
                }else if(map[y][x]==4){
                    Mix_PlayChannel(-1,eat_fruit,0);
                    pontos+=2500;
                    frutas[fase] = true;
                    map[y][x]=0;
                }
            }else if(directpac==1 && pacmanPosition.y-1>=6 && map[y-1][x]!=1){
               
                directpac_ant = directpac;
                pacmandirecao=1;
                pacmanPosition.y-=4;
                if(map[y][x]==2){
                    contpontosget++;
                    Mix_PlayChannel(-1,eatpontos,0);
                    pontos+= 100;
                    map[y][x] = 0;
                }else if(map[y][x]==3){
                     
                    Mix_PlayChannel(-1,pilula_sound,3);
                    timePacman=0;
                    pilula_effect = true;
                    pontos+=200;
                    map[y][x]=0;
                }else if(map[y][x]==4){
                    Mix_PlayChannel(-1,eat_fruit,0);
                    pontos+=2500;
                    frutas[fase] = true;
                    map[y][x]=0;
                }
            }else if(directpac==2  && map[y][x+1]!=1){
               
                directpac_ant = directpac;
                pacmandirecao=2;
                pacmanPosition.x+=4;
                if(pacmanPosition.x>=648 && y==13){
                     pacmanPosition.x = 0;
                }
                if(map[y][x]==2){
                    contpontosget++;
                    Mix_PlayChannel(-1,eatpontos,0);
                    pontos+= 100;
                    map[y][x] = 0;
                }else if(map[y][x]==3){
                    
                    Mix_PlayChannel(-1,pilula_sound,3);
                    timePacman=0;
                    pilula_effect = true;
                    pontos+=200;
                    map[y][x]=0;
                }else if(map[y][x]==4){
                    Mix_PlayChannel(-1,eat_fruit,0);
                    pontos+=2500;
                    frutas[fase] = true;
                    map[y][x]=0;
                }
            }else if(directpac==3 && pacmanPosition.y+1<=648 && map[y+1][x]!=1){
              
                directpac_ant = directpac;
                pacmandirecao=3;
                pacmanPosition.y+=4;
                if(map[y][x]==2){
                    contpontosget++;
                    Mix_PlayChannel(-1,eatpontos,0);
                    pontos+= 100;
                    map[y][x] = 0;
                }else if(map[y][x]==3){
                  
                    Mix_PlayChannel(-1,pilula_sound,3);
                    timePacman=0;
                    pilula_effect = true;
                    pontos+=200;
                    map[y][x]=0;
                }else if(map[y][x]==4){
                    Mix_PlayChannel(-1,eat_fruit,0);
                    pontos+=2500;
                    frutas[fase] = true;
                    map[y][x]=0;
                }
            }
            if(pilula_effect){
                
                timePacman++;
                if(FPS*22/timePacman <=2){
                    pilula_effect = false;
                    timePacman = 0;
                }
            }
                    //238 pontos

        if(!eat_fruit)
            Mix_FreeChunk(eat_fruit);
        if(!pilula_sound)
            Mix_FreeChunk(pilula_sound);
        if(!eatpontos)
            Mix_FreeChunk(eatpontos);
    
    
}
void controlphantom(phantomInfo *phantoms,SDL_Event *event){
    const int FPS = 60;
    int timePhantom = 0;
    int x,y;
    
    for(int i=0;i<4;i++){
        if(vida){
            if(phandir[i]==0){
                x = (phantomPosition[i].x<=312.4)?(phantomPosition[i].x+10)/24.8+1:phantomPosition[i].x/24.8+1.2;
                y = (phantomPosition[i].y<=308.4)?(phantomPosition[i].y-14.6)/22.6+0.9:phantomPosition[i].y/22.6+0.4;
            }else if(phandir[i]==1){
                x = (phantomPosition[i].x<=312.4)?(phantomPosition[i].x+10)/24.8+0.6:phantomPosition[i].x/24.8+0.9;
                y = (phantomPosition[i].y<=308.4)?(phantomPosition[i].y-14.6)/22.6+1.4:phantomPosition[i].y/22.6+1.1;
            }else if(phandir[i]==2){
                x = (phantomPosition[i].x<=312.4)?(phantomPosition[i].x+10)/24.8+0.1:phantomPosition[i].x/24.8+0.1;
                y = (phantomPosition[i].y<=308.4)?(phantomPosition[i].y-14.6)/22.6+0.9:phantomPosition[i].y/22.6+0.4;
            }else if(phandir[i]==3){
                x = (phantomPosition[i].x<=312.4)?(phantomPosition[i].x+10)/24.8+0.6:phantomPosition[i].x/24.8+0.9;
                y = (phantomPosition[i].y<=308.4)?(phantomPosition[i].y-14.6)/22.6+0.2:phantomPosition[i].y/22.6+0.2;
            }
            //x = (phantomPosition[i].x<=312.4)?(phantomPosition[i].x+10)/24.8+1.2:phantomPosition[i].x/24.8+1.2;
            //y = (phantomPosition[i].y<=308.4)?(phantomPosition[i].y-14.6)/22.6+0.9:phantomPosition[i].y/22.6+0.9;
            //atravessar a tela



            if(phantomPosition[i].x<=0 && y==13){
                if(pilula_effect)
                    phantomPosition[i].x = 620;
                else
                    phantomPosition[i].x = 645;
            }else if(phantomPosition[i].x>=646 && y==13){
                if(pilula_effect)
                    phantomPosition[i].x = 5;
                else
                    phantomPosition[i].x = 0;
            }

    
            
                if(init){
                        
                        //fantasma 3 (persegue o pacman) 
                        if(i==3 && !friend && !pilula_effect){

                            
                            if(phantomPosition[i].x < pacmanPosition.x && phandir[i] !=0 && map[y][x+1]!=1){
                                phandir[i] = 2;
                            }else if(phantomPosition[i].x > pacmanPosition.x && phandir[i] !=2 && map[y][x-1]!=1){
                                phandir[i] = 0;
                            }else if(phantomPosition[i].y < pacmanPosition.y && phandir[i] !=1 && map[y+1][x]!=1){
                                phandir[i] = 3;
                            }else if(phantomPosition[i].y > pacmanPosition.y && phandir[i] !=3 && map[y-1][x]!=1){
                                phandir[i] = 1;
                            }
                        }else if(i==2 && !friend && !pilula_effect){//fantasma 2 (se posiciona a 32 pixels de distancia)
                            if(phantomPosition[i].x < pacmanPosition.x+64 && phandir[i] !=0 && map[y][x+1]!=1){
                                phandir[i] = 2;
                            }else if(phantomPosition[i].x > pacmanPosition.x+64 && phandir[i] !=2 && map[y][x-1]!=1){
                                phandir[i] = 0;
                            }else if(phantomPosition[i].y < pacmanPosition.y+64 && phandir[i] !=1 && map[y+1][x]!=1){
                                phandir[i] = 3;
                            }else if(phantomPosition[i].y > pacmanPosition.y+64 && phandir[i] !=3 && map[y-1][x]!=1){
                                phandir[i] = 1;
                            }
                        }else if(i==1 && !friend && !pilula_effect){//fantasma 1 (se posiciona semelhante ao 2)
                            if(phantomPosition[i].x < pacmanPosition.x-32 && phandir[i] !=0 && map[y][x+1]!=1){
                                phandir[i] = 2;
                            }else if(phantomPosition[i].x > pacmanPosition.x-32 && phandir[i] !=2 && map[y][x-1]!=1){
                                phandir[i] = 0;
                            }else if(phantomPosition[i].y < pacmanPosition.y-32 && phandir[i] !=1 && map[y+1][x]!=1){
                                phandir[i] = 3;
                            }else if(phantomPosition[i].y > pacmanPosition.y-32 && phandir[i] !=3 && map[y-1][x]!=1){
                                phandir[i] = 1;
                            }
                        }
                    
                    
                }
            
                            
            //fantasma 0 (aleatorio(ze doidao))
                //direita
            
            if(phandir[i]==2 && map[y][x+1]==1){
                if(map[y-1][x]!=1 && map[y+1][x]!=1){
                    (rand()%2) ? (phandir[i]=1) : (phandir[i]=3);
                    
                }else{
                    (map[y-1][x]!=1) ? (phandir[i]=1) : (phandir[i]=3);
                }
            }
                //esquerda
            if(phandir[i]==0 && map[y][x-1]==1){
                if(map[y-1][x]!=1 && map[y+1][x]!=1){
                    (rand()%2) ? (phandir[i]=1) : (phandir[i]=3);
                    
                }else{
                    (map[y-1][x]!=1) ? (phandir[i]=1) : (phandir[i]=3);
                }
            }
            //baixo
            if(phandir[i]==3 && (map[y+1][x]==1 || phantomPosition[i].y+1>=648)){
                if(map[y][x-1]!=1 && map[y][x+1]!=1){
                    (rand()%2) ? (phandir[i]=0) : (phandir[i]=2);
                    
                }else{
                    (map[y][x-1]!=1) ? (phandir[i]=0) : (phandir[i]=2);
                }
            }
            //cima
            if(phandir[i]==1 && (map[y-1][x]==1 || phantomPosition[i].y-1<=6)){
                if(map[y][x-1]!=1 && map[y][x+1]!=1){
                    (rand()%2) ? (phandir[i]=0) : (phandir[i]=2);
                    
                }else{
                    (map[y][x-1]!=1) ? (phandir[i]=0) : (phandir[i]=2);
                }
            }

                
                        
                
                if(map[y][x]==9){
                    if(map[y][x+1]==9){
                        phandir[i] = 2;
                    }else{
                        phandir[i] = 1;
                    }       
                }
                if(map[y-1][x]==1){
                    init = true;
                }
            if(i==3 && friend){
                pacfriend(event);
            }else{




                //movendo os fantasmas
                if(phandir[i]==0 && map[y][x-1]!=1){
                    if(pilula_effect)
                        phantomPosition[i].x-=(fase==1)?2.5*0.75:(fase==2)?3*0.75:(fase==3)?4*0.75:2*0.75;
                    else
                        phantomPosition[i].x-=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
                }else if(phandir[i]==1 && map[y-1][x]!=1 && phantomPosition[i].y-1>=0){
                    if(pilula_effect)
                        phantomPosition[i].y-=(fase==1)?2.5*0.75:(fase==2)?3*0.75:(fase==3)?4*0.75:2*0.75;
                    else
                        phantomPosition[i].y-=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
                }else if(phandir[i]==2 && map[y][x+1]!=1){
                    if(pilula_effect)
                        phantomPosition[i].x+=(fase==1)?2.5*0.75:(fase==2)?3*0.75:(fase==3)?4*0.75:2*0.75;
                    else
                        phantomPosition[i].x+=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
                }else if(phandir[i]==3 && map[y+1][x]!=1 && phantomPosition[i].y+1<=648){
                    if(pilula_effect)
                        phantomPosition[i].y+=(fase==1)?2.5*0.75:(fase==2)?3*0.75:(fase==3)?4*0.75:2*0.75;
                    else
                        phantomPosition[i].y+=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
                }
            }
            if(pilula_effect)
                timePhantom=0;
        
            timePhantom++;
            if(pilula_effect && FPS/timePhantom >=4){    
                phantomRect[i].y = phantoms->framePhantomHeight[0]*2;
                if(phantoms->olhos[i])
                    phantomRect[i].y = phantoms->framePhantomHeight[0];
                else{
                    phantomRect[i].y = phantoms->framePhantomHeight[0]*2;
                }
            }
            else
                phantomRect[i].y = 0;
            if(pilula_effect && vida && abs(pacmanPosition.x - phantomPosition[i].x)<16 && abs(pacmanPosition.y - phantomPosition[i].y)<16){
                if(phantoms->olhos[i]==false){
                    Mix_PlayChannel(-1,eat_ghost,0);
                    SDL_Delay(200);
                    timePhantom++;
                    pontos+=150;
                    while(FPS/timePhantom ==4){
                        Mix_FreeChunk(eat_ghost);
                        timePhantom = 0;
                    }
                    
                }
                pontos+=200;
                phantoms->olhos[i] = true;
            }
            if(!pilula_effect){
                if(abs(pacmanPosition.x - phantomPosition[i].x)<16 && abs(pacmanPosition.y - phantomPosition[i].y)<16){
                        morreu = true;
                }
                phantoms->olhos[i] = false;
            }
            
        }
        if(!cor){SDL_RenderCopy(renderTarget,phantomImage[0],&phantomRect[i],&phantomPosition[i]);}
        else{
            SDL_RenderCopy(renderTarget,phantomImage[0],&phantomRect[0],&phantomPosition[0]);
            SDL_RenderCopy(renderTarget,phantomImage[1],&phantomRect[1],&phantomPosition[1]);
            SDL_RenderCopy(renderTarget,phantomImage[2],&phantomRect[2],&phantomPosition[2]);
            SDL_RenderCopy(renderTarget,phantomImage[3],&phantomRect[3],&phantomPosition[3]);
        }
        
        
    }
    
    
}
void mapa(int mod){
    SDL_Rect itemPosition;
    itemPosition.w = itemPosition.h = 36;
    SDL_Rect frutaPosition;
    frutaPosition.w = frutaPosition.h = 42;

    SDL_Rect faseFrutaPosition;
    faseFrutaPosition.w = faseFrutaPosition.h = 40;
    faseFrutaPosition.x = 874;faseFrutaPosition.y = 594;
    

    //0 - void,1 - parede,2 - pontos,3 - pilulas
    int i,j;
    
    char mp[32][29] ={{1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1},
                      {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,1},
                      {1,3,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,3,1,1},
                      {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,1},
                      {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1},
                      {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1,1},
                      {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1,1},
                      {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,1},
                      {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,0,1,1,1,0,0,1,1,1,0,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,0,1,1,1,0,0,1,1,1,0,1,1,2,1,1,1,1,1,1,1},
             /*13*/   {0,0,0,0,0,0,0,0,0,0,1,1,0,0,9,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
                      {1,1,1,1,1,1,2,1,1,0,1,1,0,9,9,0,1,1,0,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,0,0,0,0,4,0,0,0,0,0,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1,1},
                      {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1},
                      {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,1},
                      {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,1},
                      {1,3,2,2,1,1,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,1,1,2,2,3,1,1},
                      {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1},
                      {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1},
                      {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,1},
                      {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1},
                      {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1},
                      {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    for(i=0;i<32;i++){
        for(j=0;j<29;j++){
            if(mod){
                map[i][j] = mp[i][j];
            }
            if(map[i][j]==2){
                
                itemPosition.x = (j<=13)?j*24.8-10:j*24.8; 
                itemPosition.y = (i<=13)?i*22.6+14.6:i*22.6;
 
                SDL_RenderCopy(renderTarget, item, NULL, &itemPosition);
            }else if(map[i][j]==3){
                itemPosition.x = (j<=13)?j*24.8-10:j*24.8; 
                itemPosition.y = (i<=13)?i*22.6+14.6:i*22.6;
                if(frameTime<=9){
                SDL_RenderCopy(renderTarget, pilula, NULL, &itemPosition);
                }
            }else if(map[i][j]==4){
                frutaPosition.x = (j<=13)?j*24.8-10:j*24.8; 
                frutaPosition.y = (i<=13)?i*22.6+14.6:i*22.6;
                SDL_RenderCopy(renderTarget, fruta[fase], NULL, &frutaPosition);
            }
        }
    }
    for(int h=0;h<4;h++){
        faseFrutaPosition.x -= 40;
        if(frutas[h])
            SDL_RenderCopy(renderTarget, fruta[h], NULL, &faseFrutaPosition);

    }

}
int home(){
    vidabonus = false;
    fase = 0;
    vidas = 3;
    win = false;
    FILE *arquivo = NULL;
    arquivo = fopen("highscore.txt","r");
    char texto[40];
    valor=0;
    while(fgets(texto,40,arquivo)!=NULL)
    valor = valor*10+(atoi(texto));
    fclose(arquivo);

    Mix_Music *homesound = NULL;
    const int FPS = 60;
    pacmandirecao = 2;
    //phantom directions
    for(int i=0;i<4;i++){
        phandir[i]=0;
    }
    
    SDL_Window * window = NULL;
    SDL_Texture * imageSurface = NULL;
    SDL_Texture * currentImage = NULL;
    SDL_Texture * resetImage = NULL;
    SDL_Texture * twoPlayers = NULL;
    SDL_Texture * textq = NULL;
    SDL_Texture * highScore = NULL;
    SDL_Texture * highNumber = NULL;
    SDL_Texture * texts = NULL;
    //pacman variaveis
    SDL_Rect playerRect;
    pacmanPosition.x = 420.5; 
    pacmanPosition.y = 200;
    pacmanPosition.w = pacmanPosition.h = 48;
    //phantom variaveis
    
    for(int i=0;i<4;i++){
        phantomPosition[i].x = 550+(i*50);
        phantomPosition[i].y = 15;
        phantomPosition[i].w = phantomPosition[i].h = 46;
    }
    
    //reset variaveis
    SDL_Rect resetRect;
    resetRect.x = 360;
    resetRect.y = 500;
    resetRect.w = resetRect.h = 52;
    //two players variaveis
    SDL_Rect twoRect;
    twoRect.x = 490;
    twoRect.y = 500;
    twoRect.w = twoRect.h = 52;

    


    //variaveis do pacman
    int frameWidth,frameHeight;
    int textureWidth,textureHeight;
    //variaveis do phantom
    int framePhantomWidth[4],framePhantomHeight[4];
    int texturePhantomWidth[4],texturePhantomHeight[4];
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0){
        printf("Erro ao inicializar video");
    }else{
        if(TTF_Init()<0)
            printf("Erro ao inicializar função ttf");
        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
            printf("Erro ao inicializar o mixer");
        //carregando audio
        homesound = Mix_LoadMUS("home.mp3");
        Mix_VolumeMusic(80);
        


        window = SDL_CreateWindow("Pac-Man GO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,900,680,SDL_WINDOW_SHOWN);
        renderTarget = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        //carregando em funcao da cor
        corset:
        //carregando pacman em funcao da cor
        if(!cor){currentImage = LoadTexture("pacman0.bmp",renderTarget);}
        else{currentImage = LoadTexture("pacman0_rgb.bmp",renderTarget);}
        //carregando fantasma em função da cor
        if(!cor){phantomImage[0] = LoadTexture("phantom0.bmp",renderTarget);}
        else{
            phantomImage[0] = LoadTexture("phantom0_orange.bmp",renderTarget);
            phantomImage[1] = LoadTexture("phantom0_blue.bmp",renderTarget);
            phantomImage[2] = LoadTexture("phantom0_pink.bmp",renderTarget);
            phantomImage[3] = LoadTexture("phantom0_red.bmp",renderTarget);
        }
        //carregando a imagem
        SDL_QueryTexture(currentImage,NULL,NULL,&textureWidth,&textureHeight);
        frameWidth = textureWidth/2;
        frameHeight = textureHeight/5;
        playerRect.x = playerRect.y = 0;
        playerRect.w = frameWidth;
        playerRect.h = frameHeight;
        
        //carregando phantom imagem
        if(!cor){
            SDL_QueryTexture(phantomImage[0],NULL,NULL,&texturePhantomWidth[0],&texturePhantomHeight[0]);
            framePhantomWidth[0] = texturePhantomWidth[0]/4;
            framePhantomHeight[0] = texturePhantomHeight[0]/3;
            for(int i=0;i<4;i++){
                phantomRect[i].x = framePhantomWidth[0]*2;
                phantomRect[i].y = 0;
                phantomRect[i].w = framePhantomWidth[0];
                phantomRect[i].h = framePhantomHeight[0];
            }
            
        }else{
            
             for(int i=0;i<4;i++)
                SDL_QueryTexture(phantomImage[i],NULL,NULL,&texturePhantomWidth[i],&texturePhantomHeight[i]);
            for(int i=0;i<4;i++){
                framePhantomWidth[i] = texturePhantomWidth[i]/4;
                framePhantomHeight[i] = texturePhantomHeight[i]/3;
                phantomRect[i].x = framePhantomWidth[0]*3;
                phantomRect[i].y = 0;
                phantomRect[i].w = framePhantomWidth[0];
                phantomRect[i].h = framePhantomHeight[0];
            }
        }
        
        //carregando background home em função da cor
        if(!cor){imageSurface = LoadTexture("home.bmp",renderTarget);}
        else{imageSurface = LoadTexture("home_com_rgb.bmp",renderTarget);}
        
        //carregando reset em funcao da cor
        if(!cor){resetImage = LoadTexture("reset.bmp",renderTarget);}
        else{resetImage = LoadTexture("reset_n_rgb.bmp",renderTarget);}
        //carregando twoplayers em função da cor
        if(!friend)
            twoPlayers = LoadTexture("two_players_off.bmp",renderTarget);
        if(friend)
            twoPlayers = LoadTexture("two_players_on.bmp",renderTarget);

        if(gotocor)
            goto fimcorset;
        //carregando fonte
        TTF_Font * font;
        SDL_Color color = {255,255,255,255};
        font = TTF_OpenFont("pacman.ttf",18);
        textSurface = TTF_RenderText_Solid(font,"START",color);
        texts = SDL_CreateTextureFromSurface(renderTarget,textSurface);
        //carregando fonte de quit
        textSurface = TTF_RenderText_Solid(font,"QUIT",color);
        textq = SDL_CreateTextureFromSurface(renderTarget,textSurface);
        //carregando font high score
        textSurface = TTF_RenderText_Solid(font,"High Score",color);
        highScore  =  SDL_CreateTextureFromSurface(renderTarget,textSurface);
        //carregand font hig number
        sprintf(texto,"%d",valor);
        textSurface = TTF_RenderText_Solid(font,texto,color);
        highNumber =  SDL_CreateTextureFromSurface(renderTarget,textSurface);
        //posicionando fonte
        SDL_Rect textRect;
        textRect.x = 160;
        textRect.y = 515;
        SDL_QueryTexture(texts,NULL,NULL,&textRect.w,&textRect.h);
        //botao de quit
        SDL_Rect qtRect;
        qtRect.x = 670;
        qtRect.y = 515;
        SDL_QueryTexture(textq,NULL,NULL,&qtRect.w,&qtRect.h);
        //botao high score
        SDL_Rect hSoreRect;
        hSoreRect.x = 350;
        hSoreRect.y = 15;
        SDL_QueryTexture(highScore,NULL,NULL,&hSoreRect.w,&hSoreRect.h);
        //highscore NUMBER
        SDL_Rect numberSoreRect;
        numberSoreRect.x = 350;
        numberSoreRect.y = 15*3;
        SDL_QueryTexture(highNumber,NULL,NULL,&numberSoreRect.w,&numberSoreRect.h);
        
        
        SDL_Event event;
        int boolean=1;

        while(boolean){
            if(!Mix_PlayingMusic())
                Mix_PlayMusic(homesound,-1);
            while(SDL_PollEvent(&event)!=0){
                if(event.type == SDL_QUIT){
                    boolean=0;
                    quit = true;
                }else if(event.type == SDL_MOUSEMOTION){
                    mousex = event.motion.x;
                    mousey = event.motion.y;
                    acender(&resetRect,&twoRect,&textRect,&qtRect,mousex,mousey,&event);
                }else if(event.type == SDL_MOUSEBUTTONDOWN){
                    acender(&resetRect,&twoRect,&textRect,&qtRect,mousex,mousey,&event);
                    if(cor){
                        gotocor = true;
                        goto corset;
                    }else{
                        gotocor = true;
                        goto corset;
                    }
                    fimcorset:
                    if(quit){
                        
                        Mix_FreeMusic(homesound);
                        SDL_DestroyWindow(window);
                        SDL_DestroyTexture(imageSurface);
                        SDL_DestroyTexture(resetImage);
                        SDL_DestroyTexture(currentImage);
                        SDL_DestroyTexture(twoPlayers);
                        SDL_DestroyTexture(textq);
                        SDL_DestroyTexture(highNumber);
                        SDL_DestroyTexture(highScore);
                        SDL_DestroyTexture(texts);
                        gotocor = false;
                        return 0;
                    }
                    
                }
                    
            }
            frameTime++;
            if(FPS/frameTime==4){
                frameTime=0;
                playerRect.x += frameWidth;
                if(playerRect.x>=textureWidth){
                    playerRect.x =0;
                }
                //muda a direcao da imagem
                playerRect.y =(pacmandirecao==0)?frameHeight*2:(pacmandirecao==1)?
                frameHeight*3:(pacmandirecao==2)?frameHeight*0:frameHeight*1;
                
            }
            pacmanhome();
            phantomhome();
            if(!cor){
                for(int i=0;i<4;i++){
                    phantomRect[i].x = (phandir[i]==0)?framePhantomWidth[0]*2:(phandir[i]==1)?framePhantomWidth[0]*3:
                                    (phandir[i]==2)?framePhantomWidth[0]*0:framePhantomWidth[0]*1;
                }
            }else{
                for(int i=0;i<4;i++){
                    phantomRect[i].x = (phandir[i]==0)?framePhantomWidth[i]*2:(phandir[i]==1)?framePhantomWidth[i]*3:
                                    (phandir[i]==2)?framePhantomWidth[i]*0:framePhantomWidth[i]*1;
                }
            }
            
            SDL_RenderClear(renderTarget);
            SDL_RenderCopy(renderTarget, imageSurface, NULL, NULL);
            SDL_RenderCopy(renderTarget, resetImage,NULL,&resetRect);
            SDL_RenderCopy(renderTarget,twoPlayers,NULL,&twoRect);
            SDL_RenderCopy(renderTarget,currentImage,&playerRect,&pacmanPosition);
            if(!cor){
                for(int i=0;i<4;i++){
                    SDL_RenderCopy(renderTarget,phantomImage[0],&phantomRect[i],&phantomPosition[i]);
                }
            }else{
                for(int i=0;i<4;i++){
                   SDL_RenderCopy(renderTarget,phantomImage[0],&phantomRect[0],&phantomPosition[0]);
                   SDL_RenderCopy(renderTarget,phantomImage[1],&phantomRect[1],&phantomPosition[1]);
                   SDL_RenderCopy(renderTarget,phantomImage[2],&phantomRect[2],&phantomPosition[2]);
                   SDL_RenderCopy(renderTarget,phantomImage[3],&phantomRect[3],&phantomPosition[3]);
                }
            }
            SDL_RenderCopy(renderTarget,texts,NULL,&textRect);
            SDL_RenderCopy(renderTarget,textq,NULL,&qtRect);
            SDL_RenderCopy(renderTarget,highScore,NULL,&hSoreRect);
            SDL_RenderCopy(renderTarget,highNumber,NULL,&numberSoreRect);
            SDL_RenderPresent(renderTarget);
        }
        

    }
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(imageSurface);
    SDL_DestroyTexture(resetImage);
    SDL_DestroyTexture(currentImage);
    SDL_DestroyTexture(twoPlayers);
    SDL_DestroyTexture(textq);
    SDL_DestroyTexture(highNumber);
    SDL_DestroyTexture(highScore);
    SDL_DestroyTexture(texts);
    Mix_FreeMusic(homesound);
    
    Mix_Quit();
    SDL_Quit();
    
    return 0;
}
void pacmanhome(){

    if(pacmanPosition.x>=680){
        
        pacmandirecao=0;
    }
    if(pacmanPosition.x<=160){
        
        pacmandirecao=2;
    }

    if(pacmandirecao==2){
        if(abs(pacmanPosition.x-mousex)<=50 && abs(pacmanPosition.y-mousey)<=50){
            
            pacmanPosition.x+=8;
        

        }else{
            pacmanPosition.x+=2;
        }
        
    }        
    if(pacmandirecao==0){
        if(abs(pacmanPosition.x-mousex)<=50 && abs(pacmanPosition.y-mousey)<=50){
           
            pacmanPosition.x-=8;
            
        }else{
            pacmanPosition.x-=2;
        }
        
    }
        
}
void phantomhome(){
    for(int i=0;i<4;i++){

        if(phantomPosition[i].x!=550){
            phandir[i]=0;
        }else if(phantomPosition[i].x==550 && phantomPosition[i].y<=100){
            phandir[i]=3;
        }else if(phantomPosition[i].y>100){
            phandir[i]=0;
        }
        if(phantomPosition[i].x<290){
            phandir[i]=1;
        }
        if(phandir[i]==1 && phantomPosition[i].y<17){
            phandir[i]=0; 
        }
        if(phandir[i]==0 && phantomPosition[i].x<-5){
            phantomPosition[i].x=900;
        }

        

        //
        if(phandir[i]==0)
            phantomPosition[i].x-=2;
        else if(phandir[i]==1)
            phantomPosition[i].y-=2;
        else if(phandir[i]==2)
            phantomPosition[i].x+=2;
        else if(phandir[i]==3)
            phantomPosition[i].y+=2;
    }

}
void acender(SDL_Rect *reset,SDL_Rect *twoPlayer,SDL_Rect *textStart,SDL_Rect *textQuit,int x,int y,SDL_Event *event){
    if(x>346 && x<420 && y>480 && y<550){
        reset->w = 62;
        reset->h = reset->w;
        if(event->type == SDL_MOUSEBUTTONDOWN)
            if(event->button.clicks==1){
                if(!cor)
                    cor = true;
                else
                    cor = false;
            }
        tocar = false;
            
    }else{
        reset->w = 52;
        reset->h = reset->w;
    }
    //botao twoplayer
    if(x>476 && x<550 && y>480 && y<550){
        twoPlayer->w = 62;
        twoPlayer->h = twoPlayer->w;
        if(event->type == SDL_MOUSEBUTTONDOWN)
            if(event->button.clicks==1){
               friend = (!friend)?true:false;
            }

    }else{
        twoPlayer->w = 52;
        twoPlayer->h = twoPlayer->w;
    }
    //botao start
    if(x>156 && x<290 && y>486 && y<550){
        textStart->w = 90+90/6+6;
        textStart->h = 24+24/6+2;
        if(event->type == SDL_MOUSEBUTTONDOWN)
            if(event->button.clicks==2){
                returnhome = 1;
               
                quit = true;
            }
                
    }else{
        textStart->w = 90;
        textStart->h = 24;
    }
    //botao quit
    if(x>646 && x<780 && y>486 && y<550){
        textQuit->w = 90+90/6+6;
        textQuit->h = 24+24/6+2;
           
        if(event->type == SDL_MOUSEBUTTONDOWN)
            if(event->button.clicks==2)
                quit =true;
                
               
                
                
    }else{
        textQuit->w = 90;
        textQuit->h = 24;
    }
    
}
void restartgame(SDL_Event *event){
    
    if(pontos>valor){
            FILE *arquivo;
            char texto[40];
            arquivo = fopen("highscore.txt","w");
            sprintf(texto,"%d",pontos);
            fprintf(arquivo,"%s",texto);
            fclose(arquivo);
    }




    int FPS = 60;
    int frame = 0;
    SDL_Texture * imageSurface = NULL;
    SDL_Texture * currentImage = NULL;
    int frameWidth,frameHeight;
    int textureWidth,textureHeight;
    if(!cor){
        currentImage = LoadTexture("pacman1.bmp",renderTarget);
        SDL_QueryTexture(currentImage,NULL,NULL,&textureWidth,&textureHeight);
        imageSurface = LoadTexture("background.bmp",renderTarget);
    }else{
        currentImage = LoadTexture("pacman1_rgb.bmp",renderTarget);
        SDL_QueryTexture(currentImage,NULL,NULL,&textureWidth,&textureHeight);
        imageSurface = LoadTexture("background_rgb.bmp",renderTarget);
    }
  

    frameWidth = textureWidth/4;
    frameHeight = textureHeight;

    pacdead.x = pacdead.y = 0;
    pacdead.w = frameWidth;
    pacdead.h = frameHeight;


    superonze = false;
    start_sound = (superonze)?Mix_LoadWAV("superonze0.wav"):Mix_LoadWAV("pacman_start.wav");
    
   
   
        
    if(morreu){
        death_sound = Mix_LoadWAV("pacman_death.wav");
        pacmandirecao = 0;
        Mix_Pause(-1);
        vidas--;
        morreu = false;
        Mix_Resume(-1);
        Mix_PlayChannel(-1,death_sound,0);
        while(1){
            frame++;
            if(FPS/frame==4){
                frame=0;
                pacdead.x += frameWidth;
                if(pacdead.x>=textureWidth){
                    pacdead.x =0;
                    break;
                }    
            }
            SDL_RenderClear(renderTarget);
            SDL_RenderCopy(renderTarget,imageSurface,NULL,NULL);
            SDL_RenderCopy(renderTarget,currentImage,&pacdead,&pacmanPosition);
            SDL_RenderPresent(renderTarget);
            
        }
        







        pacmanPosition.x = 328; 
        pacmanPosition.y = 494;
        for(int i =0;i<4;i++){
            phantomPosition[i].x = 280+(i*46);
            phantomPosition[i].y = 300;
        }
        phantomPosition[3].x = 325;
        phantomPosition[3].y = 232;
        
    }
    if(morreu)
        Mix_FreeChunk(death_sound);
    
    if(inicio){
        contpontosget = 0;
        Mix_Pause(-1);
        Mix_Resume(-1);
        Mix_PlayChannel(-1,start_sound,0);
        (superonze)?SDL_Delay(11500):SDL_Delay(4400);
        if(!vidas)
            vidas = 3;
        vida = vidas;
        inicio = false;
        pontos = pontos;
        pacmandirecao = 0;
    

        
    }
    
    if(contpontosget==238){
        pacmanPosition.x = 328; 
        pacmanPosition.y = 494;
        for(int i =0;i<4;i++){
            phantomPosition[i].x = 280+(i*46);
            phantomPosition[i].y = 300;
        }
        phantomPosition[3].x = 325;
        phantomPosition[3].y = 232;
        pilula_effect = false;
        contpontosget = 0;
        inicio = true;
        fase++;mapa(1);
        
        if(vidas<3 && fase==3 && !vidabonus && frutas[0] && frutas[1] && frutas[2]){
            vidabonus = true;
            vidas++;
        }
        if(fase==4)
            win = true;


        
        
    }
        
        SDL_PollEvent(event);
        if(space){
            switch (event->type){
                case (SDL_KEYDOWN):
                    
                    switch (event->key.keysym.sym){
                        case(SDLK_SPACE):
                            inicio =1;
                            space = false;
                        break;
                    }

                break;
            }
        }
    SDL_DestroyTexture(imageSurface);
    SDL_DestroyTexture(currentImage);
    Mix_FreeChunk(start_sound);
   
    
}
void pacfriend(SDL_Event *event){
    int x=0,y=0; 
    switch (event->type){
        case (SDL_KEYDOWN):
            switch (event->key.keysym.sym){
                
                    case(SDLK_a):
                        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+1:phantomPosition[3].x/24.8+1.2;
                        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+0.9:phantomPosition[3].y/22.6+0.4;                     
                        phandir[3] =0;   
                    break;
                    case(SDLK_w):
                        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+0.6:phantomPosition[3].x/24.8+0.9;
                        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+1.4:phantomPosition[3].y/22.6+1.1;
                        phandir[3] =1; 
                    break;  
                    case(SDLK_d):
                        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+0.1:phantomPosition[3].x/24.8+0.1;
                        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+0.9:phantomPosition[3].y/22.6+0.4;
                        phandir[3] =2;    
                    break;
                    
                    case(SDLK_s):
                        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+0.6:phantomPosition[3].x/24.8+0.9;
                        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+0.2:phantomPosition[3].y/22.6+0.2;
                        phandir[3] =3;    
                    break;
                    
                                   
                     
            }
        break;
    
    }
    if(phandir[3]==0){
        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+1:phantomPosition[3].x/24.8+1.2;
        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+0.9:phantomPosition[3].y/22.6+0.4;
    }
    else if(phandir[3]==1){
        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+0.6:phantomPosition[3].x/24.8+0.9;
        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+1.4:phantomPosition[3].y/22.6+1.1;
    }else if(phandir[3]==2){
        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+0.1:phantomPosition[3].x/24.8+0.1;
        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+0.9:phantomPosition[3].y/22.6+0.4;
    }else if(phandir[3]==3){
        x = (phantomPosition[3].x<=312.4)?(phantomPosition[3].x+10)/24.8+0.6:phantomPosition[3].x/24.8+0.9;
        y = (phantomPosition[3].y<=308.4)?(phantomPosition[3].y-14.6)/22.6+0.2:phantomPosition[3].y/22.6+0.2;
    }
        
             
    //movimentação do panman
        if(phandir[3]==0 && map[y][x-1]!=1){
             phantomPosition[3].x-=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
             if(phantomPosition[3].x<0 && y==13)
                 phantomPosition[3].x = 648; 
        }else if(phandir[3]==1 && phantomPosition[3].y-1>=6 && map[y-1][x]!=1){
            phantomPosition[3].y-=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
        }else if(phandir[3]==2  && map[y][x+1]!=1){
            phantomPosition[3].x+=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
            if(phantomPosition[3].x>=648 && y==13)
                 phantomPosition[3].x = 0;
        }else if(phandir[3]==3 && phantomPosition[3].y+1<=648 && map[y+1][x]!=1){
            phantomPosition[3].y+=(fase==1)?2.5:(fase==2)?3:(fase==3)?4:2;
        }
}
void game(){
    //returnhome =1;
            pacmandirecao = 0;
            
            const int FPS = 60;
            int width=900;/*680*///900;
            int height=680;/*662*///680;

            SDL_Window * window= NULL; //janela
            SDL_Texture * imageSurface = NULL;
            SDL_Texture * currentImage = NULL;
            
            //phatom variaveis
            
            //216 13
            for(int i =0;i<4;i++){
                phantomPosition[i].x = 280+(i*46);
                phantomPosition[i].y = 300;
                phantomPosition[i].w = phantomPosition[i].h = 41;
            }
            //o que persegue tem que ficar fora
            phantomPosition[3].x = 325;
            phantomPosition[3].y = 232;
            //life pacman
            typedef struct{
                SDL_Rect paclife;
                int vidas;
            }lifePacman;

            typedef struct{
                int x1;
                int x2;
                int x3;
                int x4;
            }distance;
            //distancia entre uma vida e outra
            distance vidapac;
            vidapac.x1 = 720;
            vidapac.x2 = 770;
            vidapac.x3 = 820;




            //pacman variaveis
            lifePacman vidaImg;
            vidaImg.vidas = 3;
            vidaImg.paclife.x = 700;
            vidaImg.paclife.y = 520;
            vidaImg.paclife.w = vidaImg.paclife.h = 48;
            //
            SDL_Rect playerRect;
            pacmanPosition.x = 328; 
            pacmanPosition.y = 494;
            pacmanPosition.w = pacmanPosition.h = 41;//42;
            //fantasmas
            
            
            phantomInfo phantoms;
            phantoms.olhos[0] = false;
            phantoms.olhos[1] = false;
            phantoms.olhos[2] = false;
            phantoms.olhos[3] = false;
            
            //pacman variaveis
            int frameWidth,frameHeight;
            int textureWidth,textureHeight;
            

            if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0){
                printf("Erro ao inicializar video| audio");
            }else{
                if(TTF_Init()<0){
                    printf("Erro ao inicializar função ttf");
                }
                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
                    printf("Erro ao inicializar o mixer");
                //carregando sons
                
                Mix_Chunk *game_sound = NULL;
                
                Mix_Chunk *eat_pontos_sound = NULL;
                Mix_Chunk *eat_fruit_sound = NULL;
                Mix_Chunk *extrapac_sound = NULL;
                
                //
                start_sound = Mix_LoadWAV("pacman_start.wav");
                
                eat_pontos_sound = Mix_LoadWAV("pacman_eatpontos.wav");Mix_VolumeChunk(eat_pontos_sound,70);
                eat_fruit_sound = Mix_LoadWAV("pacman_eatfruit.wav");Mix_VolumeChunk(eat_fruit_sound,70);
                pilula_sound = Mix_LoadWAV("pacman_pilulaefecct.wav");Mix_VolumeChunk(pilula_sound,70);
                extrapac_sound = Mix_LoadWAV("pacman_extrapac.wav");Mix_VolumeChunk(extrapac_sound,70);
                eat_ghost = Mix_LoadWAV("eat_ghost.wav");Mix_VolumeChunk(eat_ghost,70);
                game_sound = Mix_LoadWAV("game.wav");Mix_VolumeChunk(game_sound,70);
                //
                
                    Mix_PlayChannel(-1,game_sound,1000);

                
                window = SDL_CreateWindow("Pac-Man GO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
                renderTarget = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                //pacman
                if(!cor){currentImage = LoadTexture("pacman0.bmp",renderTarget);}
                else{currentImage = LoadTexture("pacman0_rgb.bmp",renderTarget);}
                SDL_QueryTexture(currentImage,NULL,NULL,&textureWidth,&textureHeight);
                frameWidth = textureWidth/2;
                frameHeight = textureHeight/5;

                playerRect.x = playerRect.y = 0;
                playerRect.w = frameWidth;
                playerRect.h = frameHeight;

                //fantasmas
                if(!cor){
                    phantomImage[0] = LoadTexture("phantom0.bmp",renderTarget);
                    SDL_QueryTexture(phantomImage[0],NULL,NULL,&phantoms.texturePhantomWidth[0],&phantoms.texturePhantomHeight[0]);
                    phantoms.framePhantomWidth[0] = phantoms.texturePhantomWidth[0]/4;
                    phantoms.framePhantomHeight[0] = phantoms.texturePhantomHeight[0]/3;
                    for(int i=0;i<4;i++){
                        phantomRect[i].x = phantoms.framePhantomWidth[0]*3;
                        phantomRect[i].y = 0;
                        phantomRect[i].w = phantoms.framePhantomWidth[0];
                        phantomRect[i].h = phantoms.framePhantomHeight[0];
                    }
                }else{
                    phantomImage[0] = LoadTexture("phantom0_orange.bmp",renderTarget);
                    phantomImage[1] = LoadTexture("phantom0_blue.bmp",renderTarget);
                    phantomImage[2] = LoadTexture("phantom0_pink.bmp",renderTarget);
                    phantomImage[3] = LoadTexture("phantom0_red.bmp",renderTarget);
                    for(int i=0;i<4;i++)
                        SDL_QueryTexture(phantomImage[i],NULL,NULL,&phantoms.texturePhantomWidth[i],&phantoms.texturePhantomHeight[i]);
                    for(int i=0;i<4;i++){
                        phantoms.framePhantomWidth[i] = phantoms.texturePhantomWidth[i]/4;
                        phantoms.framePhantomHeight[i] = phantoms.texturePhantomHeight[i]/3;
                        phantomRect[i].x = phantoms.framePhantomWidth[0]*3;
                        phantomRect[i].y = 0;
                        phantomRect[i].w = phantoms.framePhantomWidth[0];
                        phantomRect[i].h = phantoms.framePhantomHeight[0];
                    }
                }
                
                //
                //carregando o backgorund em funcao da cor
                if(!cor){imageSurface = LoadTexture("background.bmp",renderTarget);}
                else{imageSurface = LoadTexture("background_rgb.bmp",renderTarget);}
                //carregando os pontos em funcao da cor
                if(!cor){item = LoadTexture("item.bmp",renderTarget);}
                else{item = LoadTexture("item_rgb.bmp",renderTarget);}
                //carregando a pilula em funcao da cor
                if(!cor){pilula = LoadTexture("itemp.bmp",renderTarget);}
                else{pilula = LoadTexture("itemp_rgb.bmp",renderTarget);}
                //carregando as frutas em funcao da cor
                if(!cor){
                    for(int i=0;i<4;i++){
                        char name[] = {0};
                        sprintf(name,"fruta%d",i);
                        strcat(name,".bmp");
                        fruta[i] = LoadTexture(name,renderTarget);
                    }
                }else{
                    for(int i=0;i<4;i++){
                        char name[] = {0};
                        sprintf(name,"fruta%d",i);
                        strcat(name,"_rgb.bmp");
                        fruta[i] = LoadTexture(name,renderTarget);
                    }
                }


                mapa(1);
                //texto
                int boo = 0;
                TTF_Font * font;
                SDL_Color color = {255,255,255,255};
                font = TTF_OpenFont("pacman.ttf",18);
                char textPontos[30] = {0};
                //carregando pontos
                ttf:
                sprintf(textPontos,"%d",pontos);
                textSurface = TTF_RenderText_Solid(font,textPontos,color);
                text = SDL_CreateTextureFromSurface(renderTarget,textSurface);
                //liberando o ponteiro
                SDL_FreeSurface(textSurface);
                textSurface = NULL;
                //
                SDL_Rect textRect;
                textRect.x = 715;
                textRect.y = 70;
                SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
                if(boo){
                    goto saida;
                }
        
                int boolean = 1;
                SDL_Event event;
                while (boolean){
                    while(SDL_PollEvent(&event)!=0){
                        if(event.type == SDL_QUIT || !vidas){
                            boolean=0;
                            returnhome = 0;
                            Mix_FreeChunk(game_sound);
                            Mix_FreeChunk(eat_ghost);
                            Mix_FreeChunk(eat_pontos_sound);
                            Mix_FreeChunk(eat_fruit_sound);
                            Mix_FreeChunk(pilula_sound);
                            Mix_FreeChunk(death_sound);
                            Mix_FreeChunk(extrapac_sound);
                            break;  
                        }
                    }
                    
                    frameTime++;
                    if(FPS/frameTime==4){
                        frameTime=0;
                        playerRect.x += frameWidth;
                        if(playerRect.x>=textureWidth){
                            playerRect.x =0;
                        }
                        //muda a direcao da imagem
                        playerRect.y =(pacmandirecao==0)?frameHeight*2:(pacmandirecao==1)?frameHeight*3:(pacmandirecao==2)?frameHeight*0:frameHeight*1;
                        if(!cor){
                            for(int i=0;i<4;i++){
                                phantomRect[i].x = (phandir[i]==0)?phantoms.framePhantomWidth[0]*2:(phandir[i]==1)?phantoms.framePhantomWidth[0]*3:
                                                (phandir[i]==2)?phantoms.framePhantomWidth[0]*0:phantoms.framePhantomWidth[0]*1;
                            }
                        }else{
                            for(int i=0;i<4;i++){
                            phantomRect[i].x = (phandir[i]==0)?phantoms.framePhantomWidth[i]*2:(phandir[i]==1)?phantoms.framePhantomWidth[i]*3:
                                            (phandir[i]==2)?phantoms.framePhantomWidth[i]*0:phantoms.framePhantomWidth[i]*1;
                            }
                        }
                        
                    }

                
                    

                    //pacman
                    SDL_RenderClear(renderTarget);
                    restartgame(&event);

                    if(win){
                            boolean=0;
                            returnhome = 0;
                            Mix_FreeChunk(game_sound);
                            Mix_FreeChunk(eat_ghost);
                            Mix_FreeChunk(eat_pontos_sound);
                            Mix_FreeChunk(eat_fruit_sound);
                            Mix_FreeChunk(pilula_sound);
                            Mix_FreeChunk(death_sound);
                            Mix_FreeChunk(extrapac_sound);
                            break;  
                    }
                    SDL_RenderCopy(renderTarget, imageSurface, NULL, NULL);
                    if(!vidas)
                        break;
                    if(vida)
                        controlpacman(&event,eat_pontos_sound,pilula_sound,eat_fruit_sound);
                    mapa(0);
                    boo=1;
                    goto ttf;
                    saida:
                    //mostrar pacman
                    if(vida || inicio)
                        SDL_RenderCopy(renderTarget,currentImage,&playerRect,&pacmanPosition);
                    
                    vidaImg.vidas = vidas;
                    for(int i =0;i<vidaImg.vidas;i++){
                        vidaImg.paclife.x = (i==0)?vidapac.x1:(i==1)?vidapac.x2:vidapac.x3;
                        SDL_RenderCopy(renderTarget,currentImage,&playerRect,&vidaImg.paclife);
                    }
                    
                        
                    
                    controlphantom(&phantoms,&event);
                    SDL_RenderCopy(renderTarget,text,NULL,&textRect);
                    SDL_RenderPresent(renderTarget);
                }
                if(!vidas)
                    Mix_FreeChunk(game_sound);
            }
            

            SDL_DestroyWindow(window);
            SDL_DestroyTexture(text);
            
            text = NULL;
            if(!vidas){
                vidas = 3;
                pontos = 0;
                fase = 0;
                gameover();
            }
            if(win)
                gamewin();
}
void gameover(){


    frutas[0]=false;
    frutas[1]=false;
    frutas[2]=false;
    frutas[3]=false;




    contpontosget = 0;
    Mix_Music *homesound = NULL;
    bool click = false;
    SDL_Event event;
    SDL_Window * window = NULL;
    SDL_Texture * imageSurface = NULL;
    SDL_Texture * press = NULL;
    //linha dinamica
    SDL_Texture * back = NULL;
    //
    SDL_Texture * toReturnHome = NULL;

    window = SDL_CreateWindow("Pac-Man GO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,900,680,SDL_WINDOW_SHOWN);
    renderTarget = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    imageSurface = LoadTexture("gameover.bmp",renderTarget);
    TTF_Init();
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    homesound = Mix_LoadMUS("gameover.mp3");
    TTF_Font * font;
    SDL_Color color = {255,255,255,255};
    font = TTF_OpenFont("pacman.ttf",18);
    textSurface = TTF_RenderText_Solid(font,"Press",color);
    press = SDL_CreateTextureFromSurface(renderTarget,textSurface);
    textSurface = TTF_RenderText_Solid(font,"back",color);
    back = SDL_CreateTextureFromSurface(renderTarget,textSurface);
    textSurface = TTF_RenderText_Solid(font,"to return home :( .",color);
    toReturnHome = SDL_CreateTextureFromSurface(renderTarget,textSurface);

    
    SDL_Rect textRect[3];
    
    
    textRect[0].x = 190;textRect[1].x = 310;textRect[2].x = 410;
    textRect[0].y = 460;textRect[1].y = 460;textRect[2].y = 460;
    

    SDL_QueryTexture(press,NULL,NULL,&textRect[0].w,&textRect[0].h);
    SDL_QueryTexture(back,NULL,NULL,&textRect[1].w,&textRect[1].h);
    SDL_QueryTexture(toReturnHome,NULL,NULL,&textRect[2].w,&textRect[2].h);
    bool boolean = true;
    
    while(boolean){
        if(!Mix_PlayingMusic())
                Mix_PlayMusic(homesound,-1);
        while(SDL_PollEvent(&event)!=0){
            if(event.type == SDL_QUIT){
                boolean = false;
                returnhome = 0;
                break;
            }else if(event.type == SDL_MOUSEMOTION){
                mousex = event.motion.x;
                mousey = event.motion.y;
                acenderFimGame(&textRect[1],mousex,mousey,&event,&click);
            }else if(event.type == SDL_MOUSEBUTTONDOWN){
                acenderFimGame(&textRect[1],mousex,mousey,&event,&click);
                if(click){
                    boolean = false;
                    returnhome = 0;
                    break;
                }
            }



            SDL_RenderClear(renderTarget);
            SDL_RenderCopy(renderTarget, imageSurface, NULL, NULL);
            SDL_RenderCopy(renderTarget,press,NULL,&textRect[0]);
            SDL_RenderCopy(renderTarget,back,NULL,&textRect[1]);
            SDL_RenderCopy(renderTarget,toReturnHome,NULL,&textRect[2]);
            SDL_RenderPresent(renderTarget);
        }
    }
    Mix_FreeMusic(homesound);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(press);
    SDL_DestroyTexture(imageSurface);
    SDL_DestroyTexture(back);
    SDL_DestroyTexture(toReturnHome);
}
void acenderFimGame(SDL_Rect *back,int x,int y,SDL_Event *event,bool *click){
   if(x>300 && x<400 && y>440 && y<508){
        back->w = 72+72/6+6;
        back->h = 24+24/6+2;
       
        if(event->type == SDL_MOUSEBUTTONDOWN){
            if(event->button.clicks==1){
                *click = true; 
            }
        }     
    }else{
        back->w = 72;
        back->h = 24;
    }
}
void gamewin(){


    contpontosget = 0;
    frutas[0]=false;
    frutas[1]=false;
    frutas[2]=false;
    frutas[3]=false;
    
    bool click = false;
    cor = true;
    SDL_Event event;
    bool boolean = true;
    Mix_Music *homesound = NULL;
    SDL_Window * window = NULL;
    SDL_Texture * imageSurface = NULL;
    SDL_Texture * back = NULL;
    SDL_Texture * quit = NULL;
    SDL_Texture * txtpontos = NULL;
    //SDL_Texture
    //900 680
    window = SDL_CreateWindow("Pac-Man GO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,960,540,SDL_WINDOW_SHOWN);
    renderTarget = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!cor)
        imageSurface = LoadTexture("gamewin.bmp",renderTarget);
    else
        imageSurface = LoadTexture("gamewin_rgb.bmp",renderTarget);

    //carregando musica
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    homesound = Mix_LoadMUS("end.mp3");
    
    //carregando texto
    TTF_Init();
    TTF_Font * font;
    SDL_Color color = {255,255,255,255};
    font = TTF_OpenFont("pacman.ttf",16);
    textSurface = TTF_RenderText_Solid(font,"Go home",color);
    back = SDL_CreateTextureFromSurface(renderTarget,textSurface);
    textSurface = TTF_RenderText_Solid(font,"Quit",color);
    quit = SDL_CreateTextureFromSurface(renderTarget,textSurface);

    char text[30] = {0};
    sprintf(text,"Score: %d",pontos);
    font = TTF_OpenFont("pacman.ttf",18);
    textSurface = TTF_RenderText_Solid(font,text,color);
    txtpontos = SDL_CreateTextureFromSurface(renderTarget,textSurface);


    //go home
    SDL_Rect textRect[3];
    textRect[0].x = 40;
    textRect[0].y = 480;
    SDL_QueryTexture(back,NULL,NULL,&textRect[0].w,&textRect[0].h);
    //quit
    textRect[1].x = 840;
    textRect[1].y = 480;
    SDL_QueryTexture(quit,NULL,NULL,&textRect[1].w,&textRect[1].h);
    //pontos
    textRect[2].x = 310;
    textRect[2].y = 32;
    SDL_QueryTexture(txtpontos,NULL,NULL,&textRect[2].w,&textRect[2].h);
    
    while(boolean){
        if(!Mix_PlayingMusic())
                Mix_PlayMusic(homesound,-1);
        while(SDL_PollEvent(&event)!=0){
            if(event.type == SDL_QUIT){
                boolean = false;
                returnhome = 0;
                break;
            }else if(event.type == SDL_MOUSEMOTION){
                mousex = event.motion.x;
                mousey = event.motion.y;
                acenderGameWin(&textRect[0],&textRect[1],mousex,mousey,&event,&click);
            }else if(event.type ==  SDL_MOUSEBUTTONDOWN){
                mousex = event.motion.x;
                mousey = event.motion.y;
                acenderGameWin(&textRect[0],&textRect[1],mousex,mousey,&event,&click);
                if(click){
                    boolean = false;
                    returnhome = 0;
                    break;
                }
            }
                
            SDL_RenderClear(renderTarget);
            SDL_RenderCopy(renderTarget, imageSurface, NULL, NULL);
            SDL_RenderCopy(renderTarget,back,NULL,&textRect[0]);
            SDL_RenderCopy(renderTarget,quit,NULL,&textRect[1]);
            SDL_RenderCopy(renderTarget,txtpontos,NULL,&textRect[2]);
            SDL_RenderPresent(renderTarget);
        }
    }
    SDL_DestroyWindow(window);
    Mix_FreeMusic(homesound);
    return;
}
void acenderGameWin(SDL_Rect *acao_home,SDL_Rect *acao_quit,int x,int y,SDL_Event *event,bool *click){
    //home
    if(x>36 && x<162 && y>470 && y<512){
        acao_home->w = 112+112/6+6;
        acao_home->h = 21+21/6+2;
        if(event->type == SDL_MOUSEBUTTONDOWN)
            if(event->button.clicks==1)
                *click = true;
                
    }else{
        acao_home->w = 112;
        acao_home->h = 21;
    }
    //quit
    if(x>828 && x<912 && y>468 && y<512){
        acao_quit->w = 65+65/6+6;
        acao_quit->h = 21+21/6+2;
        if(event->type == SDL_MOUSEBUTTONDOWN)
            if(event->button.clicks==2){
                *click = true;
                quit = true;
            }
    }else{
        acao_quit->w = 65;
        acao_quit->h = 21;
    }
}
void controlRed(SDL_Rect *phantoms,int x,int y){
    
    map_aux[phantoms->y][phantoms->x] = 1;
    nodepac * rootPac = 0; 
    node * root = (node*)malloc(sizeof(node));
    nodepac *p;
    root->ispacman = false;
    root->father = 0;
    root->i = phantoms->x;
    root->j = phantoms->y;
    rec(root,x,y,&rootPac);
    while(rootPac->next!=0){
        p = rootPac;
                
    }


}
void rec(node *p,int x,int y,nodepac **npac){
    for(int k=0;k<4;k++){
        int di=0,dj=0;
        dir(k,&di,&dj);
        
        if(map[p->j+di][p->i+dj]!=1 && map_aux[p->j+di][p->i+dj]!=1){
            //node * dir = (node*)malloc(sizeof(node));
            p->direct[k] = (node*)malloc(sizeof(node)); 
            p->direct[k]->i = p->i+di;
            p->direct[k]->j = p->j+dj;
            p->direct[k]->father = p;
            //condicao a mais, se achar o pacman
            if(abs(p->i*x - pacmanPosition.x)<5 && abs(p->j*y - pacmanPosition.y)<5){
                nodepac * myPac = (nodepac*)malloc(sizeof(nodepac));
                (*npac)->next = p->direct[k];
                myPac->key = p->direct[k];
                myPac->next = (*npac);
                (*npac)->next = p->direct[k];                
            }else{
                map_aux[p->j][p->i] = 1;
                rec(p->direct[k],x,y,npac);
            }
            
            //se o pacman for falso executa a funcao
                
        }
    }
}
void dir(int pos,int *di,int *dj){
    switch(pos){
        case 0://left
        *di = 0;
        *dj = -1;
        break;
        case 1://up
        *di = -1;
        *dj = 0;
        break;
        case 2://right
        *di = 0;
        *dj = 1;
        break;
        case 3://down
        *di = 1;
        *dj = 0;
        break; 
    }

    
}
