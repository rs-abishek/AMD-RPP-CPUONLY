#include <cpu/rpp_cpu_common.hpp>

template <typename T>
RppStatus gamma_correction_host(T* srcPtr, RppiSize srcSize, T* dstPtr,
                                   Rpp32f gamma,
                                   Rpp32u channel)
{
    T *srcPtrTemp, *dstPtrTemp;
    srcPtrTemp = srcPtr;
    dstPtrTemp = dstPtr;

    Rpp8u pixel;

    for (int i = 0; i < (channel * srcSize.width * srcSize.height); i++)
    {
        pixel = ((Rpp32f) (*srcPtrTemp)) / 255.0;
        pixel = pow(pixel, gamma);
        pixel = pixel * 255.0;
        *dstPtrTemp = (T) pixel;
        srcPtrTemp++;
        dstPtrTemp++;
    }

    return RPP_SUCCESS;

}
