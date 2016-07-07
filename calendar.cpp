#include <iostream>
#include <iomanip>
using namespace std;


int getMonth(int month);
int getYear(int year);
int computeOffset(int year, int month);
int numDaysYear(int year);
int numDaysMonth(int year, int month);
bool isLeapYear(int year);
void display(int year, int month, int offset);


/**********************************************************************
 * This function will call all the functions necessary to make a calendar
 * for any given month and year.
 ***********************************************************************/
int main()
{
   int numDays;
   int offset;
   int month;
   int year;

   month = getMonth(month);

   year = getYear(year);

   offset = computeOffset(year, month);

   display(year, month, offset);

   return 0;
}

/***********************************************************************
 * Gets the month number.
 **********************************************************************/
int getMonth(int month)
{
   cout << "Enter a month number: ";
   cin >> month;

   while ( month < 1 || month > 12)
   {
      cout << "Month must be between 1 and 12.\n"
           << "Enter a month number: ";
      cin >> month;
   }

   return month;
}

/***********************************************************************
 * Gets the year.
 **********************************************************************/
int getYear(int year)
{
   cout << "Enter year: ";
   cin >> year;

   while ( year < 1753)
   {
      cout << "Year must be 1753 or later.\n"
           << "Enter year: ";
      cin >> year;
   }
   return year;
}

/***********************************************************************
 * Computes the offset.
 **********************************************************************/
//computes offset
int computeOffset(int year, int month)
{
   int numDays = 0;

   for ( int Year = 1753; Year < year; Year++)

      numDays  += numDaysYear(Year);


   for ( int Month = 1; Month < month; Month++)

      numDays += numDaysMonth(year, Month);

      int offset = numDays % 7;


   return offset;
}





/***********************************************************************
 * Computes the number of days in the given year.
 **********************************************************************/
int numDaysYear(int year)
{
   int daysYear = 365 + isLeapYear(year);
   return daysYear;
}

/***********************************************************************
 * Calculates the number of days in the given month.
 **********************************************************************/
int numDaysMonth(int year, int month)
{
   int daysMonth;

   if ( month == 1)
      daysMonth = 31;
   else if ( month == 2)
   {
      if (isLeapYear(year) == true)
         daysMonth = 29;
      else
         daysMonth = 28;
   }
   else if ( month == 3)
      daysMonth = 31;
   else if ( month == 4)
      daysMonth = 30;
   else if ( month == 5)
      daysMonth = 31;
   else if ( month == 6)
      daysMonth = 30;
   else if ( month == 7)
      daysMonth = 31;
   else if ( month == 8)
      daysMonth = 31;
   else if ( month == 9)
      daysMonth = 30;
   else if ( month == 10)
      daysMonth = 31;
   else if ( month == 11)
      daysMonth = 30;
   else if ( month == 12)
      daysMonth = 31;

   return daysMonth;
}

/***********************************************************************
 * Determines if given year is a leap year.
 **********************************************************************/
bool isLeapYear(int year)
{
   if ( year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
      return true;
   else
      return false;
}
 /**********************************************************************
 * Displays the calender table.
 **********************************************************************/
void display(int year, int month, int offset)
 {
    int dayOfWeek;
    int day;

    cout << endl;
    if ( month == 1)
       cout << "January";
    else if ( month == 2)
       cout << "February";
    else if ( month == 3)
       cout << "March";
    else if ( month == 4)
       cout << "April";
    else if ( month == 5)
       cout << "May";
    else if ( month == 6)
       cout << "June";
    else if ( month == 7)
       cout << "July";
    else if ( month == 8)
       cout << "August";
    else if ( month == 9)
       cout << "September";
    else if ( month == 10)
       cout << "October";
    else if ( month == 11)
       cout << "November";
    else if ( month == 12)
       cout << "December";


    cout << ", " << year << "\n";
    // Display month header
    cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";

    // Gets the correct offset width and end the line on the right
    //day of the week
    if (offset == 0)
    {
       day = 2;
       cout << setw(6);
    }
    else if (offset == 1)
    {
       day = 3;
       cout << setw(10);
    }
    else if (offset == 2)
    {
       day = 4;
       cout << setw(14);
    }
    else if (offset == 3)
    {
       day = 5;
       cout << setw(18);
    }
    else if (offset == 4)
    {
       day = 6;
       cout << setw(22);
    }
    else if (offset == 5)
    {
       day = 7;
       cout << setw(26);
    }
    else if (offset == 6)
    {
       day = 1;
       cout << setw(2);
    }
    else
       cout << "Error offset must be >= 0 and <=6\n";

    // The loop for displaying the days and ending the line in the right place
    for ( dayOfWeek = 1; dayOfWeek <= numDaysMonth(year, month); dayOfWeek++ )
    {
       cout << "  " <<  setw(2) << dayOfWeek;
       ++day;
       if (day == 8)
       {
          cout << "\n";
          day = 1;
       }
    }
    if ( day >= 2 && day <= 7)
       cout << "\n";

    return;
 }