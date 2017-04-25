#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

// Includes all header files that has been used in the project loaded once only
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>


// Structure date is used in all different classes and data structures
struct date
{
        int day;
        int month;
        int year;
};

// Structure used for storing the book records temporarily after reading from array or before storing in array
struct bookStr
{
    int book_id; // 10 bytes
    char book_name[45]; // 40 bytes
    char book_category[10]; // (F)iction/(T)extBooks/(E)ssays/(M)agazines/(A)utobiography/(S)ports
    struct date book_aq_dt; // 8 bytes
    char book_status[10]; //(A)vailable/(B)orrowed
    char book_author_name[45]; //40 bytes
    char book_ISBN[15]; // 12 bytes
};

// Structure used for storing the subscriber records temporarily after reading from array or before storing in array
struct subscriberStr
{
    int subscriber_id; // 10 bytes
    char subscriber_name[45]; // 40 bytes
    struct date subscriber_joining_dt; // 8 bytes
    int subscriber_num_borrowed; // 2 bytes
    char subscriber_address[45]; //40 bytes
    char subscriber_id_proof[15]; // 12 bytes
};

// Structure used for storing the transactor records (borrow and return) temporarily after reading from array or before storing in array
struct trStr
{
    int transactor_id; // 10 bytes
    int book_id; // 10 bytes
    int subscriber_id; // 10 bytes
    struct date borrow_dt;
    struct date return_dt;
};

// Date related commonly used functions
// This function will compute the day difference between two dates
double daydiff(int d1, int m1, int y1, int d2, int m2, int y2 )
{
    double difference;
    y1 = y1-1900;
    y2 = y2-1900;
    struct std::tm a = {0,0,0,d1,m1,y1}; /* June 24, 2004 */
    struct std::tm b = {0,0,0,d2,m2,y2}; /* July 5, 2004 */
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
    {
        difference = std::difftime(y, x) / (60 * 60 * 24);
    }
    return difference;
}

// get today's day
int getTodayDay()
{
  // current date/time based on current system
   time_t now = time(0);
   tm *ltm = localtime(&now);
   return  ltm->tm_mday ;
}

// get today's month
int getTodayMonth()
{
  // current date/time based on current system
   time_t now = time(0);
   tm *ltm = localtime(&now);
   return  ltm->tm_mon+1 ;
}

// get today's year
int getTodayYear()
{
  // current date/time based on current system
   time_t now = time(0);
   tm *ltm = localtime(&now);
   return  1900 + ltm->tm_year ;
}

// This function has been used to generate aging reports where a given date is compared with current date
// it returns difference in number of dates
double todaydiff(struct date dt)
{
    return daydiff(dt.day,  dt.month,  dt.year, getTodayDay(), getTodayMonth(), getTodayYear());
}

#endif // COMMON_H_INCLUDED
