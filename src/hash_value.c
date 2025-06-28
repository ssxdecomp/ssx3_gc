/*
0x801ccfbc GetHashValue32
0x801ccfe4 tHashName32::getHashValue

*/

typedef unsigned int uint;

uint GetHashValue32(char* str);
uint tHashName32_scoperes_getHashValue(uint*, char*);
//void cRandom_scoperes_seed(uint param_1, uint param_2);

//uint BXrandom;
extern uint* BXrandom;


void BXsrand(uint param_1){
    cRandom_scoperes_seed(BXrandom, param_1);
}

// extern void* fn_random;                    // declared elsewhere
// extern void lbl_random_seed(void*, void*); // takes a function pointer and argument

// void wrapper_call_random_seed(void* arg) {
//     fun_random_seed(&dat_random, arg);
// }



uint GetHashValue32(char* str){
    char hash[4];
    return tHashName32_scoperes_getHashValue((uint*)hash, str);
}

uint tHashName32_scoperes_getHashValue(uint* out, char* str){
    uint hash = 0;
    uint top = 0;

    while (*str) {
        hash = (hash << 4) + (signed char)(*str++);
        top = hash & 0xF0000000;
        if (top != 0) {
            hash ^= (top >> 23);
            hash ^= top;
        }
    }

    *out = hash;
    return hash;
}