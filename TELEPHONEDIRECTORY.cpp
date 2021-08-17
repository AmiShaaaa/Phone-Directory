#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <cwchar>
#include <windows.h>
#define _WIN32_WINNT 0x0601

using namespace std;

const int T_S = 200;

//Here we have made a class for the contacts we want to store as favourates of an account
class HashTableEntry {
   public:
      int k;
      string fname;
      string lname;
      string phoneNumber;
      
      //Parameterized Constructor to store the favourate contacts
      HashTableEntry(int k, string fname, string lname, string phoneNumber ) {
         this->k= k;
         this->fname = fname;
         this->lname = lname;
         this->phoneNumber = phoneNumber;
      }
};

//Hash table for hashing
class HashMapTable {

   private:
      HashTableEntry **t;

   public:
      HashMapTable() {
         t = new HashTableEntry * [T_S];
         for (int i = 0; i< T_S; i++) {
            t[i] = NULL;
         }
      }
       
      //here we are using Division method Hashing Function for the address to store 
      int HashFunc(int k) {
         return k % T_S;
      }

      void Insert(int k,string fname,string lname, string phoneNumber ) {
         int h = HashFunc(k);

         while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
         }

         if (t[h] != NULL)
            delete t[h];
         t[h] = new HashTableEntry(k, fname,lname,phoneNumber);
    //      cout<<fname<<endl;
    //     cout<<phoneNumber<<endl;
       }
  
        void Display() {
              cout<<"\nAll Favourite Contacts\n"<<endl;

   for (int i = 0; i < T_S; i++) {
            if (t[i] != NULL){
  cout<<"\nFirst Name:"<<t[i]->fname;
  cout<<"\nLast Name:"<<t[i]->lname;
  cout<<"\nPhone Number:"<<t[i]->phoneNumber;
  cout<<"\n";
            }
           
         }
       getch();
      }

       int getLength() {
           
           int len=0;
   for (int i = 0; i < T_S; i++) {
            if (t[i] != NULL)
             len++;
         }
         
         return len;
       
      }

      //Destructor
      ~HashMapTable() {
         for (int i = 0; i < T_S; i++) {
            if (t[i] != NULL)
               delete t[i];
               delete[] t;
         }
      }
};

//Here we have made class directory with all fields of contacts
class directory
{
    int phonenumber;
    char fname[50], lname[50];
       HashMapTable hash;
           

public:

    string getpword()
    {
        char ch;
        string pass = "";
        cout << "Please Enter the Password: ";
    oo:
        ch = getch();

        if (ch == 8)
        {
            goto oo;
        }

        while (ch != 13)
        {
            if (ch == 8)
            {
                if (pass.size() == 0)
                {
                    goto ps;
                }
                pass.erase(pass.size() - 1);
                cout << "\b \b";
            ps:
                goto pp;
            }
            pass.push_back(ch);
            cout << "*";
        pp:
            ch = getch();
        }
        return pass;
    }

    //class function to check if username already exists
    int check(string a)
    {
        int flag = 0;
        string b;
        fstream f1("Accounts.dir", ios::in);

        while (f1)
        {
            f1 >> b;
            if (b == a)
            {
                flag = 1;
                break;
            }
        }
        f1.close();

        if (flag == 1)
        {
            cout << "\nSorry! Username already exists. \nPlease try another: ";
            return 1;
        }
        return 0;
    }

    //class function to Log-In in DIRECTORY
    int LogIn()
    {
        string uname, password, struname, strpassword, line;
    ghi:
        fstream file1("Accounts.dir");
        int flag = 0, nextLoc = 0;

        system("cls");

        cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";
        cout << "Please Enter Your Username: ";
        cin >> struname;

        if (struname == "Admin")
        {
            return 2;
        }
        if (struname == "admin")
        {
            return 3;
        }

        while (!file1.eof())
        {
            getline(file1, line);

            nextLoc = line.find(" ");

            uname = line.substr(0, nextLoc);

            line = line.substr(nextLoc + 1, line.length());
            password = line;
            if (uname == struname)
            {
                flag = 1;
                break;
            }
        }

        file1.close();
        if (flag == 1)
        {

        def:
            strpassword = getpword();
            if (strpassword == password)
            {
                cout << "Log-In Succesful.";
            }
            else
            {
                cout << "\nWrong Password! ";
                goto def;
            }
        }

        else
        {
            cout << "\n\nYour Username was not Found in our Database.\nPlease Sign-Up or Enter correct Username";
            cout << "\nPress   <1> To Sign-Up    OR\n        <2> To Log-In Again\n";
            int choice1;
            cin >> choice1;

            if (choice1 == 1)
            {
                return 1;
            }
            else
            {
                goto ghi;
            }
        }
        return 0;
    }

