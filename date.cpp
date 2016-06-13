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

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>

#include "date.h"


namespace  novars {




char DATE::hour_letters_array_[24] = {'A','B','C','D','E','F','G','H',
                                    'I','J','K','L','M','N','O','P',
                                    'Q','R','S','T','U','V','W','X'};

unsigned int DATE::days_in_month_[2][12] = {{31,28,31,30,31,30,31,31,30,31,30,31},
                                     {31,29,31,30,31,30,31,31,30,31,30,31}};

DATE::DATE()
{
    time_t  curtime;
    struct tm *loctime;
    /* Get the current time. */
    curtime = time (NULL);
    /* Convert it to local time representation. */
    //loctime = localtime (&curtime);

#ifdef UNIX
    localtime_r(&curtime, localtime);
#elif WIN32
    localtime_s(localtime, &curtime);
#endif

    setYear((unsigned int)(loctime->tm_year+1900));
    setYear2((unsigned int)(loctime->tm_year % 100));
    setMonth((unsigned int)loctime->tm_mon);
    setDay((unsigned int)loctime->tm_mday);
    setHour((unsigned int)loctime->tm_hour);
    setMin((unsigned int)loctime->tm_min);
    setSec((unsigned int)loctime->tm_sec);
    setDOY((unsigned int)(loctime->tm_yday+1));
}

DATE::DATE(double sec1, int GPSWeek)
{
    // Reference epoch
    const int refGPSWeek = 782;
    const int refYear = 1995;
    // Day of week, hour, minutes, seconds
    int DOW = (int)(sec1 / 86400);
    int hour = (int)((sec1 - DOW*86400) / 3600);
    int minutes = (int)((sec1 - (DOW*86400 + hour*3600)) / 60);
    double seconds = sec1 - (DOW*86400 + hour*3600 + minutes*60);
    // deltaDOY - number of DOYs since ref. epoch
    // delta    - days number since beginning of the current year.
    //
    int deltaDOY = (GPSWeek - refGPSWeek)*7 + DOW;
    int delta = deltaDOY;
    int i = 0, daysInNextYear = 365;
    while (delta >= daysInNextYear )
    {
        int DOYS = 365;
        if ( ((1995+i) % 4) == 0)    // 2006 is ref. epoch
            if ( ((1995+i) % 100) != 0 || ( (i+1995) % 100 == 0 && (i+1995) % 400 == 0 ) )
                DOYS = 366;

        delta -= DOYS;
        i++;
        // Compute number days in next year
        daysInNextYear = 365;
        if ( ((i+1995) % 4) == 0)
            if ((i+1995) % 100 != 0 || ( (i+1995) % 100 == 0 && (i+1995) % 400 == 0 ) )
                daysInNextYear = 366;
    }

    // Set the internal variables
    setYear((unsigned int)(refYear+i));
    setYear2((unsigned int)((refYear+i) % 100));
    setDOY((unsigned int)(delta+1)); // delta days + 1 - number of current DOY;

    setHour((unsigned int)(hour));
    setMin((unsigned int)(minutes));
    setSec(seconds);

    // Determine mounth number;
    int DOY = delta+1;
    int DOM = DOY; // Day of mounth

    // Remember array indexing begins with 0 !!!!
    //int days_in_month_[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    int is_leap_year = 0;

    if ( (getYear() % 4 )== 0)
        if ( (getYear() % 100 ) != 0 || (getYear() % 100 == 0 && getYear() % 400 == 0 ) )
            is_leap_year = 1;

    i = 0;

    while (DOY > 0)
    {
        DOY -= days_in_month_[is_leap_year][i];
        i++;
    }

    setMonth(i);

    for (unsigned int j = 1; j < getMonth(); j++)
    {
        DOM -= days_in_month_[is_leap_year][j-1];
    }

    setDay(DOM);

}

std::ostream &operator << (std::ostream &output, const DATE &date)
{
    //   2007     1     4     0     0    0.0000000
    output.precision(7);
    output << std::setw(6) << date.year_ << std::setw(6) << date.month_ << std::setw(6) << date.day_ << std::setw(6) << date.hour_
    << std::setw(6) << date.min_;
    output.precision(4);
    output.setf(std::ios::fixed);
    output << std::setw(13) << (double)date.sec_;
    return output;
}

void DATE::setCurrentTime()
{
    time_t  curtime;
    struct tm *loctime;
    /* Get the current time. */
    curtime = time (NULL);
    /* Convert it to local time representation. */
    loctime = localtime (&curtime);

    setYear((unsigned int)(loctime->tm_year+1900));
    setYear2((unsigned int)(loctime->tm_year % 100));
    setMonth((unsigned int)loctime->tm_mon);
    setDay((unsigned int)loctime->tm_mday);
    setHour((unsigned int)loctime->tm_hour);
    setMin((unsigned int)loctime->tm_min);
    setSec((unsigned int)loctime->tm_sec);
}


int DATE::prewHour() const
{

    int prewHour = getHour() - 1;
    if (prewHour == 0)
        prewHour = 23;

    return prewHour;
}

int DATE::prewDOY() const
{
    unsigned int year_minus_1 = year_-1;

    int prewDOY = getDOY() - 1;
    if (prewDOY == 0)
    {
        if ( (year_minus_1 % 4 ) == 0)
        {
            if ( year_minus_1 % 100 != 0 || ( (year_minus_1 % 100 == 0) && (year_minus_1 % 400 == 0) ) )
                prewDOY = 365;
            else
                prewDOY = 364;
        }
    }
    return prewDOY;

}

} // namespace novars

