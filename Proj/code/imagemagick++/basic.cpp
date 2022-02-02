#include <Magick++.h>
#include <iostream>

//#define INPUT_FNAME "../examples/giphy.gif"
#define INPUT_FNAME "../examples/gifer.gif"
//#define INPUT_FNAME "../examples/logo.gif"
#define OUTPUT_FNAME_NO_EXTENSION "../examples/fname_no_extension"
#define OUTPUT_EXTENSION "png"
#define OUTPUT_FNAME_FULL "../examples/fname_full.gif"

int main(int /*argc*/, char **argv) {
//    Magick::InitializeMagick(*argv);

    //Magick::Image::read(const string& filename);
    //Magick::Image::write(const string& filename);
    //Magick::Image::write(Blob* blob);
// writing to Blobs is discussed in the Blobs section below
// Reading the contents of a disk file into an image object can be performed
// if the default Image costructor was used
// Example:
    Magick::Image my_image; // create an *empty* image using the default Image constructor
// coding style example for using the Magick++ exceptions
try {
    my_image.read(INPUT_FNAME);
    std::cout << "Success: read" << std::endl;
}
catch (Magick::Error& my_error) {
// because 'Error' is derived from the standard C++ exception, it has a 'what()' method
    std::cout << "a Magick++ error occurred: " << my_error.what()
              << std::endl;
}
catch ( ... ) {
    std::cout << "an unhandled error has occurred; exiting application."
              << std::endl;
    exit(1);
}

    
// read a GIF image file from disk;
// the image format is automatically set to GIF
// Writing an Image object to a disk file:
// the format of the image file is either specified by the file extension,
// or if the file extension is missing then the write format is taken from the image's
// "format" attribute (see the 'Image::magick()' method above)
// Example:
//    my_image.magick(OUTPUT_EXTENSION);
//// set the "format" attribute of my_image to PNG
//    my_image.write(OUTPUT_FNAME_NO_EXTENSION); // write to disk an image file (based on
// my_image canvas); the image is saved to the
// file file_name_no_extension in PNG format
    my_image.write(OUTPUT_FNAME_FULL); // write to disk an image file (based
// on my_image canvas); the format of
// file_name_explicit_extension is
// GIF, and *not* PNG
// NOTE : writing 'my_image' to disk via 'Magick::write()' in a GIF file format doesn't
// change the my_image format (i.e. the "format" attribute my_image format remains PNG)

    return 0;


}
