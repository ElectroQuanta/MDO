/**
 * @file fragDiffuser.h
 * @author Jose Pires
 * @date 2022-02-03
 *
 * @brief Fragrance diffuser class
 *
 */

#ifndef _FRAGDIFFUSER_H_
#define _FRAGDIFFUSER_H_

#include <pthread.h>
#include "frag.h"
#include "ddDigitalOut.h"

namespace Frag{
class Diffuser{
private:
    static int Instances;
    bool _enabled; /**< asserts if the ad is currently enabled */
    pthread_mutex_t _mutex; /**< protect access to the enabled state */
    int _id; /**< device driver ID associated */
    Fragrance _frag; /**< fragrance associated with the diffuser */
    DeviceDriver::DigitalOutput *_dd;
    bool _ddWorking;
public:
    /**< Constructors/Destructors */
    Diffuser(Fragrance &f);
    ~Diffuser();
    /**< Getters */
    /**
     * @brief Asserts the diffuser state
     * @return the enables state
     */
    bool enabled();
    /**
     * @brief Retrieves the fragrance used by the diffuser
     * @param f: fragrance to be filled (output)
     */
    void fragrance(Fragrance &f);
    /**< Setters / Mutators */
    /**
     * @brief Enables/disables the diffuser
     * @param enabled: the enabling state of the diffuser
     */
    void enable(bool enabled);
    /**
     * @brief Sets the diffuser fragrance
     * @param f: fragrance
     */
    void setFragrance(const Fragrance &f);
};
};
#endif // _FRAGDIFFUSER_H__H
