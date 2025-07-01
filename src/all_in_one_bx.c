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
0x801cd02c cLoadTimer::endload
0x801CD044 cLoadTimer::update
0x801CD0BC cLoadTimer::setnextpercent
0x801cd118 cLoadTimer::startload
0x801cd138 fn_801CD138
0x801CD144 fn_801CD144
0x801CD168 cExecutionMan::checkHalt
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
const float lbl_803DF07C = 0.0;
const float lbl_803DF080 = 2.0;
const float lbl_803DF084 = 0.5;
const float lbl_803DF088 = 0.001;
const float lbl_803DF08C = 0.99999;
const float lbl_803DF090 = 3.14159265;
const float lbl_803DF094 = -1.0;
const float lbl_803DF098 = 100.0;
const double lbl_803DF0A0 = 4503601774854144.0; // if split into floats it's 176.0 and -0.0
const float lbl_803DF0A8 = -1.5;
const float lbl_803DF0AC = 10.0;

uint BXrandom[6];
uint AIrandom[6];


uint lbl_803DA9DC;
//extern lbl_803D96C8;
//static const char lbl_803D96C8[] = "default";
static const char lbl_803D96C8[] __attribute__((section(".sdata"))) = "default";



void operator_space_new_801CCC50(uint param_1){
  fn_801CCB88(param_1,lbl_803D96C8,lbl_803DA9DC,0);
  return;
}

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

uint cRandom_scoperes_random(uint *param_1) {
    uint r0, r4, r5, r6, r7;

    r4 = param_1[5];
    r5 = param_1[4];
    r7 = r4 + r5;

    r0 = 0;
    if (r7 < r4 || r7 < r5) r0 = 1;

    param_1[4] = r7;

    r5 = param_1[3];
    r6 = r5 + r0;
    r6 = r7 + r6;
    param_1[3] = r6;

    r5 = param_1[2];
    r0 = (r6 < r7) ? 1 : 0;
    r7 = r6 + r5 + r0;
    param_1[2] = r7;

    r5 = param_1[1];
    r0 = (r7 < r6) ? 1 : 0;
    r6 = r7 + r5 + r0;
    param_1[1] = r6;

    r5 = param_1[0];
    r0 = (r6 < r7) ? 1 : 0;
    r5 = r6 + r5 + r0;
    param_1[0] = r5;

    // Increment param_1[5..0] with carry propagation
    if (++param_1[5] == 0) {
        if (++param_1[4] == 0) {
            if (++param_1[3] == 0) {
                if (++param_1[2] == 0) {
                    if (++param_1[1] == 0) {
                        ++param_1[0];
                        ++r5;
                    }
                }
            }
        }
    }

    return r5;
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


void cLoadTimer_scoperes_endload(float *param_1){
    param_1[5] = lbl_803DF098;
    param_1[6] = lbl_803DF07C;
    param_1[0] = lbl_803DF098;
    return;
}

void cLoadTimer_scoperes_update(){}

extern lbl_803DA9D8;

void cLoadTimer_scoperes_setnextpercent(float param_1,float *param_2){
    float _a = lbl_803DF0A8;
    float _b = lbl_803DF098;
    param_2[4] = *(float *)(lbl_803DA9D8 + 0x20);
    param_2[1] = param_2[2];
    param_2[2] = param_1;
    param_2[7] = _a / ((param_2[3] * (param_2[2] - param_2[1])) / _b);
    param_2[5] = param_2[2];
    param_2[6] = *param_2 - param_2[2];
}

void cLoadTimer_scoperes_startload(float param_1, float *param_2){
    param_2[3] = param_1;
    param_2[0] = lbl_803DF07C;
    param_2[2] = lbl_803DF07C;
    param_2[5] = lbl_803DF07C;
    param_2[6] = lbl_803DF07C;
    param_2[7] = lbl_803DF07C;
}

uint fn_801CD138(){
    return *(uint*)(lbl_803DA9D8 + 0xc);
}

void fn_801CD144(){
    fn_801CD248(lbl_803DA9D8);
}