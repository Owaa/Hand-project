#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include <stdio.h>
#include <string>
using namespace std;
using namespace cv;




int edgeThresh = 1;
int lowThreshold = 40;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;

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

        cvtColor(tmp_frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 3.5, 3.5);
  	
  	   	Canny( edges, edges, lowThreshold, lowThreshold * 3, kernel_size );

  		  dst = Scalar::all(0);
    	  tmp_frame.copyTo( dst, edges);
        
        createTrackbar( "Min Threshold:", "video", &lowThreshold, max_lowThreshold, NULL );
        imshow("video", edges);
        int keycode = waitKey(30);
        if( keycode == 27 )
            break;
        
    }
    return 0;
}