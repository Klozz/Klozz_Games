/* Naves GAME
 * Autor: Carlos Jes�s AKA KLOZZ <TeamMEX@XDA>
 *
 * V1.0
 *
 *
 */
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>

using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
/*
 * Nueva funcion de tipo void para obtener valores cada que queramos sin necesidad
 * de volver a reescribir todo.
 */

void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;//obtener el parametro expuesto en la funcion
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);

}

//Eliminamos el cursor de la ventana de ejecuci�n.
void OcultarCursor(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1; //Obtendra valores desde 1 hasta 100 m�ximo
    cci.bVisible = FALSE;//Puede obtener falso o verdadero(falso no se muestrea)

    SetConsoleCursorInfo(hCon,&cci);
}

//Clase metodo o funcion (es lo mismo XD) Nave :3
class NAVE{
    int x,y;
    int corazones;
    int vidas;
public:
    NAVE(int _x , int _y ,int _corazones, int _vidas); //Constructor :)
    int X(){ return x;}//Para obtener valores privados en asteroide
    int Y(){ return y;}
    void HEART() {corazones--;}
    int BID() {return vidas;}
    void pintar();
    void borrar();
    void mover();
    void pintar_corazones();
    void muerte();
    void explosion();
};
//Funciones de la clase nave
void NAVE::pintar(){ //operador para la clase para la funcion
    gotoxy(x,y); printf("  %c", 30);
    gotoxy(x,y+1); printf(" %c%c%c", 40,207,41);
    gotoxy(x,y+2); printf("%c%c %c%c", 30,190,190,30);
}

void NAVE::borrar(){
    gotoxy(x,y); printf("         ");
    gotoxy(x,y+1); printf("         ");
    gotoxy(x,y+2); printf("         ");
}

void NAVE::mover(){
 if(kbhit()){
                char tecla = getch();//para leer lo ingresado en teclado
                borrar(); //borrar;
                if (tecla == IZQUIERDA && x > 3)x--;//comillas simples para evaluar un caracter
                if (tecla == DERECHA && x+6 < 77)x++; // NOTa: Al compilar el compilador nota que
                if (tecla == ARRIBA && y > 4)y--; //estamos comparando un numero con un char entonces lo que hace
                                        // es verificar que numero corresponde a cual tecla en ascii
                if (tecla == ABAJO && y+3 < 33)y++;//por ahora queda el rastro
                //if (tecla == 'e') corazones--;
                pintar(); //llamamos el metodo de pintar
                pintar_corazones();
        }


}

//Designar constructores
NAVE::NAVE(int _x,int _y, int _corazones, int _vidas){

    x = _x;
    y = _y;
    corazones = _corazones;
    vidas = _vidas;
}
/*
NAVE::NAVE(int _x,int _y): x(_x),y(_y){

}
o esta manera
*/
//Crear que detecte la colision con el borde y no avance
void colision_borde(){
    for(int i = 2; i<78; i++){
        gotoxy(i,3);printf("%c", 205);
        Sleep(6);
        gotoxy(i,33);printf("%c",205);

    }

    for(int i=4 ; i < 33;i++){
        gotoxy(2,i);printf("%c", 186);
        Sleep(6);
        gotoxy(77,i);printf("%c",186);

    }

    gotoxy(2,3);printf("%c",201);
    gotoxy(2,33);printf("%c",200);
    gotoxy(77,3);printf("%c",187);
    gotoxy(77,33);printf("%c",188);

}

void NAVE::pintar_corazones(){
    gotoxy(52,2);printf("vidas:");
    gotoxy(58,2);printf("     ");
     for(int i = 0 ; i < vidas; i++){
        gotoxy(58+i,2); printf("%c",3); //(pintamos un corazon)
    }
    gotoxy(64,2);printf("Energia:");
    gotoxy(72,2);printf("     ");
    for(int i = 0 ; i < corazones; i++){
        gotoxy(72+i,2); printf("%c",219); //(pintamos un corazon)
    }

}
void NAVE::explosion(){//Animacion de explosion :3
        borrar();
        gotoxy(x,y);printf("    **   ");//Animacion de exploci�n
        gotoxy(x,y+1);printf("  ****   ");
        gotoxy(x,y+2);printf("   **   ");
        Sleep(200);

        borrar();
        gotoxy(x,y);printf(" *  **  * ");//Animacion de exploci�n
        gotoxy(x,y+1);printf("  ****  ");
        gotoxy(x,y+2);printf(" *  **  *");
        Sleep(200);

        borrar();
        vidas--;
        corazones = 3;
        pintar_corazones();
        pintar();

}
void NAVE::muerte(){

    if(corazones == 0){
        explosion();
    }
}


//Clase Asteroide
class asteroide{

