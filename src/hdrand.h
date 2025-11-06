#ifndef _RANDOM_TEMPERATURE_GENERATOR_H
#define _RANDOM_TEMPERATURE_GENERATOR_H

#define RDRAND_METHOD (unsigned char)0x00
#define RDSEED_METHOD (unsigned char)0x01
#define NOSEED 0
#define DEBUG 0
#define NOT_SUPPORT 0xFF

#define MODE 0x64
#if (MODE == 0x64)
    #define DEFAULT_MODE unsigned long long
#endif
#if (MODE == 0x86)
    #define DEFAULT_MODE unsigned long
#endif

/*
Generate a random number by hardware using termal entropy and raw entropy.

The library only works with the rdrand and rdseed CPU commands.
If your CPU is younger than the x86 architecture, these commands will not work. 
*/
template <typename T = DEFAULT_MODE>
class HardwareRandom{
    public:
    HardwareRandom(T seed);
    HardwareRandom(T seed, unsigned char method);
    HardwareRandom(void);
    //HardwareRandom(unsigned char method);

    unsigned long long random64(void);
    unsigned long random32(void);
    DEFAULT_MODE random(void);

    private:
    int (*random_method)(); 
    void update_seed(void);
    T seed;
};

#endif