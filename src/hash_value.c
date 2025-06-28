/*
0x801ccf40 _AIrand
0x801ccf68 BXrand
0x801ccf90 BXsrand
0x801ccfbc GetHashValue32
0x801ccfe4 tHashName32::getHashValue
//end 0x801CD02C

*/

typedef unsigned int uint;

uint GetHashValue32(char* str);
uint tHashName32_scoperes_getHashValue(uint*, char*);

char AIrandom[24];
char BXrandom[24];


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
    uint top;
    uint shifted;

    while (*str) {
        hash = (hash << 4) + *str++;
        top = hash & 0xF0000000;

        if (top != 0) {
            shifted = top >> 23;
            hash ^= shifted;
            hash ^= top;
        }
    }

    *out = hash;
    return *out;
}