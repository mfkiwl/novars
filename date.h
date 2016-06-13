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
public:
    friend std::ostream &operator << (std::ostream &, const DATE &);
private:
    unsigned int year_;
    unsigned int year2_;
    unsigned int month_;
    unsigned int day_;
    unsigned int day_of_year_;
    unsigned int hour_;
    unsigned int min_;
    double sec_;

    static char hour_letters_array_[24];
    static unsigned int days_in_month_[2][12];

public:
    DATE();

    DATE(double sec_, int GPSWeek);

    inline unsigned int getYear() const { return year_ ; }

    inline unsigned int getYear2() const { return year2_; }

    inline unsigned int getMonth() const { return month_; }

    inline unsigned int getDay() const { return day_; }

    inline unsigned int getDOY() const { return day_of_year_; }

    inline unsigned int getHour() const { return hour_; }

    inline unsigned int getMin() const { return min_; }

    inline double getSec() const { return sec_; }

    inline char getHourLetter() const { if(hour_ >=0 && hour_ < 24) return hour_letters_array_[hour_]; }

    inline void setYear(unsigned int yr) { year_ = yr; }

    inline void setYear2(unsigned int yr2) { year2_ = yr2; }

    inline void setMonth(unsigned int month) { month_ = month; }

    inline void setDay(unsigned int day) { day_ = day; }

    inline void setDOY(unsigned int dayOfYear) { day_of_year_ = dayOfYear; }

    inline void setHour(unsigned int hour) { hour_ = hour; }

    inline void setMin(unsigned int minute) { min_ = minute; }

    inline void setSec(double seconds) { sec_ = seconds; }

    void setCurrentTime();

    int prewHour() const;

    int prewDOY() const ;

    inline int prewYear() const { return (year_ - 1); }

    inline int prewYear2() const { return (year2_ - 1); }


};

} // namespace novars


#endif
