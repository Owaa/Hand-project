/*!\file openCV.c
 *
 * \brief intro OpenCV
 * 
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 *
 * \date January 30 2015
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>

 
 static void toGray(IplImage * img);
 static void isolation(IplImage * img , IplImage * img2);


int main(int argc, char ** argv) {
 IplImage* img = NULL, * imgG = NULL , * imgG2 = NULL;
  CvCapture * capture = NULL;
  CvSize s;
  /* si pas de webcam IplImage* img = cvLoadImage("image.png", CV_LOAD_IMAGE_COLOR); */
  capture = cvCaptureFromCAM(CV_CAP_ANY);
  s.width = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
  s.height = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
  fprintf(stderr, "dimensions du flux %dx%d\n", s.width, s.height);
  cvNamedWindow("Intro OpenCV", CV_WINDOW_AUTOSIZE);
  // imgG = cvCreateImage(s, IPL_DEPTH_8U, 1);


  while((img = cvQueryFrame(capture))) {
    // cvCvtColor(img, imgG, CV_RGB2GRAY);
    // cvSmooth(imgG, imgG, CV_GAUSSIAN, 15, 15, 0, 0);
   
    
    imgG2 = cvCloneImage(img);
    
    isolation(img, imgG);
    imgG = cvCloneImage(imgG2);


    cvShowImage("Intro OpenCV", img);

    if((cvWaitKey(10) & 0xFF) == 27)
      break;
  }
  if(capture)
    cvReleaseCapture(&capture);
  return 0;
}

/* si un grayscale à la main */
/*!\brief modifie une image couleur RGB de manière à calculer une
 * valeur unique par composante (ici la luminance) et ainsi obtenir
 * une image en niveau de gris.
 */
static void toGray(IplImage * img) {
  int i, j;
  unsigned char * dd = (unsigned char *)img->imageData;
  assert(img->nChannels == 3);
  for(i = 0; i < img->height; i++) {
    for(j = 0; j < img->width; j++) {
      double v = 0;
      v += 0.114 * dd[i * img->widthStep + j * img->nChannels + 0];
      v += 0.587 * dd[i * img->widthStep + j * img->nChannels + 1];
      v += 0.299 * dd[i * img->widthStep + j * img->nChannels + 2];
      dd[i * img->widthStep + j * img->nChannels + 0] = (unsigned char)v;
      dd[i * img->widthStep + j * img->nChannels + 1] = (unsigned char)v;
      dd[i * img->widthStep + j * img->nChannels + 2] = (unsigned char)v;
    }
  }
}
int diff( unsigned char a , unsigned char b){


if( a > b)
  return a - b;
return b-a;



}

static void isolation(IplImage * img , IplImage * img2) {

  if(img2 == NULL) return;
  int i, j;
  unsigned char * dd = (unsigned char *)img->imageData;
  unsigned char * dd2 = (unsigned char *)img2->imageData;
  assert(img->nChannels == 3);
  for(i = 0; i < img->height; i++) {
    for(j = 0; j < img->width; j++) {
      int test1 =
        dd[i * img->widthStep + j * img->nChannels + 0] +
        dd[i * img->widthStep + j * img->nChannels + 1] +
        dd[i * img->widthStep + j * img->nChannels + 2] ;
      int test2 =
        dd2[i * img2->widthStep + j * img2->nChannels + 0] +
        dd2[i * img2->widthStep + j * img2->nChannels + 1] +
        dd2[i * img2->widthStep + j * img2->nChannels + 2] ;

      if(  

        diff(  dd[i * img->widthStep + j * img->nChannels + 0] , dd2[i * img2->widthStep + j * img2->nChannels + 0]) < 30 &&
        diff(  dd[i * img->widthStep + j * img->nChannels + 1] , dd2[i * img2->widthStep + j * img2->nChannels + 1]) < 30 &&
        diff(  dd[i * img->widthStep + j * img->nChannels + 2] , dd2[i * img2->widthStep + j * img2->nChannels + 2]) < 30

        )
      {

 double v = 0.0;
      dd[i * img->widthStep + j * img->nChannels + 0] = (unsigned char)v;
      dd[i * img->widthStep + j * img->nChannels + 1] = (unsigned char)v;
      dd[i * img->widthStep + j * img->nChannels + 2] = (unsigned char)v;


      }else {
     

      double v = 255.0;
      dd[i * img->widthStep + j * img->nChannels + 0] = (unsigned char)v;
      dd[i * img->widthStep + j * img->nChannels + 1] = (unsigned char)v;
      dd[i * img->widthStep + j * img->nChannels + 2] = (unsigned char)v;
}


      
    }
  }
}
