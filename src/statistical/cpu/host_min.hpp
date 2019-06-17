#include <cpu/rpp_cpu_common.hpp>

template <typename T>
RppStatus min_host(T* srcPtr1, T* srcPtr2, RppiSize srcSize, T* dstPtr,
                                   unsigned int channel)
{
    for (int i = 0; i < (channel * srcSize.width * srcSize.height); i++)
    {
        dstPtr[i] = RPPMIN2(srcPtr1[i], srcPtr2[i]);
    }

    return RPP_SUCCESS;

}