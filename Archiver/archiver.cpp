#include <iostream>
#include <fstream>
#include <string>

std::string SpacesRemove(std::string str){
    for(int i = 0; i < str.length(); ++i){
        if(str[i] == ' ' && str[i + 1] == ' '){
            str.erase(str.begin() + i);
            if(i != 0){
                i = i - 1;
            }
        }
    }
    return str;
}

int main(){
    std::string text, filename;
    int counter;
    
    std::cout << "Enter file name (inside this folder): " << std::endl;
    std::cin >> filename;

    std::ifstream File(filename);
    std::ofstream ResultFile("result.txt");
    
    while(std::getline(File, text)){
        if(text.substr(0, 8) == "#include"){
            ResultFile << SpacesRemove(text) << std::endl;
        }
        else{
            ResultFile << SpacesRemove(text);
        }
    }
    ResultFile.close();
    File.close();

    return 0;
}