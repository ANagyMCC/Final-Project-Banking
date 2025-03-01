#include <iostream>

using namespace std;

// Account Management | Primary Class that handles account information such as creating, deleting, managing, merging, and other operations.
// Incode 'Acc' refers to 'Account'
class Account_Management
{
    private:
        // Boolean 'Clear_Info' is used to ensure that account information is always returned to default states.
        bool Clear_Info = true;

    protected:
        // Account Creation Number | Used by the bank for internal use, to identify how many members are active at the bank, and to award the Xth customer for chosing this bank.
        int Acc_Create_Num;
        // Account Number | Primary Account Identifier
        int Acc_Num;
        // Account Name | Personal Identifier
        string Acc_Name;    
        // Account Birth Year | Personal Identifier
        int Acc_Birthyear;
        // Account Balance | Personal/Account Information
        double Acc_Balance;
        // Account Recovery Key | Personal/Recovery identifier
        int Acc_Rec_Key;

        // Interger Array for essential account information, or identifiers, using a fixed set of data. The array consists of 4 values, given the removal of unnessesary information, the customer name and balance, and adding an additional 'member number', assigned by the Bank for internal use.
        int E_Account_Info[4];
        

    public:
        // Fucntion Clear_Acc_Info is used, with true boolean 'Clear_Info', to ensure that account information is always returned to default states.
        void Clear_Acc_Info(){
            if(Clear_Info == true){
                Acc_Create_Num = 0;
                Acc_Num = 1234567890;
                Acc_Name = "JOHN DOE";  
                Acc_Birthyear = 1234;
                Acc_Balance = 0;
                Acc_Rec_Key = 123456;
                E_Account_Info[Acc_Create_Num, Acc_Num, Acc_Birthyear, Acc_Rec_Key];
            }
        }

        // Basic Account Info struct, used to combine multiple data types, to present general information to the user, about their account. (work in progress)
        struct B_Account_Info{
            int Acc_Num;
            string Acc_Name;
            double Acc_Balance; 
        };

        // Create_Acc is used to create a new account, and list it within the system. (will output to txt file with persistant log by Phase 2)
        int Create_Acc(){
            cout << "Welcome to the Account Creation Menu, you will be asked various questions that are neccessary to complete an account. \nAt the end of this process, you will be provided with an account recovery key, which must be kept safe at all times, in case your account needs to be recovered.\n";
        }
};


// Transaction History | Secondary Class that manages the logging of transaction interactions within each account. This will be fully implemented in Phase2, with an input/output from a persistant external txt file.
class Transaction_History : public Account_Management
{
    // Retrieve Balance Function used to preform a retrieval of the specified account's balance, given the account number. At this point, the user has already validated who they are.
    double Retrieve_Balance(int Acc_Num){

    }
};

// User Authentication | Validates Account Information, Authenticates Users into accounts, and Verifies Identity using recovery key and other methods.
class User_Authentication : public Account_Management
{

};

class Banking_Interface : public User_Authentication
{
    private:
        int User_Action = 0;
    public:
        // This 'Banking_Interface' gives the options of Accessing an existing account, creating an entirely new account, or recovering an account from a key that is assigned to a profile
        void Begin_Text(){
            cout << "Greetings Valued Customer! \n Please select an action from below.\n  1  | Access Account\n  2  | Create New Account\n  3  | Recover an Account (using Recovery Code)\n  4  | Exit\nInput your choice: ";
            cin >> User_Action;
            cout << "\n";
        }
        void Begin_Interaction(){
            Begin_Text();
            if(User_Action == 1){
                User_Authentication::Create_Acc();
            }
            else if(User_Action == 2){
                
            }
            else if(User_Action == 3){
                //(Recovery)Create after accounts
            }
            else if(User_Action == 4){
                cout << "Thank you for using our services, valued customer, we look forward to your next visit!\n";
                exit;
            }
            else{
                cout << "| ERROR! | No choice selected, or invalid input, type a number!\n";
                User_Action = 0;
                Begin_Text();
            }
        }
};

int main()
{
    // Starting Initialization
    Account_Management Acc_Manage;
    Transaction_History Trans_Hist;
    User_Authentication User_Auth;
    Banking_Interface Interface;

    // Starting Processes
    Acc_Manage.Clear_Acc_Info();

    // Begin Program by starting the inteface interaction function.
    Interface.Begin_Interaction();

    return 0;
}