/*
 *
 * This file is a part of NovaRS.
 *     
 * NovaRS, the GNSS station controlling software.
 * Copyright (C) 2016  Mykhailo Lytvyn
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//#ifndef TYPEDEFS_H_
//#define TYPEDEFS_H_

#pragma  once

#include <stdint.h>
#include "config.h"

namespace novars {
#ifdef UNIX
    typedef int8_t Char;
    typedef uint8_t UChar;
    typedef int16_t Short;
    typedef uint16_t UShort;
    typedef int32_t Long;
    typedef uint32_t ULong;
#endif

#ifdef WIN32
    typedef __int8 Char;
    typedef __uint8 UChar;
    typedef __int16 Short;
    typedef __uint16 UShort;
    typedef __int32 Long;
    typedef __uint32 ULong;
#endif

    typedef ULong sat_flag_t;
    // Bit allocation
    // GNSStype, Freq slot (GLONASS) | PRN | Spare bits | Signal type
    // xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
    static sat_flag_t GNSS_TYPE      = 0xF0000000;
    static sat_flag_t FREQUENCY_SLOT = 0x0F000000;
    static sat_flag_t PRN            = 0x00FF0000;
    static sat_flag_t SIGNAL_TYPE    = 0x000000FF;

    static sat_flag_t GPS            = 0x10000000;
    static sat_flag_t GLONASS        = 0x20000000;
    static sat_flag_t GALILEO        = 0x40000000;
    static sat_flag_t SBAS           = 0x80000000;

    static sat_flag_t L1CA           = 0b00000001;
    static sat_flag_t L5             = 0b00000010;
    static sat_flag_t L2P            = 0b00000100;
    static sat_flag_t L2P_CODELESS   = 0b00001000;
    static sat_flag_t L2C            = 0b00010000;
    static sat_flag_t L2CA           = 0b00100000;
    static sat_flag_t E1             = 0b01000000;
    static sat_flag_t E5a            = 0b10000000;
    static sat_flag_t E5b            = 0b00000011;
    static sat_flag_t AltBOC         = 0b00000110;
    static sat_flag_t OMNISTAR       = 0b00001100;

} // namespace novars

//#endif // TYPEDEFS_H_
