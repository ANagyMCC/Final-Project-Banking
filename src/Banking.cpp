// Anthony Nagy | COMS-280-WWW02 | Final Project
#include <iostream>
#include <string>
#include <typeinfo>
#include <algorithm>
//#include <time.h>
#include <chrono>
#include <sstream>
#include <ctime>
#include <format>
#include <optional>

//#include "Account_Balance.txt"
//#include "Account_Info.txt"

using namespace std;

// Incode 'Acc' refers to 'Account'
// Debug for Return Values are as follows: | return(0) = Program Exit | return(1) = Default Value(TBD) | return(2) = Success/Verified/Valid | return(3) = Invalid/Input-Error/General-Error | return(4,5,6,7) = Verification for Accounts/Recovery Process

/*class Time_Date_Management{
    public:
    //using namespace chrono;

    //auto now = chrono::system_clock::now();
    time

    //floor<days>(chrono::system_clock::now()).year())

};*/

class Utility_Functions
{
    private:
        // Will Implement MM/DD/YYYY input if enough time later.
        int get_Current_Year_int(){
            int Final_Result;
            time_t current_Time = time(0);
            tm* local_Time = localtime(&current_Time);
            // char type array used to store the year.
            char local_Year[5];
            
            // strftime used to convert the local time data structure into a more readable format, with only the neccessary information.
            strftime(local_Year, sizeof(local_Year), "%Y", local_Time);
            //cout << "\n 2: DEBUG START | " << local_Year << " | END\n "; USED FOR DEBUG
            Final_Result = Str_to_Int(local_Year);
            //cout << "\n 3: DEBUG START | " << Final_Result << " | END\n "; USED FOR DEBUG
            return(Final_Result);
        }

    protected:
    /*
    Func Status Indications (used to allow for further control over how the program operates.)
    Func Status = 0 | Default Execution/Null Execution
    Func Status = 1 | Successful Execution
    Func Status = 2 | Failed Execution / Error Handling Executed
    Func Status = 3 | Start/Restart Status (Indicator for class functions to check before starting (neccessary to prevent memory overloading))
    */
    int Function_Status = 0;

    public:
        // Integer variable used to store the current year for external processing.
        int Current_Year_int = get_Current_Year_int();

        bool is_Int(string Sample_Input){
            bool b_Result;
            if(Sample_Input.empty()){
                b_Result = false;
                return(b_Result);
            }

            for(char temp : Sample_Input){
                if(!isdigit(temp) && temp != '-' && temp != '+' && temp != '*' && temp != '/'){
                    b_Result = false;
                    return(b_Result);
                }
            }

            b_Result = true;
            return(b_Result);
        }
        
        template <typename I>
        bool is_Int(const I& Sample_Input){
            bool b_Result = false;
            b_Result = (is_integral<I>::value);
            return(b_Result);
        }

        // Str_to_Int converts a user input into a usable format for interpretation of integer values, while allowing for error checks.
        int Str_to_Int(string Sample_Input){
            int temp_Variable = 0;
            // Output_Variable used for error checks, if value remains 0 on return, error handling will occur within returned structure.
            //int Output_Variable = 0;
            //cout << "ENTERED FUNCTION"; //USED FOR DEBUG
            try{
                //while(Function_Status == 3){
                    stringstream ss(Sample_Input);
                    if(ss >> temp_Variable){
                        //Output_Variable = stoi(Sample_Input);
                        //cout << "ENTERED INTEGER"; //USED FOR DEBUG
                        Function_Status = 1;
                        return(temp_Variable);
                        //cout << "\n" << Output_Variable; USED FOR DEBUG
                    }
                    else{
                        Function_Status = 2;
                        cerr << "| Error | Non-Integer value detected.";
                        return(5);
                        //throw(invalid_argument("Non-Integer value detected."));
                        
                        //ss.clear();
                        //ss.ignore(numeric_limits<streamsize>::max(), '\n');
                        //cout << "| Error | Non-Integer value detected : " << Sample_Input << "\n";
                        //cout << "function still running";
                        //return(1);
                        
                        //return(1);
                    }

                    //cout << "\n" << Sample_Input; USED FOR DEBUG
                    //cout << "\n" << Output_Variable; USED FOR DEBUG
                //}
            }
            /*catch(int Err){
                cerr << "ENTER CATCH";
                if(Err == 1){
                    //Function_Status = 1;
                    cerr << "\n| Fatal Error | Non-Integer value detected.";
                }
                else{ cerr << "| Unknown Error |";}
            }*/
            catch(const invalid_argument& Err_Code){
                Function_Status = 2;
                cerr << "| Error | Invalid Argument! | " << Sample_Input << " |\n\n";
                return(5);
            }
            catch (const out_of_range& Err_Code){
                Function_Status = 2;
                cerr << "| Error | Out of Range!" << Err_Code.what() << "\n\n";
                return(5);
            }
            catch(...){
                Function_Status = 2;
                cerr << "| Unknown Error - Inside 'Utility_Functions' |";
                return(5);
            }
        }



};

