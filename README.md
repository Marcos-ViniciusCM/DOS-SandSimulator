# Simulador de Areia Caindo em DOS (C)

Trata-se de uma implementação de um simulador de física de partículas de areia (Falling Sand Automata / Automato Celular) para o MS-DOS, desenvolvida em C, que utiliza programação gráfica com VGA (Modo 13h - 320x200, 256 cores).

Este repositório serve como registo da minha evolução técnica e dos experimentos realizados na área de desenvolvimento de baixo nível e programação retro.

## Objetivos
- Aperfeiçoar os conhecimentos de programação de baixo nível e arquitetura x86 real mode;
- Compreender melhor o funcionamento da comunicação direta com o hardware e memória de vídeo (VRAM);
- Praticar a manipulação de matrizes, física de autómatos celulares e otimização de estruturas de dados em C;
- Desenvolver um motor de simulação de física sem recorrer a bibliotecas gráficas modernas;
- Documentar a minha evolução e os meus experimentos com o desenvolvimento para o DOS.

## Tecnologias
- **Linguagem:** C
- **Plataforma:** MS-DOS
- **Modo gráfico:** VGA Mode 13h (320x200, 256 cores)
- **Compilador:** Open Watcom V2
- **Emulador:** DOSBox

## Funcionalidades
- Simulação de física de partículas (areia) em tempo real baseada em autómatos celulares;
- Acesso e renderização com gravação direta no buffer de memória VGA (`0xA000`);
- Atualização e verificação de colisões e estabilidade do tabuleiro em tempo real.

## Sobre a implementação
Este projeto foi desenvolvido com o objetivo principal de compreender os conceitos envolvidos na programação para DOS e a manipulação direta de autómatos celulares, em vez de focar apenas na otimização avançada de desempenho.

Embora existam técnicas mais eficientes para a renderização e atualização do grid (como a utilização de *double buffering* na RAM), optei por implementar a lógica fundamental de forma manual, a fim de compreender melhor o funcionamento interno do hardware gráfico e o controle de memória em C.

Por conseguinte, algumas partes do código poderão ser aprimoradas no futuro, mas foram mantidas para registo do processo de aprendizagem.
