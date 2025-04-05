// Anthony Nagy | COMS-280-WWW02 | Final Project
#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <chrono>

//#include "Account_Balance.txt"
//#include "Account_Info.txt"

using namespace std;

// Incode 'Acc' refers to 'Account'
// Debug for Return Values are as follows: | return(0) = Program Exit | return(1) = Default Value(TBD) | return(2) = Success/Verified/Valid | return(3) = Invalid/Input-Error/General-Error | return(4,5,6,7) = Verification for Accounts/Recovery Process

/*class Time_Date_Management{
    public:
    //using namespace chrono;

    //auto now = std::chrono::system_clock::now();
    time

    //floor<days>(chrono::system_clock::now()).year())

};*/

// Account Management | Primary Class that handles account information such as creating, deleting, managing, merging, and other operations.
class Account_Management
{
    private:
        

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

        string User_Input;
        
        // Basic Account Info struct, used to combine multiple data types, to present general information to the user, about their account. (work in progress)
        /*struct B_Account_Info{
            int Num;
            string Name;
            double Balance; 
        };*/

    public:
        // Fucntion Clear_Acc_Info is used to ensure that account information is always returned to default states.
        void Acc_Clear_Info(){
            Acc_Create_Num = 0;
            Acc_Num = 1234567890;
            string Acc_Name = "JOHN DOE";  
            Acc_Birthyear = 1234;
            Acc_Balance = 0;
            Acc_Rec_Key = 123456;
            int E_Account_Info[4] = {Acc_Create_Num, Acc_Num, Acc_Birthyear, Acc_Rec_Key};
            
        }

        int Acc_Create_Step1(){
            // Instructions
            cout << "Welcome to the Account Creation Menu, you will be asked various questions that are neccessary to complete the creation of an account at this Bank. \nAt the end of this process, you will be provided with an account recovery key, which must be kept safe at all times, in case your account needs to be recovered.\nPlease press 'Enter' if you understand the instructions: ";
            
            // std::cin.ignore is used to clear the buffer from any possible newline(\n) characters that might interfear with the check that the 'Enter Key' is being pressed.
            cin.ignore();
            // Check to see if the Enter key (new line) is pressed, loop will only break if enter is pressed, or program is terminated.
            if (cin.get() == '\n'){
                // Setting Press_Enter to true instantly ends the while loop.
                return(2);
            }

            return(1);
        }

        int Acc_Create_Step2(){
            // Variable Initialization
            // Name_Space_Count | Used to count the number of spaces within the name provided.
            int Name_Space_Count;
            // Name_Length | Used to count the number of characters in a name.
            int Name_Length;
            // Alpha_Count | Used to count the number of alphabetical characters in a name.
            int Alpha_Count;

            //Second Verification that the specific step's data is reset to default value "JOHN DOE"
            Acc_Name = "JOHN DOE";

            //Begin gathering information to create the account/
            cout << "\nPlease enter your full name (First and Last, A-Z): ";
            getline(cin, Acc_Name);
            //toupper(Acc_Name);
            transform(Acc_Name.begin(), Acc_Name.end(), Acc_Name.begin(), ::toupper);

            // Set Default values of variables.

            Name_Space_Count = 0;
            Name_Length = 0;
            Alpha_Count = 0;

            Name_Length = Acc_Name.length();
            //cout << Name_Length;

            // For loop used to identify each char within the name, counting space's, and detecting any characters not considered 'legal'.
            for(int Char_Val : Acc_Name){
                /*
                // All characters of a name are set to uppercase values for Bank Use.
                Char_Val = toupper(Char_Val);
                */
                //cout << Char_Val << " \n";
                if(static_cast<int>(Char_Val) == 32){
                    Name_Space_Count++;
                    //Name_Length++;
                }
                // Check to determine if a specific char within the Acc_Name string has a value of A through Z, does nothing.
                else if((static_cast<int>(Char_Val) >= 65) && (static_cast<int>(Char_Val) <= 90)){ Alpha_Count++; }
                // Check to determine if a specific char within the Acc_Name string is the value of ' or `, does nothing.
                else if((static_cast<int>(Char_Val) == 39) || (static_cast<int>(Char_Val) == 96)){ }
                //if(((static_cast<int>(Char_Val) >= 97) && (static_cast<int>(Char_Val) <= 90))){ cout << "Program Error, toupper(char) failed."; }
                
                // Used the comment below to track the ASCII value of each char, giving me the specific value to target to and debug the error checks for the name string.
                //cout << "\nYour name contains " << Name_Space << " Spaces.";
                // If all other checks fail, the program returns an error, due to a specific char in the Acc_Name string not being considered a legal character.
                else{
                    cout << "Invalid Character detected! (Only A-Z, ' or `, and one space is allowed.)";
                    return(3);
                }
            }
            if(Name_Length == 0){
                cout << "\nEmpty, or Invalid Input! | Please enter your first and last name.";
                return(3);
            }
            else if(!(Name_Space_Count == 1)){
                cout << "Invalid Number of spaces within the name provided! Please make sure to give a first and last, with one space. (Eg. 'John Doe')";
                return(3);
            }
            else if((Alpha_Count < 2) || (Alpha_Count > 60)){
                cout << "Too few, or too many characters in name, please enter a name between 2 and 60 characters in length! (Only A-Z, ' or `, and one space is allowed.)";
                return(3);
            }
            /*else{
                cout << "Unknown Error!";
                return(3);
            }*/

            return(1);
        }

