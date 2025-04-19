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
#include <sstream>
#include <random>
#include <vector>
#include <optional>
#include <cctype>

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

    public:
        /*
        Func Status Indications (used to allow for further control over how the program operates.)
        Func Status = 0 | Default Execution/Null Execution
        Func Status = 1 | Successful Execution
        Func Status = 2 | Failed Execution / Error Handling Executed
        Func Status = 3 | Start/Restart Status (Indicator for class functions to check before starting (neccessary to prevent memory overloading))
        */
        int Function_Status = 0;
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
            try{
                stringstream Str_Stream(Sample_Input);
                if(Str_Stream >> temp_Variable){
                    Function_Status = 1;
                    return(temp_Variable);
                }
                else{
                    Function_Status = 2;
                    cerr << "| Error | Non-Integer value detected.\n";
                    return(5);
                }
            }
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

        double Str_to_Double(string Sample_Input){
            double temp_Variable = 0;
            // Output_Variable used for error checks, if value remains 0 on return, error handling will occur within returned structure.
            try{
                stringstream Str_Stream(Sample_Input);
                if(Str_Stream >> temp_Variable){
                    Function_Status = 1;
                    return(temp_Variable);
                }
                else{
                    Function_Status = 2;
                    cerr << "| Error | Non-Double value detected.\n";
                    return(5);
                }
            }
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

        string Generate_Random_Key(int Key_Length){
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

// Chose Persistant Storage Methods instead of dynamically allocated for absolute control over the flow, execution, exception handling, and other features of the program.
class Database_Management : public Utility_Functions
{
    private:
        Utility_Functions Util_Func;
        const string    Account_Info_file = "Account_Info.txt";
        const string    Account_Trans_file = "Account_Transactions.txt";
    

    protected:
        int Account_Count(){
            string              Data_line;
            string              Data_segment;
            string              Acc_Data_Field = "Acc_Create_Num";
            int                 Line_Count;
            optional<string>    current_Acc_Data;
            // Vector used to contain a single account worth of data.
            vector<string>      Acc_Data;
            // ifstream Input_File creates a stream object, and attempts to open "Account_Info.txt"
            ifstream            Input_File(Account_Info_file);

            Line_Count = 0;
            if(Input_File.is_open()){
                while(getline(Input_File, Data_line)){

                    Line_Count++;
                }
                Input_File.close();
            }
            else{ 
                cerr << "\n| ERROR | Unable to open 'Account_Info.txt'.";
            }
            return(Line_Count);
        }

        // View Account Info is used to gather specific data from the Account_Info Database, and return a specific number and type of outputs.
        vector<string> View_Account_Info(int target_Vector_Field, string target_Data_Value){
            // Variable Initialization
            string              Data_line;
            string              Data_segment;
            string              Acc_Data_Field;
            string              Acc_Data_Value = "";
            // Value_Target variable used to control the flow of the function, given a specific type and length of the target_Data_Value.
            int                 Value_Target;
            // Function_Status is used to control which values are removed, used in conjunction with Data_Restriction.
            int                 Function_Status = 0;
            // Data Restriciton Variable controls what data is returned within the vector, changing to 2-3 different values to represent Basic Info(0), Protected Info(1), and Processing Info(2)
            int                 Data_Restriction = 0;
            int                 Account_Count_Val = 0;
            

            optional<string>    current_Acc_Data;
            // Vector used to contain multiple different accounts worth of data.
            //vector<vector<string>> m_Acc_Data;
            // Vector used to contain a single account worth of data.
            vector<string>      Acc_Data;
            vector<string>      Acc_Data_final;
            // ifstream Input_File creates a stream object, and attempts to open "Account_Info.txt"
            ifstream            Input_File(Account_Info_file);

            // Length check of second parameter, to provide multi-usability of the function.
            Value_Target = target_Data_Value.length();
            //cout << "\nValue_Target (Length): " << Value_Target << "\n"; // USED FOR DEBUG
            if(Value_Target == 1){
                // Single value within Data Value likely executing a command that counts the amount of a specific data field.
                Acc_Data_Value = "1 CHAR";
            }
            else if(Value_Target == 4){
                // Value length of 4 is equal to Birthyear or PIN_Num.
                Acc_Data_Value = "4 CHAR";
            }
            else if(Value_Target == 8){
                // Value length of 8 is equal to a Recovery Key get process.
                Acc_Data_Value = "8 CHAR";
            }
            else if(Value_Target == 10){
                // Value length of 10 is equal to an Account Number.
                Acc_Data_Value = "10 CHAR";
                //cout << "\n10 CHAR!\n";  // USED FOR DEBUG
            }
            else{
                cerr << "\n| ERROR | Data Value out of range of possible parameters.\n";
            }
            //cout << "\n Acc_Data_Value = " << Acc_Data_Value << "\n Value Target = " << Value_Target << "\n"; // USED FOR DEBUG

            // Identifiers used to convert the short-hand target field to the string identifiers that is used within the txt document, used to specify actions for a desired vector/data field.
            if(target_Vector_Field == 1){
                Acc_Data_Field = "Acc_Create_Num";
                // If statement used to describe the behavior of the function, given a specfic target_Data_value.
                if(Acc_Data_Value == "1 CHAR"){
                    // target_Data_Value being 0 within the parameters of the function, with the Acc_Create_Num Field being selected, will retrieve the number of accounts within the list(used for awarding the n'th customer).
                    //Acc_Data_Value = "Acc_Create_Num";
                    //Function_Status = 1;
                    //MOVED TO SEPERATE FUNCTION
                }
                else { cerr << "\nFailed Execution of getting count of accounts.\n"; }
            }
            else if(target_Vector_Field == 2){
                Acc_Data_Field = "Acc_Num";
                //Function_Status = 2;
                // If statement used to describe the behavior of the function, given a specfic target_Data_value.
                //if((processed_Data_Value >= (Acc_Num_Min_Value)) && (processed_Data_Value <= (Acc_Num_Max_Value))){
                    // target_Data_Value being equal to a possibly valid account number, will check all lines of data within the database file, to check for an account matching the input value (Used for making sure duplicates don't exist).
                //}
                //else{ cerr << "| ERROR | Account out of range"; }
                if(Acc_Data_Value == "10 CHAR"){
                    Acc_Data_Value = "Acc_Num";
                }
                else{ cerr << "\n| ERROR | Account number parameter not valid.\n"; }
            }
            else if(target_Vector_Field == 3){
                Acc_Data_Field = "Acc_Name";
                //Function_Status = 3;
                // No current Use
            }
            else if(target_Vector_Field == 4){
                Acc_Data_Field = "Acc_Birthyear";
                // No current Use
            }
            else if(target_Vector_Field == 5){
                // RECOVERY KEY, Only for use with Account recovery methods. On is output to compare customer given value to value within database.
                Acc_Data_Field = "Acc_Rec_Key";
                // If statement used to describe the behavior of the function, given a specfic target_Data_value.
                //if((processed_Data_Value >= (Rec_Key_Min_Value)) && (processed_Data_Value <= (Rec_Key_Max_Value))){
                    // target_Data_Value being equal to a possibly valid Account Recovery Key, will check all lines of data within the database file, to check for an account matching the recovery key, will result in the output of a vector containing only the Recovery_Key and Acc_Num.

                //}
                if(Acc_Data_Value == "8 CHAR"){
                    Data_Restriction = 1;
                }
                else{ cerr << "\n| ERROR | Account out of range\n"; }
                

            }
            else if(target_Vector_Field == 6){
                
                // Only output data if checking that a specific account numbers' pin number is equal to that of what is in the database.
                // Acc_Data_Field = "Acc_PIN_Num";
                // If statement used to describe the behavior of the function, given a specfic target_Data_value.
                //if(processed_Data_Value == 0){

                //}
                //else{ cerr << "\nPIN Numbers cannot be viewed after becoming the active PIN for an account. If your account needs to be recovered, pick that option within the login menu.\n"; }
                if(Acc_Data_Value == "10 CHAR"){
                    Acc_Data_Field = "Acc_Num";
                    Data_Restriction = 2;
                    //cout << "Restriction Set to 2";  // USED FOR DEBUG
                }
                else{ cerr << "\n| ERROR | Gathering of PIN not Successful.\n"; }
            }
            else if(target_Vector_Field == 7){
                
                // Only output data if checking that a specific account numbers' pin number is equal to that of what is in the database.
                // Acc_Data_Field = "Acc_PIN_Num";
                // If statement used to describe the behavior of the function, given a specfic target_Data_value.
                //if(processed_Data_Value == 0){

                //}
                //else{ cerr << "\nPIN Numbers cannot be viewed after becoming the active PIN for an account. If your account needs to be recovered, pick that option within the login menu.\n"; }
                if(Acc_Data_Value == "10 CHAR"){
                    Acc_Data_Field = "Acc_Num";
                    Account_Count_Val = -1;
                    //cout << "Restriction Set to 2";  // USED FOR DEBUG
                }
                else{ cerr << "\n| ERROR | Gathering of PIN not Successful.\n"; }
            }
            else if(target_Vector_Field == 0){
                // All basic values will be displayed within the output variable
                // If statement used to describe the behavior of the function, given a specfic target_Data_value.
                //if((processed_Data_Value >= (Acc_Num_Min_Value)) && (processed_Data_Value <= (Acc_Num_Max_Value))){
                    // target_Data_value being equal to a valid account number within the database will result in the output of the general information of an account.

                //}
                if(Acc_Data_Value == "10 CHAR"){
                    // Account Lookup method used with an account number to output general info.
                    Acc_Data_Field = "Acc_Num";
                    Data_Restriction = 0;
                    cout << "\nTARGET SUCCESS";
                }
                else{ cerr << "\nNo valid input for General Account lookup.\n"; }
            }
            else{
                //cerr << "\n| ERROR | Invalid Target Data Field, or out of valid range: \n" << target_Vector_Field << ".\n"; // USED FOR DEBUG
                // Do nothing, Line does not contain target data, continue.
            }

            if(Input_File.is_open()){
                while(getline(Input_File, Data_line)){
                    // Process of data within a string stream
                    stringstream Str_Stream(Data_line);
                    Acc_Data.clear();
                    while(getline(Str_Stream, Data_segment, ',')){
                        // Trims the container blocks (,) used to seperate the data of the accounts. Output is more suitable for processing within code.
                        Data_segment.erase(0, Data_segment.find_first_not_of(" "));
                        Data_segment.erase((Data_segment.find_last_not_of(" ") + 1));
                        // Trims the container blocks ([ and ]) used to hold data of the account, 
                        if((Data_segment.front() == '[') && (Data_segment.back() == ']')){
                            Data_segment = Data_segment.substr(1, (Data_segment.length() - 2));
                            Acc_Data.push_back(Data_segment);
                        }
                        else{
                        // Append 
                        //cout << "Append1"; // USED FOR DEBUG
                        Acc_Data.push_back(Data_segment);
                        }
                    }
                    for(size_t i = 0; i < Acc_Data.size(); ++ i){
                        //cout << "FOR LOOP" << i << "\n"; // USED FOR DEBUG
                        if((Acc_Data[i]) == Acc_Data_Field){
                            if(i + 1 < Acc_Data.size()){
                                //cout << "\nEnter1"; // USED FOR DEBUG
                                current_Acc_Data = Acc_Data[(i + 1)];
                                if (current_Acc_Data.has_value() && (current_Acc_Data.value() == target_Data_Value)){ 
                                    //cout << "\nEnter2;"; // USED FOR DEBUG
                                    
                                    if(Data_Restriction == 0){
                                        // Acc_Data_final will only include the data fields perscribed by the data restriction status. (Basic Info) [includes Acc_Num, Acc_Name, Acc_Birthyear, and Acc_Num]
                                        //cout << "\nRestriction 1 Detected"; // USED FOR DEBUG
                                        Acc_Data_final.resize(6);
                                        Acc_Data_final[0] = (Acc_Data[2]);
                                        Acc_Data_final[1] = (Acc_Data[3]);
                                        Acc_Data_final[2] = (Acc_Data[4]);
                                        Acc_Data_final[3] = (Acc_Data[5]);
                                        Acc_Data_final[4] = (Acc_Data[6]);
                                        Acc_Data_final[5] = (Acc_Data[7]);
                                        return(Acc_Data_final);
                                    }
                                    else if(Data_Restriction == 1){
                                        //cout << "\nRestriction 2 Detected"; // USED FOR DEBUG
                                        //string temp_var;
                                        // Acc_Data_final will only include the data fields perscribed by the data restriction status. (Protected Info) [includes Acc_Num and Acc_Rec_Key]
                                        //temp_var = ((Acc_Data[2]) + (Acc_Data[3]) + );
                                        Acc_Data_final.resize(4);
                                        Acc_Data_final[0] = (Acc_Data[2]);
                                        Acc_Data_final[1] = (Acc_Data[3]);
                                        Acc_Data_final[2] = (Acc_Data[8]);
                                        Acc_Data_final[3] = (Acc_Data[9]);
                                        return(Acc_Data_final);
                                    }
                                    else if(Data_Restriction == 2){
                                        //cout << "\nRestriction 2 Output Attempted"; // USED FOR DEBUG
                                        // Acc_Data_final will only include the data fields perscribed by the data restriction status. (Processing Info) [includes Acc_Num and Acc_PIN_Num]
                                        Acc_Data_final.resize(4);
                                        Acc_Data_final[0] = (Acc_Data[2]);
                                        Acc_Data_final[1] = (Acc_Data[3]);
                                        Acc_Data_final[2] = (Acc_Data[10]);
                                        Acc_Data_final[3] = (Acc_Data[11]);
                                        return(Acc_Data_final);
                                    }
                                    else if(Account_Count_Val == (-1)){
                                        Acc_Data_final.resize(4);
                                        Acc_Data_final[0] = (Acc_Data[0]);
                                        Acc_Data_final[1] = (Acc_Data[1]);
                                        Acc_Data_final[2] = (Acc_Data[2]);
                                        Acc_Data_final[3] = (Acc_Data[3]);
                                        return(Acc_Data_final);
                                    }
                                    Input_File.close(); 
                                }
                                else{
                                    // Do nothing, as this data does not contain the desired value.
                                    //cerr << "\nValue not found within line.\n"; // USED FOR DEBUG
                                }
                            }
                        }
                    }
                }
                Input_File.close();
            }
            else{ 
                cerr << "\n| ERROR | Unable to open 'Account_Info.txt'.";
            }
            return {};
        }

        void Append_Account_Info(string Acc_Num, string Acc_Name, string Acc_Birthyear, string Acc_Rec_Key, string Acc_PIN_Num){
            // Variable Initialization
            int             Acc_Create_Num;
            string          Format_String;
            // String Steam type being used to create a string within memory, and then formatting the entire built list into a single string.
            ostringstream   Str_Stream;
            /* Output_File used to declare the target file name. If this banking system were implemented into a real world scenario, there would likely need to be multiple files which were able to transfer data back and forth, 
            to minimize the time needed to scan each file for specific data. For the purposes of this project however, one single file for each different data structure will satisfy the needs. Uses Append mode to open the file, to prevent overwritting.*/
            ofstream        Output_File(Account_Info_file, ios::app);

            Acc_Create_Num = (Account_Count() + 1);
            

            Str_Stream << "Acc_Create_Num, [" << Acc_Create_Num << "], Acc_Num, [" << Acc_Num << "], Acc_Name, [" << Acc_Name << "], Acc_Birthyear, [" << Acc_Birthyear << "], Acc_Rec_Key, [" << Acc_Rec_Key << "], Acc_PIN_Num, [" << Acc_PIN_Num << "]";
            Format_String = Str_Stream.str();

            
            if(Output_File.is_open()){
                Output_File << Format_String << "\n";
                Output_File.close();
                cout << "\nAccount Data Successfully Output to Account Database! (Account_Info.txt)\n";
            }
            else { cerr << "\nData Export Failed!\n"; }

        }
        
        vector<string> View_Balance_Info(string target_Acc_Num){
            // Variable Initialization
            string              Data_line;
            string              Data_segment;
            string              Acc_Data_Field;
            string              Acc_Data_Value = "";
            // Value_Target variable used to control the flow of the function, given a specific type and length of the target_Data_Value.
            int                 Value_Target;
            // Function_Status is used to control which values are removed, used in conjunction with Data_Restriction.
            int                 Function_Status = 0;
            // Data Restriciton Variable controls what data is returned within the vector, changing to 2-3 different values to represent Basic Info(0), Protected Info(1), and Processing Info(2)
            int                 Data_Restriction = 0;
            // Vector used to contain a single account worth of data.
            vector<string>      Acc_Data;
            vector<string>      Acc_Data_final;
            // ifstream Input_File creates a stream object, and attempts to open "Account_Info.txt"
            ifstream            Input_File(Account_Trans_file);

            if(Input_File.is_open()){
                while(getline(Input_File, Data_line)){
                    // Checks that data is of value [A#] and not [T#]
                    if(Data_line.find("[A1]") == 0){
                        // Process of data within a string stream
                        stringstream Str_Stream(Data_line);
                        Acc_Data.clear();
                        while(getline(Str_Stream, Data_segment, ',')){
                            // Trims the container blocks (,) used to seperate the data of the accounts. Output is more suitable for processing within code.
                            Data_segment.erase(0, Data_segment.find_first_not_of(" "));
                            Data_segment.erase((Data_segment.find_last_not_of(" ") + 1));
                            // Trims the container blocks ([ and ]) used to hold data of the account, 
                            if((Data_segment.front() == '[') && (Data_segment.back() == ']')){
                                Data_segment = Data_segment.substr(1, (Data_segment.length() - 2));
                                
                            }
                            Acc_Data.push_back(Data_segment);
                        }
                        for(size_t i = 0; i < Acc_Data.size(); ++ i){
                            //cout << "FOR LOOP" << i << "\n"; // USED FOR DEBUG
                            if((Acc_Data[i] == "Acc_Num") && ((i + 1) < Acc_Data.size())){
                                //cout << "\nEnter1"; // USED FOR DEBUG
                                if (Acc_Data[i + 1] == target_Acc_Num){ 
                                    //cout << "\nEnter2;"; // USED FOR DEBUG
                                    Acc_Data_final.resize(2);
                                    Acc_Data_final[0] = (Acc_Data[2]);
                                    Acc_Data_final[1] = (Acc_Data[4]);
                                    // ACC_Data_final includes Acc_Num and Acc_Balance
                                    Input_File.close(); 
                                    return(Acc_Data_final);
                                }
                            Input_File.close();
                            }
                        }
                    }
                }
                Input_File.close();
            }
            else{ 
                cerr << "\n| ERROR | Unable to open 'Account_Info.txt'.";
            }
            return {};
        }

        void Append_Balance_Info(string Acc_Num, string Acc_Balance){
            // Variable Initialization

            int             Trans_Data_Iteration;
            string          Trans_Iteration_input;
            string          Format_String;
            string          Iteration_Identifier;
            vector<string>  Account_Iteration_Data;
            // String Steam type being used to create a string within memory, and then formatting the entire built list into a single string.
            ostringstream   Str_Stream;
            /* Output_File used to declare the target file name. If this banking system were implemented into a real world scenario, there would likely need to be multiple files which were able to transfer data back and forth, 
            to minimize the time needed to scan each file for specific data. For the purposes of this project however, one single file for each different data structure will satisfy the needs. Uses Append mode to open the file, to prevent overwritting.*/
            ofstream        Output_File(Account_Trans_file, ios::app);

            Account_Iteration_Data = Database_Management::View_Account_Info(7, "3822124730");
            Trans_Iteration_input = Account_Iteration_Data[1];
            Trans_Data_Iteration = (Util_Func.Str_to_Int(Trans_Iteration_input) + 1);
            

            Str_Stream << "[" << Iteration_Identifier << "], Acc_Num, [" << Acc_Num << "], Acc_Balance, [" << Acc_Balance << "]";
            Format_String = Str_Stream.str();

            
            if(Output_File.is_open()){
                Output_File << Format_String << "\n";
                Output_File.close();
                cout << "\nAccount Data Successfully Output to Account Database! (Account_Info.txt)\n";
            }
            else { cerr << "\nData Export Failed!\n"; }

        }
};

// Account Management | Primary Class that handles account information such as creating, deleting, managing, merging, and other operations.
class Account_Management : public Database_Management
{
    private:
        Utility_Functions Util_Func;

    protected:
        // Account Creation Number | Used by the bank for internal use, to identify how many members are active at the bank, and to award the Xth customer for chosing this bank.
        string Acc_Create_Num;
        // Account Number | Personal Identifier
        string Acc_Num;
        // Account Name | Personal Identifier
        string Acc_Name;    
        // Account Birth Year | Personal Identifier
        string Acc_Birthyear;
        // Account Recovery Key | Personal/Recovery Identifier
        string Acc_Rec_Key;
        // Account PIN Number | Personal Identifier
        string Acc_PIN_Num;
        // Account Balance | Personal/Account Information
        //double Acc_Balance;


        // Interger Array for essential account information, or identifiers, using a fixed set of data. The array consists of 4 values, given the removal of unnessesary information, the customer name and balance, and adding an additional 'member number', assigned by the Bank for internal use.
        //int E_Account_Info[4];

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
            Acc_Create_Num.clear();
            Acc_Num.clear();
            Acc_Name.clear();  
            Acc_Birthyear.clear();
            Acc_Rec_Key.clear();
            Acc_PIN_Num.clear();
            //Acc_Balance = 0;

            //int E_Account_Info[4] = {, Acc_Num, Acc_Birthyear, Acc_Rec_Key};
            
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
                    if(Util_Func.is_Int(User_Input)){
                        Acc_Birthyear = User_Input;
                        //cout << "\nYear is an int!"; //USED FOR DEBUG
                        cout << "\nThe current year is " << Util_Func.Current_Year_int << ".\n";

                        Acc_Birthage = ((Util_Func.Current_Year_int)-(Util_Func.Str_to_Int(Acc_Birthyear)));
                        cout << Acc_Name << " is approximately " << Acc_Birthage << " years old.\n";
                        if (Acc_Birthage == 0){
                            cerr << "\n| Error | Empty or Invalid input.";
                            return(3);
                        }
                        else if((Acc_Birthage < 2 || Acc_Birthage > 130)){
                            cerr << "\n| Error | Birthyear out of realistic range.";
                            return(3);
                        }
                        Util_Func.Function_Status = 0;
                        return(4);
                        //cout << "SUCCESS2!"; // USED FOR DEBUG
                    }
                    else if(Util_Func.Function_Status == 2){ return(3); }
                    else{
                        cerr << "User Input is not an integer!";
                        return(3);
                    }

                }
                else{ return(3); }

            return(0);
        }
        int Acc_Create_Step4(){
            // Initialize Variables
            
            // Process
            // Random_Recovery_Key variable being set to the output of the randomly generated, 8 digit long key.
            Acc_Rec_Key = Util_Func.Generate_Random_Key(8);
            cout << "\nYour randomized account recovery key is: "<< Acc_Rec_Key << ". \nThis 'Recovery Key' is the backup key you will need to provide; if you lose the passcode you are about to enter, and need to reset it, or otherwise need to recover your account.\n";

            return(5);
        }

        int Acc_Create_Step5(){
            //Initizlize Variables
            string User_Input = "";

            // User Input
            cout << "\nPlease input a four digit PIN (Personal Identification Number), you will need to remember this for preforming transactions, or general access to your account. \nEnter the four (4) digit code now: ";
            cin.clear();
            User_Input.clear();
            if(getline(cin, User_Input)){
                // Processing & Error Handling
                // Calling the is_Int 'Utility' Function to provide error handling for the user input, unless the Input is successful, the Acc_Create_Step5() function will restart with cleared values.
                if(Util_Func.is_Int(User_Input)){
                    if(User_Input.length() == 4){
                        Acc_PIN_Num = User_Input;
                        return(6);
                    }
                    else{
                        cerr << "| ERROR | Entered PIN Number, '" << User_Input << "', is not four in length, as required.\n\n";
                        return(5);
                    }
                    Util_Func.Function_Status = 0;
                }
                else
                { 
                    cerr << "\n| ERROR! | No choice selected, or invalid input: '" << User_Input << "'. \nType a set of four numbers, each of them being between between 0 and 9! (Ex. '1234')\nResetting PIN Input...\n";
                    Acc_PIN_Num.clear();
                    cin.clear();
                    User_Input.clear();
                    return(5);
                }
            }
            else{ 
                cerr << "\n| Unknown Input Error within getline() function |\n";
                cin.clear();
                User_Input.clear(); 
                return(5);
            }

            return(5);
        }

        // Acc_Create_Step6 used to check that no accounts exist with duplicate essential information (only the account number currently), then assigns the Acc_Num to the data set.
        int Acc_Create_Step6(){
            // Variable Initialization

            string Acc_Num_temp;
            string Acc_Num_final;
            
            Acc_Num_final.clear();
            while(Acc_Num_final.empty()){
                Acc_Num_temp = (Util_Func.Generate_Random_Key(10));

                if((Database_Management::View_Account_Info(2, Acc_Num_temp).empty())){
                    // No Account Found with the specified Account Number
                    Acc_Num_final = Acc_Num_temp;
                    cout << "\n Your Account Number is what you will use to make transactions, and recover your account, this is a randomly generated value, write this down: '" << Acc_Num_final << "'\n";
                }
                else{
                    // Account found with account number, do nothing, and continue to check for an avaliable number.
                }
                
            }
            Database_Management::Append_Account_Info(Acc_Num_final, Acc_Name, Acc_Birthyear, Acc_Rec_Key, Acc_PIN_Num);
            //cout << "\n Function Complete.\n"; // USED FOR DEBUG

            return(7);
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
            while((Step_Status == 6)){
                Step_Status = Acc_Create_Step6();
            }
            // Step Status 7 indicates that the account creation process is complete.
            if(Step_Status == 7){
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
    private:
        Utility_Functions Util_Func;
    public:
    // Retrieve Balance Function used to preform a retrieval of the specified account's balance, given the account number. At this point, the user has already validated who they are.
    double Retrieve_Balance(string Acc_Num){
            vector<string> Acc_Info;
            Acc_Info = Database_Management::View_Balance_Info(Acc_Num);
            if(!(Acc_Info.empty())){
                //cout << "\nBalance Output for account '" << Acc_Num << "' : '" << Acc_Info[1] << "'.\n"; // USED FOR DEBUG
                if(Acc_Num == Acc_Info[0]){
                    return(Util_Func.Str_to_Double(Acc_Info[1]));
                }
                else{
                    cerr << "\n| ERROR | Balance Retrieval failed.\n";
                    return(-1);
                }
            }
            else{
                cerr << "\n| ERROR | Balance Retrieval Failed!\n";
            }

        return(-1);
    }
    // Retrieve_Transaction function is used to get the details of a specific transaction, given a transaction ID, and an account number involved with said transaction.
    /*double Retrieve_Transaction(string Trans_Number, string Acc_Num){
    
        return(0);
    }*/
};

// User Authentication | Validates Account Information, Authenticates Users into accounts, and Verifies Identity using recovery key and other methods.
class User_Authentication : public Transaction_History
{
    private:

    public:

        int Acc_Login(){
            // Mistake count variable is used to provide a tracking of mistakes for use in the security process for accounts. Can be implemented in future, not necessary for project, would be for real world.
            //int Mistake_Count = 0;
            string User_Input;
            string User_Input_segment;
            string Acc_Num; 
            string Acc_PIN_Num;
            string Acc_Balance;
            vector<string> Acc_Info;
            vector<string> User_Input_final;
            Transaction_History Trans_Hist;
            Utility_Functions Util_Func;

            cout << "\n| Account Login Menu | - Please enter the Account Number associated with the account you wish to login to, and the PIN Number associated with that account. \nEnter this as a comma seprated list such as (0000000000, 1234).\nEnter the information now: ";

            // User Input
            cin.clear();
            User_Input.clear();
            if(getline(cin, User_Input)){
                stringstream Str_Stream(User_Input);

                //if(Utility_Functions::is_Int(User_Input)){
                    //Acc_Num = User_Input.find_first_not_of(",");
                    //cout << Acc_Num;
                //}
                while(getline(Str_Stream, User_Input_segment, ',')){
                    User_Input_segment = User_Input_segment.substr((User_Input_segment.find_first_not_of(' ')), ((User_Input_segment.find_last_not_of(' ')) - (User_Input_segment.find_first_not_of(' ')) + 1));
                    User_Input_final.push_back(User_Input_segment);
                    //cout << "\nsegment\n"; // USED FOR DEBUG
                }
                if(User_Input_final.size() == 2){
                    Acc_Num = User_Input_final[0];
                    Acc_PIN_Num = User_Input_final[1];
                    //cout << "Acc_Num: '" << Acc_Num << "' Acc_PIN_Num: '" << Acc_PIN_Num << "'\n"; // USED FOR DEBUG
                    if((Util_Func.is_Int(Acc_Num)) && (Util_Func.is_Int(Acc_PIN_Num))){
                        Acc_Info = Database_Management::View_Account_Info(6, Acc_Num);
                        if(!(Acc_Info.empty())){
                            //cout << "Account Info: '" << (Acc_Info[1]) << "' and '" << (Acc_Info[3]) << "'\n"; // USED FOR DEBUG
                            // if statement will execute under the condition that an account is found with the input value.
                            if((Acc_Info[3]) == (Acc_PIN_Num)){
                                // Login Successful! | ACCOUNT MENU |
                                cout << "\nLogin Successful!";
                                Acc_Balance = to_string(Trans_Hist.Retrieve_Balance(Acc_Num));
                                cout << "\nYou currently have an avalaible balance of : '$" << Acc_Balance << "'";

                                return(2);
                            }
                        }
                        else
                        {
                            cerr << "\nUnsuccessful Login, PIN Incorrect!\n";
                        }
                    }
                    else{
                        cerr << "\n| ERROR | Input value is not of the requried type (integer).\n";
                    }
                }
                else{
                    cerr << "\n| ERROR | User Input Invalid, too many parts to the list!\n";
                    return(1);
                }

            }
            else{ 
                cerr << "\n| ERROR | User Input Failed.\n";
                return(1); 
            }

            return(1);
        }

};

// This 'Banking_Interface' gives the options of Accessing an existing account, creating an entirely new account, or recovering an account from a key that is assigned to a profile.
class Banking_Interface : public Transaction_History
{
    private:
        string User_Input;
        Utility_Functions Util_Func;
        
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
                if(Util_Func.is_Int(User_Input)){
                    User_Action = Util_Func.Str_to_Int(User_Input);
                    Util_Func.Function_Status = 0;
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

            User_Authentication User_Auth;

            // User Action 1 | Access Account
            while(User_Action == 1){
                temp_Var = User_Auth.Acc_Login();
                //cerr << "\n temp_var: " << temp_Var << "\n"; // USED FOR DEBUG
                if(temp_Var == 2){
                    //Successful login/balance output.
                    return(3);
                }
                else{
                    cerr << "\nInvalid output, resetting login.\n";
                }

            }
            // User Action 2 | Access Account
            while(User_Action == 2){
                temp_Var = Account_Management::Acc_Create();
                if(temp_Var == 1){
                    cout << "\nAccount Creation Successful. Thank you, " << Acc_Name << ".";
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

    //Acc_Manage.Acc_Create_Step6();
    //double temp; // USED FOR DEBUG
    //temp = Trans_Hist.Retrieve_Balance("3822124730"); // USED FOR DEBUG
    //cout << "\n" << temp << "\n"; // USED FOR DEBUG

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