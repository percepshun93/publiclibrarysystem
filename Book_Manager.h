#ifndef BOOK_MANAGER_H_INCLUDED
#define BOOK_MANAGER_H_INCLUDED
// Coded by Santanu Karmakar
// Book Manager is the class that contains the book library
// Book manager has all the functions that manipulates the book information
// Book manager also contains the functions for prining book related reports
class BookManager
{
   private:
    int nextBookId;
    int nextBookIndex;

   public:
    Book BookList[1000];
    void checkBookEnv(); // Check the environment for books
    void createBlankFile(); // Create a blank file template
    void readBookInfo(); // Read all book information from file to BookList
    void writeBookInfo();// Write all book information into file from BookList
    void addBookInfo(); // Get details from user and store append into array
    int findBookInfo(int book_id); // Finds book information by its id
    void deleteBookInfo(); // Delete book information from array after getting book id from user
    void printBookList(); // Print list of books monthwise
    void printBookListByCategory();
};

// This function checks if the text file containing the book records exits or not
// if it does not then it creates a blank text file for books
void BookManager::checkBookEnv()
{
    FILE *fp = fopen ("AllBooks.txt", "r");
    if (fp!=NULL)
        fclose (fp);
    else
        createBlankFile();
}

// The function that creates a blank text file
void BookManager::createBlankFile()
{
    FILE *fp;
    fp = fopen("AllBooks.txt", "w");
    fclose(fp);
}

// This function will read all the records and store them into an array at the begining
void BookManager::readBookInfo() //Read all book information from file to BookList
{
    struct bookStr bs;
    char buff[150];
    char fld[50];
    int i = 0;
    nextBookId = 10000;

    FILE *fp;
    fp = fopen("AllBooks.txt", "r" );
    while (fgets(buff, 113, fp)!=NULL)
    {
            // Read the actual fields from buffer
            Validator::stringExtract(fld, buff, 0, 9);
            bs.book_id = atoi(fld);
            // Find the max Book ID and assign it nextBookID
            if (nextBookId < bs.book_id)
                nextBookId = bs.book_id;
            //---------------------------
            Validator::stringExtract(fld, buff, 10, 49);
            strcpy(bs.book_name,fld);
            Validator::stringExtract(fld, buff, 50, 50);
            strcpy(bs.book_category,fld);
            Validator::stringExtract(fld, buff, 51, 52);
            bs.book_aq_dt.day = atoi(fld);
            Validator::stringExtract(fld, buff, 53, 54);
            bs.book_aq_dt.month = atoi(fld);
            Validator::stringExtract(fld, buff, 55, 58);
            bs.book_aq_dt.year = atoi(fld);
            Validator::stringExtract(fld, buff, 59, 59);
            strcpy(bs.book_status,fld);
            Validator::stringExtract(fld, buff, 60, 99);
            strcpy(bs.book_author_name, fld);
            Validator::stringExtract(fld, buff, 100, 111);
            strcpy(bs.book_ISBN, fld);


             // Assign them to the BookList array in the current array position
            BookList[i].set_book_id(bs.book_id);
            //cout<< BookList[i].get_book_id()<<endl;
            BookList[i].set_book_name(bs.book_name);
            //cout<< BookList[i].get_book_name()<<endl;
            BookList[i].set_book_category(bs.book_category);
            //cout<< BookList[i].get_book_category()<<endl;
            BookList[i].set_book_aq_dt(bs.book_aq_dt.day, bs.book_aq_dt.month, bs.book_aq_dt.year);
            //cout<<BookList[i].get_book_aq_day()<<BookList[i].get_book_aq_month()<<BookList[i].get_book_aq_year()<<endl;
            BookList[i].set_book_status(bs.book_status);
            //cout<<BookList[i].get_book_status()<<endl;
            BookList[i].set_book_author_name(bs.book_author_name);
            //cout<<BookList[i].get_book_author_name()<<endl;
            BookList[i].set_book_ISBN(bs.book_ISBN);
            //cout<<BookList[i].get_book_ISBN()<<endl;
            i++; // set the index to next array position
    }
    nextBookId = nextBookId+1;
    nextBookIndex = i;
    cout << "Next Book index : " << nextBookIndex << endl;
    cout << "Next Book Id : " << nextBookId<<endl;
}

