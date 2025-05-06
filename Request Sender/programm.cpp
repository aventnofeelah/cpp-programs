
#include <iostream>
#include <string>
#include <windows.h>
#include <map>
#include <curl/curl.h>

auto parseFunc(std::string s){
  std::map<std::string, std::string> json;
  std::string key, val;
  int isVal = 0;
  for(int i = 1; i < s.length() - 1; ++i){
    if(s[i] != ':' && isVal == 0 && s[i] != ',' && s[i] != '"'){
      key = key + std::string(1, s[i]);
    }
    else if(s[i] != ':' && isVal == 1 && s[i] != ',' && s[i] != '"'){
      val = val + std::string(1, s[i]);
    }
    else if(s[i] == ':'){
      isVal = 1;
    }
    else if(s[i] == ','){
      isVal = 0;
      json[key] = val;
      val = "";
      key = "";
    }
  }
  json[key] = val;
  return json;
}

size_t write_function(char *contents, size_t size, size_t nmemb, void *userp){
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
};

int main(){
    CURL *curl;
    CURLcode res;

    int isWorking = 1, opt;
    std::string ip_text, response;
    while(isWorking){
        std::cout << "Choose option: " << std::endl << "1.Your IP data" << std::endl << "2.Get your public IP" << std::endl << "3.Get ISP by IP" << std::endl << "4.Get location by IP" << std::endl << "5.Exit" << std::endl;
        std::cin >> opt;
        if(opt == 1){
            ShellExecuteA(NULL, "open", "cmd.exe", "/k ipconfig", NULL, SW_SHOWNORMAL);
        }
        else if(opt == 2){
            response.clear();
            curl = curl_easy_init();

            curl_easy_setopt(curl, CURLOPT_URL, "http://ip-api.com/json/");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            res = curl_easy_perform(curl);
            if(res != CURLE_OK){
                std::cout << curl_easy_strerror(res) << std::endl;
            }
            else{
                std::cout << "Response: " << parseFunc(response)["query"] << std::endl;
            }
            curl_easy_cleanup(curl);
        }
        else if(opt == 3){
            response.clear();
            std::cout << "Enter public IP:" << std::endl;
            std::cin >> ip_text;
            ip_text = "http://ip-api.com/json/" + ip_text;

            curl = curl_easy_init();

            curl_easy_setopt(curl, CURLOPT_URL, ip_text.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            res = curl_easy_perform(curl);
            if(res != CURLE_OK){
                std::cout << curl_easy_strerror(res) << std::endl;
            }
            else{
                std::cout << "Response: " << parseFunc(response)["isp"] << std::endl;
            }
            curl_easy_cleanup(curl);
        }
        else if(opt == 4){
            response.clear();
            std::cout << "Enter public IP:" << std::endl;
            std::cin >> ip_text;
            ip_text = "http://ip-api.com/json/" + ip_text;

            curl = curl_easy_init();

            curl_easy_setopt(curl, CURLOPT_URL, ip_text.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            res = curl_easy_perform(curl);
            if(res != CURLE_OK){
                std::cout << curl_easy_strerror(res) << std::endl;
            }
            else{
                std::cout << "Country: " << parseFunc(response)["country"] << std::endl;
                std::cout << "City: " << parseFunc(response)["city"] << std::endl;
                std::cout << "Latitude: " << parseFunc(response)["lat"] << std::endl;
                std::cout << "Longitude: " << parseFunc(response)["lon"] << std::endl;
            }
            curl_easy_cleanup(curl);
        }
        else if(opt == 5){
            isWorking = 0;
        }
        else{
            std::cout << "Invalid option" << std::endl;
        }
    }
    return 0;
}

