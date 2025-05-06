#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <limits>
#include <cstring>  
#include <cerrno>

using namespace std;

int main(){
    class FilesApp{
    private:
        int answer;
        string file_name;
        string text;
        string file_path;
        string file_ready;

    public: 
        void exitFunc(){
            exit(0);
        }

        void deleteFunc(){
            cout << "Enter file name or file path to delete: " << endl;
            char file[256];
            cin >> file;
            int result = remove(file);
            if(result == 0){
                cout << "File deleted." << endl;
            }
            else{
                cerr << "Error deleting file: " << strerror(errno) << endl;
            }
            startFunc();
        }

        void readFunc(){
            cout << "Enter file name or file path you want open: " << endl;
            cin >> file_name;
            string file_text;
            ifstream MyReadFile(file_name);
            if(MyReadFile.fail()){
                cerr << "Error opening file:" << strerror(errno) << endl;
            }
            else{
                while (getline(MyReadFile, file_text)) {
                    cout << file_text << endl;
                }
            }
            MyReadFile.close();
            startFunc();
        }

        void writeFunc(){
            cout << "Write file name or file path you want to write to: " << endl;
            cin >> file_name;
            ofstream MyFile(file_name);
            if(MyFile.fail()){
                cerr << "Error opening file:" << strerror(errno) << endl;
            }
            else{
                cout << "Enter text and end it with ';': " << endl;
                getline(cin, text, ';');
                MyFile << text;
            }
            MyFile.close();
            startFunc();
        }

        void createFunc(){
            cout << "Enter file path with slash at the end: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            getline(cin, file_path);
            cout << "Enter file name with extension: " << endl;
            cin >> file_name;
            file_ready = file_path + file_name;
            ofstream outfile(file_ready);
            if(outfile.fail()){
                cerr << "Error creating file: " << strerror(errno) << endl;
            }
            else{
                cout << "File created." << endl;
                cout << file_ready << endl;
            }
            outfile.close();
            startFunc();
        };

        void startFunc(){
            cout << "Choose what you want to do: " << endl;
            cout << "1.Create file." << endl;
            cout << "2.Write to file." << endl;
            cout << "3.Read file." << endl;
            cout << "4.Delete file." << endl;
            cout << "0.Exit." << endl;
            cin >> answer;
            switch(answer){
                case 0:
                    exitFunc();
                    break;
                case 1:
                    createFunc();
                    break;   
                case 2:
                    writeFunc();
                    break; 
                case 3:
                    readFunc();
                    break; 
                case 4:
                    deleteFunc();
                    break;
            }
        }
    };
    FilesApp object;
    object.startFunc();

    return 0;
}