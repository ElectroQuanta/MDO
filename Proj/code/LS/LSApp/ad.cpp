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

Ad::Ad(std::string fname, std::string link, int fragID, int filterID,
       int timeslot) {
    pthread_mutex_init(&_mutex, NULL);

    setFname(fname);
    setLink(link);
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
int Ad::fragID() const{
    return _fragranceID;
}
int Ad::filterID() const{
    return _filterID;
}
int Ad::timeslot() const{
    return _timeslot;
}
bool Ad::enabled() {
    bool enabled = false;
    pthread_mutex_lock(&_mutex);
    enabled = _enabled;
    pthread_mutex_unlock(&_mutex);

    return enabled;
}

    /**< Setters / Mutators */
void Ad::setFname(std::string fname){
    _fname = fname;
}
void Ad::setLink(std::string link){
    _link = link;
}
void Ad::setFragID(int id){
    _fragranceID = id;
}
void Ad::setFilterID(int id){
    _filterID = id;
}
void Ad::setTimeslot(int tslot){
    _timeslot = tslot;
}
void Ad::enable(bool enabled){
    pthread_mutex_lock(&_mutex);
    _enabled = enabled;
    pthread_mutex_unlock(&_mutex);
}

bool Ad::save(){

    std::string path = "../ads/" + _fname + ".txt";
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
    std::string path = "../ads/" + fname + ".txt";
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
