#include "mygl.h"

//
// >>> Defina aqui as funções que você implementar <<<
//

void PutPixel(Ponto coordenada, Cor RGBA){
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH] = RGBA.red;
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH + 1] = RGBA.green;
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH + 2] = RGBA.blue;
    fb_ptr[4*coordenada.x + 4*coordenada.y*IMAGE_WIDTH + 3] = RGBA.alpha;
}
void DrawLine(Ponto inicio, Ponto fim, Cor RGBAi, Cor RGBAf){
    int dx, dy;                                     //dx = Variação de x, dy =  Variação de y
    int sim = 0, inv = 0, rev;                      //sim = Verifica se dy foi multiplicado por -1
    int D, pix_L, pix_NE;                           //inv = Verifica se a reta foi invertida
    Ponto pt0 = inicio;                             //rev = Guarda o valor de dy antes da recalculação de dx e dy na inversão
    Ponto pt1 = fim;                                //d = Posição inicial do pixel
    Cor inter = RGBAi;                              //pix_L = incremento para o pixel L
    dx = fim.x - inicio.x;                          //pix_NE = incremento para o pixel NE
    dy = fim.y - inicio.y;                          //inter = variavel para fazer a interpolação de cor

    if(modulo(dx) < modulo(dy)){                    //Se |dx| < |dy|, os pontos se invertem, sendo x = -y e y = x,
        pt0 = inverte(inicio, dy);                  //e por fim é recalculado dx e dy
        pt1 = inverte(fim, dy);
        rev = dy;
        dx = pt1.x - pt0.x;
        dy = pt1.y - pt0.y;
        inv = 1;
    }
    if(dx < 0){                                     //Se dx < 0, os pontos são invertidos e é recalculado dx e dy
        pt0 = fim;
        pt1 = inicio;
        inter = RGBAf;
        RGBAf = RGBAi;
        dx = pt1.x - pt0.x;
        dy = pt1.y - pt0.y;
    }
    if(dy < 0){                                     //Se dy < 0, dy é multiplicado por -1 e sim = 1
        dy = dy * -1;
        sim = 1;
    }

    D = 2 * dy - dx;                              //Calculo do primeiro pixel
    pix_L = 2 * dy;                               //Calculo do movimento para o pixel a leste
    pix_NE = 2 * (dy - dx);                       //Calculo do movimento para o pixel a nordeste



    do{                                             //Loop para a formação da linha
        inter = InterpolarCor(inter,RGBAf,pt0,pt1);      //Faz a interpolação das cores RGBAi e RGBAf
        if(inv == 1){
            PutPixel(reverte(pt0,rev),inter);       //Inverte o pixel e pinta ele
        } else {
            PutPixel(pt0,inter);                    //Pinta o pixel
        }

        if(D <= 0){                                //Caso a posição inicial seja = 0 ou menor, o pixel ativado sera o leste
            D += pix_L;                            //e sera incrementado 1 na coordenada x
            pt0.x++;
        }
        else{
            D += pix_NE;                            //Caso contrario, é ativado o pixel a nordeste, sera incrementado +1 na
            pt0.x++;                                //coordenada x e dependendo do estado da simetria(sim) a coordenada y
            if(sim == 0){                           //perdera ou ganhara 1
                pt0.y++;
            } else {
                pt0.y--;
            }
        }
    }while(pt0.x < pt1.x);
}
void DrawTriangle(Ponto v0, Ponto v1, Ponto v2, Cor RGBA0,Cor RGBA1,Cor RGBA2){
    DrawLine(v0,v1,RGBA0,RGBA1);
    DrawLine(v1,v2,RGBA1,RGBA2);
    DrawLine(v2,v0,RGBA2,RGBA0);
}
//-----------------------------------------------------------------------------------
int modulo(int x){
    if(x >= 0)
        return x;
    else
        return -x;
}
Ponto inverte(Ponto pt, int i){
    Ponto inv;
    if(i < 0){
        inv.x = -pt.y;
        inv.y = pt.x;
    }
    else {
        inv.x = pt.y;
        inv.y = pt.x;
    }
    return inv;
}
Ponto reverte(Ponto pt, int r){
    Ponto rev;
    if(r < 0){
        rev.x = pt.y;
        rev.y = -pt.x;
    }
    else {
        rev.x = pt.y;
        rev.y = pt.x;
    }
    return rev;
}
Cor InterpolarCor(Cor RGBA1, Cor RGBA2, Ponto inicio, Ponto fim) {
    Cor inter = RGBA1;
    float dx = fim.x - inicio.x;

    inter.red += (float)(RGBA2.red - RGBA1.red)/dx;
    inter.green += (float)(RGBA2.green - RGBA1.green)/dx;
    inter.blue += (float)(RGBA2.blue - RGBA1.blue)/dx;
    inter.alpha = 255;
    
    return inter;
}

// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {
    //
    // >>> Chame aqui as funções que você implementou <<<
    Cor clr1 = {255,0,0,255};
    Cor clr2 = {0,255,0,255};
    Cor clr3 = {0,0,255,255};

    Ponto pt1 = {128,128};
    Ponto pt2 = {256,384};
    Ponto pt3 = {384,128};

    DrawTriangle(pt1,pt2,pt3,clr1,clr2,clr3);




}
