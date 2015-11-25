#include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <iostream>
 #include <stdio.h>
 #include <stdlib.h>

 using namespace cv;
 using namespace std;

 Mat src; Mat src_gray;
Mat tmp_frame, edges, dst;
 int thresh = 100;
 int max_thresh = 255;
 RNG rng(12345);

 /// Function header
 void thresh_callback(int, void* );

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";
char* source_window = "Source";
/** @function main */
int main( int argc, char** argv )
 {
      // recupere la camera
   VideoCapture cap;
   

        
   cap.open(0);
   if( !cap.isOpened() )
    {
        printf("\nCLa webcam ne c'est pas ouverte !\n");
        return -1;
    }


 

    for(;;)
    {
      cap >> src;
      if( src.empty() )
            break;
      /// Convert image to gray and blur it
      cvtColor( src, src_gray, CV_BGR2GRAY );
      GaussianBlur(src_gray, src_gray, Size(7,7), 3.5, 3.5);

   
      namedWindow( source_window, CV_WINDOW_AUTOSIZE );
      imshow( source_window, src );

      createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
      thresh_callback( 0, 0 );

      int keycode = waitKey(30);
        if( keycode == 27 )
            break;

   }
   return(0);
 }

 /** @function thresh_callback */
 void thresh_callback(int, void* )
 {
   Mat src_copy = src.clone();
   Mat threshold_output;
   vector<vector<Point> > contours;
   vector<Vec4i> hierarchy;
   // Creer  la window

   
   namedWindow( "Contour fenetre", CV_WINDOW_AUTOSIZE );
   

   createTrackbar( trackbar_type, "Contour fenetre", &threshold_type, max_type, NULL );
   createTrackbar( trackbar_value, "Contour fenetre", &threshold_value, max_value, NULL );

   threshold( src_gray, threshold_output, threshold_value, max_BINARY_value,threshold_type );
 
   findContours( threshold_output, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  
   vector<vector<Point> >hull( contours.size() );
   for( int i = 0; i < contours.size(); i++ ){

         convexHull( Mat(contours[i]), hull[i], false ); 
   }
   printf("%d\n",contours.size() );

   Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
   for( int i = 0; i< contours.size(); i++ )
      {
         int val = (i + 1 ) * 92978 ;
         printf("%d %d  %d \n", val  % 256,  val  / 256 % 256, val/ 256 / 256 % 256 );
        Scalar color = Scalar( val % 256,  val  / 256 % 256, val / 256 / 256 % 256 );
        drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       // drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
      }

  
  // Affiche la window
   imshow( "Hull demo", drawing );
 }