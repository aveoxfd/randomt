#ifndef _RANDOM_TEMPERATURE_GENERATOR_H
#define _RANDOM_TEMPERATURE_GENERATOR_H

#define RDRAND_METHOD (unsigned char)0x00
#define RDSEED_METHOD (unsigned char)0x01
#define NOSEED      0
#define DEBUG       1
#define NOT_SUPPORT 0xFF

#define CLANG   1
#define CPPLANG 0
#define LANG CPPLANG

#define MODE 0x64
#if (MODE == 0x64)
    typedef unsigned long long DEFAULT_MODE;
#endif
#if (MODE == 0x86)
    typedef unsigned long  DEFAULT_MODE;
#endif
#if (MODE == 0x386)
    typedef unsigned short DEFAULT_MODE;
#endif

#if (DEBUG)
extern "C"{
    int __get_hardrand_rdrand(void);
    int __get_hardrand_rdseed(void);
}
#endif

#if (LANG == CPPLANG)
/*
Generate a random number by hardware using termal entropy and raw entropy.

The library only works with the rdrand and rdseed CPU commands.
If your CPU is younger than the x86 architecture, these commands will not work. 
Make sure your CPU supports these commands before using this library.
Usage:
    #include "hdrand.h"
    HardwareRandom r; // Creates a random generator with default seed and method (rdrand).
    HardwareRandom r(123456); // Creates a random generator with seed 123456 and default method (rdrand).
    HardwareRandom r(123456, RDRAND_METHOD); // Creates a random generator with seed 123456 and rdrand method.
    HardwareRandom r(123456, RDSEED_METHOD); // Creates a random generator with seed 123456 and rdseed method.
    HardwareRandom r; // Creates a random generator with default seed and method (rdrand).
*/
template <typename T = DEFAULT_MODE>
class HardwareRandom{
    private:
    T seed;
    int(*random_method)(void);

    public:
    HardwareRandom(T seed, unsigned char method);
    HardwareRandom(T seed);
    HardwareRandom(void);
    
    T random(void);
    void update_seed(void); 
    T random64(void);
    T random32(void);
};
#endif


/*
Generates a random number using hardware random method in C language style.
*/
#if(LANG == CLANG)
void update_seed(void);
DEFAULT_MODE random(void);
unsigned long random32(void);
unsigned long long random64(void);
unsigned short random16(void);
unsigned char random8(void);
#endif

#endif