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
struct linha{
    Ponto inicio;
    Ponto fim;
};
typedef struct linha Linha;
struct triangulo{
    Ponto v0;
    Ponto v1;
    Ponto v2;
};
typedef struct triangulo Triangulo;

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Declare aqui as funções que você implementar <<<
//

void PutPixel(Ponto coordenada, Cor rgba);
void DrawLine(Ponto inicio, Ponto fim, Cor rgba1, Cor rgba2);
void DrawTriangle(Ponto v0, Ponto v1, Ponto v2, Cor rgba0,Cor rgba1,Cor rgba2);
Cor RetornaCor();
Ponto CriaPonto();
int modulo(int x);
Ponto inverte(Ponto pt);
Cor InterpolarCor(Cor a, Cor b, int deltaX);

#endif  // MYGL_H
