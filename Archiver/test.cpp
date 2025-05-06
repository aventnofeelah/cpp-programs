#include <iostream>
#include <string>

int main(){
    int num;
    std::cout << "Enter number from 0 to 100" << std::endl;
    std::cin >> num;

    if(num < 0 || num > 100){
        std::cout << "Invalid number" << std::endl;
    }
    else{
        for(int iter = 0; iter < num; ++iter){
            std::cout << iter << std::endl;
        }
    }
    return 0;
}