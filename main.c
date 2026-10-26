#include <stdio.h>
#include <dos.h>
#include <i86.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define SCREEN_WIDTH 320
#define SET_MODE 0x00
#define VIDEO_INT 0x10
#define SCREEN_HEIGTH 200
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03

typedef unsigned char bytePerson;

unsigned char __far *VGA = (unsigned char __far *)0xA0000000L;

// 320x200

unsigned char tabuleiroVisual[64000] = {0};

unsigned int posicaoGraos[50000];
unsigned int quantidadeGrao = 0;

unsigned int mouse_on = 0;
unsigned int num_button = 0;

void defineMode(bytePerson mode)
{
    union REGS regs;
    regs.h.ah = SET_MODE;
    regs.h.al = mode;
    int86(VIDEO_INT, &regs, &regs);
}

void voltaTexto()
{
    union REGS regs;
    // voltar modo texto
    regs.h.ah = 0x00;
    regs.h.al = 0x3;
    int86(0x10, &regs, &regs);
}

unsigned int podeCair(int x, int y)
{
    unsigned int indexAtual = y * 320 + x;

    if (y >= 199)
        return indexAtual;
    // cai para baixo
    if (tabuleiroVisual[indexAtual + 320] == 0)
    {
        return indexAtual + 320;
    }
    // cai para direita
    else if (x < 319 && tabuleiroVisual[indexAtual + 321] == 0)
    {
        return indexAtual + 321;
    }
    // cai para esquerda
    else if (x > 0 && tabuleiroVisual[indexAtual + 319] == 0)
    {
        return indexAtual + 319;
    }
    else
    {
        return indexAtual;
    }
}

void inicializarMouse()
{
    union REGS regs;

    regs.x.ax = 0;
    int86(0x33, &regs, &regs);

    mouse_on = regs.x.ax;
    num_button = regs.x.bx;

    if (mouse_on)
    {
    }
    else
    {
        printf("mouseErro");
    }
}

void CalculaLogicaApenasGrao()
{
    int x, y, i;
    unsigned cai, offset;
    for (i = 0; i < quantidadeGrao; i++)
    {
        // offset = ((y << 6) + (y << 8) + x);
        offset = posicaoGraos[i];
        y = offset / 320;
        x = offset % 320;
        cai = podeCair(x, y);
        if (offset == cai)
            continue;
        tabuleiroVisual[offset] = 0;
        posicaoGraos[i] = cai;
        tabuleiroVisual[cai] = 1;
        VGA[offset] = 0;
        VGA[cai] = 14;
    }
}

int main()
{
    union REGS regs;

    int dx = 0;
    int dy = 0;
    int cx = 0;
    unsigned int offset = 0;
    unsigned int x = 0;
    unsigned int y = 0;
    int button = 0;
    int cai = 0;
    int px = 0;
    int py = 0;

    defineMode(VGA_256_COLOR_MODE);
    inicializarMouse();

    while (!button)
    {
        regs.x.ax = 3;
        int86(0x33, &regs, &regs);
        x = regs.x.cx; // 2
        y = regs.x.dx;

        if (quantidadeGrao > 50000)
        {
            break;
        }

        offset = (x >> 1) + ((y << 8) + (y << 6));
        if (tabuleiroVisual[offset] == 0)
        {
            posicaoGraos[quantidadeGrao] = offset;
            tabuleiroVisual[offset] = 14;
            quantidadeGrao++;
        }
        // posição x vai de 0 a 639 entao tem que dividir por 2
        // desenhaTela();
        CalculaLogicaApenasGrao();
        if (regs.x.bx & 1)
        {
            button = 1;
        }
    }

    // getch();

    defineMode(TEXT_MODE);
    printf("Hello, World!\n");
    return 0;
}