// Account Management | Primary Class that handles account information such as creating, deleting, managing, merging, and other operations.
class Account_Management : public Utility_Functions
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
            cout << "\nWelcome to the Account Creation Menu, you will be asked various questions that are neccessary to complete the creation of an account at this Bank. \nAt the end of this process, you will be provided with an account recovery key, which must be kept safe at all times, in case your account needs to be recovered.\nPlease press 'Enter' if you understand the instructions: ";
            
            // std::cin.clear() is used to clear the buffer from any possible newline(\n) characters that might interfere with the check that the 'Enter Key' is being pressed.
            cin.clear();

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
            int Name_Space_Count = 0;
            // Name_Length | Used to count the number of characters in a name.
            int Name_Length = 0;
            // Alpha_Count | Used to count the number of alphabetical characters in a name.
            int Alpha_Count = 0;

            //Second Verification that the specific step's data is reset to default value "JOHN DOE"
            Acc_Name = "JOHN DOE";

            // Begin gathering information to create the account.
            // Context Statement
            {
            cout << "\nPlease enter your full name (First and Last, A-Z): ";
            }

            // User Input
            {
            cin.clear();
            Acc_Name.clear();
            getline(cin, Acc_Name);
            }
            
            // Processing
            {
            //
            transform(Acc_Name.begin(), Acc_Name.end(), Acc_Name.begin(), ::toupper);
            Name_Length = Acc_Name.length();
            
            //cout << Name_Length; USED FOR DEBUG

            // For loop used to identify each char within the name, counting space's, and detecting any characters not considered 'legal' within the context.
            for(int Char_Val : Acc_Name){
                //cout << Char_Val << " \n"; USED FOR DEBUG
                if(static_cast<int>(Char_Val) == 32){
                    Name_Space_Count++;
                }
                // Check to determine if a specific char within the Acc_Name string has a value of A through Z, increments the Alpha_Count int variable, used as a counter.
                else if((static_cast<int>(Char_Val) >= 65) && (static_cast<int>(Char_Val) <= 90)){ Alpha_Count++; }
                // Check to determine if a specific char within the Acc_Name string is the value of ' or `, increments the Alpha_Count int variable, used as a counter.
                else if((static_cast<int>(Char_Val) == 39) || (static_cast<int>(Char_Val) == 96)){ Alpha_Count++; }
                // Used the comment below to track the ASCII value of each char, giving me the specific value to target to and debug the error checks for the name string.
                //cout << "\nYour name contains " << Name_Space << " Spaces."; USED FOR DEBUG

                // If all other checks fail, the program returns an error, due to a specific char in the Acc_Name string not being considered a legal character.
                else{
                    cerr << "Invalid Character detected! (Only A-Z, ' or `, and one space is allowed.)";
                    return(2);
                }
            }
            }
            // Error Handling
            {
            if(Name_Length == 0 || Name_Length == NULL){
                cerr << "\nEmpty, or Invalid Input! | Please enter your first and last name.";
                return(2);
            }
            else if(!(Name_Space_Count == 1)){
                cerr << "Invalid Number of spaces within the name provided! Please make sure to give a first and last, with one space. (Eg. 'John Doe')";
                return(2);
            }
            else if((Alpha_Count < 2) || (Alpha_Count > 60)){
                cerr << "Too few, or too many characters in name, please enter a name between 2 and 60 characters in length! (Only A-Z, ' or `, and one space is allowed.)";
                return(2);
            }
            }
            // Closing statement for Step2.
            cout << "Thank you, " << Acc_Name << ".\n";

            return(3);
        }

        int Acc_Create_Step3(){
            int Acc_Birthage = 0;
            //int temp_Var1;

            // Variable Initialization
            string User_Input;

            // Context Statement
            cout << "\nPlease enter your birth year (####): ";
            cin.clear();
            User_Input.clear();

            //try{
                // User Input
                // std::cin.clear() is used to clear the buffer from any possible newline(\n) characters that might interfere with the check that the 'Enter Key' is being pressed.
                if(getline(cin, User_Input)){

                // Processing
                    if(Utility_Functions::is_Int(User_Input)){
                        Acc_Birthyear = Utility_Functions::Str_to_Int(User_Input);
                    }
                    else{
                        cerr << "User Input is not an integer!";
                        return(3);
                    }
                    //cout << "| 1 |" << User_Input; //USED FOR DEBUG
                    //cout << "| 2 |" << Acc_Birthyear; //USED FOR DEBUG
                    //if((Utility_Functions::is_Int(Acc_Birthyear))){ cout << "SUCESS1!"; } USED FOR DEBUG
                    if(Utility_Functions::Function_Status == 1){
                        //cout << "\nYear is an int!"; //USED FOR DEBUG
                        cout << "\nThe current year is :" << Utility_Functions::Current_Year_int << "\n";

                        Acc_Birthage = ((Utility_Functions::Current_Year_int)-(Acc_Birthyear));
                        cout << Acc_Name << " is approximately " << Acc_Birthage << " years old.\n";
                        if (Acc_Birthage == 0){
                            cerr << "\n| Error | Empty or Invalid input.";
                            return(3);
                        }
                        else if((Acc_Birthage < 2 || Acc_Birthage > 130)){
                            cerr << "\n| Error | Birthyear out of realistic range.";
                            return(3);
                        }
                        Function_Status = 0;
                        return(4);
                        //cout << "SUCCESS2!"; // USED FOR DEBUG
                        //cout << "\nAge of user is " << Acc_Birthage << " years old.";

                    }
                    else if(Utility_Functions::Function_Status == 2){
                        return(3);
                    }
                    else{
                        return(3);
                    }
                }
                else{ return(3); }
                
            //}
            /*catch(int Err_Code){
                if(Err_Code == 1){
                    cerr << "\n| Error | Invalid data type, does not identify as an integer!.";
                }
                else if(Err_Code == 2){
                    cerr << "\n| Error | Birthyear out of realistic range.";
                }
                else if(Err_Code == 3){
                    cerr << "\n| Error | Empty or invalid input!";
                }
                else if(Err_Code == 4){
                    cerr << "\n| Unknown Error! |";
                }
                else{
                    cerr << "\n| Undetermined Error Code |";
                }
            }
            catch(...){
                cerr << "\n| Unknown Error |";
            }*/
            /*if(Utility_Functions::Function_Status == 1){
                cout << "\n| OUTPUT STATUS 1 |";
            }
            else if(Utility_Functions::Function_Status == 2){
                cout << "\n| OUTPUT STATUS 2 |";
            }
            else if(Utility_Functions::Function_Status == 0){
                cout << "\n| OUTPUT STATUS 0 |";
            }*/

            return(0);
        }

        // Create_Acc is used to create a new account, and list it within the system. (will output to txt file with persistant log by Phase 2)
        int Acc_Create(){
            Acc_Clear_Info();

            // Variable Initialization
            int Step_Status = 1;

            // Run Account Creation Steps, while determining the return values. Commented out cout's are used for debug.
            while((Step_Status == 1)){
                Step_Status = Acc_Create_Step1();
                //cout << "\n" << Step_Status; //USED FOR DEBUG
                
            }
            //Step_Status = 0;
            while((Step_Status == 2)){
                Step_Status = Acc_Create_Step2();
                //cout << "\n" << Step_Status; //USED FOR DEBUG
            }
            //Step_Status = 0;
            while((Step_Status == 3)){
                Step_Status = Acc_Create_Step3();
                //cout << "\n" << Step_Status; //USED FOR DEBUG
            }
            if(Step_Status == 4){
                // Account Creation Complete
                return(3);
            }
            else if(Step_Status == 0){
                cerr << "| Error Encountered | ";
                Step_Status = 1;
                return(2);
            }
            return(0);
        }
};

