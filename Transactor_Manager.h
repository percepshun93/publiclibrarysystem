#ifndef TRANSACTOR_MANAGER_H_INCLUDED
#define TRANSACTOR_MANAGER_H_INCLUDED
// Coded by Santanu Karmakar
// Class for managing Transaction list in for of array as well as to store them in a text file
class TransactorManager
{
   private:
    BookManager bm;
    SubscriberManager sm;
    int nextTrId;
    int nextTrIndex;

   public:
    Transactor TrList[1000];
    void checkTrEnv(); // Check the environment for Transactions
    void createBlankFile(); // Create a blank file template
    void readTrInfo(); // Read all Transaction information from file to TransactionList
    void writeTrInfo();// Write all Transaction information into file from TransactionList
    void BrTrInfo(); // Get details about borrowing from user and store append into array
    void RnTrInfo(); // Get details of return from  user and store append into array
    void deleteTrInfo(); // Delete book information from array after getting book id from user
    void printAgingList(); // Print aging report month wise
    void printAgingFineList(); // Print aging report with fine month wise
};

// Checks the existance of transaction text file if not then it creates
void TransactorManager::checkTrEnv()
{
    FILE *fp = fopen ("AllTrs.txt", "r");
    if (fp!=NULL)
        fclose (fp);
    else
        createBlankFile();
}

// Creates a blank transaction file
void TransactorManager::createBlankFile()
{
    FILE *fp;
    fp = fopen("AllTrs.txt", "w");
    fclose(fp);
}

//Read all Transaction information from file to TransactionList Array
void TransactorManager::readTrInfo()
{
    struct trStr ts;
    char buff[150];
    char fld[50];
    int i = 0;
    nextTrId = 10000;

    FILE *fp;
    fp = fopen("AllTrs.txt", "r" );
    while (fgets(buff, 47, fp)!=NULL)
    {
            // Read the actual fields from buffer
            Validator::stringExtract(fld, buff, 0, 9);
            ts.transactor_id = atoi(fld);
            // Find the max Transactor ID and assign it nextTrId
            if (nextTrId < ts.transactor_id)
                nextTrId = ts.transactor_id;
            //--------------------------------
            Validator::stringExtract(fld, buff, 10, 19);
            ts.book_id = atoi(fld);
            Validator::stringExtract(fld, buff, 20, 29);
            ts.subscriber_id = atoi(fld);
            Validator::stringExtract(fld, buff, 30, 31);
            ts.borrow_dt.day = atoi(fld);
            Validator::stringExtract(fld, buff, 32, 33);
            ts.borrow_dt.month = atoi(fld);
            Validator::stringExtract(fld, buff, 34, 37);
            ts.borrow_dt.year = atoi(fld);
            Validator::stringExtract(fld, buff, 38, 39);
            ts.return_dt.day = atoi(fld);
            Validator::stringExtract(fld, buff, 40, 41);
            ts.return_dt.month = atoi(fld);
            Validator::stringExtract(fld, buff, 42, 45);
            ts.return_dt.year = atoi(fld);



             // Assign them to the BookList array in the current array position
            TrList[i].set_transactor_id(ts.transactor_id);
            TrList[i].set_book_id(ts.book_id);
            TrList[i].set_subscriber_id(ts.subscriber_id);
            TrList[i].set_borrow_dt(ts.borrow_dt.day, ts.borrow_dt.month, ts.borrow_dt.year);
            TrList[i].set_return_dt(ts.return_dt.day, ts.return_dt.month, ts.return_dt.year);
            i++; // set the index to next array position
    }
    nextTrId = nextTrId+1;
    nextTrIndex = i;
    cout << "Next Transactor index : " << nextTrIndex << endl;
    cout << "Next Transactor Id : " << nextTrId<<endl;
}

