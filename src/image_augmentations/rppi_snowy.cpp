// rppi_snowy

// Uncomment the segment below to get this standalone to work for basic unit testing

#include "rppdefs.h"
#include "rppi_image_augumentations.h"
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "cpu/rpp_cpu_input_and_display.hpp"
#include <cpu/rpp_cpu_pixel_arrangement_conversions.hpp>
#include "cpu/host_snowy.hpp"
#include "../color_model_conversions/cpu/host_rgb_to_hsv.hpp"
#include "../color_model_conversions/cpu/host_hsv_to_rgb.hpp"
#include "../color_model_conversions/cpu/host_rgb_to_hsl.hpp"
#include "../color_model_conversions/cpu/host_hsl_to_rgb.hpp"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
using namespace std::chrono;





RppStatus
rppi_snowyRGB_u8_pln3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr,
                         Rpp32f strength)
{

    snowy_host<Rpp8u>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp8u*>(dstPtr),
                           strength,
                           RPPI_CHN_PLANAR, 3, RGB);
    return RPP_SUCCESS;
}

RppStatus
rppi_snowyRGB_u8_pkd3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr,
                         Rpp32f strength)
{

    snowy_host<Rpp8u>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp8u*>(dstPtr),
                           strength,
                           RPPI_CHN_PACKED, 3, RGB);
    return RPP_SUCCESS;
}

RppStatus
rppi_snowyHSV_u8_pln3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr,
                         Rpp32f strength)
{

    snowy_host<Rpp32f>(static_cast<Rpp32f*>(srcPtr), srcSize, static_cast<Rpp32f*>(dstPtr),
                           strength,
                           RPPI_CHN_PLANAR, 3, HSV);
    return RPP_SUCCESS;
}

RppStatus
rppi_snowyHSV_u8_pkd3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr,
                         Rpp32f strength)
{

    snowy_host<Rpp32f>(static_cast<Rpp32f*>(srcPtr), srcSize, static_cast<Rpp32f*>(dstPtr),
                           strength,
                           RPPI_CHN_PACKED, 3, HSV);
    return RPP_SUCCESS;
}





