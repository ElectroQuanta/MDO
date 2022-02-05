//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <fcntl.h>
#include <iostream>
#include "ddDigitalOut.h"
#include "fragDiffuser.h"
#include "frag.h"

using namespace DeviceDriver;
using namespace std;
using namespace Frag;

void simpleDelay (void)
{
    volatile unsigned int i;
    for (i = 0; i != 100000000; i++);
}	

int main(void)
{

    //DigitalOutput frag("frag", 0);
    Fragrance f(0);
    Diffuser fd(f);

    
    bool enabled = false;
    while (getchar() != 0x20) {
        fd.enable(enabled);
        enabled = !enabled;
        /* code */
    }
    

    return 0;

}