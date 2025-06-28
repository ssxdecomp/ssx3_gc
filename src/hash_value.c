/*
0x801ccfbc GetHashValue32
0x801ccfe4 tHashName32::getHashValue

*/

typedef unsigned int uint;

uint GetHashValue32(char* str);
uint tHashName32_scoperes_getHashValue(uint*, char*);
//extern void cRandom_scoperes_seed(uint *param_1, uint param_2);

//extern uint* BXrandom; 
char AIrandom[24]; // 24 bytes long
char BXrandom[24]; // 24 bytes long


uint _AIrand(void){
    return cRandom_scoperes_random(&AIrandom);
}

uint BXrand(void){
    return cRandom_scoperes_random(&BXrandom);
}

void BXsrand(uint param_1){
    cRandom_scoperes_seed(BXrandom, param_1);
}


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