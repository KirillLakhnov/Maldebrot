//#define NO_O
//#define SSE 
//#define AVX2
//#define AVX512

#include "maldebrot.hpp"

#ifdef NO_O
    #include "maldebrot_no.hpp"
#endif

#ifdef SSE
    #include "maldebrot_SSE.hpp"
#endif

#ifdef AVX2
    #include "maldebrot_AVX2.hpp"
#endif

#ifdef AVX512
    #include "maldebrot_AVX512.hpp"
#endif


int main ()
{
#ifdef NO_O
    maldebrot (set_maldebrot_no_o);
 #endif

#ifdef SSE
    maldebrot (set_maldebrot_sse);
#endif

#ifdef AVX2
    maldebrot (set_maldebrot_avx2);
#endif

#ifdef AVX512
    maldebrot (set_maldebrot_avx512);
#endif

    return 0;
}