// rppi_convert_bit_depth

// Uncomment the segment below to get this standalone to work for basic unit testing

#include "rppdefs.h"
#include "rppi_filter_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "cpu/rpp_cpu_input_and_display.hpp"
#include <cpu/rpp_cpu_pixel_arrangement_conversions.hpp>
#include "cpu/host_convert_bit_depth.hpp"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
using namespace std::chrono;




RppStatus
rppi_convert_bit_depth_u8s8_pln1_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp8s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp8s*>(dstPtr),
                                         1, 
                                         RPPI_CHN_PLANAR, 1);
    return RPP_SUCCESS;
}

RppStatus
rppi_convert_bit_depth_u8s8_pln3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp8s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp8s*>(dstPtr),
                                         1, 
                                         RPPI_CHN_PLANAR, 3);
    return RPP_SUCCESS;
}

RppStatus
rppi_convert_bit_depth_u8s8_pkd3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp8s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp8s*>(dstPtr),
                                         1, 
                                         RPPI_CHN_PACKED, 3);
    return RPP_SUCCESS;
}



RppStatus
rppi_convert_bit_depth_u8u16_pln1_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp16u>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp16u*>(dstPtr),
                                         2, 
                                         RPPI_CHN_PLANAR, 1);
    return RPP_SUCCESS;
}

RppStatus
rppi_convert_bit_depth_u8u16_pln3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp16u>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp16u*>(dstPtr),
                                         2, 
                                         RPPI_CHN_PLANAR, 3);
    return RPP_SUCCESS;
}

RppStatus
rppi_convert_bit_depth_u8u16_pkd3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp16u>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp16u*>(dstPtr),
                                         2, 
                                         RPPI_CHN_PACKED, 3);
    return RPP_SUCCESS;
}



RppStatus
rppi_convert_bit_depth_u8s16_pln1_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp16s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp16s*>(dstPtr),
                                         3, 
                                         RPPI_CHN_PLANAR, 1);
    return RPP_SUCCESS;
}

RppStatus
rppi_convert_bit_depth_u8s16_pln3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp16s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp16s*>(dstPtr),
                                         3, 
                                         RPPI_CHN_PLANAR, 3);
    return RPP_SUCCESS;
}

RppStatus
rppi_convert_bit_depth_u8s16_pkd3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
{
    convert_bit_depth_host<Rpp8u, Rpp16s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp16s*>(dstPtr),
                                         3, 
                                         RPPI_CHN_PACKED, 3);
    return RPP_SUCCESS;
}



//RppStatus
//rppi_convert_bit_depth_u8s32_pln1_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
//{
//    convert_bit_depth_host<Rpp8u, Rpp32s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp32s*>(dstPtr),
//                                         4, 
//                                         RPPI_CHN_PLANAR, 1);
//    return RPP_SUCCESS;
//}
//
//RppStatus
//rppi_convert_bit_depth_u8s32_pln3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
//{
//    convert_bit_depth_host<Rpp8u, Rpp32s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp32s*>(dstPtr),
//                                         4, 
//                                         RPPI_CHN_PLANAR, 3);
//    return RPP_SUCCESS;
//}
//
//RppStatus
//rppi_convert_bit_depth_u8s32_pkd3_host(RppPtr_t srcPtr, RppiSize srcSize, RppPtr_t dstPtr)
//{
//    convert_bit_depth_host<Rpp8u, Rpp32s>(static_cast<Rpp8u*>(srcPtr), srcSize, static_cast<Rpp32s*>(dstPtr),
//                                         4, 
//                                         RPPI_CHN_PACKED, 3);
//    return RPP_SUCCESS;
//}





