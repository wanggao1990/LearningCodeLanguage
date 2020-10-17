#pragma once

#include <stdint.h>
#include <string>

#define MICRO_SECONDS_PRE_SEC 1000000

namespace netlib
{

class Date
{
    Date() : microSecondsSinceEpoch_(0){};
    explicit Date(int64_t microSec) : microSecondsSinceEpoch_(microSec){};

    Date(unsigned int year,
         unsigned int month,
         unsigned int day,
         unsigned int hour = 0,
         unsigned int minute = 0,
         unsigned int second = 0,
         unsigned int microSecond = 0);

    static const Date date();

    static const Date now()
    {
        return Date::date();
    }   

    const Date after(double second) const;

    /// Create a Date object equal to * this, but the number of microseconds is
    /// zero.
    const Date roundSecond() const;

    /// Create a Date object equal to * this, but numbers of hours, minutes,
    /// seconds and microseconds are zero.
    const Date roundDay() const;

     ~Date(){};


    bool operator==(const Date &date) const
    {
        return microSecondsSinceEpoch_ == date.microSecondsSinceEpoch_;
    }
    bool operator!=(const Date &date) const
    {
        return microSecondsSinceEpoch_ != date.microSecondsSinceEpoch_;
    }
    bool operator<(const Date &date) const
    {
        return microSecondsSinceEpoch_ < date.microSecondsSinceEpoch_;
    }
    bool operator>(const Date &date) const
    {
        return microSecondsSinceEpoch_ > date.microSecondsSinceEpoch_;
    }
    bool operator>=(const Date &date) const
    {
        return microSecondsSinceEpoch_ >= date.microSecondsSinceEpoch_;
    }
    bool operator<=(const Date &date) const
    {
        return microSecondsSinceEpoch_ <= date.microSecondsSinceEpoch_;
    }
    int64_t microSecondsSinceEpoch() const
    {
        return microSecondsSinceEpoch_;
    }
    struct tm tmStruct() const;

 /// Generate a UTC time string
    /**
     * Example:
     * 20180101 10:10:25            //If the @param showMicroseconds is false
     * 20180101 10:10:25:102414     //If the @param showMicroseconds is true
     */
    std::string toFormattedString(bool showMicroseconds) const;

    /// Generate a UTC time string formated by the @param fmtStr
    /**
     * The @param fmtStr is the format string for the function strftime()
     * Example:
     * 2018-01-01 10:10:25          //If the @param fmtStr is "%Y-%m-%d
     * %H:%M:%S" and the @param showMicroseconds is false 2018-01-01
     * 10:10:25:102414   //If the @param fmtStr is "%Y-%m-%d %H:%M:%S" and the
     * @param showMicroseconds is true
     */
    std::string toCustomedFormattedString(const std::string &fmtStr,
                                          bool showMicroseconds = false) const;

    /// Generate a local time zone string, the format of the string is same as
    /// the mothed toFormattedString
    std::string toFormattedStringLocal(bool showMicroseconds) const;

    /// Generate a local time zone string formated by the @param fmtStr
    std::string toCustomedFormattedStringLocal(
        const std::string &fmtStr,
        bool showMicroseconds = false) const;

    /// Generate a local time zone string for database;
    /**
     * Example:
     * 2018-01-01                   //If hours, minutes, seconds and
     * microseconds are zero 2018-01-01 10:10:25          //If the microsecond
     * is zero 2018-01-01 10:10:25:102414   //If the microsecond is not zero
     */
    std::string toDbStringLocal() const;

    void toCustomedFormattedString(const std::string &fmtStr,
                                   char *str,
                                   size_t len) const;  // UTC

    bool isSameSecond(const Date &date) const
    {
        return microSecondsSinceEpoch_ / MICRO_SECONDS_PRE_SEC ==
               date.microSecondsSinceEpoch_ / MICRO_SECONDS_PRE_SEC;
    }

    void swap(Date &that)
    {
        std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
    }

private:
    int64_t microSecondsSinceEpoch_{0};  
};


}  // namespace netlib
