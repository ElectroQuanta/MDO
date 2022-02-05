#include <iostream>
#include "sensors.h"
#include <vector>
#include <unistd.h>

using namespace std;
using namespace DeviceDriver;

bool checkDistance(int dist) {
        #define MIN_TH 2
        #define MAX_TH 30
        return (dist > MIN_TH && dist < MAX_TH);
    }

int main() {

    //std::vector<Sensor> sensors;
    Sensor s(17, 22, 1000), s2(17, 23, 1000);
    //sensors.push_back(s);
    //sensors.push_back(s2);

    //vector<Sensor*>::iterator ptr;
    /*for(int i = 0; i < sensors.size(); i++){
        if(!sensors[i].Open())
            return -1;
    }*/
    if(!s2.Open() || !s.Open())
        return -1;

    for(int i = 0; i < 10; i++) {
        /*for(int j = 0; j < sensors.size(); j++){
            cout << "Sensor " << j+1 << ": " << sensors[j].Read() << " cm |\t";
        }*/
        cout << "Sensor 1: " << s.Read() << "\t | Sensor 2: " << s2.Read();
        cout << endl;
    }

    #define TIMEOUT_S 5
    #define ITER 1
    int _delay = ITER;
    int dist;
    int count = 0;
    /*while(1) {
        
        for(int j = 0; j < ITER*TIMEOUT_S; j++) {
        count += checkDistance(s.Read());
        sleep(_delay);
        }

        if(count > (TIMEOUT_S*ITER/2))
            cout << "Sinalize!!" << endl;
        else
            cout << "NOT" << endl;
        count = 0;
    }*/

}