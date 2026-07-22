#pragma once
#pragma warning(disable : 4996)// For GetSystemDate
#include<iostream>
#include"clsString.h"
#include<vector>
#include"string"
using namespace std;

/*
 Note : 

 Never bind a non-const reference (T&) to a temporary object.
 Temporaries live only until the end of the expression.
 Use 'const T&' or create a named object instead.

 1 - Wrong:
 clsDate& d = clsDate(10, 5, 2025);   // Error

 2 - Correct:
const clsDate& d = clsDate(10, 5, 2025);   // OK (temporary lifetime is extended)

clsDate d2 = clsDate(10, 5, 2025);         // OK (copy/move)

*/
class clsDate
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;
  
public:

	clsDate()
	{
       /* clsDate CurrentDate = GetSystemDate();

        _Day   = CurrentDate.Day;
        _Month = CurrentDate.Month;
        _Year  = CurrentDate.Year;*/

        time_t T = time(0);
        tm* now = localtime(&T);

        _Year  = now->tm_year + 1900;
        _Month = now->tm_mon + 1;
        _Day   = now->tm_mday;
	}
   
    clsDate(string sDate)
    {
        vector<string> VDate;

        VDate = clsString::Split(sDate, "/");

        _Day   = stoi(VDate[0]);
        _Month = stoi(VDate[1]);
        _Year  = stoi(VDate[2]);
    }
    
    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DayOrderInYear, short Year)
    {
        clsDate TempDate = GetDateFromDayOrderInYear(DayOrderInYear, Year);

        _Day   = TempDate._Day;
        _Month = TempDate._Month;
        _Year  = TempDate._Year;
    }

    void SetDay(short Day)
    {
        _Day = Day;
    }
    short GetDay()
    {
        return _Day;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void SetMonth(short Month)
    {
       _Month = Month;
    }
    short GetMonth()
    {
        return _Month;
    }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short Year)
    {
        _Year = Year;
    }
    short GetYear()
    {
        return _Year;
    }
    __declspec(property(get = GetYear, put = SetYear)) short Year;

   static bool isLeapYear(short Year)
    {
        return ((Year % 400 == 0) || ((Year % 4 == 0) && (Year % 100 != 0)));
    }
   bool isLeapYear()
   {
       return isLeapYear(_Year);
   }

   static short NumberOfDaysInAYear(short Year)
   {
       return isLeapYear(Year) ? 366 : 365;
   }
   short NumberOfDaysInAYear()
   {
       return NumberOfDaysInAYear(_Year);
   }

   static short  NumberOfHoursInAYear(short Year)
   {
       return NumberOfDaysInAYear(Year) * 24;
   }
   short NumberOfHoursInAYear()
   {
       return NumberOfHoursInAYear(_Year);
   }

   static int  NumberOfMinutesInAYear(short Year)
   {
       return  NumberOfHoursInAYear(Year) * 60;
   }
   int NumberOfMinutesInAYear()
   {
       return NumberOfMinutesInAYear(_Year);
   }

   static int  NumberOfSecondsInAYear(short Year)
   {
       return NumberOfMinutesInAYear(Year) * 60;
   }
   int NumberOfSecondsInAYear()
   {
       return NumberOfSecondsInAYear(_Year);
   }

   static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month>12)
            return 0;

        short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];

    }
   short NumberOfDaysInAMonth()
   {
       return NumberOfDaysInAMonth(_Month, _Year);
   }

   static short NumberOfHoursInAMonth(short Month, short Year)
   {
       return NumberOfDaysInAMonth(Month, Year) * 24;
   }
   short NumberOfHoursInAMonth()
   {
       return NumberOfHoursInAMonth(_Month, _Year);
   }

   static int NumberOfMinutesInAMonth(short Month, short Year)
   {
       return NumberOfHoursInAMonth(Month, Year) * 60;
   }
   int NumberOfMinutesInAMonth()
   {
       return NumberOfMinutesInAMonth(_Month, _Year);
   }

   static int NumberOfSecondsInAMonth(short Month, short Year)
   {
       return NumberOfMinutesInAMonth(Month, Year) * 60;
   }
   int NumberOfSecondsInAMonth()
   {
       return NumberOfSecondsInAMonth(_Month, _Year);
   }
   
   static short DayOfWeekOrder(short Day, short Month, short Year)
   {
       short a, y, m, d;

       a = (14 - Month) / 12;

       y = Year - a;

       m = Month + (12 * a) - 2;

       //Gregorian
       //0:Sun, 1:Mon, 2:Tue...etc

       return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
   }
 
   static short DayOfWeekOrder(clsDate Date)
   {
       return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
   }
   short DayOfWeekOrder()
   {
       return DayOfWeekOrder(*this);
   }

   static string DayShortName(short Day, short Month, short Year)
   {

       string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

       return arrDayNames[DayOfWeekOrder(Day, Month, Year)];

   }
  

   static string DayShortName(short DayOfWeekOrder)
   {
       string arrDayNames[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

       return arrDayNames[DayOfWeekOrder];
   }
   string DayShortName()
   {
       return DayShortName(DayOfWeekOrder());
   }


   static string MonthShortName(short Month)
   {
       string arrMonthNames[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

       return arrMonthNames[Month - 1];
   }
   string MonthShortName()
   {
       return MonthShortName(_Month);
   }

   static void PrintMonthCalendar(short Month, short Year)
   {
       int NumberOfDays;

       // Index of the day from 0 to 6
       int current = DayOfWeekOrder(1, Month, Year);

       NumberOfDays = NumberOfDaysInAMonth(Month, Year);

       // Print the current month name
       printf("\n _______________%s_______________\n\n",
           MonthShortName(Month).c_str());

       // Print the columns
       printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

       // Print appropriate spaces (4 spaces per day)
       int i;
       for (i = 0; i < current; i++)
           printf("     ");  // 5 مسافات (لكن المسافة الأولى من %5d)

       for (int j = 1; j <= NumberOfDays; j++)
       {
           printf("%5d", j);  // %5d = 4 مسافات + الرقم

           if (++i == 7)
           {
               i = 0;
               printf("\n");
           }
       }

       printf("\n _________________________________\n");
   }
   void PrintMonthCalendar()
   {
       return PrintMonthCalendar(_Month, _Year);
   }

   static void PrintYearCalendar(int Year)
   {
       printf("\n  _________________________________\n\n");
       printf("           Calendar - %d\n", Year);
       printf("  _________________________________\n");


       for (int i = 1; i <= 12; i++)
       {
           PrintMonthCalendar(i, Year);
       }

       return;
   }
   void PrintYearCalendar()
   {
       printf("\n  _________________________________\n\n");
       printf("           Calendar - %d\n", _Year);
       printf("  _________________________________\n");


       for (int i = 1; i <= 12; i++)
       {
           PrintMonthCalendar(i, _Year);
       }

       return;
   }

   static short DaysFromTheBeginningOfTheYear(short Day, short Month, short Year)
   {
       short TotalDays = 0;

       for (short i = 1; i <= Month - 1; i++)
       {
           TotalDays += NumberOfDaysInAMonth(i, Year);
       }

       TotalDays += Day;

       return TotalDays;
   }
   short DaysFromTheBeginningOfTheYear()
   {
       return DaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
   }

   static void SwapDates(clsDate& Date1, clsDate& Date2)
   {
       clsDate TempDate;

       TempDate = Date1;
       Date1 = Date2;
       Date2 = TempDate;

       // Second Ways...

       /*TempDate.Day = Date1.Day;
       TempDate.Month = Date1.Month;
       TempDate.Year = Date1.Year;

       Date1.Day = Date2.Day;
       Date1.Month = Date2.Month;
       Date1.Year = Date2.Year;

       Date2.Day = TempDate.Day;
       Date2.Month = TempDate.Month;
       Date2.Year = TempDate.Year;*/

   }
   void SwapDates(clsDate &Date2)
   {
       //int main()
       // {Date.SwapDates(clsDate(1, 1, 2000)); Error...
       //Date.SwapDates(Date2); True...}
      SwapDates((*this), Date2);
   }

   static clsDate GetDateFromDayOrderInYear(short DaysOrderInAYear, short Year)
    {
        short RemainingDays = DaysOrderInAYear;
        short MonthDays;

        clsDate Date;

        Date.Year = Year;
        Date.Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Year);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }

        }

        return Date;
    }
  
   static clsDate AddDays(short NumberOfDaysToAdd, clsDate &Date)
   {

       short RemaningDays = NumberOfDaysToAdd + DaysFromTheBeginningOfTheYear(Date.Day, Date.Month, Date.Year);
       short MonthDay = 0;

       Date.Month = 1;

       while (true)
       {
           MonthDay = NumberOfDaysInAMonth(Date.Month, Date.Year);

           if (RemaningDays > MonthDay)
           {
               RemaningDays -= MonthDay;

               Date.Month++;

               if (Date.Month > 12)
               {
                   Date.Month = 1;
                   Date.Year++;
               }
           }

           else
           {
               Date.Day = RemaningDays;
               break;
           }

       }

       return Date;

   }
   void AddDays(short NumberOfDaysToAdd)
   {
       AddDays(NumberOfDaysToAdd, *this);
   }

   static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
   {
       return (Date1.Year < Date2.Year) ? true :
           (
               (Date1.Year == Date2.Year) ?
               (
                   (Date1.Month < Date2.Month) ? true :
                   (
                       (Date1.Month == Date2.Month) ?
                       Date1.Day < Date2.Day :
                       false
                       )
                   ) :
               false
               );
   }
   bool IsDateBeforeDate2(clsDate Date2)
   {
       return IsDate1BeforeDate2(*this, Date2);
   }

   static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
   {

       return (Date1.Year == Date2.Year) ?
           (
               (Date1.Month == Date2.Month) ? Date1.Day == Date2.Day : false
               )
           : false;
   }
   bool IsDateEqualDate2(clsDate Date2)
   {
       return IsDate1EqualDate2(*this, Date2);
   }

   static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
   {
       return(!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
   }
   bool IsDateAfterDate2(clsDate Date2)
   {
       return IsDate1AfterDate2(*this, Date2);
   }

   static bool IsLastDayInMonth(clsDate Date)
   {
       return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
   }
   bool IsLastDayInMonth()
   {
       return IsLastDayInMonth(*this);
   }

   static bool IsLastMonthInYear(short Month)
   {
       return (Month == 12);
   }
   bool IsLastMonthInYear()
   {
       return IsLastMonthInYear(_Month);
   }

   static bool IsLastDayInYear(clsDate Date)
   {
       return (IsLastDayInMonth(Date) && IsLastMonthInYear(Date.Month));
   }
   bool IsLastDayInYear()
   {
       return IsLastDayInYear(*this);
   }

   static clsDate AddOneDay(clsDate Date)
   {
       if (IsLastDayInMonth(Date))
       {
           if (IsLastMonthInYear(Date.Month))
           {
               Date.Day = 1;
               Date.Month = 1;
               Date.Year++;
           }

           else
           {
               Date.Day = 1;
               Date.Month++;
           }
       }

       else
       {
           Date.Day++;
       }

       return Date;
   }
   void AddOneDay()
   {
       clsDate TempDate = AddOneDay(*this);

       _Day = TempDate._Day;
       _Month = TempDate._Month;
       _Year = TempDate._Year;

       //Second Way...

       //*this=AddOneDay(*this);
   }

   static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludingEndDay = false)
    {
        int DiffDays = 0;
        short SwapFlagValue = 1;

        if (IsDate1AfterDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Date1 = AddOneDay(Date1);
            DiffDays++;
        }

        return IncludingEndDay ? ++DiffDays * SwapFlagValue : DiffDays * SwapFlagValue;

    }
   int GetDifferenceInDays(clsDate Date2, bool IncludingEndDay = false)
   {
       return GetDifferenceInDays(*this, Date2, IncludingEndDay);
   }

   static clsDate GetSystemDate()
   {
       time_t T = time(0);
       tm* now = localtime(&T);
       
       short Day, Month, Year;

       Year = now->tm_year + 1900;
       Month = now->tm_mon + 1;
       Day = now->tm_mday;

       return clsDate(Day, Month, Year);
   }
   
   static int CalculateMyAgeInDays(clsDate DateOfBirth)
   {
       return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
   }

   static  clsDate IncreaseDateByXDays(clsDate &Date, short NumberOfDays)
   {
       for (short i = 1; i <= NumberOfDays; i++)
       {
           Date = AddOneDay(Date);
       }

       return Date;
   }
   void IncreaseDateByXDays(short NumberOfDays)
   {
      IncreaseDateByXDays(*this,NumberOfDays);
   }

   static clsDate IncreaseDateByOneWeek(clsDate &Date)
   {
       for (short i = 1; i <= 7; i++)
       {
           Date = AddOneDay(Date);
       }

       return Date;
   }
   void IncreaseDateByOneWeek()
   {
       IncreaseDateByOneWeek(*this);
   }

   static  clsDate IncreaseDateByXWeeks(clsDate &Date, short NumberOfWeeks)
   {
       for (short i = 1; i <= NumberOfWeeks; i++)
       {
           Date = IncreaseDateByOneWeek(Date);
       }

       return Date;
   }
   void IncreaseDateByXWeeks(short NumberOfWeeks)
   {
       IncreaseDateByXWeeks(*this, NumberOfWeeks);
   }

   static clsDate IncreaseDateByOneMonth(clsDate &Date)
   {

       if (IsLastMonthInYear(Date.Month))
       {
           Date.Year++;
           Date.Month = 1;
       }

       else
           Date.Month++;

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;


       return Date;
   }
   void IncreaseDateByOneMonth()
   {
       IncreaseDateByOneMonth(*this);
   }

   static clsDate IncreaseDateByXMonths(clsDate &Date, short NumberOfMonths)
   {
       for (short i = 1; i <= NumberOfMonths; i++)
       {
           Date = IncreaseDateByOneMonth(Date);
       }

       return Date;
   }
   void IncreaseDateByXMonths(short NumberOfMonths)
   {
       IncreaseDateByXMonths(*this, NumberOfMonths);
   }

   static clsDate IncreaseDateByOneYear(clsDate &Date)
   {
       Date.Year++;


       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;


       return Date;
   }
   void IncreaseDateByOneYear()
   {
       IncreaseDateByOneYear(*this);
   }

   static clsDate IncreaseDateByXYears(clsDate &Date, short NumberOfYears)
   {
       Date.Year += NumberOfYears;

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void IncreaseDateByXYears(short NumberOfYears)
   {
       IncreaseDateByXYears(*this, NumberOfYears);
   }

   static clsDate IncreaseDateByOneDecade(clsDate &Date)
   {
       for (short i = 1; i <= 10; i++)
       {
           Date = IncreaseDateByOneYear(Date);
       }

       return Date;
   }
   void IncreaseDateByOneDecade()
   {
       IncreaseDateByOneDecade(*this);
   }

   static clsDate IncreaseDateByXDecades(clsDate &Date, short NumberOfDecades)
   {
       Date.Year += (10 * NumberOfDecades);

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;


       return Date;
   }
   void IncreaseDateByXDecades(short NumberOfDecades)
   {
      IncreaseDateByXDecades(*this, NumberOfDecades);
   }

   static clsDate IncreaseDateByOneCentury(clsDate &Date)
   {
       Date.Year += 100;

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void IncreaseDateByOneCentury()
   {
       IncreaseDateByOneCentury(*this);
   }

   static  clsDate IncreaseDateByOneMillennium(clsDate& Date)
   {
       Date.Year += 1000;

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void IncreaseDateByOneMillennium()
   {
       IncreaseDateByOneMillennium(*this);
   }

   static bool IsFirstDayInMonth(short Day)
   {
       return (Day == 1);
   }
   bool IsFirstDayInMonth()
   {
       return IsFirstDayInMonth(_Day);
   }

   static bool IsFirstMonthInYear(short Month)
   {
       return (Month == 1);
   }
   bool IsFirstMonthInYear()
   {
       return IsFirstMonthInYear(_Month);
   }

   static clsDate DecreaseDateByOneDay(clsDate &Date)
   {
       if (IsFirstDayInMonth(Date.Day))
       {
           if (IsFirstMonthInYear(Date.Month))
           {
               Date.Year--;
               Date.Month = 12;
               Date.Day = 31;
           }

           else
           {
               Date.Month--;
               Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
           }
       }

       else
       {
           Date.Day--;
       }

       return Date;
   }
   void DecreaseDateByOneDay()
   {
       DecreaseDateByOneDay(*this);
   }

   static clsDate DecreaseDateByXDays(clsDate &Date, short NumberOfDays)
   {
       for (short i = 1; i <= NumberOfDays; i++)
       {
           Date = DecreaseDateByOneDay(Date);
       }

       return Date;
   }
   void DecreaseDateByXDays(short NumberOfDays)
   {
       DecreaseDateByXDays(*this, NumberOfDays);
   }

   static clsDate DecreaseDateByOneWeek(clsDate &Date)
   {
       for (short i = 1; i <= 7; i++)
       {
           Date = DecreaseDateByOneDay(Date);
       }

       return Date;
   }
   void DecreaseDateByOneWeek()
   {
       DecreaseDateByOneWeek(*this);
   }

   static clsDate DecreaseDateByXWeeks(clsDate &Date, short NumberOfWeeks)
   {
       for (short i = 1; i <= NumberOfWeeks; i++)
       {
           Date = DecreaseDateByOneWeek(Date);
       }

       return Date;
   }
   void DecreaseDateByXWeeks(short NumberOfWeeks)
   {
       DecreaseDateByXWeeks(*this, NumberOfWeeks);      
   }

   static clsDate DecreaseDateByOneMonth(clsDate &Date)
   {
       if (IsFirstMonthInYear(Date.Month))
       {
           Date.Year--;
           Date.Month = 12;
       }

       else
       {
           Date.Month--;
       }

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void DecreaseDateByOneMonth()
   {
       DecreaseDateByOneMonth(*this);
   }

   static clsDate DecreaseDateByXMonths(clsDate& Date, short NumberOfMonths)
   {
       for (short i = 1; i <= NumberOfMonths; i++)
       {
           Date = DecreaseDateByOneMonth(Date);
       }

       return Date;
   }
   void DecreaseDateByXMonths(short NumberOfMonths)
   {
       DecreaseDateByXMonths(*this,NumberOfMonths);
   }
   
   static clsDate DecreaseDateByOneYear(clsDate &Date)
   {
       Date.Year--;

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void DecreaseDateByOneYear()
   {
      DecreaseDateByOneYear(*this);
   }

   static clsDate DecreaseDateByXYears(clsDate &Date, short NumberOfYears)
   {
       Date.Year -= NumberOfYears;


       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void DecreaseDateByXYears(short NumberOfYears)
   {
       DecreaseDateByXYears(*this, NumberOfYears);
   }

   static clsDate DecreaseDateByOneDecade(clsDate &Date)
   {
       for (short i = 1; i <= 10; i++)
       {
           Date = DecreaseDateByOneYear(Date);
       }

       return Date;
   }
   void DecreaseDateByOneDecade()
   {
       DecreaseDateByOneDecade(*this);
   }

   static clsDate DecreaseDateByXDecades(clsDate &Date, short NumberOfDecades)
   {
       Date.Year -= (NumberOfDecades * 10);

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void DecreaseDateByXDecades(short NumberOfDecades)
   {
       DecreaseDateByXDecades(*this, NumberOfDecades);
   }

   static clsDate DecreaseDateByOneCentury(clsDate &Date)
   {
       Date.Year -= 100;

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void DecreaseDateByOneCentury()
   {
       DecreaseDateByOneCentury(*this);
   }

   static clsDate DecreaseDateByOneMillennium(clsDate &Date)
   {
       Date.Year -= 1000;

       short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (NumberOfDaysInCurrentMonth < Date.Day)
           Date.Day = NumberOfDaysInCurrentMonth;

       return Date;
   }
   void DecreaseDateByOneMillennium()
   {
       DecreaseDateByOneMillennium(*this);
   }

   static bool IsEndOfWeek(clsDate Date)
   {
       return (DayOfWeekOrder(Date) == 6);
   }
   bool IsEndOfWeek()
   {
       return IsEndOfWeek(*this);
   }

   static bool IsWeekEnd(clsDate Date)
   {
       //Weekends are Fri and Sat

       short DateIndex = DayOfWeekOrder(Date);

       return (DateIndex == 5 || DateIndex == 6);
   }
   bool IsWeekEnd()
   {
       return IsWeekEnd(*this);
   }

   static bool IsBusinessDay(clsDate Date)
   {
       //return(DayOfWeekOrder != 5 || DayOfWeekOrder != 6);
       return (!IsWeekEnd(Date));
   }
   bool IsBusinessDay()
   {
       return IsBusinessDay(*this);
   }

   static short DaysUntilTheEndOfWeek(clsDate Date){
       return(6 - DayOfWeekOrder(Date));
   }
   short DaysUntilTheEndOfWeek()
   {
       return DaysUntilTheEndOfWeek(*this);
   }

   static short DaysUntilTheEndOfMonth(clsDate Date)
   {
       clsDate EndOfMonthDate;

       EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
       EndOfMonthDate.Month = Date.Month;
       EndOfMonthDate.Year = Date.Year;

       return GetDifferenceInDays(Date, EndOfMonthDate, true);
   }
   short DaysUntilTheEndOfMonth()
   {
       return DaysUntilTheEndOfMonth(*this);
   }

   static short DaysUntilTheEndOfYear(clsDate Date)
   {
       clsDate EndOfYearDate;

       EndOfYearDate.Day = 31;
       EndOfYearDate.Month = 12;
       EndOfYearDate.Year = Date.Year;

       return GetDifferenceInDays(Date, EndOfYearDate, true);
   }
   short DaysUntilTheEndOfYear()
   {
       return DaysUntilTheEndOfYear(*this);
   }

   //i added this method to calculate business days between 2 Dates
   static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
   {

       short Days = 0;
       while (IsDate1BeforeDate2(DateFrom, DateTo))
       {
           if (IsBusinessDay(DateFrom))
               Days++;

           DateFrom = AddOneDay(DateFrom);
       }

       return Days;

   }

   static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
   {
       return CalculateBusinessDays(DateFrom, DateTo);
   }
   //above method is eough , no need to have method for the object

   static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
   {

       short WeekEndCounter = 0;

       for (short i = 1; i <= VacationDays; i++)
       {

           if (IsWeekEnd(DateFrom))
               WeekEndCounter++;

           DateFrom = AddOneDay(DateFrom);
       }
       //to add weekends 
       for (short i = 1; i <= WeekEndCounter; i++)
           DateFrom = AddOneDay(DateFrom);

       return DateFrom;
   }

   enum enDateCompare { Before = -1, Equal = 0, After = 1 };
   static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
   {
       if (IsDate1BeforeDate2(Date1, Date2))
           return enDateCompare::Before;

       if (IsDate1EqualDate2(Date1, Date2))
           return enDateCompare::Equal;

       /*if (IsDate1AfterDate2(Date1, Date2))
           return enDateCompare::After;*/

           //This is Faster
       return enDateCompare::After;
   }
   enDateCompare CompareDates(clsDate Date2)
   {
       return CompareDates(*this, Date2);
   }

   static bool IsValidDate(clsDate Date)
   {
       if (Date.Day < 1 || Date.Day>31)
           return false;

       if (Date.Month < 1 || Date.Month>12)
           return false;

       if (Date.Month == 2)
       {
           if (isLeapYear(Date.Year))
           {
               if (Date.Day > 29)
                   return false;
           }

           else
           {
               if (Date.Day > 28)
                   return false;
           }
       }

       if (clsDate::After == clsDate::CompareDates(Date, clsDate::GetSystemDate()))
           return false; 
       
       short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

       if (Date.Day > DaysInMonth)
           return false;



       return true;

   }
   bool IsValid()
   {
       return IsValidDate(*this);
   }

   static clsDate StringToDate(string Text)
   {
       vector<string> vDate = clsString::Split(Text, "/");

       clsDate Date;

       Date.Day = stoi(vDate[0]);
       Date.Month = stoi(vDate[1]);
       Date.Year = stoi(vDate[2]);

       return Date;
   }
  
   static string DateToString(clsDate Date)
   {
       return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
   }
   string DateToString()
   {
       return DateToString(*this);
   }

   static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
   {
       string FormattedDateString = "";

       FormattedDateString = clsString::ReplaceWordInStringUsingBuiltInFunction(DateFormat, "dd", to_string(Date.Day));
       FormattedDateString = clsString::ReplaceWordInStringUsingBuiltInFunction(FormattedDateString, "mm", to_string(Date.Month));
       FormattedDateString = clsString::ReplaceWordInStringUsingBuiltInFunction(FormattedDateString, "yyyy", to_string(Date.Year));

       return FormattedDateString;

       // 1/12/2000
       // dd/mm/yyyy -> 1/12/2000
       // mm/dd/yyyy -> 12/1/2000
       // yyyy/mm/dd -> 2000/12/1

   }
   string FormatDate(string DateFormat = "dd/mm/yyyy")
   {
       return FormatDate(*this, DateFormat);
   }

    void Print()
    {
        cout << DateToString() << endl;
    }

    //Append..
};

