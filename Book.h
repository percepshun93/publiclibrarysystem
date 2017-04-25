#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include <cstring>
// Coded by Santanu Karmakar
// Book Class - It includes all information about a single book
// It also defines all setter getter functions for all the private data members.
class Book
{
private :
    int book_id; // 10 bytes
    char book_name[45]; // 40 bytes
    char book_category[10]; // (F)iction/(T)extBooks/(E)ssays/(M)agazines/(A)utobiography/(S)ports
    struct date book_aq_dt; // 8 bytes
    char book_status[10]; //(A)vailable/(B)orrowed
    char book_author_name[45]; //40 bytes
    char book_ISBN[15]; // 12 bytes

public :
    // Book Id setter and getter functions
    void set_book_id(int bk_id)
    {
        book_id = bk_id;
    }

    int get_book_id()
    {
       return book_id;
    }

    // Book Name setter and getter functions
    void set_book_name(char *bk_nm)
    {
        strcpy(book_name, bk_nm);
    }

    char *get_book_name()
    {
        return book_name;
    }

    // Book Category setter and getter functions
    void set_book_category(char *bk_cat)
    {
        strcpy(book_category, bk_cat);
    }

    char *get_book_category()
    {
        return book_category;
    }

    // Book Acquire Date setter and getter functions
    void set_book_aq_dt(int dt, int mt, int yr)
    {
        book_aq_dt.day = dt;
        book_aq_dt.month = mt;
        book_aq_dt.year = yr;
    }

    struct date get_book_aq_dt()
    {
        return book_aq_dt;
    }

    int get_book_aq_day()
    {
        return book_aq_dt.day;
    }

    int get_book_aq_month()
    {
        return book_aq_dt.month;
    }

    int get_book_aq_year()
    {
        return book_aq_dt.year;
    }

    // Book Status setter and getter functions
    void set_book_status(char *bk_stat)
    {
        strcpy(book_status, bk_stat);
    }

    char *get_book_status()
    {
        return book_status;
    }

    // Book Author Name setter and getter functions
    void set_book_author_name(char *bk_athr_nm)
    {
        strcpy(book_author_name, bk_athr_nm);
    }

    char *get_book_author_name()
    {
        return book_author_name;
    }

    // book ISBN setter and getter functions
    void set_book_ISBN(char *bk_ISBN)
    {
        strcpy(book_ISBN, bk_ISBN);
    }

    char *get_book_ISBN()
    {
        return book_ISBN;
    }
};


#endif // BOOK_H_INCLUDED
