#include "post.h"
#include <qcoreapplication.h>

#define MEDIA_PATH "../posts/media"

Post::Post(std::string msg, MediaType_t medType){
    _msg = msg;

    setMediaType(medType);
}
void Post::setMsg(std::string msg){
    _msg = msg;
}
void Post::setMediaType(MediaType_t medType){
    _mediaType = medType;
    _mediaPath = MEDIA_PATH;

    switch(_mediaType){
    case MediaType::PNG : 
        _mediaPath += ".png";
        break;
    case MediaType::GIF :
        _mediaPath += ".gif";
        break;
    }
}

void Post::Msg(std::string &msg){
    msg = _msg;
}
void Post::MediaPath(std::string &media_path){
    media_path = _mediaPath;
}
MediaType_t Post::MediaType() const{
    return _mediaType;
}
