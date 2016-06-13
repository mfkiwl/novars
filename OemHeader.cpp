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

#include "OemHeader.h"

namespace novars {



OemHeader::OemHeader()
{

}


bool OemHeader::decodeASCII(const std::string &buf)
{
    if(buf.empty())
        return false;

    std::vector<std::string> fields;

    split(buf, ',', fields);

    if((unsigned int)fields.size() < 10)
        return false;

    if(!parseMessageID(fields.at(1)))
        return false;

/*
    UChar length_;
    MessageID message_id_;
    MessageType message_type_;
    UChar message_length_;
    UShort sequence_;
    UChar idle_time_    ;
    TimeStatus time_status_;
    DATE date_;
    ULong receiver_status_;
    UShort receiver_sw_version_;
*/
    return true;
}

bool OemHeader::parseMessageID(const std::string &msgID)
{

    if(msgID == std::string("#RANGE"))
    {
        message_id_ = RANGE;
        return true;
    }

    if(msgID == std::string("#RANGECMP"))
    {
        message_id_ = RANGECMP;
        return true;
    }

    if(msgID == std::string("#GLOEPHEMERIS"))
    {
        message_id_ = GLOEPHEMERIS;
        return true;
    }

    if(msgID == std::string("#GPSEPHEM"))
    {
        message_id_ = GPSEPHEM;
       return true;
    }


    if(msgID == std::string("#IONUTC"))
    {
       message_id_ = IONUTC;
       return true;
    }


    return false;

}

bool OemHeader::decodeBinary(const std::vector<UChar> &buf)
{
    if(buf.size() < 28)
        return false;

    return true;
}


} // namespace novars