// This function gets information from user and creates a record to add into the array
void BookManager::addBookInfo()
{
    //
    int i;
    struct bookStr bs;
    char cbuff[100];
    cin.getline (cbuff,sizeof(cbuff)); // dummy getline command to get it work

    // Get book name from user
    cout << "Enter book name : " ;
    cin.getline (bs.book_name,sizeof(bs.book_name));
    while (!Validator::dataValidate((char *) "*", bs.book_name))
    {
       cout << "Invalid book name .. must not be blank" <<endl;
       cout << "Enter book name : " ;
       cin.getline (bs.book_name,sizeof(bs.book_name));
    }

   // Get book category from user
    cout << "Valid Categories .. (F)iction/(T)extBooks/(E)ssays/(M)agazines/(A)utobiography/(S)ports\n";
    cout << "Enter book category : " ; // (F)iction/(T)extBooks/(E)ssays/(M)agazines/(A)utobiography/(S)ports
    cin.getline (cbuff,sizeof(cbuff));
    while (!Validator::dataValidate((char *) "F", cbuff)&&!Validator::dataValidate((char *) "T", cbuff)&&!Validator::dataValidate((char *) "E", cbuff)&&!Validator::dataValidate((char *) "M", cbuff)&&!Validator::dataValidate((char *) "A", cbuff)&&!Validator::dataValidate((char *) "F", cbuff))
    {
       cout << "Invalid book category .." <<endl;
       cout << "Valid Categories .. (F)iction/(T)extBooks/(E)ssays/(M)agazines/(A)utobiography/(S)ports\n";
       cout << "Enter book category : " ;
       cin.getline (cbuff,sizeof(cbuff));
    }
    strcpy(bs.book_category, cbuff);

   // Get book aquire date from user
   cout << "Enter book aquire date in DD-MM-YYYY format : ";
   cin >> cbuff;
   while (!Validator::dateValidate((char *) "DD-MM-YYYY", cbuff))
   {
       cout << "Inavalid date entry ..\n" << endl;
       cout << "Enter book aquire date in DD-MM-YYYY format : ";
       scanf("%s", cbuff);
   }
   bs.book_aq_dt.day = Validator::extractDay((char *) "DD-MM-YYYY", cbuff);
   bs.book_aq_dt.month = Validator::extractMonth((char *) "DD-MM-YYYY", cbuff);
   bs.book_aq_dt.year = Validator::extractYear((char *) "DD-MM-YYYY", cbuff);
   cin.getline (cbuff,sizeof(cbuff)); // dummy getline command to get it work


    // Get book author name from user
    cout << "Enter author name : " ;
    //cin.getline (bs.book_author_name,sizeof(bs.book_author_name));
    cin.getline (cbuff,sizeof(cbuff));
    while (!Validator::dataValidate((char *) "a*", cbuff))
    {
       cout << "Invalid author name .. must not be blank\n" <<endl;
       cout << "Enter author name : " ;
       cin.getline (cbuff,sizeof(cbuff));
    }
     strcpy(bs.book_author_name,cbuff);


    // Get book ISBN from user
    cout << "Enter ISBN : " ;
    cin.getline ( bs.book_ISBN,sizeof(bs.book_ISBN));
    while (!Validator::dataValidate((char *) "*", bs.book_ISBN))
    {
       cout << "Invalid ISBN .. must not be blank" <<endl;
       cout << "Enter ISBN : " ;
       cin.getline ( bs.book_ISBN,sizeof(bs.book_ISBN));
    }


    strcpy(bs.book_status,"A");


    i = nextBookIndex;
    BookList[i].set_book_id(nextBookId);
    BookList[i].set_book_name(bs.book_name);
    BookList[i].set_book_category(bs.book_category);
    BookList[i].set_book_aq_dt(bs.book_aq_dt.day, bs.book_aq_dt.month, bs.book_aq_dt.year);
    BookList[i].set_book_status(bs.book_status);
    BookList[i].set_book_author_name(bs.book_author_name);
    BookList[i].set_book_ISBN(bs.book_ISBN);
    // Increment the next positions
    nextBookId = nextBookId+1;
    nextBookIndex = nextBookIndex + 1;
}

