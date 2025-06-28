/*
Real split 

0x801CCED8 AIfrand
0x801ccf40 _AIrand
0x801ccf68 BXrand
0x801ccf90 BXsrand
0x801ccfbc GetHashValue32
0x801ccfe4 tHashName32::getHashValue
//end 0x801CD02C

*/

typedef unsigned int uint;

float AIfrand(float min, float max);
uint _AIrand(void);
uint BXrand(void);
void BXsrand(uint param_1);
uint GetHashValue32(char* str);
uint tHashName32_scoperes_getHashValue(uint*, char*);

char AIrandom[24];
char BXrandom[24];
float lbl_803DF078 = 1.0;


float AIfrand(float min, float max) {
    float range = max - min;
    uint bits = (_AIrand() & 0x007FFFFF) | 0x3F800000; // Get random bits and force float exponent for 1.0f
    float f = *(float*)&bits; // reinterpret bits as float (gives [1.0, 2.0))
    float norm = f - lbl_803DF078; // subtract 1.0f using SDA float to get [0.0, 1.0)
    return norm * range + min;
}

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