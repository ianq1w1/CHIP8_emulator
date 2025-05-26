//projeto simples de um interpretador/emulador chip-8
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct CHIP8 {
    //espaco pra memoria
    uint8_t memory[4096];
    //program counter
    uint16_t PC; 
    //display(nao sei como faz isso ainda)
    uint8_t display;
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
    uint8_t registers[16];

}CHIP8; 

void cleanMemory(CHIP8* chip8){
    memset(chip8, 0, sizeof(CHIP8));
}

void Initialize(CHIP8* chip8){
    cleanMemory(chip8);
    chip8->PC = 0x200;
    chip8->sp = 0;
    chip8->I = 0;
} 