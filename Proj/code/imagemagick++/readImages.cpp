#include <list> 
#include <Magick++.h>
using namespace std; 
using namespace Magick;

#define INPUT_FNAME "../examples/animation.gif"
#define OUTPUT_FNAME "../examples/animation_out.gif"

int main(int /*argc*/,char **/*argv*/) 
{ 
    std::list<Image> images; 
    Magick::readImages( &images, INPUT_FNAME ); 
   for_each ( images.begin(), images.end(), transparentImage( "red" )  ); 
   writeImages( images.begin(), images.end(), OUTPUT_FNAME );

   return 0;
}