    //class function to create new account and sign-up
    void SignUp()
    {
        string uname, struname, line, Password;
        int flag;

        system("cls");
        cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";

        fstream file1("Accounts.dir", ios::in | ios::out | ios::app);

        cout << "Please Enter an Username: ";
    cv:
        cin >> struname;
        flag = check(struname);

        if (flag == 1)
        {
            goto cv;
        }
        cout << "Please Enter a Password: ";
        cin >> Password;
        file1 << "\n"
              << struname << " " << Password;
        cout << "\n-------Account Created Successfully---------\n\n";

        int i, j;

        for (int a = 0; a < 5; a++)
        {
            if (a < 4)
            {
                for (int s = 0; s < 70; s++)
                {
                    cout << " ";
                }
                cout << "***\n";
            }
            else
            {
                for (int s = 0; s < 60; s++)
                {
                    cout << " ";
                }
                cout << "**************\n";
            }
        }
        for (i = 1; i <= 7; i++)
        {
            for (int s = 0; s < 60; s++)
            {
                cout << " ";
            }
            for (j = 1; j <= 14; j++)
            {
                if (i == 1 || i == 7 || j == 1 || j == 14)
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << " \n";
        }
        for (int a = 0; a < 5; a++)
        {
            for (int s = 0; s < 60; s++)
            {
                cout << " ";
            }
            cout << "**************\n";
        }

        cout<<"----------------------------------------------------------------"<<struname<<" WELCOME TO PHONE DIRECTORY----------------------------------------------------------------"<<endl;
        system("pause");
        return;
    }

    //class function to print all the contacts in the directory
    void printall()
    {
        string p;
        fstream f1("Directory.dir", ios::in);
        int i=0;

        while (f1)
        {
            f1 >> p;
            cout << p<<" ";
            i++;
            if(i%3==0){
                cout<<endl;
            }
        }
        f1.close();
        getch();
    }

    //class function to print all the accounts using the directory
    void printallc()
    {
        string p;
        fstream f1("Accounts.dir", ios::in);
        int i=0;

        while (f1)
        {
            f1 >> p;
            cout << p<<" ";
            i++;
            if(i%2==0){
            cout<<endl;
            }
        }
        cout<<endl;

        f1.close();
    }

    //class function to enter the new contacts in the directory
    void GetDetails()
    {
        string fname, lname, tnumber;

        char choice = 'y';
        char favChoice='n';
        fstream myfile("Directory.dir", ios::app);

        while (choice == 'Y' || choice == 'y')
        {
            system("cls");

            cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";

            cout << "Enter First Name : ";
            cin >> fname;

            myfile << fname << " ";

            cout << "\nEnter Last Name : ";
            cin >> lname;

            myfile << lname << " ";

            cout << "\nEnter Phone Number : ";
            cin >> tnumber;

            myfile << tnumber << "\n";

             cout<<"\nDo you want to add the contact to favourites?(y/n)\n";
            cin>>favChoice;
            //to store the contacts as favourites
            if(favChoice=='y')
            hash.Insert(hash.getLength()+1,fname,lname,tnumber);
            cout<<"Contact added to favourites"<<endl;
            cout<<"firstname: "<<fname<<endl;
            cout<<"Lastname: "<<lname<<endl;
            cout<<"Phone Number: "<<tnumber<<endl;

            cout << "\nDo you want to enter more? (y/n)";
            cin >> choice;

            cout << "\n";
        }

        myfile.close();
    }

    //class function to print favourites
    void ShowFavourites()
    {
        hash.Display();

    }

    //class function to search a contact and display its contact number
    void SearchAndDisplay()
    {
        string line;
        string fName, lName, tNumber, strFName, strLName;

        char choice;
        char favChoice='n';
        int flag = 0;
        int nextLoc = 0;

        system("color E");
        system("cls");
        do
        {
            cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";
            flag = 0;
            ifstream myfile("Directory.dir");
            if (myfile.is_open())
            {
                cout << endl
                     << "Enter First Name: ";
                cin >> strFName;

                cout << "Enter Last Name: ";
                cin >> strLName;

                while (!myfile.eof())
                {
                    getline(myfile, line);

                    nextLoc = line.find(" ");

                    fName = line.substr(0, nextLoc);

                    line = line.substr(nextLoc + 1, line.length());

                    nextLoc = line.find(" ");

                    lName = line.substr(0, nextLoc);

                    line = line.substr(nextLoc + 1, line.length());

                    tNumber = line;
                    if (fName == strFName && lName == strLName)
                    {
                        cout << "\nFound!!" << endl;
                        cout << endl
                             << "First Name: " << fName << "\n"
                             << "Last Name: " << lName << "\n"
                             << "PHONE Number: " << tNumber << endl;
                             cout<<"\nDo you want to add the contact to favourites?(y/n)\n";
                             cin>>favChoice;
                             if(favChoice=='y')
                             hash.Insert(hash.getLength()+1,fName,lName,tNumber);
                             cout<<"Contact added to favourites"<<endl;
                             cout<<"firstname: "<<fName<<endl;
                             cout<<"Lastname: "<<lName<<endl;
                             cout<<"Phone Number: "<<tNumber<<endl;
                             
                        flag = 1;
                        break;
                    }
                }
            }
            else
            {
                cout << "Unable to open file" << endl;
                exit(0);
            }

            if (flag == 0)
            {
                cout << "Not Found...Sorry." << endl;
            }

            cout << "\nDo you want to enter more?(y/n) ";
            cin >> choice;
            system("cls");

        } while (choice == 'y');
        return;
    }

    //class function to delete any contact from the directory
    void Delete()
    {
        system("cls");
        string line, fName, lName, strLName, strFName, tNumber;
        int nextLoc = 0, flag = 0;

        cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";
        cout << "Please enter the first name of record you want to delete: ";
        cin >> strFName;

        cout << "\nPlease enter the last name of record you want to delete: ";
        cin >> strLName;

        ifstream myfile;

        ofstream temp;

        myfile.open("Directory.dir");
        temp.open("temp.dir");

        while (!myfile.eof())
        {
            getline(myfile, line);

            nextLoc = line.find(" ");

            fName = line.substr(0, nextLoc);

            line = line.substr(nextLoc + 1, line.length());

            nextLoc = line.find(" ");

            lName = line.substr(0, nextLoc);

            line = line.substr(nextLoc + 1, line.length());

            tNumber = line;

            if (!(fName == strFName && lName == strLName))

                temp << fName << " " << lName << " " << tNumber << endl;
            else
                flag++;
        }
        if (flag == 0)
        {
            cout << "\nRecord not found!!\n\n";
            goto afg;
        }
        cout << "The record with the name " << strFName << " " << strLName << " has been deleted " << endl;
        myfile.close();
        temp.close();

        remove("Directory.dir");
        rename("temp.dir", "Directory.dir");

    afg:
        return;
    }

    //class function to modify
    void mod()
    {
        system("cls");
        system("color E");

        string line, fName, lName, strLName, strFName, tNumber;
        int nextLoc = 0, flag = 0;
        cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";

    afgh:
        cout << "Please enter the first name of record you want to modify: ";
        cin >> strFName;

        cout << "\nPlease enter the last name of record you want to modify: ";
        cin >> strLName;

        ifstream myfile;

        ofstream temp;

        myfile.open("Directory.dir");
        temp.open("temp1.dir");

        while (!myfile.eof())
        {
            getline(myfile, line);

            nextLoc = line.find(" ");

            fName = line.substr(0, nextLoc);

            line = line.substr(nextLoc + 1, line.length());

            nextLoc = line.find(" ");

            lName = line.substr(0, nextLoc);

            line = line.substr(nextLoc + 1, line.length());

            tNumber = line;
            if (!(fName == strFName && lName == strLName))
                temp << fName << " " << lName << " " << tNumber << endl;
            else
                flag++;
        }
        if (flag == 0)
        {
            cout << "\nRecord not found!! Try Again.\n\n";
            goto afgh;
        }

        myfile.close();

        temp.close();

        remove("Directory.dir");

        rename("temp1.dir", "Directory.dir");

        string fname2, lname2, tnumber2;

        fstream myfile2("Directory.dir", ios::app);

        cout << "\n\nEnter New First Name : ";

        cin >> fname2;

        myfile2 << fname2 << " ";

        cout << "\nEnter New Last Name : ";

        cin >> lname2;

        myfile2 << lname2 << " ";

        cout << "\nEnter New Phone Number : ";

        cin >> tnumber2;

        myfile2 << tnumber2;

        myfile2.close();

        return;
    }
};

int main()
{
    directory d;
    
    int choice, choice3, returnedValue;

    char choice2 = 'y', choice4 = 'y';
    string pword;

dkj:
    system("cls");

    int x, y;

    for (int i = 0; i < 9; i++)
    {
        for (int k = 0; k < 45; k++)
        {
            cout << " ";
        }
        for (int j = 0; j < 13; j++)
        {
            x = i - 6;
            y = j - 6;
            if (x * x + y * y <= 37)
                cout << ".";
            else
                cout << " ";
            cout << " ";
        }
        cout << "\n";
    }
    for (int i = 1; i <= 13; i++)
    {
        for (int k = 0; k < 45; k++)
        {
            cout << " ";
        }
        for (int j = 1; j <= i; j++)
        {
            cout << " ";
        }
        for (int j = 1; j <= 8; j++)
        {
            cout << ". ";
        }
        cout << "\n";
    }

    for (int i = 7; i > 0; i--)
    {
        for (int k = 0; k < 61; k++)
        {
            cout << " ";
        }
        for (int j = 0; j < 13; j++)
        {
            x = i - 6;
            y = j - 6;

            if (x * x + y * y <= 37)
                cout << ".";
            else
                cout << " ";
            cout << " ";
        }

        cout << "\n";
    }

    cout << endl;
    cout << "----------------------------------------------------------------WELCOME TO PHONE Directory----------------------------------------------------------------\n";

    cout<<"ABOUT THE DIRECTORY"<<endl;
    cout<<"The Directory will contain all the social network contacts like various service helpline numbers, customer complaint numbers."<<endl;
    cout<<endl;

    cout<<"STORE AND SEARCH CONTACTS IN A EASY WAY"<<endl;
    cout<<endl;

    cout << "\nPlease Log-In or Sign-Up to Continue\n\n\t1.  Log-In to an Existing Account\n\t2.  Create a new Account\n\t3.  Exit\n";
    cout << "\nPlease Enter your choice: ";

    cin >> choice3;

    if (choice3 == 1)
    {
        returnedValue = d.LogIn();

        if (returnedValue == 1)
        {
            d.SignUp();
        }
        else if (returnedValue == 2)
        {
        yz:
            pword = d.getpword();

            if (pword == "Root")
            {
                system("cls");
                cout << "Admin Signed In\n";
                system("pause");
                goto mno;

            }
            else
            {
                cout << "\nPassword Incorrect! Please Enter Again: ";
                goto yz;

            }
        }
        else if (returnedValue == 3)
        {
        vwx:
            pword = d.getpword();
            if (pword == "root")
            {
                system("cls");
                cout << "Admin Signed In\n";
                system("pause");
                goto mno;
            }
            else
            {
                cout << "\nPassword Incorrect. Please Enter Again: ";
                goto vwx;
            }
        }
    }

    else if (choice3 == 2)
    {

    jkl:
        d.SignUp();
    }

    else
    {
        exit(0);
    }

    while (choice2 == 'Y' || choice2 == 'y')
    {
        system("color E");
        system("cls");

        cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";
        //choices for account members using the directory
        cout << "Do you want to \n\n\t1. Print All Contacts In Directories \n\t2. Search Contact From Directories \n\t3. Enter New Contacts in Directory\n\t4. Display Favourite Contacts\n\t5. Log Out\n\t6. Log Out and Exit\n";
        cout << "\nPlease enter your choice: ";
    abc:
        cin >> choice;

        switch (choice)
        {

        case 1:
            d.printall();
            break;

        case 2:
            d.SearchAndDisplay();
            break;

        case 3:
            d.GetDetails();
           
            break;

        case 4:
            d.ShowFavourites();
            break;

        case 5:
            cout << "\nLogged out successfully!\n";
            system("pause");
            goto dkj;

        case 6:
            exit(0);
            break;

        default:
            cout << "\nWrong Input! Try Again... ";
            goto abc;

        }
    }
    goto stu;
mno:
    system("color E");
    system("cls");

    cout << "\n\n\t\t-----------PHONE DIRECTORY-------------\n\n";

    //choices for admin of the directory
    cout << "Do you want to \n\n\t1. Print All Contacts In Directory \n\t2. Print All Accounts using Directory \n\t3. Search Contact From Directories \n\t4. Enter New Contacts in Directory\n\t5. Delete Contacts From Directory\n\t6. Modify Contacts In Directory\n\t7. Log Out\n\t8. Log Out and Exit\n";
    cout << "\nPlease enter your choice: ";
pqr:
    cin >> choice;
lok:
    switch (choice)
    {
    case 1:
        d.printall();
        break;

    case 2:
        d.printallc();
        break;

    case 3:
        d.SearchAndDisplay();
        break;

    case 4:
        d.GetDetails();
        break;

    case 5:
        d.Delete();
        break;

    case 6:
        d.mod();
        break;

    case 7:
        cout << "\nLogged out successfully!\n";
        system("pause");
        goto dkj;

    case 8:
        exit(0);

    default:
        cout << "\nWrong Input! Try Again... ";
        goto pqr;

    }
    cout << "Do you want to continue? (y/n) : ";
    choice4 = getch();

    if (choice4 == 'Y' || choice4 == 'y')
    {
        goto lok;

    }
    else
        goto mno;

stu:
    exit(0);
}