#ifndef TRANSACTOR_H_INCLUDED
#define TRANSACTOR_H_INCLUDED
// Coded by Santanu Karmakar
// This class defines a single record of transaction information
class Transactor
{
private :
    int transactor_id; // 10 bytes
    int book_id; // 10 bytes
    int subscriber_id; // 10 bytes
    struct date borrow_dt;
    struct date return_dt;

public :

     // Transactor Id setter and getter functions
    void set_transactor_id(int tr_id)
    {
        transactor_id = tr_id;
    }

    int get_transactor_id()
    {
       return transactor_id;
    }


    // Book Id setter and getter functions
    void set_book_id(int bk_id)
    {
        book_id = bk_id;
    }

    int get_book_id()
    {
       return book_id;
    }

   // Subscriber Id setter and getter functions
    void set_subscriber_id(int s_id)
    {
        subscriber_id = s_id;
    }

    int get_subscriber_id()
    {
       return subscriber_id;
    }

     // Book Borrow Date setter and getter functions
    void set_borrow_dt(int dt, int mt, int yr)
    {
        borrow_dt.day = dt;
        borrow_dt.month = mt;
        borrow_dt.year = yr;
    }

    struct date get_borrow_dt()
    {
        return borrow_dt;
    }

    int get_borrow_day()
    {
        return borrow_dt.day;
    }

    int get_borrow_month()
    {
        return borrow_dt.month;
    }

    int get_borrow_year()
    {
        return borrow_dt.year;
    }


      // Book Return Date setter and getter functions
    void set_return_dt(int dt, int mt, int yr)
    {
        return_dt.day = dt;
        return_dt.month = mt;
        return_dt.year = yr;
    }

    struct date get_return_dt()
    {
        return return_dt;
    }

    int get_return_day()
    {
        return return_dt.day;
    }

    int get_return_month()
    {
        return return_dt.month;
    }

    int get_return_year()
    {
        return return_dt.year;
    }

};

#endif // TRANSACTOR_H_INCLUDED
