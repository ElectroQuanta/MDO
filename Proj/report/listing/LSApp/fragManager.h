/**
 * @file fragManager.h
 * @author Jose Pires
 * @date 2022-02-03
 *
 * @brief Manages the fragrances for the station
 */
#ifndef _FRAGMANAGER_H_
#define _FRAGMANAGER_H_
#include "frag.h"
#include <vector>
#include <pthread.h>
namespace Frag{
    class Manager{
    private:
        pthread_mutex_t _mutex; /**< protect access to the push and pop */
        std::vector<Fragrance> *_fragrances = nullptr; /**< desc */
        int _activeFrag; /**< Current fragrance in the station (idx) */
    public:
        /**< Constructors/Destructors */
        Manager();
        ~Manager();
        /**
         * @brief Adds a fragrance to the Manager
         * @param f: fragrance to be added
         */
        void add(Fragrance &f);
        /**
         * @brief Removed a fragrance from the Manager
         * @param f: the fragrance to be removed
         * @return true if removed, false otherwise
         *
         * It compares the fragrance to be removed with the already present
         * and removes it if found.
         */
        bool remove(Fragrance &f);
        /**
         * @brief Find a fragrance in the manager
         * @param f: fragrance to be found
         * @return the idx if found; -1 otherwise
         *
         * It compares the fragrance to be found with the already present
         * and returns the comparison result.
         */
        int find(Fragrance &f);
        /**
         * @brief Load fragrances from database
         * @return true if loaded, false otherwise
         */
        bool load();
        /**
         * @brief Saves the fragrances to the database
         * @return true if loaded, false otherwise
         */
        bool save();
        /**
         * @brief Populates the manager with fragrances
         * @return true if populated, false otherwise
         *
         * If the loading fails, the populate can be used to create the
         * database.
         */
        bool populate();
        /**
         * @brief Sets the active fragrance
         * @param f: the fragrance to set
         *
         * It sets the active fragrance. First, it tries to find in the DB.
         * If not found, it is added to the DB.
         */
        void setActiveFrag( Fragrance &f );
        /**
         * @brief It retrieves the active fragrance in the station.
         * @param f: active fragrance (output)
         * @return true if there is an active fragrance, false otherwise;
         */
        bool ActiveFrag(Fragrance &f);
    };
};
#endif // _FRAGMANAGER_H__H
