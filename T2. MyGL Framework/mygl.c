#include "mygl.h"
#include <stdio.h>

//
// >>> Defina aqui as funções que você implementar <<<
//

void PutPixel(Ponto coordenada, Cor rgba){
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH] = rgba.red;
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH + 1] = rgba.green;
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH + 2] = rgba.blue;
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH + 3] = rgba.alpha;
}
void DrawLine(Ponto inicio, Ponto fim, Cor rgba1, Cor rgba2){
    int dx, dy;                 //dx = Variação de x, dy =  Variação de y
    int sim = 0, inv = 0;       //sim = Aplica simetria na reta
    int psi, inc1, inc2;        //psi = Posição inicial, inc1 = inclinação para leste, incl2 = inclinação para nordeste
    Ponto pt0 = inicio;
    Ponto pt1 = fim;
    Cor inter = rgba1;
    dx = fim.x - inicio.x;
    dy = fim.y - inicio.y;

    if(modulo(dx) < modulo(dy)){
        pt0 = inverte(inicio);
        pt1 = inverte(fim);
        dx = pt1.x - pt0.x;
        dy = pt1.y - pt0.y;
        inv = 1;
    }

    //Se dx < 0 os pontos são invertidos
    if(dx < 0){
        pt0 = fim;
        pt1 = inicio;
        dx = pt1.x - pt0.x;
        dy = pt1.y - pt0.y;
    }
    //Se dy < 0 é aplicado simetria na reta
    if(dy < 0){
        dy = dy * -1;
        sim = 1;
    }

    psi = 2 * dy - dx;      //Calculo do primeiro pixel
    inc1 = 2 * dy;          //Calculo do movimento para o pixel a leste
    inc2 = 2 * (dy - dx);   //Calculo do movimento para o pixel a nordeste


    //Loop para a formação da linha
    do{
        if(inv == 1){
            PutPixel(inverte(pt0),inter);
        } else {
            PutPixel(pt0,inter);     //Pinta o pixel
        }

        if(psi <= 0){           //Caso a posição inicial seja = 0 ou menor, o pixel ativado sera o leste
            psi += inc1;        //e sera incrementado 1 na coordenada x
            pt0.x++;
        }
        else{
            psi += inc2;        //Caso contrario, é ativado o pixel a nordeste, sera incrementado +1 na
            pt0.x++;            //coordenada x e dependendo do estado da simetria(sim) a coordenada y
            if(sim == 0){       //perdera ou ganhara 1
                pt0.y++;
            } else {
                pt0.y--;
            }
        }
        inter = InterpolarCor(inter,rgba2,dx);
    }while(pt0.x < pt1.x);
}

int modulo(int x){
    if(x >= 0)
        return x;
    else
        return -x;
}
Ponto inverte(Ponto pt){
    Ponto inv;
    inv.x = pt.y;
    inv.y = pt.x;

    return inv;
}
Cor InterpolarCor(Cor a, Cor b, int deltaX) {
    Cor inter = a;
    inter.red += (float)(b.red-a.red)/deltaX;
    inter.green += (float)(b.green-a.green)/deltaX;
    inter.blue += (float)(b.blue-a.blue)/deltaX;
    inter.alpha = 255;
    return inter;
}
void DrawTriangle(Ponto v0, Ponto v1, Ponto v2, Cor rgba0,Cor rgba1,Cor rgba2){
    DrawLine(v0,v1,rgba0,rgba1);
    DrawLine(v1,v2,rgba1,rgba2);
    DrawLine(v2,v0,rgba0,rgba2);
}
// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {
    //
    // >>> Chame aqui as funções que você implementou <<<
    Cor clr;
    clr.red = 255;
    clr.green = 0;
    clr.blue = 0;
    clr.alpha = 255;
    Cor clr1;
    clr1.red = 0;
    clr1.green = 255;
    clr1.blue = 0;
    clr1.alpha = 255;
    Cor clr2;
    clr2.red = 0;
    clr2.green = 0;
    clr2.blue = 255;
    clr2.alpha = 255;
    Ponto pt0;
    pt0.x = 128;
    pt0.y = 128;
    Ponto pt1;
    pt1.x = 128;
    pt1.y = 256;
    Ponto pt2;
    pt2.x = 256;
    pt2.y = 128;
    DrawTriangle(pt0,pt1,pt2,clr,clr1,clr2);

    /*for (int i=0; i<250; ++i) {
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 0] = 10;
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 1] = 200;
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 2] = 50;
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 3] = 255;
    }*/
}
