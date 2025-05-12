#include <iostream>
#include <string>
#include <windows.h>
#include <map>
#include <cstring>

class Core{
    private:
        size_t bytes;
        int block_num = 0;
        std::map <std::string, char*> blocks;
        std::map <std::string, size_t> blocks_size;
    public:
        std::pair<size_t, size_t> ram_info(){
            MEMORYSTATUSEX statex;
            statex.dwLength = sizeof(statex);
            GlobalMemoryStatusEx(&statex);
            size_t available = static_cast<size_t>(statex.ullAvailPhys);
            size_t total = static_cast<size_t>(statex.ullTotalPhys);
            return {available, total};
        }
        void show_blocks(){
            if(blocks.empty()){
                std::cerr << "There is no memory blocks." << std::endl;
            }
            else{
                for(const auto& pair : blocks){
                    std::cout << "Block name: " << pair.first << " " << "Address: " << static_cast<void*>(pair.second) << " " << "Memory used: " << blocks_size[pair.first] << " Bytes: " << std::endl; 
                }
            }
        }
        void create_block(){
            std::cout << "Enter amount of memory in bytes for block: " << std::endl;
            std::cin >> bytes;
            if(bytes > ram_info().first / 4){
                std::cerr << "Do not user more than 1/4 of available memory." << std::endl;
            }
            else if(bytes <= 0){
                std::cerr << "Invalid number of bytes." << std::endl;
            }
            else{
                std::string block_name = "block_" + std::to_string(block_num);
                char* block = new char[bytes];
                blocks[block_name] = block;
                blocks_size[block_name] = bytes;
                std::memset(blocks[block_name], 0, blocks_size[block_name]);
                block_num++;
            }
        }
        void delete_block(){
            std::string name;
            bool found = false;
            std::cout << "Enter block name for deletion: " << std::endl;
            std::cin >> name;
            for(const auto& pair : blocks){
                if(pair.first == name){
                    delete[] blocks[name];
                    blocks.erase(name);
                    blocks_size.erase(name);
                    found = true;
                    break;
                }
            }
            if(!found){
                std::cerr << "Could not find a block with this name." << std::endl;
            }
            
        }
        void show_block_content(){
            std::string name;
            bool found = false;
            std::cout << "Enter block name: " << std::endl;
            std::cin >> name;
            for(const auto& pair : blocks){
                if(pair.first == name){
                    for(size_t i = 0; i < blocks_size[name]; ++i){
                        std::cout << "Byte " << i << ": " << static_cast<int>(blocks[name][i]) << std::endl;
                    }
                    found = true;
                    break;
                }
            }
            if(!found){
                std::cerr << "Could not find a block with this name." << std::endl;
            }
        }
        void edit_block(){
            std::string name;
            size_t byte_num;
            bool found = false;
            char val;
            std::cout << "Enter block name for editing: " << std::endl;
            std::cin >> name;
            for(const auto& pair : blocks){
                if(pair.first == name){
                    found = true;
                    for(size_t i = 0; i < blocks_size[name]; ++i){
                        std::cout << "Byte " << i << ": " << static_cast<int>(blocks[name][i]) << std::endl;
                    }
                    break;
                }
            }
            if(!found){
                std::cerr << "Could not find a block with this name." << std::endl;
            }
            else{
                std::cout << "Block name: " << name << std::endl;
                for(size_t i = 0; i < blocks_size[name]; ++i){
                    std::cout << "Byte " << i << ": " << static_cast<int>(blocks[name][i]) << std::endl;
                }
                std::cout << "Choose byte to edit (number): " << std::endl;
                std::cin >> byte_num;
                if(byte_num > blocks_size[name] || byte_num < 0){
                    std::cerr << "Invalid byte number." << std::endl;
                }
                else{
                    std::cout << "Enter new value for Byte " << byte_num << ":" << std::endl;
                    std::cin >> val;
                    blocks[name][byte_num] = val;
                }
            }
        }
};

int main(){
    Core core;
    int option, isRunning = 1;
    std::pair<size_t, size_t> info = core.ram_info();
    size_t available = info.first;
    size_t total = info.second;
    while(isRunning){
        std::cout << "Select option: " << std::endl;
        std::cout << "1.Show RAM info" << std::endl;
        std::cout << "2.Show memory blocks" << std::endl;
        std::cout << "3.Create memory block" << std::endl;
        std::cout << "4.Delete memory block" << std::endl;
        std::cout << "5.Show block content" << std::endl;
        std::cout << "6.Edit memory block" << std::endl;
        std::cout << "7.Exit" << std::endl;
        std::cin >> option;
        switch(option){
            case 1: 
                std::cout << "Available: " << available / (1024 * 1024) << " MB" << std::endl;
                std::cout << "Total: " << total / (1024 * 1024) << " MB" << std::endl;
                break;
            case 2:
                core.show_blocks();
                break;
            case 3:
                core.create_block();
                break;
            case 4:
                core.delete_block();
                break;
            case 5:
                core.show_block_content();
                break;
            case 6:
                core.edit_block();
                break;
            case 7:
                isRunning = 0;
                std::cout << "The program has stopped, restart the program to start over." << std::endl;
                break;
        }
    }
    return 0;
}




