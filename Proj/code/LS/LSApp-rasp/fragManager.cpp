/**
 * @file fragManager.cpp
 * @author Jose Pires
 * @date 2022-02-03
 *
 * @brief Implementation file for Fragrance manager
 *
 */

#include <qcoreapplication.h>
#define DB_PATH "../fragrances/"
#define DB_FILE "../fragrances/db.txt"

#include "fragManager.h"
#include <fstream>

namespace Frag{

    Manager::Manager(){
        pthread_mutex_init(&_mutex, NULL);
        _fragrances = new std::vector<Fragrance>;
        _activeFrag = -1;
    }

    Manager::~Manager(){
        pthread_mutex_destroy(&_mutex);
        delete [] _fragrances;
    }

    void Manager::add(Fragrance &f){
        pthread_mutex_lock(&_mutex);
        _fragrances->push_back(f);
        pthread_mutex_unlock(&_mutex);
    }

    bool Manager::remove(Fragrance &f){
        int size = 0;
        bool found = false;
        
        pthread_mutex_lock(&_mutex);
        size = _fragrances->size();
        pthread_mutex_unlock(&_mutex);

        for( int j = 0; j < size; j++){
            pthread_mutex_lock(&_mutex);
            if(_fragrances->at(j) == f){
                _fragrances->erase(_fragrances->begin() + j);
                found = true;
            }
            pthread_mutex_unlock(&_mutex);
            if (found)
                break;
            
        }

        return found;
    }

    int Manager::find(Fragrance &f){
        
        int size = 0;
        int idx = -1;
        
        pthread_mutex_lock(&_mutex);
        size = _fragrances->size();
        pthread_mutex_unlock(&_mutex);

        for( int j = 0; j < size; j++){
            pthread_mutex_lock(&_mutex);
            if(_fragrances->at(j) == f){
                f = _fragrances->at(j);
                idx = j;
            }
            pthread_mutex_unlock(&_mutex);
            if (idx != -1)
                break;
            
        }

        return idx;
    }

    bool Manager::populate(){
        Fragrance f1(0);
        Fragrance f2(1, Intensity::MEDIUM);
        Fragrance f3(2, Intensity::HIGH);

        add(f1);
        add(f2);
        add(f3);

        return save();
    }

    bool Manager::save(){
        int size;
        std::string str = "";

        /**< try to open the file */
        std::ofstream dbFile(QCoreApplication::applicationDirPath().toStdString()
                             + "/" +  std::string(DB_FILE));
        if (!dbFile.is_open())
          return false;

        pthread_mutex_lock(&_mutex);
        size = _fragrances->size();
        pthread_mutex_unlock(&_mutex);

        for (int j = 0; j < size; j++) {
            /**< Get fragrance string */
          pthread_mutex_lock(&_mutex);
          _fragrances->at(j).serialize(str);
          pthread_mutex_unlock(&_mutex);

          /**< Write it to a file */
          dbFile << str << std::endl;
        }

        return true;
    }

    bool Manager::load(){
        std::string str = "";

        /**< try to open the file */
        std::ifstream dbFile(QCoreApplication::applicationDirPath().toStdString()
                             + "/" +  std::string(DB_FILE));
        if (!dbFile.is_open())
          return false;

        Fragrance f(0);
        
        /**< Get each fragrance (until EOF) */
        while( std::getline(dbFile, str) ) {
            
        /**< Create fragrance from it */
            f.deserialize(str);

            /**< Push it to vector */
            add(f);
        }

        return true;
    }

    void Manager::setActiveFrag(Fragrance &f){

        int idx = -1;

        /**< Find fragrance */
        idx = find(f);

        /**< if not found */
        if ( idx == -1 ){
            /**< Add it to the DB */
            add(f);

            /**< Get the insertion idx */
            pthread_mutex_lock(&_mutex);
            idx = _fragrances->size() - 1;
            pthread_mutex_unlock(&_mutex);
        }

        _activeFrag = idx;
    }

    bool Manager::ActiveFrag(Fragrance &f){

        if(_activeFrag == -1)
            return false;

        /**< Get the fragrance */
        pthread_mutex_lock(&_mutex);
        f = _fragrances->at(_activeFrag);
        pthread_mutex_unlock(&_mutex);
        return true;
    }
};
