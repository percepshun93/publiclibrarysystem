#ifndef VALIDATOR_H_INCLUDED
#define VALIDATOR_H_INCLUDED
// Coded by Santanu Karmakar
// Class validator is used for validating data based on some given format
// It is also used for doing date based validation
// These are the same functions that have been used for module II project
class Validator
{
   public :
    static int indexOf(char c, char *str);
    static char charAt(int p, char *str);
    static void stringExtract(char *dest, char *source, int sp, int ep);
    static int dataValidate(char *fmt, char *data);
    static int dateValidate(char *fmt, char *data);
    static int extractValidateDay(char *fmt, char *data, int mn, int yr);
    static int extractValidateMonth(char *fmt, char *data);
    static int extractValidateYear(char *fmt, char *data);
    static int extractDay(char *fmt, char *data);
    static int extractMonth(char *fmt, char *data);
    static int extractYear(char *fmt, char *data);
};
// This function compares the given data with a given format and returns 1 (true) or 0 (false)
int Validator::dataValidate(char *fmt, char *data)
{
        char ch;
        int i;

        int fl = strlen(fmt);
        int sl = strlen(data);

        if (indexOf('*', fmt) > -1)
        {
            if ((indexOf('*', fmt)+1) > sl)
            {
                   return 0;
            }
        }
        else
        {
            if (fl != sl)
            {
                  return 0;
            }
        }

       for(i = 0; i < fl; i++)
          {
              ch = charAt(i, data);
              if (charAt(i, fmt) == 'n')
              {
                  if (!isdigit(ch))
                  {
                     return 0;
                  }
              }
              else if (charAt(i, fmt) == 'D')
              {
                  if (!isdigit(ch))
                  {
                     return 0;
                  }
              }
              else if (charAt(i, fmt) == 'M')
              {
                  if (!isdigit(ch))
                  {
                     return 0;
                  }
              }
              else if (charAt(i, fmt) == 'Y')
              {
                  if (!isdigit(ch))
                  {
                     return 0;
                  }
              }
              else if (charAt(i, fmt) == 'x')
              {
                  if (!isalnum(ch))
                  {
                     return 0;
                  }
              }
              else if (charAt(i, fmt) == 'a')
              {
                  if (!isalpha(ch))
                  {
                     return 0;
                  }
              }
              else if (charAt(i, fmt) == '*')
              {
                     return 1;
              }
              else
              {
                  if (ch != charAt(i, fmt) )
                  {
                     return 0;
                   }
              }
       }

    return 1;
}

// This function compares the given date information  with a given format and returns 1 (true) or 0 (false)
int Validator::dateValidate(char *fmt, char *data)
{
      int mn, dy, yr;
      if (dataValidate(fmt, data))
      {

          yr = extractValidateYear(fmt, data);
          mn = extractValidateMonth(fmt, data);
          if (yr > 0 && mn > 0)
          {
              dy = extractValidateDay(fmt, data, mn, yr);
              if (dy > 0)
                 return 1;
              else
                 return 0;
          }
          else
            return 0;
      }
      return 0;
}

// Extracts the day from given date information and also checks its validity with respect to given month and year
int Validator::extractValidateDay(char *fmt, char *data, int mn, int yr)
{
      int dy = 0;
      int ps, pe;
      char dd[10];
      // Extract position of day from given date information
      ps = indexOf('D', fmt);
      pe = ps + 1;
      stringExtract(dd, data, ps, pe);
      dy = atoi(dd); // string to integer conversion
      if ((mn == 9 || mn == 4 || mn == 6 || mn == 11) && (dy >= 1 && dy <= 30))
      {
          return dy;
      }
      else if (mn == 2)
      {
          int leapyr = 0;
          if ((yr%100==0 && yr%4==0) || (yr%400==0))
             leapyr = 1;

          if ( leapyr == 1 && (dy >= 1 && dy <= 29))
               return dy;
          else if (leapyr == 0 && (dy >= 1 && dy <= 28))
               return dy;
          else
               return 0;
      }
      else if ((mn == 12 || mn == 10 || mn == 1 || mn == 3 || mn == 5 || mn == 7 || mn == 8) && (dy >= 1 && dy <= 31))
      {
               return dy;
      }
      else
               return 0;
}