// Accepts all Boorowing related data and stores it into array
void TransactorManager::BrTrInfo()
{
    //
    bm.checkBookEnv();
    bm.readBookInfo();
    sm.checkSubscriberEnv();
    sm.readSubscriberInfo();
    int i;
    struct trStr ts;
    char cbuff[100];
    cin.getline (cbuff,sizeof(cbuff)); // dummy getline command to get it work

    // Get book id from user
    cout << "Enter book id : " ;
    cin.getline (cbuff,sizeof(cbuff));
    while (!bm.findBookInfo(atoi(cbuff)))
    {
       cout << "Invalid book id .. must exist" <<endl;
       cout << "Enter book id : " ;
       cin.getline (cbuff,sizeof(cbuff));
    }
    ts.book_id = atoi(cbuff);

    // Get subscriber id from user
    cout << "Enter subscriber id : " ;
    cin.getline (cbuff,sizeof(cbuff));
    while (sm.findSubscriberInfo(atoi(cbuff)==0))
    {
       cout << "Invalid subscriber id .. must exist" <<endl;
       cout << "Enter subscriber id : " ;
       cin.getline (cbuff,sizeof(cbuff));
    }
    ts.subscriber_id = atoi(cbuff);
    cout <<"Subscriber Name : "<<  sm.SubscriberList[sm.findSubscriberInfo(ts.subscriber_id)].get_subscriber_name() << endl;

   if (sm.getSubscriberBorrowCount(ts.subscriber_id) >= 3)
   {
       cout << "Cannot borrow more than 3 books .. limit reached !!" << endl;
   }
   else
   {
      // Get book borrow date from user
      cout << "Enter book borrow date in DD-MM-YYYY format : ";
      cin >> cbuff;
      while (!Validator::dateValidate((char *) "DD-MM-YYYY", cbuff))
      {
               cout << "Inavalid date entry ..\n" << endl;
               cout << "Enter book aquire date in DD-MM-YYYY format : ";
               scanf("%s", cbuff);
      }
      ts.borrow_dt.day = Validator::extractDay((char *) "DD-MM-YYYY", cbuff);
      ts.borrow_dt.month = Validator::extractMonth((char *) "DD-MM-YYYY", cbuff);
      ts.borrow_dt.year = Validator::extractYear((char *) "DD-MM-YYYY", cbuff);

      cin.getline (cbuff,sizeof(cbuff)); // dummy getline command to get it work


      i = nextTrIndex;
      TrList[i].set_transactor_id(nextTrId);
      TrList[i].set_book_id(ts.book_id);
      TrList[i].set_subscriber_id(ts.subscriber_id);
      TrList[i].set_borrow_dt(ts.borrow_dt.day, ts.borrow_dt.month, ts.borrow_dt.year);
      TrList[i].set_return_dt(0, 0, 0);
      // Increment the next positions
      nextTrId = nextTrId+1;
      nextTrIndex = nextTrIndex + 1;
      // Increase subscriber's borrow count
      sm.incSubscriberBorrowCount(ts.subscriber_id);
      sm.writeSubscriberInfo();
   }
}

// Write all Transcation information into file from Transaction List
void TransactorManager::writeTrInfo()
{

    FILE *fp;
    fp = fopen("AllTrs.txt", "w" );
    int i;
    for(i = 0; i < nextTrIndex; i++)
    {
        fprintf(fp, "%10d", TrList[i].get_transactor_id());
        fprintf(fp, "%10d", TrList[i].get_book_id());
        fprintf(fp, "%10d", TrList[i].get_subscriber_id());
        fprintf(fp, "%2d", TrList[i].get_borrow_day());
        fprintf(fp, "%2d", TrList[i].get_borrow_month());
        fprintf(fp, "%4d", TrList[i].get_borrow_year());
        fprintf(fp, "%2d", TrList[i].get_return_day());
        fprintf(fp, "%2d", TrList[i].get_return_month());
        fprintf(fp, "%4d", TrList[i].get_return_year());

    }
    fclose(fp);
}