        int Acc_Create_Step3(){
            //using namespace chrono;

            // Variable Initialization


            //
            cout << "\nThank you, " << Acc_Name << ", Please enter your birth year (####): ";
            try{
                getline(cin, User_Input);
                try{Acc_Birthyear = stoi(User_Input);}
                catch(const std::invalid_argument& Err_Code){
                    cerr << "| Error | Invalid Argument!" << Err_Code.what() << "\n\n";
                }
                catch (const std::out_of_range& Err_Code){
                    cerr << "| Error | Out of Range!" << Err_Code.what() << "\n\n";
                }
                catch(...){
                    cerr << "| Unknown Error |";
                }
                if(typeid(Acc_Birthyear) != typeid(int)){
                    throw(1);
                }
                // Will implement date checks for current year by Phase 4.
                else if(Acc_Birthyear < 1900 || Acc_Birthyear > 2026){
                    throw(2);
                }
            }
            catch(int Err_Code){
                if(Err_Code == 1){
                    cerr << "| Error | Invalid data type";
                }
                else if(Err_Code == 2){
                    cerr << "| Error | Birthyear out of realistic range.";
                }
                else{
                    cerr << "| Undetermined Error Code |";
                }
            }
            catch(...){
                cerr << "| Unknown Error |";
            }

            return(1);
        }

        // Create_Acc is used to create a new account, and list it within the system. (will output to txt file with persistant log by Phase 2)
        int Acc_Create(){
            Acc_Clear_Info();

            // Variable Initialization
            int Step_Status = 0;

            // Run Account Creation Steps, while determining the return values. Commented out cout's are used for debug.
            while(!(Step_Status == 2)){
                Step_Status = Acc_Create_Step1();
                //cout << "\n" << Step_Status;
            }
            Step_Status = 0;
            while(!(Step_Status == 1)){
                Step_Status = Acc_Create_Step2();
                //cout << "\n" << Step_Status;
            }
            Step_Status = 0;
            while(!(Step_Status == 1)){
                Step_Status = Acc_Create_Step3();
                cout << "\n" << Step_Status;
            }
            return(1);
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
    private:

    public:
    int Acc_Login(){
        
        return(1);
    }

};

// This 'Banking_Interface' gives the options of Accessing an existing account, creating an entirely new account, or recovering an account from a key that is assigned to a profile.
class Banking_Interface : public User_Authentication
{
    private:
        int User_Action = 0;
        string User_Input;
        
    public:
        void Interface_Start_Text(){
            User_Input.clear();
            cout << "Greetings Valued Customer!\n\nPlease select an action from below.\n  1  | Access Account\n  2  | Create New Account\n  3  | Recover an Account (using Recovery Code)\n  4  | Exit\nInput your choice: ";
            try{
                if(getline(cin, User_Input)){
                    try{User_Action = stoi(User_Input);}
                    catch(const invalid_argument& Err_Code){
                        cerr << "| Error | Invalid Argument!" << Err_Code.what() << "\n\n";
                    }
                    catch (const out_of_range& Err_Code){
                        cerr << "| Error | Out of Range!" << Err_Code.what() << "\n\n";
                    }
                    catch(...){
                        cerr << "| Unknown Error |";
                    }
                    if(typeid(User_Action) != typeid(int)){
                        throw(1);
                    }
                    else if(User_Action < 1 || User_Action > 4){
                        throw(2);
                    }
                }
                else{
                    throw(3);
                }
                //cin >> User_Action;
                //cout << "001 | " << User_Input << "\n";
                
                //cout << "002 | " << User_Action;


                // Will continue on if no errors are thrown.
            }
            catch(int Err_Code){
                if(Err_Code == 1){
                    cerr << "| ERROR! | Invalid Input Data Type, enter an Integer!\n\n";
                }
                else if(Err_Code == 2){
                    cerr << "| ERROR! | Integer outside of Input Range, Enter a value 1-4!\n\n";
                }
                else if(Err_Code == 3){
                    cerr << "| ERROR! | Failed to read input";
                }
                else{
                    cerr << "| ERROR! | Undetermined Error Code";
                }
            }
            catch(...){
                cerr << "| ERROR! | Undefined Error\n";
            }
        }
        void Interface_Start_Interact(){
            // User Action 1 | Access Account
            if(User_Action == 1){
                User_Authentication::Acc_Login();
            }
            // User Action 2 | Access Account
            else if(User_Action == 2){
                Account_Management::Acc_Create();
            }
            // User Action 1 | Access Account
            else if(User_Action == 3){
                //(Recovery)Create after accounts
            }
            // User Action 1 | Access Account
            else if(User_Action == 4){
                cout << "Thank you for using our services, valued customer, we look forward to your next visit!\n";
                exit;
            }
            // Error Handle | Restart Banking Interface 
            else{
                cout << "| ERROR! | No choice selected, or invalid input, type a number!\nResetting Console...\n\n";
                User_Action = 0;
                Interface_Start_Text();
            }
            
        }
        /*catch(int Err_Code){
            if(Err_Code == 1){
                cout << "| ERROR! | No choice selected, or invalid input, type a number!\nResetting Console...\n\n";
            }
        }*/
        /*catch(...){
            cout << "Unknown Error\n";
            Interface_Start_Text();
        }*/
};

int main()
{
    // Starting Initialization
    Account_Management Acc_Manage;
    Transaction_History Trans_Hist;
    User_Authentication User_Auth;
    Banking_Interface Interface;
    //Time_Date_Management TD_Manage;

    // Starting Processes
    Acc_Manage.Acc_Clear_Info();

    // Begin Program by starting the inteface interaction function.
    Interface.Interface_Start_Text();
    Interface.Interface_Start_Interact();

    return 0;
}