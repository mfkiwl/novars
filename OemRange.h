#ifndef OEMRANGE_H
#define OEMRANGE_H


#include "OemLog.h"
#include "typedefs.h"
#include <map>


namespace novars
{

struct Observation
{
    double pseudorange;         //!< Pseudorange, m
    double pseudorangeStd;      //!< Pseudorange standard deviaton, m
    double phaseInCycles;       //!< Accumulated Doppler range with reverse sign
    double phaseStdInCycles;    //!< Phase standatd deviation, cycles
    double doppler;             //!< Doppler, Hz
    double carrierToNoiseRatio; //!< CNR, db-Hz
};


class OemRange : public OemLog
{
public:
    OemRange();
    virtual ~OemRange(){}
    void decodeASCII(const std::string &buf);
    void decodeBinary(const std::vector<UChar> &buf);
protected:
    std::map<sat_flag_t, Observation> observation_map_;
};

} // namespace novars


#endif // OEMRANGE_H
