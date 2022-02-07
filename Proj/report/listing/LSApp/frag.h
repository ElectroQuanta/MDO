/**
 * @file frag.h
 * @author Jose Pires
 * @date 2022-02-03
 *
 * @brief Fragrance class
 */
#ifndef _FRAG_H_
#define _FRAG_H_
#include <string>

/**
 * @brief Fragrance namespace
 */
namespace Frag{
#define VOL_MAX 100
    enum Intensity_t {
        LOW = 1,
        MEDIUM,
        HIGH,
    };
    typedef enum Intensity_t Intensity;
    /**
     * @brief Fragrance class
     */
    class Fragrance{
    private:
        int _id; /**< fragrance ID */
        Intensity _intensity; /**< fragrance intensity */
        int _duration_on; /**< On time (in ms) */
        int _duration_off; /**< Off time (in ms) */
        int _vol_max; /**< Max volume (in ml) */  
        int _vol_level; /**< Max volume (in ml) */
        void calcDurations(Intensity intensity); /**< Calculate durations */
    public:
        /**< Constructors/Destructors */
        Fragrance(int id = 0, Intensity intensity = Intensity::LOW,
                  int vol_max = VOL_MAX, int vol_level = VOL_MAX);
        ~Fragrance();
        /**< Getters */
        inline int id() const{
            return _id;
        }
        inline Intensity intensity() const{
            return _intensity;
        }
        inline int durationOn() const{
            return _duration_on;
        }
        inline int durationOff() const{
            return _duration_off;
        }
        inline int volMax() const{
            return _vol_max;
        }
        inline int volLevel() const{
            return _vol_level;
        }
        inline bool operator==(const Fragrance& rhs)
            { return (this->_id == rhs._id); }
        /**< Setters / Mutators */
        void setIntensity(Intensity intensity);
        inline void setVolLevel(int level){
            if( !(level < 0) )
                _vol_level = level;
        }
        /**
         * @brief Serializing object into string
         * @param s: string with the output result of the serialization
         *
         * Useful to write to streams
         */
        void serialize(std::string &s);
        /**
         * @brief Deserializing string into object
         * @param s: input string containing the data to build the object
         *
         * Useful to read from streams
         */
        void deserialize(const std::string &s);
    };
};
#endif // _FRAG_H__H