    int x,y;

public:
    int X() { return x;}
    int Y() { return y;}
    asteroide(int _x, int _y): x(_x),y(_y){}
    void pintar();
    void mover();
    void colicion(class NAVE &N);
};

void asteroide::pintar(){
    gotoxy(x,y); printf("%c", 176);
    //gotoxy(x,y); printf("%c", 169);
}

void asteroide::mover(){

    gotoxy(x,y); printf(" ");
    y++;

    if(y > 31){
        x = rand()%71 + 4;
        y = 5;
    }
    pintar();

}

void asteroide::colicion(class NAVE &N){
    if(x >= N.X() && x < N.X()+6 && y >= N.Y() && y<= N.Y()+2){//Colision
            N.HEART();
            N.borrar();//Elimina el bug de si se queda dibjado el asteroide en ela nave
            N.pintar();//Pintar la nave en caso que se borre algo
            N.pintar_corazones();
            x = rand()%71 + 4;
            y = 4;
    }

}


//Disparo
class disparo_bala{

    int x,y;
public:
    int X() {return x;}
    int Y() { return y;}
    disparo_bala( int _x , int _y):x(_x),y(_y){}
    void mover();
    bool fuera();
};
void disparo_bala::mover(){

    gotoxy(x,y); printf("  ");
    y--;
    gotoxy(x,y); printf(" * ");

}

bool disparo_bala::fuera(){

    if(y==4) return true;
    return false;

}
//Metodo main
int main(){
    colision_borde();
    OcultarCursor(); //Mandamos llamar
    NAVE N(37,30,3,3);//Objeto :3
    N.pintar(); //llamar metodo :) usando el objeto
    Sleep(4);//Retrazamos el dibujado de las vidas :)
    N.pintar_corazones();

    /*Inicia lista asteroides*/
    //Listas de asteroides
    list<asteroide*> A;
    list<asteroide*>::iterator itA;
    for(int i=0;i<6;i++){
        A.push_back(new asteroide(rand()%75+3, rand()%5+4));

    }
    /*Fin lista asteroides*/

    /*Lista balas//Listas de balas :3 */
    list<disparo_bala*> B; //Listade objetos para las balas una lista es como un Arreglo :) Se usan punteros tambien
    list<disparo_bala*>::iterator it;//iterador para recorrer las listas

    /* Fin de lista balas*/

    bool game_over = false;
    int game_score = 0;
    int meteoros_destruidos = 0;
    while(!game_over){//ejecutar mientras la instancia sea diferente a falso
    gotoxy(10,1);printf("Space Deep: By Klozz ");
    gotoxy(55,1);printf("V1.0");
    gotoxy(4,2);printf("Meteoros: %d",meteoros_destruidos);
    gotoxy(22,2);printf("Game Score: %d",game_score);
         if(kbhit()){

            char tecla = getch();
            if (tecla == 'd')
            B.push_back(new disparo_bala(N.X() + 2, N.Y() - 1));
         }

    for(it = B.begin(); it != B.end(); it++){//iterador del mismo valor de la lista inicial y sea distinto del final)

        (*it)->mover(); //puntero desreferenciado con ello podremos acceder a los metodos
        if((*it)->fuera()){
            gotoxy((*it)->X(), (*it)-> Y());//situarnos en posicion
            printf("  ");
            delete(*it);
            it = B.erase(it);

        }
    }

    for(itA = A.begin(); itA != A.end(); itA++){
        (*itA)->mover();
        (*itA)->colicion(N);

    }

        /* Detectar colisiones de balas con asteroides */
        for(itA = A.begin(); itA != A.end(); itA++){//Asteroides

            for(it = B.begin(); it != B.end(); it++){ //Balas

                if((*itA)->X() == (*it)->X() && ( (*itA)->Y() + 1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() )){//coordenadas deben ser guales

                        gotoxy((*it)->X(),(*it)->Y()); printf("  ");
                        delete(*it);
                        it = B.erase(it);
                        A.push_back(new asteroide(rand()%75 + 3, 4));
                        gotoxy((*itA)->X(),(*itA)->Y()); printf("  ");
                        delete(*itA);
                        itA = A.erase(itA);
                        game_score += 4;//puntos
                        meteoros_destruidos +=1;
            }
        }

    }/* Fin de deteccion de coliciones */

        if(N.BID() == 0) game_over = true;
         N.muerte();
         N.mover();
         Sleep(30); //Detener la ejecuci�n por 30ms para evitar se ejecute muchas veces y haya menos gasto de memoria
    }
    system("cls");
    printf("Has perdido :) espero hayas disfrutado este juego...\nUn saludo de parte de el desarrollador\n");
    printf("Developed by: Carlos Jesus AKA Klozz jesus");
    getch();//espera que se presione un boton para cerrar la ventana y evitar el molesto error de qe termino :P

}
