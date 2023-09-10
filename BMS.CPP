#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

class Bank_Account
{
    int Account_number;
    char name[50];
    char type;
    int Deposite_Money;

public:
    int retacno() const{
        return Account_number;
    }
    void report() const;
    void Open_account();
    void Display_Account();
    void Modify_account();

    void dep(int n){
        Deposite_Money+=n;
    }
    void draw(int n){
        Deposite_Money-=n;
    }
    int retdeposite()const{
        return Deposite_Money;
    }
};

void Bank_Account::Open_account()
{
    system("cls"); // to show in terminal
    cout << "Enter the Account Number" << endl;
    cin >> Account_number;
    cout << "Enter the name of the Account holder" << endl;
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter the type of Account (C/S)" << endl;
    cin >> type;

    type = toupper(type);

    cout << "Enter the initial amount for the creation of account (>=500 for saving and >=1000 for currernt)" << endl;
    cin >> Deposite_Money;
    cout << endl;

    cout << "Your account is created :)"
         << "Thank you for choosing our bank " << endl;
}
void Bank_Account::Display_Account()
{
    cout << "Account Number :" << Account_number << endl;
    cout << "Account holder's name is :" << name << endl;
    cout << "Type of the Account :" << type << endl;
    cout << "Account Balance :" << Deposite_Money << endl;
}

void Bank_Account::report() const{
           cout<<Account_number<<setw(10)<<" "<<name<<setw(6)<<type<<setw(6)<<" "<<Deposite_Money<<endl;
           
}
void Bank_Account::Modify_account(){
    cout<<"\t Account Number: "<<Account_number<<endl;
    cout<<"\t Modify Account Holder name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Modify Type of account:";
    cin>>type;
    type=toupper(type);
    cout<<"\t modify Balance account:";
    cin>>Deposite_Money;
}

void write_account();   // function to record in binary file
void delete_account(int); //function to display account details given by user
void display_details(int); //function to delete record of files
void display_all(); // to display all account holder's list
void Updatation_Bank_ac(int n);

void Money_deposite_withdraw(int n,int opt);

int main()


