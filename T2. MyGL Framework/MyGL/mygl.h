#ifndef MYGL_H
#define MYGL_H

#include <string.h>

#include "core.h"
#include "frame_buffer.h"

struct cor{
    float red;
    float green;
    float blue;
    float alpha;
};
typedef struct cor Cor;
struct ponto{
    int x;
    int y;
};
typedef struct ponto Ponto;

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Declare aqui as funções que você implementar <<<
//

void PutPixel(Ponto coordenada, Cor RGBA);                                      //Desenha um pixel na tela
void DrawLine(Ponto inicio, Ponto fim, Cor RGBAi, Cor RGBAf);                   //Desenha uma linha na tela
void DrawTriangle(Ponto v0, Ponto v1, Ponto v2, Cor RGBA0,Cor RGBA1,Cor RGBA2); //Desenha um triangulo na tela
// -----------------------------------------------------------------------------
int modulo(int x);                                                              //Alternativa para abs()
Ponto inverte(Ponto pt, int i);                                                 //Inverte x e y, podendo x = +-y
Ponto reverte(Ponto pt,int r);                                                  //Reverte x e y
Cor InterpolarCor(Cor RGBA1, Cor RGBA2, Ponto inicio, Ponto fim);                                //Interpola as cores dos pontos

#endif  // MYGL_H
