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


#ifndef OEMLOG_H
#define OEMLOG_H


#include "typedefs.h"
#include "OemHeader.h"

#include <string>
#include <vector>



namespace novars
{


class OemLog
{
public:
    OemLog();
    virtual ~OemLog(){}
    virtual void decodeASCII(const std::string &buf) = 0;
    virtual void decodeBinary(const std::vector<UChar> &buf) = 0;

protected:
    static const Char sync1_;
    static const Char sync2_;
    static const Char sync3_;
    OemHeader header_;

};

}

#endif // OEMLOG_H
