#include "host_declarations.hpp"

template <typename T>
RppStatus host_xor(T* srcPtr1, T* srcPtr2, RppiSize srcSize, T* dstPtr,
                                   unsigned int channel)
{
    for (int i = 0; i < (channel * srcSize.width * srcSize.height); i++)
    {
        Rpp32s pixel = ((Rpp32s) srcPtr1[i]) ^ ((Rpp32s) srcPtr2[i]);
        pixel = (pixel < (Rpp32s) 255) ? pixel : ((Rpp32s) 255);
        pixel = (pixel > (Rpp32s) 0) ? pixel : ((Rpp32s) 0);
        dstPtr[i] =(Rpp8u) pixel;
    }

    return RPP_SUCCESS;

}