// Transaction History | Secondary Class that manages the logging of transaction interactions within each account. This will be fully implemented by final project (chose to delay for creating more essential functions first), with an input/output from a persistant external txt file.
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
        string User_Input;
        
    protected:

    public:
        int User_Action = 0;
        int Interface_Start_Text(){
            User_Input.clear();

            cout << "Greetings Valued Customer!\n\nPlease select an action from below.\n  1  | Access Account\n  2  | Create New Account\n  3  | Recover an Account (using Recovery Code)\n  4  | Exit\nInput your choice: ";
            //try{
                // User Input
                
                cin.clear();
                if(getline(cin, User_Input)){

                    // Processing & Error Handling
                    /*try{
                        User_Action = Str_to_Int(User_Input);
                        Utility_Functions::Function_Status = 0;
                    }
                    catch(int Err_Code){
                        if(Err_Code == 0){ cerr << "\n| Outside Error 1 | Non-Typical"; }
                        else if (Err_Code == 1){ cerr << "\n| Outside Error 2 | Non-Typical"; }
                        else{ cerr << "\n| Unknown Outside Error | Non-Typical"; }
                    }
                    catch(const invalid_argument& Err_Code){
                        cerr << "| Error | Invalid Argument!" << Err_Code.what() << "\n\n";
                    }
                    catch (const out_of_range& Err_Code){
                        cerr << "| Error | Out of Range!" << Err_Code.what() << "\n\n";
                    }
                    catch(...){
                        cerr << "| Unknown Error |";
                    }*/
                    if(Utility_Functions::is_Int(User_Input)){
                        User_Action = Str_to_Int(User_Input);
                        Utility_Functions::Function_Status = 0;
                        return(2);
                    }
                    else
                    { 
                        cerr << "\n| Error | Caught Non-Int Value " << User_Input << ".\n";
                        User_Action = 0;
                        cin.clear();
                        User_Input.clear();
                    }
                    
                    //cout << User_Action; //USED FOR DEBUG
                    //cerr << User_Action; //USED FOR DEBUG
                    if(User_Action == 5){
                        //cerr << "Failure"; //USED FOR DEBUG
                        User_Action = 0;
                        return(1);
                    }
                    
                    else if(!(User_Action > 1 && User_Action < 4)){
                        return(1);
                    }
                    
                    /*else if(!(Utility_Functions::is_Int(User_Action))){ return; }
                    else if(Utility_Functions::is_Int(User_Action)){
                        //cout << "\nCORRECT!!"; USED FOR DEBUG
                        // Function executed properly;
                        return;
                    }
                    else{ cout << "NOPE!"; }*/
                
                }
                else{ 
                    cerr << "Interface Failed";
                    return(1); 
                }
                /*if(getline(cin, User_Input)){
                    try{User_Action = stoi(User_Input);}
                    catch(int Err_Code){
                        if(Err_Code == 0){ cerr << "\n| Outside Error 1 | Non-Typical"; }
                        else if (Err_Code == 0){ cerr << "\n| Outside Error 2 | Non-Typical"; }
                        else{ cerr << "\n| Unknown Outside Error | Non-Typical"; }
                    }
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
                }*/
                //cin >> User_Action;
                //cout << "001 | " << User_Input << "\n"; //USED FOR DEBUG
                
                //cout << "002 | " << User_Action; //USED FOR DEBUG


                // Will continue on if no errors are thrown.
            //}
            /*catch(int Err_Code){
                if(Err_Code == 1){
                    cout << "| ERROR! | Invalid Input Data Type, enter an Integer!\n\n";
                }
                else if(Err_Code == 2){
                    cout << "| ERROR! | Integer outside of Input Range, Enter a value 1-4!\n\n";
                }
                else if(Err_Code == 3){
                    cout << "| ERROR! | Failed to retrieve input";
                }
                else{
                    cout << "| ERROR! | Undetermined Error Code";
                }
            }
            catch(...){
                cout << "| ERROR! | Undefined Error\n";
            }*/
            return(1);
        }
        int Interface_Start_Interact(){
            // Variable Initialization
            // integer temp_Var is used to assist with error checking between functions.
            int temp_Var = 0;

            // User Action 1 | Access Account
            while(User_Action == 1){
                temp_Var = User_Authentication::Acc_Login();
            }
            // User Action 2 | Access Account
            while(User_Action == 2){
                temp_Var = Account_Management::Acc_Create();
                if(temp_Var == 3){
                    cout << "\nAccount Creation Successful, thank you, " << Acc_Name << ".";
                    //prepare for data output to txt file here (using external function)
                    return(3);
                }
                else if(temp_Var == 2){

                }
            }
            // User Action 1 | Access Account
            while(User_Action == 3){
                //(Recovery)Create after accounts
            }
            // User Action 1 | Access Account
            while(User_Action == 4){
                cout << "Thank you for using our services, valued customer, we look forward to your next visit!\n";
                exit;
            }
            // Error Handle | Restart Banking Interface 
            if((User_Action != 1) && (User_Action != 2) && (User_Action != 3) && (User_Action != 4)){
                cerr << "| ERROR! | No choice selected, or invalid input, type a number!\nResetting Console...\n\n";
                User_Action = 0;
                Interface_Start_Text();
            }
            return(2);
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
    Utility_Functions Util_Func;
    
    int Program_Status = 1;

    // Starting Processes
    Acc_Manage.Acc_Clear_Info();

    // Main Proccesses
    while(Program_Status != 0){
        while(Program_Status == 1){
            // Begin Program by starting the inteface interaction function.
            //int Output = Util_Func.get_Current_Year_int(); USED FOR DEBUG
            Program_Status = Interface.Interface_Start_Text();
            //Interface.User_Action = 0;
        }
        while(Program_Status == 2){
            Program_Status = Interface.Interface_Start_Interact();
            Interface.User_Action = 0;
        }
        if(Program_Status == 3){
            cout << "\n| Program End |"; 
            return(1);
        }
    
    }
    return(0);
}