#ifndef OEM_H
#define OEM_H

// NovAtel OEM6 specific defines

namespace novars
{

enum MessageID
{
    GPSEPHEM = 7,
    IONUTC = 8,
    RANGE = 43,
    RANGECMP = 140,
    GLOEPHEMERIS = 723
};

enum MessageType
{
    Binary = 0,
    ASCII = 1,
    AbbreviatedASCII = 2,
    NMEA = 3
};

enum TimeStatus
{
    UNKNOWN = 20,             //!< Time validity is unknown
    APPROXIMATE = 60,         //!< Time is set approximately
    COARSEADJUSTING = 80,     //!< Time is approaching coarse precision
    COARSE = 100,             //!< This time is valid to coarse precision
    COARSESTEERING = 120,     //!< Time is coarse set and is being steered
    FREEWHEELING = 130,       //!< Position is lost and the range bias cannot be calculated
    FINEADJUSTING = 140,      //!< Time is adjusting to fine precision
    FINE = 160,               //!< Time has fine precision
    FINEBACKUPSTEERING = 170, //!< Time is fine set and is being steered by the backup system
    FINESTEERING = 180,       //!< Time is fine set and is being steered
    SATTIME = 200             //!< Time from satellite. Only used in logs containing satellite data such as ephemeris and almanac
};


} // namespace novars


#endif // OEM_H

