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

using namespace std;
using namespace novars;

DATE::DATE()
{
    time_t  curtime;
    struct tm *loctime;
    /* Get the current time. */
    curtime = time (NULL);
    /* Convert it to local time representation. */
    loctime = localtime (&curtime);

    setYear((unsigned int)(loctime->tm_year+1900));
    setYear2((unsigned int)(loctime->tm_year % 100));
    setMounth((unsigned int)loctime->tm_mon);
    setDay((unsigned int)loctime->tm_mday);
    setHour((unsigned int)loctime->tm_hour);
    setMin((unsigned int)loctime->tm_min);
    setSec((unsigned int)loctime->tm_sec);
    setDOY((unsigned int)(loctime->tm_yday+1));
    switch (getHour())
    {
    case 0:
        HourLetter = 'A';
        break;
    case 1:
        HourLetter = 'B';
        break;
    case 2:
        HourLetter = 'C';
        break;
    case 3:
        HourLetter = 'D';
        break;
    case 4:
        HourLetter = 'E';
        break;
    case 5:
        HourLetter = 'F';
        break;
    case 6:
        HourLetter = 'G';
        break;
    case 7:
        HourLetter = 'H';
        break;
    case 8:
        HourLetter = 'I';
        break;
    case 9:
        HourLetter = 'J';
        break;
    case 10:
        HourLetter = 'K';
        break;
    case 11:
        HourLetter = 'L';
        break;
    case 12:
        HourLetter = 'M';
        break;
    case 13:
        HourLetter = 'N';
        break;
    case 14:
        HourLetter = 'O';
        break;
    case 15:
        HourLetter = 'P';
        break;
    case 16:
        HourLetter = 'Q';
        break;
    case 17:
        HourLetter = 'R';
        break;
    case 18:
        HourLetter = 'S';
        break;
    case 19:
        HourLetter = 'T';
        break;
    case 20:
        HourLetter = 'U';
        break;
    case 21:
        HourLetter = 'V';
        break;
    case 22:
        HourLetter = 'W';
        break;
    case 23:
        HourLetter = 'X';
        break;
    }
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
    int DaysInMounth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ( (getYear() % 4 )== 0)
        if ( (getYear() % 100 ) != 0 || (getYear() % 100 == 0 && getYear() % 400 == 0 ) )
            DaysInMounth[1] = 29;

    i = 0;

    while (DOY > 0)
    {
        DOY -= DaysInMounth[i];
        i++;
    }

    setMounth(i);

    for (unsigned int j = 1; j < getMounth(); j++)
    {
        DOM -= DaysInMounth[j-1];
    }

    setDay(DOM);
    switch (getHour())
    {
    case 0:
        HourLetter = 'A';
        break;
    case 1:
        HourLetter = 'B';
        break;
    case 2:
        HourLetter = 'C';
        break;
    case 3:
        HourLetter = 'D';
        break;
    case 4:
        HourLetter = 'E';
        break;
    case 5:
        HourLetter = 'F';
        break;
    case 6:
        HourLetter = 'G';
        break;
    case 7:
        HourLetter = 'H';
        break;
    case 8:
        HourLetter = 'I';
        break;
    case 9:
        HourLetter = 'J';
        break;
    case 10:
        HourLetter = 'K';
        break;
    case 11:
        HourLetter = 'L';
        break;
    case 12:
        HourLetter = 'M';
        break;
    case 13:
        HourLetter = 'N';
        break;
    case 14:
        HourLetter = 'O';
        break;
    case 15:
        HourLetter = 'P';
        break;
    case 16:
        HourLetter = 'Q';
        break;
    case 17:
        HourLetter = 'R';
        break;
    case 18:
        HourLetter = 'S';
        break;
    case 19:
        HourLetter = 'T';
        break;
    case 20:
        HourLetter = 'U';
        break;
    case 21:
        HourLetter = 'V';
        break;
    case 22:
        HourLetter = 'W';
        break;
    case 23:
        HourLetter = 'X';
        break;
    }

}

ostream &operator << (ostream &output, const DATE &date)
{
    //   2007     1     4     0     0    0.0000000
    output.precision(7);
    output << setw(6) << date.year << setw(6) << date.mounth << setw(6) << date.day << setw(6) << date.hour
    << setw(6) << date.min;
    output.precision(4);
    output.setf(ios::fixed);
    output << setw(13) << (double)date.sec;
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
    setMounth((unsigned int)loctime->tm_mon);
    setDay((unsigned int)loctime->tm_mday);
    setHour((unsigned int)loctime->tm_hour);
    setMin((unsigned int)loctime->tm_min);
    setSec((unsigned int)loctime->tm_sec);
}


int DATE::prewHour()
{

    int prewHour = getHour() - 1;
    if (prewHour == 0)
        prewHour = 23;

    return prewHour;
}

int DATE::prewDOY()
{
    int prewDOY = getDOY() - 1;
    if (prewDOY == 0)
    {
        if ( ((getYear() - 1) % 4 ) == 0)
        {
            if ((getYear() - 1) % 100 != 0 || ( (getYear() - 1) % 100 == 0 && (getYear() - 1) % 400 == 0 ) )
                prewDOY = 365;
            else
                prewDOY = 364;
        }
    }
    return prewDOY;

}