{
    char ch;
    int num;
    do
    {
        cout << "\t.............................................." << endl;
        cout << "\t|....WELCOME TO THE BANK MANAGEMENT SYSTEM...|" << endl;
        cout << "\t.............................................." << endl;

        cout << endl;
        cout << "\t..MAIN MENU.." << endl;
        cout << "\t1.Open Account " << endl;
        cout << "\t2.Deposite Money " << endl;
        cout << "\t3.Withdraw Money " << endl;
        cout << "\t4.Balance Enquiry " << endl;
        cout << "\t5.All account holders' list " << endl;
        cout << "\t6.close an account " << endl;
        cout << "\t7.modify an account " << endl;
        cout << "\t8.Exit " << endl;
        cout << endl;

        cout << "\tchoose one of above option :";
        cin >> ch;
        switch (ch)
        {

        case '1':
        {
            system("cls");

            write_account();
            // open account
            break;
        }
        case '2':
        {
            system("cls");
            cout << "\t Enter the account number" << endl;
            cin >> num;
            Money_deposite_withdraw(num,1);
            break; // Deposite money
        }
        case '3':
        {
            system("cls");
            cout << "\t Enter the account number" << endl;
            cin >> num;
            Money_deposite_withdraw(num,2);
            break; // withdraw money
        }
        case '4':
        {
            system("cls");
            cout << "\t Enter the account number" << endl;
            cin >> num;
            display_details(num);
            break;
        }
        case '5':
        {
            system("cls");
            cout << "\t Enter the account number" << endl;
            cin >> num;
            display_all();
            break;
        }
        case '6':
        {
            system("cls");
            cout << "\t Enter the account number" << endl;
            cin >> num;
            delete_account(num);
            break;
        }
        case '7':
        {
            system("cls");
            cout << "\t Enter the account number" << endl;
            cin >> num;
            Updatation_Bank_ac(num);
            break;
        }
        case '8':
           
           {
              cout<<"\t Thanks for using bank management system "<<endl;
           }
       }
    
    cin.ignore();  // input will not be taken after 8th case.
    cin.get();
 } while (ch != 8);
    return 0;
}
void write_account()   // function to record in binary file 
{  
    // first we taking the data from user and calling thefunction
   Bank_Account ac;
   ofstream outfile;  //we have to store offstream file
   outfile.open("Account.dat",ios::binary|ios::app);
   ac.Open_account();
   outfile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));
   outfile.close();
}
void delete_account(int n){
    Bank_Account ac;
    ifstream infile; // input file stream
    ofstream outfile;  // output file stream
    infile.open("account.dat",ios::binary);
    if(!infile){
        cout<<"file could not be open || press any key....";
        return;
    }
    outfile.open("Temp.dat",ios::binary);
    infile.seekg(0,ios::beg);
    while(infile.read(reinterpret_cast< char *>(&ac),sizeof(Bank_Account))){
        if(ac.retacno()!=n){
              outfile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));
        }
    }
    infile.close();
    outfile.close();

    remove("Banck_Account.dat");
    rename("Temp.dat","Bank_Account.dat");
    cout<<"\t record deleted....."<<endl;
}
void display_details(int n){
    Bank_Account ac;
    bool flag=false;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile){
        cout<<"file could not be open || press any key.....";
        return;
    }
    cout<<"\t Bank account details "<<endl;
    while(infile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account))){
        if(ac.retacno()==n){
            ac.Display_Account();
            flag=true;
        }
    }
    infile.close();
    if(flag==false){
        cout<<"\t Account number does not exist "<<endl;

    }
}
void display_all()        // function to display all acccount details
{
  system("cls");  // cls ->
  Bank_Account ac;
  ifstream infile;
  infile.open("account.dat",ios::binary);
  if(!infile){
    cout<<"\t file could not be open || press any key...";
    return;
  }
  cout<<"\t Bank Account Holder List "<<endl;
  cout<<"===================================================="<<endl;
  cout<<"A/c no.         NAME           Type          Balance"<<endl;
  cout<<"===================================================="<<endl;
  while(infile.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account)))      // we cconverting all the data to chararcte which we have converted intpo binary before to understand
  {
   ac.report();
  }
  infile.close();
}
void Money_deposite_withdraw(int n,int opt){
      int amt;
      bool found=false;
      Bank_Account ac;
      fstream file;
      file.open("account.dat",ios::binary | ios::in|ios::out);
      if(!file){
        cout<<"File could not be found || Press any key.....";
        return;
      }
      while(!file.eof() &&found==false){
        file.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));
        if(ac.retacno()==n){
            ac.Display_Account();
            if(opt==1){
                cout<<"\t Enter the amount to be deposited: ";
                cin>>amt;
                ac.dep(amt);

            }
            if(opt==2){
                cout<<"\t Enter the amount to be withdrawn: ";
                cin>>amt;
                int balance=ac.retdeposite()-amt;
                if(balance<0){
                    cout<<"\t Insufficient balance"<<endl;
                }
                else{
                    ac.draw(amt);
                }
            }
            int pos=(-1)*static_cast<int>(sizeof(Bank_Account));
            file.seekp(pos,ios::cur);  // move the pointer to the position of the file
            file.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account)); //write the record in the file
            cout<<"\t record updated"<<endl;
            found =true;

        }
      }
      file.close();
      if(found==false){
        cout<<"\t Record Not found"<<endl;
      }
}
void Updatation_Bank_ac(int n){
    bool found =false;
    Bank_Account ac;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out) ;// open file in binary mode
    if(!file){
        cout<<"file could bot be open ||  press any key....";

    }
    while(!file.eof()&&found==false){
        file.read(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));  // read the record from the file
        if(ac.retacno()==n){
            ac.Display_Account();
            cout<<"\t Enter the new details of account"<<endl;
            ac.Modify_account();
            int pos= (-1)*static_cast<int>(sizeof(Bank_Account)); // Move the pointer to the position of the file
            file.seekp(pos,ios::cur);  // Move the pointer  to the posotion of the file
            file.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));   // write the record from the file
            found =true;
        }
    }
    file.close();
    if(found==false){
        cout<<"\t Record not found"<<endl;
    }
}