int main(int argc, char** argv)
{
    RppiSize srcSize, dstSize;
    unsigned int channel = 3;
    Rpp32f strength;

    do
    {
        printf("\nEnter strength: ");
        scanf("%f", &strength);
    } while (strength < 0 || strength > 1);

    int format;
    printf("\nEnter input matrix format: 1 = RGB, 2 = HSV: ");
    scanf("%d", &format);

    int input;
    printf("\nEnter input: 1 = image, 2 = pixel values: ");
    scanf("%d", &input);

    int type;
    printf("\nEnter type of arrangement: 1 = planar, 2 = packed: ");
    scanf("%d", &type);

    if (input == 1)
    {
        if ( argc != 2 )
        {
            printf("usage: DisplayImage.out <Image_Path>\n");
            return -1;
        }

        Mat imageIn = imread( argv[1], 1 );

        if ( !imageIn.data )
        {
            printf("No image data \n");
            return -1;
        }

        srcSize.height = imageIn.rows;
        srcSize.width = imageIn.cols;
        dstSize.height = srcSize.height;
        dstSize.width = srcSize.width;

        printf("\nInput Height - %d, Input Width - %d, Input Channels - %d\n", srcSize.height, srcSize.width, channel);
        Rpp8u *srcPtr = imageIn.data;

        printf("\nOutput Height - %d, Output Width - %d, Output Channels - %d\n", dstSize.height, dstSize.width, channel);
        Rpp8u *dstPtr = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
        
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();

        Mat imageOut;

        if (format == 1)
        {   if (type == 1)
            {   
                printf("\nExecuting pln3...\n");
                Rpp8u *srcPtrTemp = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
                Rpp8u *dstPtrTemp = (Rpp8u *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp8u));
                rppi_packed_to_planar_u8_pkd3_host(srcPtr, srcSize, srcPtrTemp);

                start = high_resolution_clock::now();
                rppi_snowyRGB_u8_pln3_host(srcPtrTemp, srcSize, dstPtrTemp, strength);
                stop = high_resolution_clock::now();

                rppi_planar_to_packed_u8_pln3_host(dstPtrTemp, dstSize, dstPtr);

                imageOut = Mat(dstSize.height, dstSize.width, CV_8UC3, dstPtr);
            }
            else if (type == 2)
            {   
                printf("\nExecuting pkd3...\n");

                start = high_resolution_clock::now();
                rppi_snowyRGB_u8_pkd3_host(srcPtr, srcSize, dstPtr, strength);
                stop = high_resolution_clock::now();

                imageOut = Mat(dstSize.height, dstSize.width, CV_8UC3, dstPtr);
            }
        }
        else if (format == 2)
        {   if (type == 1)
            {   
                printf("\nExecuting pln3...\n");
                Rpp8u *srcPtrTempRGB = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
                Rpp32f *srcPtrTempHSV = (Rpp32f *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp32f));
                Rpp32f *dstPtrTempHSV = (Rpp32f *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp32f));
                Rpp8u *dstPtrTempRGB = (Rpp8u *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp8u));

                rppi_packed_to_planar_u8_pkd3_host(srcPtr, srcSize, srcPtrTempRGB);

                rgb_to_hsv_host(srcPtrTempRGB, srcSize, srcPtrTempHSV, RPPI_CHN_PLANAR, 3);

                start = high_resolution_clock::now();
                rppi_snowyHSV_u8_pln3_host(srcPtrTempHSV, srcSize, dstPtrTempHSV, strength);
                stop = high_resolution_clock::now();

                hsv_to_rgb_host(dstPtrTempHSV, dstSize, dstPtrTempRGB, RPPI_CHN_PLANAR, 3);

                rppi_planar_to_packed_u8_pln3_host(dstPtrTempRGB, dstSize, dstPtr);

                imageOut = Mat(dstSize.height, dstSize.width, CV_8UC3, dstPtr);
            }
            else if (type == 2)
            {   
                printf("\nExecuting pkd3...\n");
                Rpp32f *srcPtrHSV = (Rpp32f *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp32f));
                Rpp32f *dstPtrHSV = (Rpp32f *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp32f));

                rgb_to_hsv_host(srcPtr, srcSize, srcPtrHSV, RPPI_CHN_PACKED, 3);

                start = high_resolution_clock::now();
                rppi_snowyHSV_u8_pkd3_host(srcPtrHSV, srcSize, dstPtrHSV, strength);
                stop = high_resolution_clock::now();

                hsv_to_rgb_host(dstPtrHSV, dstSize, dstPtr, RPPI_CHN_PACKED, 3);

                imageOut = Mat(dstSize.height, dstSize.width, CV_8UC3, dstPtr);
            }
        }


        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "\nTime taken (milliseconds) = " << duration.count() << endl;

        Mat images(imageIn.rows, imageIn.cols*2, imageIn.type());
        imageIn.copyTo(images(cv::Rect(0,0, imageIn.cols, imageIn.rows)));
        imageOut.copyTo(images(cv::Rect(imageIn.cols,0, imageIn.cols, imageIn.rows)));

        namedWindow("Input and Output Images", WINDOW_NORMAL );
        imshow("Input and Output Images", images);

        waitKey(0);

        return 0;
    }















    int matrix;
    printf("\nEnter matrix input style: 1 = default 1 channel (1x3x4), 2 = default 3 channel (3x3x4), 3 = customized: ");
    scanf("%d", &matrix);
    
    if (format == 1)
    {
        if (matrix == 1)
        {
            printf("\nThe function is only 3 channel compatible!\n");
        }
        else if (matrix == 2)
        {
            channel = 3;
            srcSize.height = 3;
            srcSize.width = 4;
            if (type == 1)
            {
                Rpp8u srcPtr[36] = {255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 130, 129, 128, 127, 126, 117, 113, 121, 127, 111, 100, 108, 65, 66, 67, 68, 69, 70, 71, 72, 13, 24, 15, 16};
                Rpp8u dstPtr[36] = {0};
                printf("\n\nInput:\n");
                displayPlanar(srcPtr, srcSize, channel);
                rppi_snowyRGB_u8_pln3_host(srcPtr, srcSize, dstPtr, strength);
                printf("\n\nOutput of snowy Modification:\n");
                displayPlanar(dstPtr, srcSize, channel);
            }
            else if (type == 2)
            {
                Rpp8u srcPtr[36] = {255, 130, 65, 254, 129, 66, 253, 128, 67, 252, 127, 68, 251, 126, 69, 250, 117, 70, 249, 113, 71, 248, 121, 72, 247, 127, 13, 246, 111, 24, 245, 100, 15, 244, 108, 16};
                Rpp8u dstPtr[36] = {0};
                printf("\n\nInput:\n");
                displayPacked(srcPtr, srcSize, channel);
                rppi_snowyRGB_u8_pkd3_host(srcPtr, srcSize, dstPtr, strength);
                printf("\n\nOutput of snowy Modification:\n");
                displayPacked(dstPtr, srcSize, channel);
            } 
        }
        else if (matrix == 3)
        {
            printf("\nEnter number of channels: ");
            scanf("%d", &channel);
            printf("Enter height of image in pixels: ");
            scanf("%d", &srcSize.height);
            printf("Enter width of image in pixels: ");
            scanf("%d", &srcSize.width);
            printf("Channels = %d, Height = %d, Width = %d", channel, srcSize.height, srcSize.width);
            Rpp8u *srcPtr = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
            Rpp8u *dstPtr = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
            int *intSrcPtr = (int *)calloc(channel * srcSize.height * srcSize.width, sizeof(int));
            if (type == 1)
            {
                printf("\n\n\n\nEnter elements in array of size %d x %d x %d in planar format: \n", channel, srcSize.height, srcSize.width);
                inputPlanar(intSrcPtr, srcSize, channel);
                cast(intSrcPtr, srcPtr, srcSize, channel);
                printf("\n\nInput:\n");
                displayPlanar(srcPtr, srcSize, channel);
                if (channel == 1)
                {
                    printf("\nThe function is only 3 channel compatible!\n");
                }
                else if (channel == 3)
                {
                    rppi_snowyRGB_u8_pln3_host(srcPtr, srcSize, dstPtr, strength);
                }
                printf("\n\nOutput of snowy Modification:\n");
                displayPlanar(dstPtr, srcSize, channel);
            }
            else if (type == 2)
            {
                printf("\n\n\n\nEnter elements in array of size %d x %d x %d in packed format: \n", channel, srcSize.height, srcSize.width);
                inputPacked(intSrcPtr, srcSize, channel);
                cast(intSrcPtr, srcPtr, srcSize, channel);
                printf("\n\nInput:\n");
                displayPacked(srcPtr, srcSize, channel);
                if (channel == 1)
                {
                    printf("\nThe function is only 3 channel compatible!\n");
                }
                else if (channel == 3)
                {
                    rppi_snowyRGB_u8_pkd3_host(srcPtr, srcSize, dstPtr, strength);
                }
                printf("\n\nOutput of snowy Modification:\n");
                displayPacked(dstPtr, srcSize, channel);
            }
        }
    }
    else if (format == 2)
    {
        if (matrix == 1)
        {
            printf("\nThe function is only 3 channel compatible!\n");
        }
        else if (matrix == 2)
        {
            channel = 3;
            srcSize.height = 3;
            srcSize.width = 4;
            if (type == 1)
            {
                Rpp32f srcPtr[36] = {21.00, 20.00, 20.00, 19.00, 19.00, 16.00, 14.00, 17.00, 29.00, 24.00, 22.00, 24.00, 0.75, 0.74, 0.74, 0.73, 0.73, 0.72, 0.71, 0.71, 0.95, 0.90, 0.94, 0.93, 1.00, 1.00, 0.99, 0.99, 0.98, 0.98, 0.98, 0.97, 0.97, 0.96, 0.96, 0.96};
                Rpp32f dstPtr[36] = {0};
                printf("\n\nInput:\n");
                displayPlanarF(srcPtr, srcSize, channel);
                rppi_snowyHSV_u8_pln3_host(srcPtr, srcSize, dstPtr, strength);
                printf("\n\nOutput of snowy Modification:\n");
                displayPlanarF(dstPtr, srcSize, channel);
            }
            else if (type == 2)
            {
                Rpp32f srcPtr[36] = {21.0, 0.75, 1.0, 20.0, 0.74, 1.0, 20.0, 0.74, 0.99, 19.0, 0.73, 0.99, 19.0, 0.73, 0.98, 16.0, 0.72, 0.98, 14.0, 0.71, 0.98, 17.0, 0.71, 0.97, 29.0, 0.95, 0.97, 24.0, 0.9, 0.96, 22.0, 0.94, 0.96, 24.0, 0.93, 0.96};
                Rpp32f dstPtr[36] = {0};
                printf("\n\nInput:\n");
                displayPackedF(srcPtr, srcSize, channel);
                rppi_snowyHSV_u8_pkd3_host(srcPtr, srcSize, dstPtr, strength);
                printf("\n\nOutput of snowy Modification:\n");
                displayPackedF(dstPtr, srcSize, channel);
            }
        }
        else if (matrix == 3)
        {
            printf("\nEnter number of channels: ");
            scanf("%d", &channel);
            printf("Enter height of image in pixels: ");
            scanf("%d", &srcSize.height);
            printf("Enter width of image in pixels: ");
            scanf("%d", &srcSize.width);
            printf("Channels = %d, Height = %d, Width = %d", channel, srcSize.height, srcSize.width);
            Rpp32f *srcPtr = (Rpp32f *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp32f));
            Rpp32f *dstPtr = (Rpp32f *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp32f));
            if (type == 1)
            {
                printf("\n\n\n\nEnter elements in array of size %d x %d x %d in planar format: \n", channel, srcSize.height, srcSize.width);
                inputPlanarF(srcPtr, srcSize, channel);
                printf("\n\nInput:\n");
                displayPlanarF(srcPtr, srcSize, channel);
                if (channel == 1)
                {
                    printf("\nThe function is only 3 channel compatible!\n");
                }
                else if (channel == 3)
                {
                    rppi_snowyHSV_u8_pln3_host(srcPtr, srcSize, dstPtr, strength);
                }
                printf("\n\nOutput of snowy Modification:\n");
                displayPlanarF(dstPtr, srcSize, channel);
            }
            else if (type == 2)
            {
                printf("\n\n\n\nEnter elements in array of size %d x %d x %d in packed format: \n", channel, srcSize.height, srcSize.width);
                inputPackedF(srcPtr, srcSize, channel);
                printf("\n\nInput:\n");
                displayPackedF(srcPtr, srcSize, channel);
                if (channel == 1)
                {
                    printf("\nThe function is only 3 channel compatible!\n");
                }
                else if (channel == 3)
                {
                    rppi_snowyHSV_u8_pkd3_host(srcPtr, srcSize, dstPtr, strength);
                }
                printf("\n\nOutput of snowy Modification:\n");
                displayPackedF(dstPtr, srcSize, channel);
            }
        }
    }
    
}
