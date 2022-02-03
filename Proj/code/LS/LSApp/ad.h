/**
 * @file ad.h
 * @author Jose Pires
 * @date 2022-02-03
 *
 * @brief Ad class
 *
 */

#ifndef _AD_H_
#define _AD_H_

#include <string>
#include <pthread.h>

class Ad{
private:
    std::string _fname; /**< filename */
    std::string _link; /**< download link from Proxy server */
    int _fragranceID; /**< fragrance ID */
    int _filterID; /**< Filter ID */
    int _timeslot; /**< integer defining the timeslot from the beginning of the week */
    bool _enabled; /**< asserts if the ad is currently enabled */
    pthread_mutex_t _mutex; /**< protect access to the enabled state */

public:
    /**< Constructors/Destructors */
    Ad(std::string fname = "", std::string link = "",
       int fragID = 0, int filterID = 0, int timeslot = 0);
    ~Ad();
    /**< Getters */
    void fname(std::string &fname);
    void link(std::string &link);
    int fragID() const;
    int filterID() const;
    int timeslot() const;
    bool enabled();
    /**< Setters / Mutators */
    void setFname(std::string fname);
    void setLink(std::string link);
    void setFragID(int id);
    void setFilterID(int id);
    void setTimeslot(int tslot);
    void enable(bool enabled);
    bool save();
    bool load(std::string fname);
    inline bool operator==(const Ad& rhs)
        { return (this->_timeslot == rhs._timeslot); }
};


#endif // _AD_H__H
