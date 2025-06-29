/*

0x801CCC7C cRandom::random
0x801CCDB0 cRandom::seed
0x801CCE28 AIsetseed
0x801CCE58 AIgetseed
0x801CCE84 AIrangernd
0x801CCED8 AIfrand
0x801ccf40 _AIrand
0x801ccf68 BXrand
0x801ccf90 BXsrand
0x801ccfbc GetHashValue32
0x801ccfe4 tHashName32::getHashValue
//end 0x801CD02C

*/

typedef unsigned int uint;

uint cRandom_scoperes_random();
void cRandom_scoperes_seed();
void AIsetseed(unsigned int *);
void AIgetseed(unsigned int *);
float AIrangernd(float min, float max);
float AIfrand(float min, float max);
uint _AIrand(void);
uint BXrand(void);
void BXsrand(uint);
uint GetHashValue32(char* str);
uint tHashName32_scoperes_getHashValue(uint*, char*);

const uint InitSeed[6] = {
    0xF22D0E56, 0x883126E9,
    0xC624DD2F, 0x0702C49C,
    0x9E353F7D, 0x6FDF3B64
};
const float lbl_803DF078 = 1.0;
const float lbl_803DF094 = -1.0; // todo: add to split

uint BXrandom[6];
uint AIrandom[6];

float AIrangernd(float min, float max) {
  return min + max * AIfrand(lbl_803DF094,lbl_803DF078);
}

float AIfrand(float min, float max) {
    float range = max - min;
    uint bits = (_AIrand() & 0x007FFFFF) | 0x3F800000; // Get random bits and force float exponent for 1.0f
    float f = *(float*)&bits; // reinterpret bits as float (gives [1.0, 2.0))
    float norm = f - lbl_803DF078; // subtract 1.0f using SDA float to get [0.0, 1.0)
    return norm * range + min;
}

uint _AIrand(void){
    return cRandom_scoperes_random(AIrandom);
}

uint BXrand(void){
    return cRandom_scoperes_random(BXrandom);
}

void BXsrand(uint param_1){
    cRandom_scoperes_seed(BXrandom, param_1);
}


uint cRandom_scoperes_random(uint *param_1){
    return 0;
}


void cRandom_scoperes_seed(uint *param_1, uint param_2) {
    //uint* out = (uint*)param_1;
    param_1[0] = param_2 + 0xF22D0E56;
    param_1[1] = param_2 + 0x883126E9;
    param_1[2] = param_2 + 0xC624DD2F;
    param_1[3] = param_2 + 0x0702C49C;
    param_1[4] = param_2 + 0x9E353F7D;
    param_1[5] = param_2 + 0x6FDF3B64;
}

void cRandom_scoperes_cRandom(uint param_1) {
  MEM_copy(param_1, InitSeed, 0x18);
}

void AIsetseed(unsigned int * param_1) {
  MEM_copy(&AIrandom, param_1, 0x18);
}

void AIgetseed(unsigned int * param_1) {
  MEM_copy(param_1, &AIrandom, 0x18);
}







uint GetHashValue32(char* str){
    char hash[4];
    return tHashName32_scoperes_getHashValue((uint*)hash, str);
}

uint tHashName32_scoperes_getHashValue(uint* out, char* str){
    uint hash = 0;
    uint top;

    while (*str) {
        hash = (hash << 4) + *str++;
        top = hash & 0xF0000000;
        if (top != 0) {
            hash = (hash ^ (top >> 23)) ^ top;
        }
    }

    *out = hash;
    return *out;
}