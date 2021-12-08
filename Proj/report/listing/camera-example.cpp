#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio/videoio_c.h>

using namespace cv;
using namespace std;

int main(int argv, char** argc)
{
    	
	Mat frame; //frame to capture
	VideoCapture cap(0);  //streaming from the camera 
	                      //(in this case 0 is the ID of the camera)
   
	//verify if the camera opened
    	if (!cap.isOpened()){
	        cerr << "ERROR! Unable to open camera\n";
	        return -1;
	    }

		//Start acquisition
	cout << "Start grabbing" << endl
	<< "Press any key to terminate" << endl;
	
	    //Infinite loop
	for (;;)
	{
		//Read the frame from the camera
	        cap.read(frame);
		//Avoid to show no frame
	        if (frame.empty()){
	        	cerr << "ERROR! Blank frame grabbed \n";
	        	break;
	        }

		//Show the captured frame
	        imshow("Live", frame);
		
		//If a key is pressed, exit the loop and stops de execution
	        if (waitKey (5) >= 0)
	        	break;
	}
	return 0;
}
