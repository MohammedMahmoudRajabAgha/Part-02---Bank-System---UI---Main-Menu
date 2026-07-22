#pragma once
#include<iostream>
#include"clsDate.h"
using namespace std;


class clsPeriod
{
    clsDate _StartDate;
    clsDate _EndDate;

public:

    clsPeriod(clsDate StartDate, clsDate EndDate)
    {
        _StartDate = StartDate;
        _EndDate = EndDate;
    }

    void SetStartDate(clsDate StartDate)
    {
        _StartDate = StartDate;
    }
    clsDate GetStartDate()
    {
        return _StartDate;
    }
    __declspec(property(get = GetStartDate, put = SetStartDate)) clsDate StartDate;

    void SetEndDate(clsDate EndDate)
    {
        _EndDate = EndDate;
    }
    clsDate GetEndDate()
    {
        return _EndDate;
    }
    __declspec(property(get = GetEndDate, put = SetEndDate)) clsDate EndDate;

    static bool IsOverLapPeriods(clsPeriod Period1, clsPeriod Period2)
    {
        if (clsDate::CompareDates(Period1.StartDate, Period2.EndDate) == clsDate::enDateCompare::After
            ||
            clsDate::CompareDates(Period1.EndDate, Period2.StartDate) == clsDate::enDateCompare::Before)
            return false;

        return true;

    }
    bool IsOverLapPeriods(clsPeriod Period2)
    {
        return IsOverLapPeriods(*this, Period2);
    }

     void Print()
    {
        cout << "Period Start : ";
        StartDate.Print();

        cout << "Period End : ";
        EndDate.Print();

    }

    //Append...

    static int PeriodLengthInDays(clsPeriod Period, bool IncludingEndDay = false)
    {
        return(clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludingEndDay));
    }
    int PeriodLengthInDays(bool IncludingEndDay = false)
    {
        return PeriodLengthInDays(*this, IncludingEndDay);
    }

    static bool IsDateInPeriod(clsPeriod Period, clsDate Date)
    {
        return !(clsDate::CompareDates(Period.StartDate, Date) == clsDate::enDateCompare::After
            ||
            clsDate::CompareDates(Period.EndDate, Date) == clsDate::enDateCompare::Before);
    }
    bool IsDateInPeriod(clsDate Date)
    {
        return IsDateInPeriod(*this, Date);
    }

    static int CountOverLapDays(clsPeriod Period1, clsPeriod Period2)
    {
        short Period1Length = PeriodLengthInDays(Period1, true);
        short Period2Length = PeriodLengthInDays(Period2, true);
        int OverLapDays = 0;

        if (!IsOverLapPeriods(Period1, Period2))
            return 0;

        if (Period1Length < Period2Length)
        {
            while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
            {
                if (IsDateInPeriod(Period2, Period1.StartDate))
                    OverLapDays++;

                Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);
            }
        }

        else
        {
            while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
            {
                if (IsDateInPeriod(Period1, Period2.StartDate))
                    OverLapDays++;

                Period2.StartDate = clsDate::AddOneDay(Period2.StartDate);
            }
        }

        return OverLapDays;
    }
    int CountOverLapDays(clsPeriod Period2)
    {
        return CountOverLapDays(*this, Period2);
    }


};