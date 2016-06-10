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


#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <iomanip>


namespace novars
{

class DATE
{
    friend std::ostream &operator << (ostream &, const DATE &);
private:
    unsigned int year;
    unsigned int year2;
    unsigned int mounth;
    unsigned int day;
    unsigned int DOY;
    unsigned int hour;
    unsigned int min;
    double sec;
    char HourLetter;

public:
    DATE(); // default constructor
    DATE(double sec, int GPSWeek);
    inline unsigned int getYear()
    {
        return year ;
    };
    inline unsigned int getYear2()
    {
        return year2;
    };
    inline unsigned int getMounth()
    {
        return mounth;
    };
    inline unsigned int getDay()
    {
        return day;
    };
    inline unsigned int getDOY()
    {
        return DOY;
    };
    inline unsigned int getHour()
    {
        return hour;
    };
    inline unsigned int getMin()
    {
        return min;
    };
    inline double       getSec()
    {
        return sec;
    };
    inline char		getHourLetter()
    {
        return HourLetter;
    };
    inline void setYear(unsigned int yr)
    {
        year = yr;
    };
    inline void setYear2(unsigned int yr2)
    {
        year2 = yr2;
    };
    inline void setMounth(unsigned int mth)
    {
        mounth = mth;
    };
    inline void setDay(unsigned int d)
    {
        day = d;
    };
    inline void setDOY(unsigned int Dy)
    {
        DOY = Dy;
    };
    inline void setHour(unsigned int h)
    {
        hour = h;
    };
    inline void setMin(unsigned int m)
    {
        min = m;
    };
    inline void setSec(double s)
    {
        sec = s;
    };
    void setCurrentTime();


    int prewHour();
    int prewDOY();
    inline int prewYear()
    {
        return (year - 1);
    };
    inline int prewYear2()
    {
        return (year2 - 1);
    };

    // operators

};

} // namespace novars





#endif
