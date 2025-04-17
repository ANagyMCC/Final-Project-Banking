// Anthony Nagy | COMS-280-WWW02 | Final Project
#include <iostream>
#include <string>
//#include <typeinfo>
#include <algorithm>
//#include <chrono>
#include <sstream>
#include <ctime>
#include <format>
#include <fstream>
#include <random>

//#include "Account_Balance.txt"
//#include "Account_Info.txt"

using namespace std;

// Incode 'Acc' refers to 'Account'
// Debug for Return Values are as follows: | return(0) = Program Exit | return(1) = Default Value(TBD) | return(2) = Success/Verified/Valid | return(3) = Invalid/Input-Error/General-Error | return(4,5,6,7) = Verification for Accounts/Recovery Process

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
                        cerr << "| Error | Non-Integer value detected.\n";
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
                cerr << "| Unknown Error - Inside 'Utility_Functions' |\n";
                return(5);
            }
        }

        string Generate_Recovery_Key(int Key_Length){
            // Initialize Variables
            string Recovery_Key = "";
            random_device Random;

            // Process
            // A non-deterministic random number generator that uses the randomness inherent in the OS and hardware.
            mt19937 Rand_Generator(Random());
            // By creating a distribution object, a desired range of values can be set (0-9), this also provides the variable type of int to the compiler.
            uniform_int_distribution<> Random_Range(0, 9);

            // for loop is used to grab a randomized int value between the ranges of 0 and 9, and then append it to the Recovery_Key string using +=, for a specified number of iterations.
            for(int i = 0; i < Key_Length; ++i){
                Recovery_Key += to_string(Random_Range(Rand_Generator));
            }

            // Uninitialize possible memory intensive operations.
            ~Rand_Generator();

            // Return Complete Recovery_Key.
            return(Recovery_Key);
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
            if(Name_Length == 0){
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

            // std::cin.clear() and User_Input.clear() is used to clear the buffer from any possible newline(\n) characters that might interfere with the check that the 'Enter Key' is being pressed.
            cin.clear();
            User_Input.clear();
                // User Input
                
                if(getline(cin, User_Input)){
                    // Processing
                    if(Utility_Functions::is_Int(User_Input)){
                        Acc_Birthyear = Utility_Functions::Str_to_Int(User_Input);
                    }
                    else{
                        cerr << "User Input is not an integer!";
                        return(3);
                    }
                    
                    if(Utility_Functions::Function_Status == 1){
                        //cout << "\nYear is an int!"; //USED FOR DEBUG
                        cout << "\nThe current year is " << Utility_Functions::Current_Year_int << ".\n";

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
                    }
                    else if(Utility_Functions::Function_Status == 2){ return(3); }
                    else{ return(3); }

                }
                else{ return(3); }

            return(0);
        }
        int Acc_Create_Step4(){
            // Initialize Variables
            string Random_Recovery_Key = "";
            
            // Process
            // Random_Recovery_Key variable being set to the output of the randomly generated, 8 digit long key.
            Random_Recovery_Key = Utility_Functions::Generate_Recovery_Key(8);
            cout << "\nYour randomized account recovery key is: "<< Random_Recovery_Key << ". \nThis 'Recovery Key' is the backup key you will need to provide; if you lose the passcode you are about to enter, and need to reset it, or otherwise need recover the account.\n";

            return(5);
        }

        int Acc_Create_Step5(){
            //Initizlize Variables
            int Acc_PIN = 0;
            string User_Input = "";

            // User Input
            cout << "\nPlease input a four digit PIN (Personal Identification Number), you will need to remember this for preforming transactions, or general access to your account. \nEnter the four (4) digit code now: ";
            cin.clear();
            User_Input.clear();
            if(getline(cin, User_Input)){
                // Processing & Error Handling
                // Calling the is_Int 'Utility' Function to provide error handling for the user input, unless the Input is successful, the Acc_Create_Step5() function will restart with cleared values.
                if(Utility_Functions::is_Int(User_Input)){
                    Acc_PIN = Str_to_Int(User_Input);
                    Utility_Functions::Function_Status = 0;
                    return(6);
                }
                else
                { 
                    cerr << "\n| ERROR! | No choice selected, or invalid input: '" << User_Input << "'. \nType a set of four numbers, each of them being between between 0 and 9! (Ex. '1234')\nResetting PIN Input...\n";
                    Acc_PIN = 0;
                    cin.clear();
                    User_Input.clear();
                }
            }
            else{ 
                cerr << "\n| Unknown Input Error within getline() function |";
                cin.clear();
                User_Input.clear(); 
            }

            return(5);
        }

        // Create_Acc is used to create a new account, and list it within the system. (will output to txt file with persistant log by Phase 2)
        int Acc_Create(){
            Acc_Clear_Info();

            // Variable Initialization
            int Step_Status = 1;

            // Run Account Creation Steps, while determining the return values. Commented out cout's are used for debug.
            // These Loops provide the ability for each step to not be interupted, from incorrect inputs, while allowing exception handling both ways.
            while((Step_Status == 1)){
                // Acc_Create_Step1() is used to provide a disclaimer to ensure the user understands what they must enter. A successful and valid input will continue to the next step.
                Step_Status = Acc_Create_Step1();
                //cout << "\n" << Step_Status; //USED FOR DEBUG
                
            }
            while((Step_Status == 2)){
                // Acc_Create_Step2() is used to gather the name of the customer that is to be used in the account creation process. A successful and valid input will continue to the next step.
                Step_Status = Acc_Create_Step2();
                //cout << "\n" << Step_Status; //USED FOR DEBUG
            }
            while((Step_Status == 3)){
                // Acc_Create_Step3() is used to gather the birth year of the customer that is to be used in the account creation process. A successful and valid input will continue to the next step.
                Step_Status = Acc_Create_Step3();
                //cout << "\n" << Step_Status; //USED FOR DEBUG
            }
            while((Step_Status == 4)){
                // Acc_Create_Step4() is used to generate and provide the user with a randomized recovery key for secure access to their account. A successful and valid input will continue to the next step.
                Step_Status = Acc_Create_Step4();
            }
            while((Step_Status == 5)){
                // Acc_Create_Step5() is used to gather a PIN number from the user for their regular use on the account. A successful and valid input will continue to the next step.
                Step_Status = Acc_Create_Step5();
            }
            
            // Step Status 6 indicates that the account creation process is complete.
            if(Step_Status == 6){
                // Account Creation Complete
                return(1);
            }
            else if(Step_Status == 0){
                cerr << "| Error Encountered | ";
                Step_Status = 1;
            }
            return(0);
        }
};

