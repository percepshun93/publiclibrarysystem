#ifndef SUBSCRIBER_MANAGER_H_INCLUDED
#define SUBSCRIBER_MANAGER_H_INCLUDED
// Coded by Santanu Karmakar
// This class is for maintaining subscriber's list as an array which is eventually stored in the file.
class SubscriberManager
{
   private:
    int nextSubscriberId;
    int nextSubscriberIndex;


   public:
    Subscriber SubscriberList[1000];
    void checkSubscriberEnv(); // Check the environment for Subscriber
    void createBlankFile(); // Create a blank file template
    void readSubscriberInfo(); // Read all Subscriber information from file to BookList
    void writeSubscriberInfo();// Write all Subscriber information into file from BookList
    void addSubscriberInfo(); // Get Subscriber details from user and store append into array
    int findSubscriberInfo(int subscriber_id); // Finds a Subscriber by its id and prints the name
    void deleteSubscriberInfo(); // Delete Subscriber information from array after getting book id from user
    int incSubscriberBorrowCount(int subscriber_id);
    int decSubscriberBorrowCount(int subscriber_id);
    int getSubscriberBorrowCount(int subscriber_id);
    void printSubscriberList(); // Print list of Subscriber monthwise
    void printSubscriberProfile(); //Print subscriber profile

};

// Tjis function will check the subsciber's file and if not present it will create a blank file.
void SubscriberManager::checkSubscriberEnv()
{
    FILE *fp = fopen ("AllSubscribers.txt", "r");
    if (fp!=NULL)
        fclose (fp);
    else
        createBlankFile();
}

// For creating a blank subscriber's text file
void SubscriberManager::createBlankFile()
{
    FILE *fp;
    fp = fopen("AllSubscribers.txt", "w");
    fclose(fp);
}

// This function will read the entire ste of information from the file into an array
void SubscriberManager::readSubscriberInfo() //Read all subscriber information from file to BookList
{
    struct subscriberStr ss;
    char buff[150];
    char fld[50];
    int i = 0;
    nextSubscriberId = 10000;

    FILE *fp;
    fp = fopen("AllSubscribers.txt", "r" );
    while (fgets(buff, 113, fp)!=NULL)
    {
            // Read the actual fields from buffer
            Validator::stringExtract(fld, buff, 0, 9);
            ss.subscriber_id = atoi(fld);
            // Find the max Subscriber ID and assign it nextSubscriber ID
            if (nextSubscriberId < ss.subscriber_id)
                nextSubscriberId = ss.subscriber_id;
            //---------------------------
            Validator::stringExtract(fld, buff, 10, 49);
            strcpy(ss.subscriber_name,fld);
            Validator::stringExtract(fld, buff, 50, 51);
            ss.subscriber_joining_dt.day = atoi(fld);
            Validator::stringExtract(fld, buff, 52, 53);
            ss.subscriber_joining_dt.month = atoi(fld);
            Validator::stringExtract(fld, buff, 54, 57);
            ss.subscriber_joining_dt.year = atoi(fld);
            Validator::stringExtract(fld, buff, 58, 59);
            ss.subscriber_num_borrowed = atoi(fld);
            Validator::stringExtract(fld, buff, 60, 99);
            strcpy(ss.subscriber_address, fld);
            Validator::stringExtract(fld, buff, 100, 111);
            strcpy(ss.subscriber_id_proof, fld);


             // Assign them to the BookList array in the current array position
            SubscriberList[i].set_subscriber_id(ss.subscriber_id);
            SubscriberList[i].set_subscriber_name(ss.subscriber_name);
            SubscriberList[i].set_subscriber_joining_dt(ss.subscriber_joining_dt.day, ss.subscriber_joining_dt.month, ss.subscriber_joining_dt.year);
            SubscriberList[i].set_subscriber_num_borrowed(ss.subscriber_num_borrowed);
            SubscriberList[i].set_subscriber_address(ss.subscriber_address);
            SubscriberList[i].set_subscriber_id_proof(ss.subscriber_id_proof);
            i++; // set the index to next array position
    }
    nextSubscriberId = ss.subscriber_id+1;
    nextSubscriberIndex = i;
    cout << "Next Subscriber index : " << nextSubscriberIndex << endl;
    cout << "Next Subscriber Id : " << nextSubscriberId<<endl;
}

