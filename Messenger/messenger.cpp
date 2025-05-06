#include <iostream>
#include <string>
#include <fstream>
#include <chrono> 
#include <ctime>
#include <vector>
#include <limits>

class Messenger{
        private:
            std::string session;
            std::string username;
            std::string password;
        public:
            std::string session_generator(std::string name){
                std::srand(time(0));
                int randomNum = std::rand() % 10000;
                session = name + "_" + std::to_string(randomNum);
                std::cout << "Your session: " << session << std::endl; 
                return session;
            }
            std::string username_parser(std::string user){
                std::string username = "";
                for(int i = 0; i < user.length(); ++i){
                    if(user[i] == 'e' && user[i + 1] == ':' && user[i + 2] == ' '){
                        for(int j = i + 3; j < user.length(); ++j){
                            if(user[j] != ','){
                                username += user[j];
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                }
                return username;
            }
            std::string password_parser(std::string user){
                std::string parsed_pw = "";
                for(int i = 0; i < user.length(); ++i){
                    if(user[i] == 'r' && user[i + 1] == 'd' && user[i + 2] == ':' && user[i + 3] == ' '){
                        for(int j = i + 4; j < user.length(); ++j){
                            if(user[j] != ','){
                                parsed_pw += user[j];
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    }
                }
                return parsed_pw;
            }
            bool password_validator(std::string password){
                std::string not_allowed_symbols = "!@#$%^&*()=+,./<>?";
                bool is_valid = true;
                for(int i = 0; i < password.length(); ++i){
                    for(int j = 0; j < not_allowed_symbols.length(); ++j){
                        if(not_allowed_symbols[j] == password[i]){
                            is_valid = false;
                        }   
                    }
                }
                return is_valid;
            }
            std::string password_encrypt(std::string pw){
                std::string hashed_pw = "";
                std::string alph = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                for(int i = 0; i < pw.length(); ++i){
                    int c = 0;
                    for(int j = 0; j < alph.length(); ++j){
                        if(pw[i] == alph[j]){
                            hashed_pw += std::to_string(j) + ':';
                            ++c;
                        }
                    }
                    if(!c){
                        hashed_pw += pw[i];
                        hashed_pw += ':';
                    }
                }
                return hashed_pw;
                }
            std::string password_decrypt(std::string pw){
                std::string alph = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                std::string nums = "0123456789";
                std::string decrypted_pw = "";
                std::string temp = "";
                for(int i = 0; i < pw.length(); ++i){
                    if(pw[i] != ':'){
                        temp += pw[i];
                    }
                    else{
                        int c = 0;
                        for(int j = 0; j < temp.length(); ++j){
                            for(int k = 0; k < nums.length(); ++k){
                                if(temp[j] == nums[k]){
                                    ++c;
                                }
                            }
                        }
                        if(c != temp.length()){
                            decrypted_pw += temp;
                        }
                        else{
                            decrypted_pw += alph[stoi(temp)];
                        }
                        temp = "";
                    }
                }
                return decrypted_pw;
            }
            std::string get_last_id(){
                std::string id = "", temp;
                bool is_empty = true;
                std::ifstream ReadFile("users.txt");
                //check 1
                // std::getline(ReadFile, temp);
                // if(temp.empty()){
                //     id = "1";
                // }
                // else{
                //     is_empty = false;
                // }

                //check 2
                while(std::getline(ReadFile, temp)){
                    if(!temp.empty()){
                        is_empty = false;
                        break;
                    }
                }
                if(is_empty){
                    id = "1";
                }
                ReadFile.close();
                if(is_empty == false){
                    std::ifstream ReadFile("users.txt", std::ios::ate);
                    std::streampos file_size = ReadFile.tellg();
                    std::streamoff file_size_off = static_cast<std::streamoff>(file_size); 
                    std::string temp = "";
                    char ch;
                    for(std::streamoff i = file_size_off - 3; i >= 0; --i){ //3 beacuse there are can be \n in users.txt so tellg() will return 2
                        ReadFile.seekg(i);
                        ReadFile.get(ch);
                        if(ch != '\n' && i != file_size_off - 1){
                            temp = ch + temp;
                        }
                        else{break;}
                    }
                    for(int i = temp.find(' '); i < temp.length(); i++){
                        if(temp[i] != ','){
                            id += temp[i];
                        }
                        else{break;}
                    }
                    ReadFile.close();
                    id = std::to_string(stoi(id) + 1);
                }
                return id;
            }
            std::string regist_user(){
                while(true){
                    bool username_taken = false;
                    std::cout << "Enter username: " << std::endl;
                    std::cin >> username;
                    std::ifstream ReadFile("users.txt");
                    std::string temp;
                    while(std::getline(ReadFile, temp)){
                        if(username_parser(temp) == username){
                            std::cout << "Username is already taken" << std::endl;
                            username_taken = true;
                            break;
                        }
                    }
                    ReadFile.close();
                    if(username_taken == false){break;}
                }
                while(true){
                    std::cout << "Enter password: " << std::endl;
                    std::cin >> password;
                    if(password_validator(password)){
                        std::string encrypted_pw = password_encrypt(password);
                        std::string user_str = "id: " + get_last_id() + ", " + "username: " + username + ", " + "password: " + encrypted_pw + ", " + "messages: ";
                        std::ofstream AddToFile("users.txt", std::ios::app);
                        AddToFile << user_str << "\n";
                        AddToFile.close();
                        break;
                    }
                    else{
                        std::cout << "Password contains not allowed symbols." << std::endl;
                    }
                }
                return session_generator(username);
            }
            std::string login_user(){
                while(true){
                    std::string temp;
                    bool user_found, is_valid;
                    std::cout << "Enter username: " << std::endl;
                    std::cin >> username;
                    std::ifstream ReadFile("users.txt");
                    while(std::getline(ReadFile, temp)){
                        if(username_parser(temp) == username){
                            user_found = true;
                            break;
                        }
                    }
                    if(user_found){
                        while(true){
                            std::cout << "Enter password: " << std::endl;
                            std::cin >> password;
                            if(password != password_decrypt(password_parser(temp))){
                                std::cout << "Incorrect password" << std::endl;
                            }
                            else{
                                is_valid = true;
                                break;
                            }
                        }
                    }
                    else{
                        std::cout << "User not found" << std::endl;
                    }
                    if(is_valid){
                        break;
                    }
                    ReadFile.close();
                    }
                return session_generator(username);
            }
            void send_message(){
                std::string temp, message, curr_time, curr_user = "";
                std::vector<std::string> users_vec;
                bool user_found;
                if(session == ""){
                    std::cout << "Please sing up or log in" << std::endl;
                }
                else{
                    std::cout << "Enter receiver username: " << std::endl;
                    std::cin >> username;
                    std::ifstream ReadFile("users.txt");
                    while(std::getline(ReadFile, temp)){
                        if(username_parser(temp) == username){
                            user_found = true;
                            break;
                        }
                    }
                    ReadFile.close();
                    if(user_found){
                        std::cout << "Enter message: " << std::endl;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        std::getline(std::cin, message);
                        auto now = std::chrono::system_clock::now();
                        std::time_t t = std::chrono::system_clock::to_time_t(now);
                        std::tm* local_time = std::localtime(&t);
                        curr_time = std::to_string(local_time->tm_mday) + "-" + std::to_string(local_time->tm_mon + 1) + "-" + std::to_string(local_time->tm_year + 1900);
                        for(int i = 0; i < session.length(); ++i){
                            if(session[i] == '_'){
                                break;
                            }
                            else{
                                curr_user += session[i];
                            }
                        }
                        std::ifstream ReadFile("users.txt");
                        while(std::getline(ReadFile, temp)){
                            if(username_parser(temp) == username){
                                temp += curr_user + ": " + "{" + message + " : " + curr_time + "}" + "|";
                                users_vec.push_back(temp);
                            }
                            else{
                                users_vec.push_back(temp);
                            }
                        }
                        ReadFile.close();
                        std::ofstream Overwrite("users.txt", std::ios::trunc);
                        for(std::string x : users_vec){
                            Overwrite << x << "\n";
                        }
                        Overwrite.close();
                    }
                    else{
                        std::cout << "User not found" << std::endl;
                    }
                }
            }
            void show_messages(){
                if(session == ""){
                    std::cout << "Please sing up or log in" << std::endl;
                }
                else{
                    std::string temp, messages = "", curr_user = "";
                    for(int i = 0; i < session.length(); ++i){
                        if(session[i] == '_'){
                            break;
                        }
                        else{
                            curr_user += session[i];
                        }
                    }
                    std::cout << "Your messages: " << std::endl;
                    std::cout << "=======================================" << std::endl;
                    std::ifstream ReadFile("users.txt");
                    while(std::getline(ReadFile, temp)){
                        if(username_parser(temp) == curr_user){
                            for(int i = 0; i < temp.length(); ++i){
                                if(temp[i] == 's' && temp[i + 1] == ':' && temp[i + 2] == ' '){
                                    for(int j = i + 3; j < temp.length(); ++j){
                                        messages += temp[j];
                                    }
                                }
                            }
                        }
                    }
                    ReadFile.close();
                    for(int i = 0; i < messages.length(); ++i){
                        if(messages[i] != '|'){
                            std::cout << messages[i];
                        }
                        else if (messages[i] == '|' || i == messages.length() - 1){
                            std::cout << std::endl;
                        }
                    }
                    std::cout << "=======================================" << std::endl;
                } 
            }
    };

int main(){
    Messenger obj;
    int option, isRunning = 1;
    while(isRunning){
        std::cout << "Select option: " << std::endl;
        std::cout << "1.Sing up" << std::endl;
        std::cout << "2.Log in" << std::endl;
        std::cout << "3.Send message" << std::endl;
        std::cout << "4.Message box" << std::endl;
        std::cout << "5.Exit" << std::endl;
        std::cin >> option;
        switch(option){
            case 1:
                obj.regist_user();
                break;
            case 2:
                obj.login_user();
                break;
            case 3:
                obj.send_message();
                break;
            case 4:
                obj.show_messages();
                break;
            case 5:
                isRunning = 0;
                std::cout << "The program has stopped, restart the program to start over." << std::endl;
                break;
        }
    }
    return 0;
}


