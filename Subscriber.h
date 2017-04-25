#ifndef SUBSCRIBER_H_INCLUDED
#define SUBSCRIBER_H_INCLUDED
// Coded by Santanu Karmakar
// This class defines the information content for a single Subscriber
class Subscriber
{
private :
    int subscriber_id; // 10 bytes
    char subscriber_name[45]; // 40 bytes
    struct date subscriber_joining_dt; // 8 bytes
    int subscriber_num_borrowed; // 2 bytes
    char subscriber_address[45]; //40 bytes
    char subscriber_id_proof[15]; // 12 bytes

public :
    // Subscriber Id setter and getter functions
    void set_subscriber_id(int s_id)
    {
        subscriber_id = s_id;
    }

    int get_subscriber_id()
    {
       return subscriber_id;
    }

    // Subscriber Name setter and getter functions
    void set_subscriber_name(char *s_nm)
    {
        strcpy(subscriber_name, s_nm);
    }

    char *get_subscriber_name()
    {
        return subscriber_name;
    }


    // Subscriber Joining Date setter and getter functions
    void set_subscriber_joining_dt(int dt, int mt, int yr)
    {
        subscriber_joining_dt.day = dt;
        subscriber_joining_dt.month = mt;
        subscriber_joining_dt.year = yr;
    }

    struct date get_subscriber_joining_dt()
    {
        return subscriber_joining_dt;
    }

    int get_subscriber_joining_day()
    {
        return subscriber_joining_dt.day;
    }

    int get_subscriber_joining_month()
    {
        return subscriber_joining_dt.month;
    }

    int get_subscriber_joining_year()
    {
        return subscriber_joining_dt.year;
    }

    // This stores the number of books borrowed information and provides setter and getter functions
    void set_subscriber_num_borrowed(int s_num_borrowed)
    {
        subscriber_num_borrowed = s_num_borrowed;
    }

    int get_subscriber_num_borrowed()
    {
       return subscriber_num_borrowed;
    }


    // Subscriber's address setter and getter functions
    void set_subscriber_address(char *s_address)
    {
        strcpy(subscriber_address, s_address);
    }

    char *get_subscriber_address()
    {
        return subscriber_address;
    }

    // Subscriber id proof setter and getter functions
    void set_subscriber_id_proof(char *s_id_proof)
    {
        strcpy(subscriber_id_proof, s_id_proof);
    }

    char *get_subscriber_id_proof()
    {
        return subscriber_id_proof;
    }
};

#endif // SUBSCRIBER_H_INCLUDED