// Extracts the month from given date information and checks its validity between range of 01 and 12
int Validator::extractValidateMonth(char *fmt, char *data)
{
      int mn = 0;
      int ps, pe;
      char mm[10];
      // Extract position of month string from format
      ps = indexOf('M', fmt);
      pe = ps + 1;
      stringExtract(mm, data, ps, pe);
      mn = atoi(mm); // string to integer conversion
      if (mn >= 1 && mn <= 12)
           return mn;
      else
           return 0;
}

// Extracts the year from given data information and checks its validity between range of 1900 and 2050
int Validator::extractValidateYear(char *fmt, char *data)
{
      int yr = 0;
      int ps, pe;
      char yy[10];
      // Extract position of yr string from format
      // Check if year has a YYYY format
      if (strstr(fmt,"YYYY")!=NULL)
      {
        ps =  indexOf('Y',fmt);
        pe =  ps + 3;
        stringExtract(yy, data, ps, pe);
        yr = atoi(yy);
        if (yr >= 1900 && yr <= 2050)
           return yr;
        else
           return 0;
      }
      else
      {
        ps =  indexOf('Y', fmt);
        pe =  ps + 1;
        stringExtract(yy, data, ps, pe);
        yr = atoi(yy);
        if (yr >= 00 && yr <= 20)
           return 2000+yr;
        else
           return 0;
      }
}

// Custom string function to find position of character c in string str
int Validator::indexOf(char c, char *str)
{
    int i = 0;
    while(*(str+i) != '\0')
    {
        if(*(str+i) == c)
           return i;
        i++;
    }
    return -1;
}

// Custom string function to find the character at position p in string str
char Validator::charAt(int p, char *str)
{
    int i = 0;
    while(*(str+i) != '\0')
    {
        if(p == i)
           return *(str+i);
        i++;
    }
    return '\0';
}

// Custom string function to extract a part of string
void Validator::stringExtract(char *dest, char *source, int sp, int ep)
{
    int s=0,i;
    for(i=sp ; i<=ep; i++)
    {
        *(dest+s) = *(source+i);
        s++;
    }
    *(dest+s) = '\0';
}

int Validator::extractDay(char *fmt, char *data)
{
      int dy = 0;
      int ps, pe;
      char dd[10];
      // Extract position of day from given date information
      ps = indexOf('D', fmt);
      pe = ps + 1;
      stringExtract(dd, data, ps, pe);
      dy = atoi(dd); // string to integer conversion
      return dy;
}

// Extracts the month from given date information and checks its validity between range of 01 and 12
int Validator::extractMonth(char *fmt, char *data)
{
      int mn = 0;
      int ps, pe;
      char mm[10];
      // Extract position of month string from format
      ps = indexOf('M', fmt);
      pe = ps + 1;
      stringExtract(mm, data, ps, pe);
      mn = atoi(mm); // string to integer conversion
      return mn;
}

// Extracts the year from given data information and checks its validity between range of 1900 and 2050
int Validator::extractYear(char *fmt, char *data)
{
      int yr = 0;
      int ps, pe;
      char yy[10];
      // Extract position of yr string from format
      // Check if year has a YYYY format
      if (strstr(fmt,"YYYY")!=NULL)
      {
        ps =  indexOf('Y',fmt);
        pe =  ps + 3;
        stringExtract(yy, data, ps, pe);
        yr = atoi(yy);
        return yr;
      }
      else
      {
        ps =  indexOf('Y', fmt);
        pe =  ps + 1;
        stringExtract(yy, data, ps, pe);
        yr = atoi(yy);
        return 2000+yr;
      }
}



#endif // VALIDATOR_H_INCLUDED
