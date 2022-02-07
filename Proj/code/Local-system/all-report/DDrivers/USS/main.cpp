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

    Sensor s(17, 22, 1000), s2(17, 23, 1000);
    if(!s2.Open() || !s.Open())
        return -1;

    #define TIMEOUT_S 5
    #define ITER 1
    int _delay = ITER;
    int dist;
    int count = 0;
    while(1) {
        
        for(int j = 0; j < ITER*TIMEOUT_S; j++) {
        count += checkDistance(s.Read());
        sleep(_delay);
        }

        if(count > (TIMEOUT_S*ITER/2))
            cout << "Sinalize!!" << endl;
        else
            cout << "NOT" << endl;
        count = 0;
    }

}