// Accepts return date information and updates a borrow transaction
void TransactorManager::RnTrInfo()
{
    bm.checkBookEnv();
    bm.readBookInfo();
    sm.checkSubscriberEnv();
    sm.readSubscriberInfo();
    int tr_id, i, id_ret=-1;
    char cbuff[100];
    struct date dt;
    cout << "Enter Transactor id to return book :";
    cin >> tr_id;
    for(i=0; i<nextTrIndex; i++)
    {
        if(TrList[i].get_transactor_id()==tr_id)
        {
           id_ret = i;
           break;
        }
    }
    if (id_ret>=0)
    {
          // Get the book return date
           cout << "Enter book return date in DD-MM-YYYY format : ";
           cin >> cbuff;
           while (!Validator::dateValidate((char *) "DD-MM-YYYY", cbuff))
           {
               cout << "Inavalid date entry ..\n" << endl;
               cout << "Enter return in DD-MM-YYYY format : ";
               scanf("%s", cbuff);
           }
           dt.day = Validator::extractDay((char *) "DD-MM-YYYY", cbuff);
           dt.month = Validator::extractMonth((char *) "DD-MM-YYYY", cbuff);
           dt.year = Validator::extractYear((char *) "DD-MM-YYYY", cbuff);

           TrList[i].set_return_dt(dt.day, dt.month, dt.year);
           if (sm.getSubscriberBorrowCount(TrList[i].get_subscriber_id()) > 0)
           {
             sm.decSubscriberBorrowCount(TrList[i].get_subscriber_id());
             sm.writeSubscriberInfo();
           }


    }
}

// Deletes a transaction
// Ideally it should not allow deleting until the borrowed book is returned. Currently this restrictio is not there
// Students are encouraged to build this restriction
void TransactorManager::deleteTrInfo()
{
    int tr_id, i, id_del=-1;
    cout << "Enter Transaction id to delete :";
    cin >> tr_id;
    for(i=0; i<nextTrIndex; i++)
    {
        if(TrList[i].get_transactor_id()==tr_id)
        {
           id_del = i;
           break;
        }
    }
    if (id_del>=0)
    {
        for (i=id_del; i<nextTrIndex-1; i++)
        {
           TrList[i] = TrList[i+1];
        }
        TrList[nextTrIndex-1].set_transactor_id(0);
    }
    nextTrIndex = nextTrIndex-1;
}

// Report for aging list
void TransactorManager::printAgingList()
{
    int mnt, year, i;

    cout << "Enter month (1-12) :";
    cin >> mnt;
    cout << "Enter year (yyyy) :";
    cin >> year;
    printf ("Month :  %d \n", mnt);
    printf ("Year  :  %d \n", year);
    printf ("Transactor Id    Book Id    Subscriber Id      Date Borrowed     Days retained\n");
    printf ("--------------------------------------------------------------------------------\n");
    for(i=0; i<nextTrIndex; i++)
    {
        if(TrList[i].get_borrow_month()==mnt && TrList[i].get_borrow_year() == year && TrList[i].get_return_day() == 0)
        {
           printf("%10d   %10d   %10d           %2d-%2d-%4d            %6.2f  \n",TrList[i].get_transactor_id(),TrList[i].get_book_id(), TrList[i].get_subscriber_id(), TrList[i].get_borrow_day(), TrList[i].get_borrow_month(), TrList[i].get_borrow_year(), todaydiff(TrList[i].get_borrow_dt()));
        }
    }

}

// Report for printing aging as well as fine
void TransactorManager::printAgingFineList()
{
    int mnt, year, i;

    cout << "Enter month (1-12) :";
    cin >> mnt;
    cout << "Enter year (yyyy) :";
    cin >> year;
    printf ("Month :  %d \n", mnt);
    printf ("Year  :  %d \n", year);
    printf ("Transactor Id    Subscriber Id      BookId     Days retained        Fine Payable\n");
    printf ("--------------------------------------------------------------------------------\n");
    for(i=0; i<nextTrIndex; i++)
    {
        if(TrList[i].get_borrow_month()==mnt && TrList[i].get_borrow_year() == year && TrList[i].get_return_day() == 0)
        {
           printf("%10d   %10d         %10d       %6.2f          %8.2f\n",TrList[i].get_transactor_id(), TrList[i].get_subscriber_id(), TrList[i].get_book_id(), todaydiff(TrList[i].get_borrow_dt()), (todaydiff(TrList[i].get_borrow_dt())-7)*2.0);
        }
    }

}

#endif // TRANSACTOR_MANAGER_H_INCLUDED