// This function will add a subscriber's information into the array
// User will provide the information about the subscriber
void SubscriberManager::addSubscriberInfo()
{
    //
    int i;
    struct subscriberStr ss;
    char cbuff[100];
    cin.getline (cbuff,sizeof(cbuff)); // dummy getline command to get it work

    // Get subscriber name from user
    cout << "Enter Subscriber name : " ;
    cin.getline (ss.subscriber_name,sizeof(ss.subscriber_name));
    while (!Validator::dataValidate((char *) "*", ss.subscriber_name))
    {
       cout << "Invalid subscriber name .. must not be blank" <<endl;
       cout << "Enter Subscriber name : " ;
       cin.getline (ss.subscriber_name,sizeof(ss.subscriber_name));
    }


   // Get joining date from user
   cout << "Enter joining date in DD-MM-YYYY format : ";
   cin >> cbuff;
   while (!Validator::dateValidate((char *) "DD-MM-YYYY", cbuff))
   {
       cout << "Inavalid date entry ..\n" << endl;
       cout << "Enter book aquire date in DD-MM-YYYY format : ";
       scanf("%s", cbuff);
   }
   ss.subscriber_joining_dt.day = Validator::extractDay((char *) "DD-MM-YYYY", cbuff);
   ss.subscriber_joining_dt.month = Validator::extractMonth((char *) "DD-MM-YYYY", cbuff);
   ss.subscriber_joining_dt.year = Validator::extractYear((char *) "DD-MM-YYYY", cbuff);
   cin.getline (cbuff,sizeof(cbuff)); // dummy getline command to get it work


    // Get address from user
    cout << "Enter address : " ;
    cin.getline (cbuff,sizeof(cbuff));
    while (!Validator::dataValidate((char *) "*", cbuff))
    {
       cout << "Invalid address .. must not be blank\n" <<endl;
       cout << "Enter address : " ;
       cin.getline (cbuff,sizeof(cbuff));
    }
     strcpy(ss.subscriber_address,cbuff);


    // Get Id proof of the subscriber from user
    cout << "Enter Id proof : " ;
    cin.getline ( ss.subscriber_id_proof,sizeof(ss.subscriber_id_proof));
    while (!Validator::dataValidate((char *) "*", ss.subscriber_id_proof))
    {
       cout << "Invalid Id proof .. must not be blank" <<endl;
       cout << "Enter Id proof : " ;
       cin.getline ( ss.subscriber_id_proof,sizeof(ss.subscriber_id_proof));
    }

    ss.subscriber_num_borrowed = 0;

    i = nextSubscriberIndex;
    SubscriberList[i].set_subscriber_id(nextSubscriberId);
    SubscriberList[i].set_subscriber_name(ss.subscriber_name);
    SubscriberList[i].set_subscriber_joining_dt(ss.subscriber_joining_dt.day, ss.subscriber_joining_dt.month, ss.subscriber_joining_dt.year);
    SubscriberList[i].set_subscriber_num_borrowed(ss.subscriber_num_borrowed);
    SubscriberList[i].set_subscriber_address(ss.subscriber_address);
    SubscriberList[i].set_subscriber_id_proof(ss.subscriber_id_proof);
    // Increment the next positions
    nextSubscriberId = nextSubscriberId+1;
    nextSubscriberIndex = nextSubscriberIndex + 1;
}

// This function will dump the entire set of records from array to the file.
void SubscriberManager::writeSubscriberInfo()// Write all book information into file from BookList
{
    FILE *fp;
    fp = fopen("AllSubscribers.txt", "w" );
    int i;
    for(i = 0; i < nextSubscriberIndex; i++)
    {
        fprintf(fp, "%10d", SubscriberList[i].get_subscriber_id());
        fprintf(fp, "%40s", SubscriberList[i].get_subscriber_name());
        fprintf(fp, "%2d", SubscriberList[i].get_subscriber_joining_day());
        fprintf(fp, "%2d", SubscriberList[i].get_subscriber_joining_month());
        fprintf(fp, "%4d", SubscriberList[i].get_subscriber_joining_year());
        fprintf(fp, "%2d", SubscriberList[i].get_subscriber_num_borrowed());
        fprintf(fp, "%40s", SubscriberList[i].get_subscriber_address());
        fprintf(fp, "%12s", SubscriberList[i].get_subscriber_id_proof());

    }
    fclose(fp);
}

// This function will get a subscribers borrow count for books .. ist is often used for checking if the subscriber has crossed the limit of 3 books
int SubscriberManager::getSubscriberBorrowCount(int subscriber_id)
{
   int  i, id_fn=-1;

    for(i=0; i<nextSubscriberIndex; i++)
    {
        if(SubscriberList[i].get_subscriber_id()==subscriber_id)
        {
           id_fn = i;
           break;
        }
    }
    if (id_fn>=0)
    {
            return SubscriberList[i].get_subscriber_num_borrowed();
    }
    else
            return 0;
}

