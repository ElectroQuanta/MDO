#ifndef _POST_H_
#define _POST_H_

#include <string>

enum MediaType { PNG = 0, GIF };
typedef enum MediaType MediaType_t;

class Post{
public:
    Post(std::string msg = "#MDO ", MediaType_t medType = MediaType::PNG);
    void setMsg(std::string msg);
    void setMediaType(MediaType_t medType);

    void Msg(std::string &msg);
    void MediaPath(std::string &media_path);
    MediaType_t MediaType() const;
private:

    std::string _msg;
    std::string _mediaPath;
    MediaType_t _mediaType;
};


#endif // _POST_H__H
