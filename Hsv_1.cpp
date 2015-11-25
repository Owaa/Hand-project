#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include <stdio.h>
#include <string>
 
#include <iostream>
#include <stdlib.h>
using namespace std;
using namespace cv;

Mat tmp_frame, img_hsv, mask, output ;

int h = 0, s = 0, v = 0, tolerance = 10;

void getObjectColor(int event, int x, int y, int flags, void *param = NULL) {
 
    // Vars
    CvScalar pixel;
    //Mat hsv;
 
    if(event == CV_EVENT_LBUTTONUP) {
 
        
        //cvtColor(tmp_frame,hsv,CV_BGR2HSV);
       
        pixel.val[0] = img_hsv.at<Vec3b>(Point(x, y))[0];
        pixel.val[1] = img_hsv.at<Vec3b>(Point(x, y))[1];
        pixel.val[2] = img_hsv.at<Vec3b>(Point(x, y))[2];
 
         printf("%d\n", tmp_frame.at<Vec3b>(Point(x, y))[1]);
 //        // Change the value of the tracked color with the color of the selected pixel
        h = (int)pixel.val[0];
        s = (int)pixel.val[1];
        v = (int)pixel.val[2];
 
        // Release the memory of the hsv image
           // cvReleaseImage(&hsv);
 
    }
 
}


int main(int argc, char** argv)
{
    VideoCapture cap;
    if( argc < 2 )
        cap.open(0);
    else
        cap.open(std::string(argv[1]));
    if( !cap.isOpened() )
    {
        printf("\nCan not open camera or video file\n");
        return -1;
    }

    string nameWindow = "winwow output";
    
    cap >> tmp_frame;

    if(tmp_frame.empty())
    {
        printf("can not read data from the video source\n");
        return -1;
    }
    namedWindow(nameWindow, 1);
    namedWindow("input", 1);
    setMouseCallback(nameWindow, getObjectColor, NULL);

    for(;;)
    {
        cap >> tmp_frame;
        if( tmp_frame.empty() )
            break;
        printf(" %d   %d   %d\n" , h , s , v);
        cvtColor(tmp_frame,img_hsv,CV_BGR2HSV);

        mask = img_hsv.clone();
         
        Scalar lower = Scalar( h - tolerance , s - tolerance , v );
        Scalar upper = Scalar( h + tolerance , s + tolerance , v);
        inRange(img_hsv, lower, upper, mask);
        //bitwise_and(tmp_frame, tmp_frame, output, mask= mask);

        imshow(nameWindow , mask);

       // imshow("input" , tmp_frame);
        int keycode = waitKey(30);
        if( keycode == 27 )
            break;
        
    }
    return 0;
}