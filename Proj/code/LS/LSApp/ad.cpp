/**
 * @file ad.cpp
 * @author Jose Pires
 * @date 2022-02-03
 *
 * @brief Implementation class for Ad
 *
 */

#include "ad.h"
#include <fstream>

const std::string Ad::ads_path_prefix = "../ads/";
const std::string Ad::media_path_prefix = "media/";

Ad::Ad(std::string fname, std::string link, int fragID, int filterID,
       int timeslot) {
    pthread_mutex_init(&_mutex, NULL);

    setFname(fname);
    setLink(link);
    setMediaPath(fname);
    setFragID(fragID);
    setFilterID(filterID);
    setTimeslot(timeslot);
    enable(false);
}

Ad::~Ad(){
  pthread_mutex_destroy(&_mutex);
}

/**< Getters */
void Ad::fname(std::string &fname){
    fname = _fname;
}
void Ad::link(std::string &link){
    link = _link; 
}
void Ad::mediaPath(std::string &mediaPath){
    mediaPath = _mediaPath; 
}
int Ad::fragID() {
    int fragID;
    pthread_mutex_lock(&_mutex);
    fragID = _fragranceID;
    pthread_mutex_unlock(&_mutex);

    return fragID;
}
int Ad::filterID(){
    int filterID;
    pthread_mutex_lock(&_mutex);
    filterID = _filterID;
    pthread_mutex_unlock(&_mutex);

    return filterID;
}
int Ad::timeslot(){
    int timeslot;
    pthread_mutex_lock(&_mutex);
    timeslot = _timeslot;
    pthread_mutex_unlock(&_mutex);

    return timeslot;
}
bool Ad::enabled() {
    bool enabled = false;
    pthread_mutex_lock(&_mutex);
    enabled = _enabled;
    pthread_mutex_unlock(&_mutex);

    return enabled;
}

    /**< Setters / Mutators */
void Ad::setFname(const std::string fname){
    _fname = fname;
}
void Ad::setLink(const std::string link){
    _link = link;
}
void Ad::setMediaPath(const std::string mediaPath){
    _mediaPath = ads_path_prefix + media_path_prefix + mediaPath;
}
void Ad::setFragID(const int id){
    pthread_mutex_lock(&_mutex);
    _fragranceID = id;
    pthread_mutex_unlock(&_mutex);
}
void Ad::setFilterID(const int id){
    pthread_mutex_lock(&_mutex);
    _filterID = id;
    pthread_mutex_unlock(&_mutex);
}
void Ad::setTimeslot(const int tslot){
    pthread_mutex_lock(&_mutex);
    _timeslot = tslot;
    pthread_mutex_unlock(&_mutex);
}
void Ad::enable(const bool enabled){
    pthread_mutex_lock(&_mutex);
    _enabled = enabled;
    pthread_mutex_unlock(&_mutex);
}

bool Ad::save(){
    std::string path = ads_path_prefix + _fname + ".txt";
    std::ofstream file (path);

    /**< Try to open file */
    if( !file.is_open() )
        return false;

    /**< Write to file */
    file << _fname << std::endl;
    file << _link << std::endl;
    file << _fragranceID << std::endl;
    file << _filterID << std::endl;
    file << _timeslot;

    return true;
}

bool Ad::load(std::string fname){
    std::string path = ads_path_prefix + _fname + ".txt";
    std::ifstream file (path);

    /**< Try to open file */
    if( !file.is_open() )
        return false;

    /**< Read from file */
    file >> _fname;
    file >> _link;
    file >> _fragranceID;
    file >> _filterID;
    file >> _timeslot;

    return true;
}
