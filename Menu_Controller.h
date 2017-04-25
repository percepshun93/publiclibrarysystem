#ifndef MENU_CONTROLLER_H_INCLUDED
#define MENU_CONTROLLER_H_INCLUDED
// Coded by : Santanu Karmakar
// This class provides the complete menu system for navigating into the system

class MenuControl
{
  public:
    void showMain();
    void bookMenu();
    void subsciberMenu();
    void transactorMenu();
    void reportMenu();
};
    // This function is for main menu
    void MenuControl::showMain()
    {
        int ch;
        cout << "         Main Menu" << endl;
        cout << "         ---------" << endl << endl;
        cout << "   1)  Book Menu" << endl;
        cout << "   2)  Subscriber Manu  "<< endl;
        cout << "   3)  Transaction Menu "<< endl;
        cout << "   4)  Reports          "<< endl;
        cout << "   5)  exit             "<<endl<<endl;
        cout << "   Enter your choice :";
        cin >> ch;

        switch(ch)
        {
        case 1:
            bookMenu();
            break;
        case 2:
            subsciberMenu();
            break;
        case 3:
            transactorMenu();
            break;
        case 4:
            reportMenu();
            break;
        case 5:
            break;
        default :
            cout << "Invalid choice .. " << endl;
      }
    }
    // This function is for book menu
    void MenuControl::bookMenu()
    {
        int ch = 0;
        BookManager bm;
        bm.checkBookEnv();
        bm.readBookInfo();
        while (ch!=4)
        {
            cout << endl<<endl;
            cout << "         Book Menu" << endl;
            cout << "         ---------" << endl << endl;
            cout << "   1)  New Book" << endl;
            cout << "   2)  Remove Book  "<< endl;
            cout << "   3)  Print List "<< endl;
            cout << "   4)  Exit         "<< endl<<endl;;
            cout << "   Enter your choice :";
            cin >> ch;

           switch(ch)
            {
            case 1:
                bm.addBookInfo();
                break;
            case 2:
                bm.deleteBookInfo();
                break;
            case 3:
                bm.printBookList();
                break;
            case 4:
                break;
            default :
                cout << "Invalid choice .. " << endl;
            }
         }
         bm.writeBookInfo();

    }
    // This is the subscriber's menu
    void MenuControl::subsciberMenu()
    {
        int ch = 0;
        SubscriberManager sm;
        sm.checkSubscriberEnv();
        sm.readSubscriberInfo();
        while (ch!=4)
        {
            cout << endl<<endl;
            cout << "         Subscriber Menu" << endl;
            cout << "         ----------------" << endl << endl;
            cout << "   1)  New Subscriber" << endl;
            cout << "   2)  Remove Subscriber  "<< endl;
            cout << "   3)  Print Subscriber Profile "<< endl;
            cout << "   4)  Exit         "<< endl<<endl;;
            cout << "   Enter your choice :";
            cin >> ch;

           switch(ch)
            {
            case 1:
                sm.addSubscriberInfo();
                break;
            case 2:
                sm.deleteSubscriberInfo();
                break;
            case 3:
                sm.printSubscriberProfile();
                break;
            case 4:
                break;
            default :
                cout << "Invalid choice .. " << endl;
            }
         }
         sm.writeSubscriberInfo();

    }
    // This provides the transactor menu options for borrowing and returning books
    void MenuControl::transactorMenu()
    {
       int ch = 0;
        TransactorManager tm;
        tm.checkTrEnv();
        tm.readTrInfo();
        while (ch!=5)
        {
            cout << endl<<endl;
            cout << "         Transactor Menu" << endl;
            cout << "         ---------------" << endl << endl;
            cout << "   1)  Borrow Book" << endl;
            cout << "   2)  Return Book  "<< endl;
            cout << "   3)  Remove Transaction  "<< endl;
            cout << "   4)  Print Aging List "<< endl;
            cout << "   5)  Exit         "<< endl<<endl;;
            cout << "   Enter your choice :";
            cin >> ch;

           switch(ch)
            {
            case 1:
                tm.BrTrInfo();
                break;
            case 2:
                tm.RnTrInfo();
                break;
            case 3:
                tm.deleteTrInfo();
                break;
            case 4:
                tm.printAgingList();
                break;
            case 5:
                break;
            default :
                cout << "Invalid choice .. " << endl;
            }
         }
         tm.writeTrInfo();
    }
    // Menu for some additional reports
    void MenuControl::reportMenu()
    {
        int ch = 0;
        BookManager bm;
        bm.checkBookEnv();
        bm.readBookInfo();
        SubscriberManager sm;
        sm.checkSubscriberEnv();
        sm.readSubscriberInfo();
        TransactorManager tm;
        tm.checkTrEnv();
        tm.readTrInfo();
        while (ch!=4)
        {
            cout << endl<<endl;
            cout << "       Report Menu" << endl;
            cout << "       -----------" << endl << endl;
            cout << "   1)  Aging and Fine" << endl;
            cout << "   2)  Subscriber List  "<< endl;
            cout << "   3)  Books by category "<< endl;
            cout << "   4)  Exit         "<< endl<<endl;;
            cout << "   Enter your choice :";
            cin >> ch;

           switch(ch)
            {
            case 1:
                tm.printAgingFineList();
                break;
            case 2:
                sm.printSubscriberList();
                break;
            case 3:
                bm.printBookListByCategory();
                break;
            case 4:
                break;
            default :
                cout << "Invalid choice .. " << endl;
            }
         }
    }

#endif // MENU_CONTROLLER_H_INCLUDED
