#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include <stdio.h>
#include <string>
using namespace std;
using namespace cv;



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


    Mat tmp_frame, edges, dst;
    cap >> tmp_frame;

    if(tmp_frame.empty())
    {
        printf("can not read data from the video source\n");
        return -1;
    }
    namedWindow("video", 1);


    for(;;)
    {
        cap >> tmp_frame;
        if( tmp_frame.empty() )
            break;

        // cvtColor(tmp_frame, edges, CV_BGR2GRAY);
        // GaussianBlur(edges, edges, Size(7,7), 3.5, 3.5);


        imshow("video", tmp_frame);
        int keycode = waitKey(30);
        if( keycode == 27 )
            break;
        
    }