// This function dumps the all the records in array into the text file at the end of all book related operations
void BookManager::writeBookInfo()// Write all book information into file from BookList
{

    FILE *fp;
    fp = fopen("AllBooks.txt", "w" );
    int i;
    for(i = 0; i < nextBookIndex; i++)
    {
        fprintf(fp, "%10d", BookList[i].get_book_id());
        fprintf(fp, "%40s", BookList[i].get_book_name());
        fprintf(fp, "%1s", BookList[i].get_book_category());
        fprintf(fp, "%2d", BookList[i].get_book_aq_day());
        fprintf(fp, "%2d", BookList[i].get_book_aq_month());
        fprintf(fp, "%4d", BookList[i].get_book_aq_year());
        fprintf(fp, "%1s", BookList[i].get_book_status());
        fprintf(fp, "%40s", BookList[i].get_book_author_name());
        fprintf(fp, "%12s", BookList[i].get_book_ISBN());

    }
    fclose(fp);
}

int BookManager::findBookInfo(int book_id)
{   int  i, id_fn=-1;
    for(i=0; i<nextBookIndex; i++)
    {
        if(BookList[i].get_book_id()==book_id)
        {
           id_fn = i;
           break;
        }
    }
    if (id_fn>=0)
    {
            cout << "Book Name : " << BookList[id_fn].get_book_name()<<endl;
            return 1;
    }
    else
            return 0;
}

// This function will delete a book record from array based on given book id
void BookManager::deleteBookInfo()
{   int book_id, i, id_del=-1;
    cout << "Enter book id to delete :";
    cin >> book_id;
    for(i=0; i<nextBookIndex; i++)
    {
        if(BookList[i].get_book_id()==book_id)
        {
           id_del = i;
           break;
        }
    }
    if (id_del>=0)
    {
        for (i=id_del; i<nextBookIndex-1; i++)
        {
            BookList[i] = BookList[i+1];
        }
        BookList[nextBookIndex-1].set_book_id(0);
    }
    nextBookIndex = nextBookIndex-1;
}

// This function will print a report based on given month and year.
// The report is not properly aligned.
// I leave that option to the students if they wish.
void BookManager::printBookList()
{
    int mnt, year, i;

    cout << "Enter month (1-12) :";
    cin >> mnt;
    cout << "Enter year (yyyy) :";
    cin >> year;
    printf ("Month :  %d \n", mnt);
    printf ("Year  :  %d \n", year);
    printf ("      Book Id             Name                                                                            Author                      ISBN      Date\n");
    printf ("------------------------------------------------------------------------\n");
    for(i=0; i<nextBookIndex; i++)
    {
        if(BookList[i].get_book_aq_month()==mnt && BookList[i].get_book_aq_year() == year )
        {
           printf("%10d %40s                     %40s                  %12s  %2d-%2d-%4d\n",BookList[i].get_book_id(),BookList[i].get_book_name(),BookList[i].get_book_author_name(), BookList[i].get_book_ISBN(), BookList[i].get_book_aq_day(), BookList[i].get_book_aq_month(), BookList[i].get_book_aq_year());
        }
    }

}

// This function will print a report based on given category.
// The report is not properly aligned.
// I leave that option to the students if they wish.
void BookManager::printBookListByCategory()
{
    int i;
    char sbook_category[2], lbook_category[2];
    string category_name;
    cout << "Enter the category (F/T/E/M/A/S) : ";
    cin >> sbook_category;
    switch(sbook_category[0])
    {
    case 'F' :
        category_name = "Fiction";
        break;
    case 'T' :
        category_name = "Text Book";
        break;
    case 'E' :
        category_name = "Essay";
        break;
    case 'M' :
        category_name = "Magazine";
        break;
    case 'A' :
        category_name = "Autobiography/Biography";
        break;
    case 'S' :
        category_name = "Sports";
        break;
    }

    cout << "Book Category : "<< category_name << endl;

    printf ("      Book Id             Name                                                                            Author                      ISBN      Date\n");
    printf ("------------------------------------------------------------------------\n");
    for(i=0; i<nextBookIndex; i++)
    {
        strcpy(lbook_category, BookList[i].get_book_category());
        if(lbook_category[0]==sbook_category[0])
        {
           printf("%10d %40s  %40s  %12s  %2d-%2d-%4d\n",BookList[i].get_book_id(),BookList[i].get_book_name(),BookList[i].get_book_author_name(), BookList[i].get_book_ISBN(), BookList[i].get_book_aq_day(), BookList[i].get_book_aq_month(), BookList[i].get_book_aq_year());
        }
    }
}

#endif // BOOK_MANAGER_H_INCLUDED
