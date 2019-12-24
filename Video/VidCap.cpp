#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>
#include <string>

using namespace cv;
using namespace std;

double CountProceedingTime(VideoCapture cap){

  string window_name = "Test";
  namedWindow(window_name);

  int frames = 0;
  time_t start, end;
  time(&start);
  while (true) {
      Mat frame;
      bool is_success = cap.read(frame);

      if (!is_success) {
          destroyWindow(window_name);
          break;
      }

      frames ++;
      imshow(window_name, frame);

      if (frames == 100){
          destroyWindow(window_name);
          break;
      }

      if (waitKey(10) == 27){
          cout << "You closed the camera" << endl;
          destroyWindow(window_name);
          break;
      }
  }
  time(&end);

  return (difftime(end, start)) / frames;
}


int main() {
  
  cout << "Enter file path" << endl;
  string filename;
  cin >> filename;

  VideoCapture cap (filename);

  if (!cap.isOpened()){
      cout << "File not opened";
      cin.get();
      return -1;
  }

  int fps;
  fps = cap.get(CAP_PROP_FPS);

  double proceed_time = CountProceedingTime(cap);

  double needed_time = 1.0/fps;
  double waiting_time = needed_time- proceed_time;

  cout << "To change fps press 'Enter'" << endl;
  cout << "To get latest frame press 'Space'" << endl;
  cout << "To exit program press 'Esc'" << endl;

  namedWindow("My Camera");
  namedWindow("Latest frame");

  while (true) {
      Mat frame;
      bool is_success = cap.read(frame);

      if (!is_success) {
          cout << "Camera is disconnected" << endl;
          destroyWindow("My Camera");
          break;
      }

      imshow("My Camera", frame);

      int key;
      if (waiting_time == 0) {
         key = waitKey(10);
      } else { key = waitKey(waiting_time * 1000);}

      if (key == 27){
          cout << "You closed the camera" << endl;
          destroyWindow("My Camera");
          return 0;
      }

      if (key == 32) {

          imshow("Latest frame", frame);

          /*if (waitKey(10) == 27){
              cout << "You closed the camera" << endl;
              destroyWindow("Latest frame");
              break;
          }*/
      }

      if (key == 13){
          cout << "Enter new fps";
          cin >> fps;
          needed_time = 1.0/fps;
          waiting_time = needed_time - proceed_time;
          if (waiting_time < 0) {
              cout << "Program works too slow, impossible to decode with needed fps";
              return -1;
          }
      }
  }

  return 0;
}