int main(int argc, char** argv)
{
    RppiSize srcSize, dstSize;
    unsigned int channel;

    int conversionType = 0;
    printf("\nEnter conversion type: 1 = Rpp8u to Rpp8s, 2 = Rpp8u to Rpp16u, 3 = Rpp8u to Rpp16s: ");
    scanf("%d", &conversionType);

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

        do
        {   printf("\nThe image input/inputs can be interpreted as 1 or 3 channel (greyscale or RGB). Please choose - only 1 or 3: ");
            scanf("%d", &channel);
        }while (channel != 1 && channel != 3);

        Mat imageIn;

        if (channel == 1)
        {
            imageIn = imread( argv[1], 0 );
        }
        else if (channel ==3)
        {
            imageIn = imread( argv[1], 1 );
        }

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

        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();

        Mat imageOut;

        if (conversionType == 1)
        {
            Rpp8s *dstPtr = (Rpp8s *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8s));
            if (type == 1)
            {   
                if (channel == 1)
                {
                    printf("\nExecuting pln1...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s8_pln1_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_8SC1, dstPtr);
                    
                }
                else if (channel == 3)
                {
                    printf("\nExecuting pln3...\n");
                    Rpp8u *srcPtrTemp = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
                    Rpp8s *dstPtrTemp = (Rpp8s *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp8s));
                    rppi_packed_to_planar_u8_pkd3_host(srcPtr, srcSize, srcPtrTemp);

                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s8_pln3_host(srcPtrTemp, srcSize, dstPtrTemp);
                    stop = high_resolution_clock::now();

                    rppi_planar_to_packed_s8_pln3_host(dstPtrTemp, dstSize, dstPtr);

                    imageOut = Mat(dstSize.height, dstSize.width, CV_8SC3, dstPtr);
                }
            }
            else if (type == 2)
            {   
                if (channel == 1)
                {
                    printf("\nExecuting pln1 for pkd1...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s8_pln1_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_8SC1, dstPtr);
                }
                else if (channel ==3)
                {
                    printf("\nExecuting pkd3...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s8_pkd3_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_8SC3, dstPtr);
                }
            }
        }
        else if (conversionType == 2)
        {
            Rpp16u *dstPtr = (Rpp16u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp16u));
            if (type == 1)
            {   
                if (channel == 1)
                {
                    printf("\nExecuting pln1...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8u16_pln1_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16UC1, dstPtr);
                    
                }
                else if (channel == 3)
                {
                    printf("\nExecuting pln3...\n");
                    Rpp8u *srcPtrTemp = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
                    Rpp16u *dstPtrTemp = (Rpp16u *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp16u));
                    rppi_packed_to_planar_u8_pkd3_host(srcPtr, srcSize, srcPtrTemp);

                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8u16_pln3_host(srcPtrTemp, srcSize, dstPtrTemp);
                    stop = high_resolution_clock::now();

                    rppi_planar_to_packed_u16_pln3_host(dstPtrTemp, dstSize, dstPtr);

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16UC3, dstPtr);
                }
            }
            else if (type == 2)
            {   
                if (channel == 1)
                {
                    printf("\nExecuting pln1 for pkd1...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8u16_pln1_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16UC1, dstPtr);
                }
                else if (channel ==3)
                {
                    printf("\nExecuting pkd3...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8u16_pkd3_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16UC3, dstPtr);
                }
            }
        }
        else if (conversionType == 3)
        {
            Rpp16s *dstPtr = (Rpp16s *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp16s));
            if (type == 1)
            {   
                if (channel == 1)
                {
                    printf("\nExecuting pln1...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s16_pln1_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16SC1, dstPtr);
                    
                }
                else if (channel == 3)
                {
                    printf("\nExecuting pln3...\n");
                    Rpp8u *srcPtrTemp = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
                    Rpp16s *dstPtrTemp = (Rpp16s *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp16s));
                    rppi_packed_to_planar_u8_pkd3_host(srcPtr, srcSize, srcPtrTemp);

                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s16_pln3_host(srcPtrTemp, srcSize, dstPtrTemp);
                    stop = high_resolution_clock::now();

                    rppi_planar_to_packed_s16_pln3_host(dstPtrTemp, dstSize, dstPtr);

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16SC3, dstPtr);
                }
            }
            else if (type == 2)
            {   
                if (channel == 1)
                {
                    printf("\nExecuting pln1 for pkd1...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s16_pln1_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16SC1, dstPtr);
                }
                else if (channel ==3)
                {
                    printf("\nExecuting pkd3...\n");
                    start = high_resolution_clock::now();
                    rppi_convert_bit_depth_u8s16_pkd3_host(srcPtr, srcSize, dstPtr);
                    stop = high_resolution_clock::now();

                    imageOut = Mat(dstSize.height, dstSize.width, CV_16SC3, dstPtr);
                }
            }
        }
        //else if (conversionType == 4)
        //{
        //    Rpp32s *dstPtr = (Rpp32s *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp32s));
        //    if (type == 1)
        //    {   
        //        if (channel == 1)
        //        {
        //            printf("\nExecuting pln1...\n");
        //            start = high_resolution_clock::now();
        //            rppi_convert_bit_depth_u8s32_pln1_host(srcPtr, srcSize, dstPtr);
        //            stop = high_resolution_clock::now();
        //            
        //            imageOut = Mat(dstSize.height, dstSize.width, CV_32SC1, dstPtr);
        //            
        //        }
        //        else if (channel == 3)
        //        {
        //            printf("\nExecuting pln3...\n");
        //            Rpp8u *srcPtrTemp = (Rpp8u *)calloc(channel * srcSize.height * srcSize.width, sizeof(Rpp8u));
        //            Rpp32s *dstPtrTemp = (Rpp32s *)calloc(channel * dstSize.height * dstSize.width, sizeof(Rpp32s));
        //            rppi_packed_to_planar_u8_pkd3_host(srcPtr, srcSize, srcPtrTemp);
        //            
        //            start = high_resolution_clock::now();
        //            rppi_convert_bit_depth_u8s32_pln3_host(srcPtrTemp, srcSize, dstPtrTemp);
        //            stop = high_resolution_clock::now();
        //            
        //            rppi_planar_to_packed_s32_pln3_host(dstPtrTemp, dstSize, dstPtr);
        //            
        //            imageOut = Mat(dstSize.height, dstSize.width, CV_32SC3, dstPtr);
        //        }
        //    }
        //    else if (type == 2)
        //    {   
        //        if (channel == 1)
        //        {
        //            printf("\nExecuting pln1 for pkd1...\n");
        //            start = high_resolution_clock::now();
        //            rppi_convert_bit_depth_u8s32_pln1_host(srcPtr, srcSize, dstPtr);
        //            stop = high_resolution_clock::now();
        //            
        //            imageOut = Mat(dstSize.height, dstSize.width, CV_32SC1, dstPtr);
        //        }
        //        else if (channel ==3)
        //        {
        //            printf("\nExecuting pkd3...\n");
        //            start = high_resolution_clock::now();
        //            rppi_convert_bit_depth_u8s32_pkd3_host(srcPtr, srcSize, dstPtr);
        //            stop = high_resolution_clock::now();
        //            
        //            imageOut = Mat(dstSize.height, dstSize.width, CV_32SC3, dstPtr);
        //        }
        //    }
        //}

        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "\nTime taken (milliseconds) = " << duration.count() << endl;

        namedWindow("Input Image", WINDOW_NORMAL );
        imshow("Input Image", imageIn);

        namedWindow("Output Image", WINDOW_NORMAL );
        imshow("Output Image", imageOut);

        waitKey(0);

        return 0;
    }
