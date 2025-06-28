/*
0x801ccfbc GetHashValue32
0x801ccfe4 tHashName32::getHashValue

*/

typedef unsigned int uint;

uint GetHashValue32(char* param_1);
uint tHashName32_scoperes_getHashValue(uint*, char*);


uint GetHashValue32(char* param_1){
    char hash[4];
    return tHashName32_scoperes_getHashValue((uint*)hash, param_1);
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