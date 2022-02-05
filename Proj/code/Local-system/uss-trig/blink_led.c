#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ddDigitalOut.h"

using namespace DeviceDriver;
using namespace std;

void simpleDelay (void)
{
    volatile unsigned int i;
    for (i = 0; i != 100000000; i++);
}	

int main(void)
{

    DigitalOutput frag("uss", 0);

    if(!frag.Open()) {
        cout << "Could not open!" << end;
    }
    bool enabled = false;
    while (getchar() != 0x20)
        frag.Write(enabled);
        enabled = !enabled;
    {
        /* code */
    }
    

    return 0;

}