/*     
    int matrix;
    printf("\nEnter matrix input style: 1 = default 1 channel (1x3x4), 2 = default 3 channel (3x3x4), 3 = customized: ");
    scanf("%d", &matrix);

    if (matrix == 1)
    {
        channel = 1;
        srcSize.height = 3;
        srcSize.width = 4;
        Rpp8u srcPtr[12] = {130, 129, 128, 127, 126, 117, 113, 121, 127, 111, 100, 108};
        Rpp8u dstPtr[12] = {0};
        printf("\n\nInput:\n");
        displayPlanar(srcPtr, srcSize, channel);
        rppi_convert_bit_depth_u8_pln1_host(srcPtr, srcSize, dstPtr);
        printf("\n\nOutput of convert_bit_depth:\n");
        displayPlanar(dstPtr, srcSize, channel);
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
            rppi_convert_bit_depth_u8_pln3_host(srcPtr, srcSize, dstPtr);
            printf("\n\nOutput of convert_bit_depth:\n");
            displayPlanar(dstPtr, srcSize, channel);
        }
        else if (type == 2)
        {
            Rpp8u srcPtr[36] = {255, 130, 65, 254, 129, 66, 253, 128, 67, 252, 127, 68, 251, 126, 69, 250, 117, 70, 249, 113, 71, 248, 121, 72, 247, 127, 13, 246, 111, 24, 245, 100, 15, 244, 108, 16};
            Rpp8u dstPtr[36] = {0};
            printf("\n\nInput:\n");
            displayPacked(srcPtr, srcSize, channel);
            rppi_convert_bit_depth_u8_pkd3_host(srcPtr, srcSize, dstPtr);
            printf("\n\nOutput of convert_bit_depth:\n");
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
                rppi_convert_bit_depth_u8_pln1_host(srcPtr, srcSize, dstPtr);
            }
            else if (channel == 3)
            {
                rppi_convert_bit_depth_u8_pln3_host(srcPtr, srcSize, dstPtr);
            }
            printf("\n\nOutput of convert_bit_depth:\n");
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
                rppi_convert_bit_depth_u8_pln1_host(srcPtr, srcSize, dstPtr);
            }
            else if (channel == 3)
            {
                rppi_convert_bit_depth_u8_pkd3_host(srcPtr, srcSize, dstPtr);
            }
            printf("\n\nOutput of convert_bit_depth:\n");
            displayPacked(dstPtr, srcSize, channel);
        }
    }
*/
}
