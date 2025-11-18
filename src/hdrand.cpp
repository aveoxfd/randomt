#include "hdrand.h"
#include <time.h>


#define ERROR_CODE 0x128

typedef unsigned long long  uint64;
typedef unsigned long       uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;

typedef long long           sint64;
typedef long                sint32;
typedef short               sint16;
typedef char                sint8;

extern "C"{
    int __get_hardrand_rdrand(void);
    int __get_hardrand_rdseed(void);
}

#if (LANG == CPPLANG)
#include <iostream>

#define CONSTRUCTOR_MESSAGE std::cout<<"Constructor message\nSeed: "<<(uint64)seed<<"\n"
#define DEFAULT_RANDOM_METHOD __get_hardrand_rdrand

#define CHECK_SUPPORT \
switch(random_method()){\
    case NOT_SUPPORT:\
        std::cout<<"CPU doesn't support random commands.\n";\
        return NOT_SUPPORT;\
        break;\
}

template class HardwareRandom<uint64>;
template class HardwareRandom<uint32>;
template class HardwareRandom<uint16>;
template class HardwareRandom<uint8>;

template class HardwareRandom<sint64>;
template class HardwareRandom<sint32>;
template class HardwareRandom<sint16>;
template class HardwareRandom<sint8>;
template class HardwareRandom<int>;

template <typename T>
HardwareRandom<T>::HardwareRandom(T seed) : seed(seed), random_method(DEFAULT_RANDOM_METHOD) {
    CONSTRUCTOR_MESSAGE;
};

template <typename T>
HardwareRandom<T>::HardwareRandom(void) : seed(0), random_method(DEFAULT_RANDOM_METHOD){
    update_seed();
    #if (DEBUG)
    CONSTRUCTOR_MESSAGE<<"created with void parameters.\n";
    #endif
};

template <typename T>
HardwareRandom<T>::HardwareRandom(T seed, uint8 method) : seed(seed), 
random_method(
    method == RDRAND_METHOD ? __get_hardrand_rdrand : method == RDSEED_METHOD ? __get_hardrand_rdseed : __get_hardrand_rdrand
) {
    #if(DEBUG)
    CONSTRUCTOR_MESSAGE;
    #endif
};
/*
Generates a random 64-bit unsigned integer.
*/
template <typename T>
T HardwareRandom<T>::random64(void){
    seed = (random_method() * seed * 2423534837ULL + 1ULL) % 4358357894ULL;
    return (T) seed;
}
/*
Generates a random 32-bit unsigned integer.
*/
template <typename T>
T HardwareRandom<T>::random32(void){
    seed = (random_method() * seed * 2423534837ULL + 1ULL) % 4358357894ULL;
    return (T)seed;
}

/*
Generates a random number of type T.
*/
template <typename T>
T HardwareRandom<T>::random(void){
    CHECK_SUPPORT
    seed = (random_method() * seed * 2423534837ULL + 1ULL) % 4358357894ULL;
    return (T)seed;
}
/*
Updates the seed using hardware random method.
*/
template <typename T>
void HardwareRandom<T>::update_seed(void){
    seed = 1;
    int n;
    while (n == 0){
        n = random_method() * time(0) % 100 + 1;
    }
    for (int i = 0; i<n; i++){
        seed *= random_method();
    }
    seed+=random_method()*time(0);
}
#endif
/*
Generates a random number using hardware random method in C language style.
*/
#if (LANG == CLANG)

DEFAULT_MODE seed = 0;

void update_seed(void){
    seed = 1;
    int n;
    while (n == 0){
        n = __get_hardrand_rdrand() * time(0) % 100 + 1;
    }
    for (int i = 0; i<n; i++){
        seed *= __get_hardrand_rdrand();
    }
    seed+=__get_hardrand_rdrand()*time(0);
}

DEFAULT_MODE random(void){
    if (seed == 0){
        update_seed();
    }
    seed = (__get_hardrand_rdrand() * seed * 2423534837ULL + 1ULL) % 4358357894ULL;
    return (DEFAULT_MODE)seed;
}

uint32 random32(void){
    if (seed == 0){
        update_seed();
    }
    seed = (__get_hardrand_rdrand() * seed * 2423534837UL + 1UL) % 4358357894UL;
    return (uint32)seed;
}

uint64 random64(void){
    if (seed == 0){
        update_seed();
    }
    seed = (__get_hardrand_rdrand() * seed * 2423534837ULL + 1ULL) % 4358357894ULL;
    return (uint64)seed;
}

uint16 random16(void){
    if (seed == 0){
        update_seed();
    }
    seed = (__get_hardrand_rdrand() * seed * 2423534837U + 1U) % 4358357894U;
    return (uint16)seed;
}

uint8 random8(void){
    if (seed == 0){
        update_seed();
    }
    seed = (__get_hardrand_rdrand() * seed * 2423534837U + 1U) % 4358357894U;
    return (uint8)seed;
}
#endif