// Transaction History | Secondary Class that manages the logging of transaction interactions within each account. This will be fully implemented by final project (chose to delay for creating more essential functions first), with an input/output from a persistant external txt file.
class Transaction_History : public Account_Management
{
    // Retrieve Balance Function used to preform a retrieval of the specified account's balance, given the account number. At this point, the user has already validated who they are.
    double Retrieve_Balance(int Acc_Num){
        return(0);
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
            cout << "Greetings Valued Customer!\n\nPlease select an action from below.\n  1  | Access Account\n  2  | Create New Account\n  3  | Recover an Account (using Recovery Code)\n  4  | Exit\nInput your choice: ";
            
            // User Input
            cin.clear();
            User_Input.clear();

            // if statement used in input to provide error handling in the case that the Stream is unable to pull input, this should only ever happen in the case of excessive spam of characters for the input, overloading stream (possibly).
            if(getline(cin, User_Input)){

                // Processing & Error Handling
                // Calling the is_Int 'Utility' Function to provide error handling for the user input, unless the Input is successful, it will restart the entire Interface_Start_Text() function.
                if(Utility_Functions::is_Int(User_Input)){
                    User_Action = Str_to_Int(User_Input);
                    Utility_Functions::Function_Status = 0;
                    return(2);
                }
                else
                { 
                    cerr << "| ERROR! | No choice selected, or invalid input, '" << User_Input << "'. \nType a number, between 1 and 4!\nResetting Banking Interface...\n\n";
                    User_Action = 0;
                    cin.clear();
                    User_Input.clear();
                }
            }
            else{ 
                cerr << "Interface Failed";
                return(1); 
            }
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
                if(temp_Var == 1){
                    cout << "\nAccount Creation Successful, thank you, " << Acc_Name << ".";
                    //prepare for data output to txt file here (using external function)
                    temp_Var = 0;
                    return(3);
                }
            }
            // User Action 1 | Access Account
            while(User_Action == 3){
                //(Recovery)Create after accounts
            }
            // User Action 1 | Access Account
            while(User_Action == 4){
                cout << "Thank you for using our services, valued customer, we look forward to your next visit!\n";
                return(3);
            }
            // Error Handle for Input Value being out of desired range. | Restart Banking Interface 
            if(!(User_Action > 1 && User_Action < 4)){
                cin.clear();
                User_Input.clear();
                cerr << "Value outside of avaliable options, you entered: '" << User_Action << "'. Please select a number between 1 and 4!\n\n";
                User_Action = 0;
                return(1);
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
    
    /*
    Program Status Indications (used to allow for further control over how the program operates.)
    Program_Status = 0 | --- | Default Execution/Null Execution
    Program_Status = 1 | CR1 | Start/Loop Program Section 1, until value is returned of '2' to continue to next section within program.
    Program_Status = 2 | CR2 | Start/Loop Program Section 2, until value is returned of '3' to continue to next section within program.
    Program_Status = 3 | CR3 | Start Program Section 3, until value is returned of '4' to continue to next section within program.
    Program_Status = 4 | END | Indication to end the program.
    */
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
        while(Program_Status == 3){
            // temp output of 4 to continue to normal process (WIP).
            Program_Status = 4;
        }
        if(Program_Status == 4){
            cout << "\n| Program End |"; 
            return(1);
        }
    
    }
    return(0);
}