// Function that increases the Subscriber's borrow count by 1
int SubscriberManager::incSubscriberBorrowCount(int subscriber_id)
{
   int  i, id_fn=-1;

    for(i=0; i<nextSubscriberIndex; i++)
    {
        if(SubscriberList[i].get_subscriber_id()==subscriber_id)
        {
           id_fn = i;
           break;
        }
    }
    if (id_fn>=0)
    {
             SubscriberList[i].set_subscriber_num_borrowed(SubscriberList[i].get_subscriber_num_borrowed()+1);
            return 1;
    }
    else
            return 0;
}

// Function that decreases the Subscriber's borrow count by 1
int SubscriberManager::decSubscriberBorrowCount(int subscriber_id)
{
   int  i, id_fn=-1;

    for(i=0; i<nextSubscriberIndex; i++)
    {
        if(SubscriberList[i].get_subscriber_id()==subscriber_id)
        {
           id_fn = i;
           break;
        }
    }
    if (id_fn>=0)
    {
             SubscriberList[i].set_subscriber_num_borrowed(SubscriberList[i].get_subscriber_num_borrowed()-1);
            return 1;
    }
    else
            return 0;
}

// This is for searching the subscrbers information based on subscriber id
int SubscriberManager::findSubscriberInfo(int subscriber_id)
{
    int  i, id_fn=-1;

    for(i=0; i<nextSubscriberIndex; i++)
    {
        if(SubscriberList[i].get_subscriber_id()==subscriber_id)
        {
           id_fn = i;
           break;
        }
    }
    if (id_fn>=0)
    {
            return id_fn;
    }
    else
            return 0;
}

// Delete subscriber record from array
void SubscriberManager::deleteSubscriberInfo()
{   int subscriber_id, i, id_del=0;
    cout << "Enter book id to delete :";
    cin >> subscriber_id;
    for(i=0; i<nextSubscriberIndex; i++)
    {
        if(SubscriberList[i].get_subscriber_id()==subscriber_id)
        {
           id_del = i;
           break;
        }
    }
    if (id_del>0)
    {
        for (i=id_del; i<nextSubscriberIndex-1; i++)
        {
            SubscriberList[i] = SubscriberList[i+1];
        }
        SubscriberList[nextSubscriberIndex-1].set_subscriber_id(0);
    }
    nextSubscriberIndex = nextSubscriberIndex-1;
}

// Report for printing subscriber's list based on month and year of joining
void SubscriberManager::printSubscriberList()
{
    int mnt, year, i;

    cout << "Enter month (1-12) :";
    cin >> mnt;
    cout << "Enter year (yyyy) :";
    cin >> year;
    printf ("Month :  %d \n", mnt);
    printf ("Year  :  %d \n", year);
    printf ("      Subscriber Id             Name                                                    Date\n");
    printf ("------------------------------------------------------------------------\n");
    for(i=0; i<nextSubscriberIndex; i++)
    {
        if(SubscriberList[i].get_subscriber_joining_month()==mnt && SubscriberList[i].get_subscriber_joining_year() == year )
        {
           printf("%10d %40s                     %2d-%2d-%4d\n",SubscriberList[i].get_subscriber_id(),SubscriberList[i].get_subscriber_name(),  SubscriberList[i].get_subscriber_joining_day(), SubscriberList[i].get_subscriber_joining_month(), SubscriberList[i].get_subscriber_joining_year());
        }
    }

}

// This function will print subscriber profile information for a given subscriber id
void SubscriberManager::printSubscriberProfile()
{
    int subscriber_id, i;

    cout << "Enter Subscriber Id:";
    cin >> subscriber_id;
    for(i=0; i<nextSubscriberIndex; i++)
    {
        if(SubscriberList[i].get_subscriber_id() == subscriber_id )
        {
           printf ("Subscriber Id : %10d\n", SubscriberList[i].get_subscriber_id()) ;
           printf ("Name : %40s\n", SubscriberList[i].get_subscriber_name());
           printf ("Address : %40s\n", SubscriberList[i].get_subscriber_address());
           printf ("ID Proof : %12s\n", SubscriberList[i].get_subscriber_id_proof());
        }
    }

}

#endif // SUBSCRIBER_MANAGER_H_INCLUDED
