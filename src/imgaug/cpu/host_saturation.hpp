#include <cpu/rpp_cpu_common.hpp>

template <typename T, typename U>
RppStatus saturation_host(T* srcPtr, RppiSize srcSize, U* dstPtr,
                    Rpp32f saturationFactor,
                    RppiChnFormat chnFormat, unsigned channel, RppiFormat imageFormat)
{
    if (imageFormat == RGB)
    {
        if (chnFormat == RPPI_CHN_PLANAR)
        {
            Rpp32u channel = 3;
            Rpp32f *pHSV = (Rpp32f *)malloc(channel * srcSize.width * srcSize.height * sizeof(Rpp32f));
            for (int i = 0; i < (srcSize.width * srcSize.height); i++)
            {
                float rf, gf, bf, cmax, cmin, delta;
                rf = ((float) srcPtr[i]) / 255;
                gf = ((float) srcPtr[i + (srcSize.width * srcSize.height)]) / 255;
                bf = ((float) srcPtr[i + (2 * srcSize.width * srcSize.height)]) / 255;
                cmax = ((rf > gf) && (rf > bf)) ? rf : ((gf > bf) ? gf : bf);
                cmin = ((rf < gf) && (rf < bf)) ? rf : ((gf < bf) ? gf : bf);
                delta = cmax - cmin;

                if (delta == 0)
                {
                    pHSV[i] = 0;
                }
                else if (cmax == rf)
                {
                    pHSV[i] = round(60 * fmod(((gf - bf) / delta),6));
                }
                else if (cmax == gf)
                {
                    pHSV[i] = round(60 * (((bf - rf) / delta) + 2));
                }
                else if (cmax == bf)
                {
                    pHSV[i] = round(60 * (((rf - gf) / delta) + 4));
                }
                
                while (pHSV[i] > 360)
                {
                    pHSV[i] = pHSV[i] - 360;
                }
                while (pHSV[i] < 0)
                {
                    pHSV[i] = 360 + pHSV[i];
                }

                if (cmax == 0)
                {
                    pHSV[i + (srcSize.width * srcSize.height)] = 0;
                }
                else
                {
                    pHSV[i + (srcSize.width * srcSize.height)] = delta / cmax;
                }

                pHSV[i + (2 * srcSize.width * srcSize.height)] = cmax;

            }
            for (int i = 0; i < (srcSize.width * srcSize.height); i++)
            {
                pHSV[i + (srcSize.width * srcSize.height)] *= saturationFactor;
                pHSV[i + (srcSize.width * srcSize.height)] = (pHSV[i + (srcSize.width * srcSize.height)] < (float) 1) ? pHSV[i + (srcSize.width * srcSize.height)] : ((float) 1);
                pHSV[i + (srcSize.width * srcSize.height)] = (pHSV[i + (srcSize.width * srcSize.height)] > (float) 0) ? pHSV[i + (srcSize.width * srcSize.height)] : ((float) 0);
            }
            for (int i = 0; i < (srcSize.width * srcSize.height); i++)
            {
                float c, x, m, rf, gf, bf;
                c = pHSV[i + (2 * srcSize.width * srcSize.height)] * pHSV[i + (srcSize.width * srcSize.height)];
                x = c * (1 - abs((fmod((pHSV[i] / 60), 2)) - 1));
                m = pHSV[i + (2 * srcSize.width * srcSize.height)] - c;
                
                if ((0 <= pHSV[i]) && (pHSV[i] < 60))
                {
                    rf = c;
                    gf = x;
                    bf = 0;
                }
                else if ((60 <= pHSV[i]) && (pHSV[i] < 120))
                {
                    rf = x;
                    gf = c;
                    bf = 0;
                }
                else if ((120 <= pHSV[i]) && (pHSV[i] < 180))
                {
                    rf = 0;
                    gf = c;
                    bf = x;
                }
                else if ((180 <= pHSV[i]) && (pHSV[i] < 240))
                {
                    rf = 0;
                    gf = x;
                    bf = c;
                }
                else if ((240 <= pHSV[i]) && (pHSV[i] < 300))
                {
                    rf = x;
                    gf = 0;
                    bf = c;
                }
                else if ((300 <= pHSV[i]) && (pHSV[i] < 360))
                {
                    rf = c;
                    gf = 0;
                    bf = x;
                }

                dstPtr[i] = (Rpp8u) round((rf + m) * 255);
                dstPtr[i + (srcSize.width * srcSize.height)] = (Rpp8u) round((gf + m) * 255);
                dstPtr[i + (2 * srcSize.width * srcSize.height)] = (Rpp8u) round((bf + m) * 255);
            }
        }
        else if (chnFormat == RPPI_CHN_PACKED)
        {
            Rpp32u channel = 3;
            Rpp32f *pHSV = (Rpp32f *)malloc(channel * srcSize.width * srcSize.height * sizeof(Rpp32f));
            for (int i = 0; i < (3 * srcSize.width * srcSize.height); i += 3)
            {
                float rf, gf, bf, cmax, cmin, delta;
                rf = ((float) srcPtr[i]) / 255;
                gf = ((float) srcPtr[i + 1]) / 255;
                bf = ((float) srcPtr[i + 2]) / 255;
                cmax = ((rf > gf) && (rf > bf)) ? rf : ((gf > bf) ? gf : bf);
                cmin = ((rf < gf) && (rf < bf)) ? rf : ((gf < bf) ? gf : bf);
                delta = cmax - cmin;

                if (delta == 0)
                {
                    pHSV[i] = 0;
                }
                else if (cmax == rf)
                {
                    pHSV[i] = round(60 * fmod(((gf - bf) / delta),6));
                }
                else if (cmax == gf)
                {
                    pHSV[i] = round(60 * (((bf - rf) / delta) + 2));
                }
                else if (cmax == bf)
                {
                    pHSV[i] = round(60 * (((rf - gf) / delta) + 4));
                }
                
                while (pHSV[i] > 360)
                {
                    pHSV[i] = pHSV[i] - 360;
                }
                while (pHSV[i] < 0)
                {
                    pHSV[i] = 360 + pHSV[i];
                }

                if (cmax == 0)
                {
                    pHSV[i + 1] = 0;
                }
                else
                {
                    pHSV[i + 1] = delta / cmax;
                }

                pHSV[i + 2] = cmax;

            }
            for (int i = 0; i < (3 * srcSize.width * srcSize.height); i += 3)
            {
                pHSV[i + 1] *= saturationFactor;
                pHSV[i + 1] = (pHSV[i + 1] < (float) 1) ? pHSV[i + 1] : ((float) 1);
                pHSV[i + 1] = (pHSV[i + 1] > (float) 0) ? pHSV[i + 1] : ((float) 0);
            }
            for (int i = 0; i < (3 * srcSize.width * srcSize.height); i += 3)
            {
                float c, x, m, rf, gf, bf;
                c = pHSV[i + 2] * pHSV[i + 1];
                x = c * (1 - abs((fmod((pHSV[i] / 60), 2)) - 1));
                m = pHSV[i + 2] - c;
                
                if ((0 <= pHSV[i]) && (pHSV[i] < 60))
                {
                    rf = c;
                    gf = x;
                    bf = 0;
                }
                else if ((60 <= pHSV[i]) && (pHSV[i] < 120))
                {
                    rf = x;
                    gf = c;
                    bf = 0;
                }
                else if ((120 <= pHSV[i]) && (pHSV[i] < 180))
                {
                    rf = 0;
                    gf = c;
                    bf = x;
                }
                else if ((180 <= pHSV[i]) && (pHSV[i] < 240))
                {
                    rf = 0;
                    gf = x;
                    bf = c;
                }
                else if ((240 <= pHSV[i]) && (pHSV[i] < 300))
                {
                    rf = x;
                    gf = 0;
                    bf = c;
                }
                else if ((300 <= pHSV[i]) && (pHSV[i] < 360))
                {
                    rf = c;
                    gf = 0;
                    bf = x;
                }

                dstPtr[i] = (Rpp8u) round((rf + m) * 255);
                dstPtr[i + 1] = (Rpp8u) round((gf + m) * 255);
                dstPtr[i + 2] = (Rpp8u) round((bf + m) * 255);
            }
        }
    }
    else if (imageFormat == HSV)
    {
        if (chnFormat == RPPI_CHN_PLANAR)
        {
            Rpp32u channel = 3;
            for (int i = 0; i < (channel * srcSize.width * srcSize.height); i++)
            {
                dstPtr[i] = srcPtr[i];
            }
            for (int i = 0; i < (srcSize.width * srcSize.height); i++)
            {
                dstPtr[i + (srcSize.width * srcSize.height)] *= saturationFactor;
                dstPtr[i + (srcSize.width * srcSize.height)] = (dstPtr[i + (srcSize.width * srcSize.height)] < (float) 1) ? dstPtr[i + (srcSize.width * srcSize.height)] : ((float) 1);
                dstPtr[i + (srcSize.width * srcSize.height)] = (dstPtr[i + (srcSize.width * srcSize.height)] > (float) 0) ? dstPtr[i + (srcSize.width * srcSize.height)] : ((float) 0);
            }
        }
        else if (chnFormat == RPPI_CHN_PACKED)
        {
            Rpp32u channel = 3;
            for (int i = 0; i < (channel * srcSize.width * srcSize.height); i++)
            {
                dstPtr[i] = srcPtr[i];
            }
            for (int i = 0; i < (3 * srcSize.width * srcSize.height); i += 3)
            {
                dstPtr[i + 1] *= saturationFactor;
                dstPtr[i + 1] = (dstPtr[i + 1] < (float) 1) ? dstPtr[i + 1] : ((float) 1);
                dstPtr[i + 1] = (dstPtr[i + 1] > (float) 0) ? dstPtr[i + 1] : ((float) 0);
            }
        }
    }

    return RPP_SUCCESS;
}