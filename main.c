//projeto simples de um interpretador/emulador chip-8
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "font.h"

typedef struct CHIP8 {
    //espaco pra memoria
    uint8_t memory[4096];
    //program counter
    uint16_t PC; 
    //display(nao sei como faz isso ainda)
    uint8_t Xdisplay[64];
    uint8_t Ydisplay[32];
    //usado para apontar locais na memoria (??)
    uint16_t I;
    //stack ! que chama funções e retorna delas (pilha né...)
    uint16_t stack[16];
    //stack pointer
    uint8_t sp;
    //atualização de quadros no display
    uint8_t delay;
    //segundo o guia isso funciona tipo o delay, só que para o som 
    uint8_t sound;

    uint8_t registers[15];

    uint8_t fontArr[80];

}CHIP8; 

void cleanMemory(CHIP8* chip8){
    memset(chip8->memory, 0, sizeof(chip8->memory));
}

void initialize(CHIP8* chip8){
    cleanMemory(chip8);
    chip8->PC = 0x200;
    chip8->sp = 0;
    chip8->I = 0;
} 

void fontInsert(CHIP8* chip8){
    memcpy(chip8->memory, chip8->fontArr, sizeof(chip8->memory));
}

bool isFull(CHIP8* chip8){
    uint16_t* stackLIFO = chip8->stack;
    uint8_t stackpointer = chip8->sp;

    if(stackpointer >= 16){
        printf("cheiao papi...\n");
        return true;
    }
    return false;
}

bool isEmpty(CHIP8* chip8){
    uint16_t* stackLIFO = chip8->stack;
    uint8_t stackpointer = chip8->sp;

    if(stackpointer <= 0){
        printf("vazio papi...\n");
        return true;
    }
    return false;
}

//adicionando endereço da função!
void pushStack(CHIP8* chip8, uint16_t* function){
   uint16_t* stackLIFO = chip8->stack;
   uint8_t* stackpointer = &(chip8->sp);
   uint16_t inst = function;
   //uint16_t* programCounter = &(chip8->PC);
   
   isFull(chip8);
   stackLIFO[*stackpointer] = chip8->PC;
   //*programCounter += 2;
   (*stackpointer)++;
}

void popStack(CHIP8* chip8){
   uint16_t* stackLIFO = chip8->stack;
   uint8_t* stackpointer = &(chip8->sp);
  // uint16_t inst = function;
   uint16_t* programCounter = &(chip8->PC);

   isEmpty(chip8);
   (*stackpointer)--;
   stackLIFO[*stackpointer] = 0;
   programCounter = stackLIFO[*stackpointer];

}

//fetch manda a instrução pra decode, e pelo q entendi a stack so armazena o endereço de memoria (o qual é o valor de PC)
//entao memory[PC] = instruções (eu acho)

void fetch(CHIP8* chip8){
    uint16_t* PCfetch = &(chip8->PC); 
    uint16_t bit1 = &(chip8->memory[*PCfetch]);
    uint16_t bit2 = &(chip8->memory[*PCfetch + 1]);
//aqui eu criei a variavel de instrução que eu, movo o primeiro bit 8 posições à esquerda, dando espaço o suficiente à direita
//assim consigo utilizar um OR operator pra alocar esse outro bit à direita (espaços de zero) 
    uint16_t instruction = bit1 << 8 | bit2;
    (*PCfetch) += 2;
//incremento PC em 2 pra pular pro proximo bloco de instrução
    decode(&instruction);

}

void decode(uint16_t *fetchedInstruction){
    // essas letras estranhas, estao no guia, mas basicamente to dividindo aq cada nibble/ byte da instrução
    //0xf000 pega o primeiro nibble, 0x0f00 pega o segundo nibble (saca só esse macete!)
    //iso pq cada 0 no hex seria um half byte e o F = 15 em hex
    // entao em binario ficaria 0000 1111 0000 0000 (logo com um operador AND iria zerar todos os nibbles q nao quero (fora do 1111))
    
    //nibbles/ half bytes
    uint16_t firstNibble = *fetchedInstruction >> 12;
    uint16_t X = (*fetchedInstruction & 0x0F00) >> 8;
    uint8_t Y = (*fetchedInstruction & 0x00F0) >> 4;
    uint8_t N = *fetchedInstruction & 0x000F;
    
    //segundo byte (terceiro e quarto nibbles)
    uint8_t NN = *fetchedInstruction & 0x00FF;
    //segundo, terceiro e quarto nibbles
    uint16_t NNN = *fetchedInstruction & 0x0FFF;

    switch (firstNibble)
    {
    case constant expression:
        /* code */
        break;
    
    default:
        break;
    }
    

}


