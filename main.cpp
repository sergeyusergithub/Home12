#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <set>


int main(){

    std::ifstream input;

    input.open("Rowling_Harry_Potter_1_Sorcerer's_Stone.txt");

    std::string str;

    // динамический массив содержащий все слова из файла
    std::vector<std::string> vecstr;

    // массив символов, которые необходимо исключить
    const char *ch = ",.'";

    int ch_size = 4;

    int count{};
    if(input.is_open()){
        int index{};
        while(!input.eof()){
            index = 0;
            input >> str;
            for(int i = 0; i < ch_size-1; ++i){
                if (index == -1 || index == 0){
                    index = str.find(ch[i]);
                }
            }
            
            if(index != -1){
                str = str.substr(0,index);
            }
            for(int i = 0; i < str.length(); ++i){
                str[i] = std::tolower(str[i]);
            }
            vecstr.push_back(str);
        }
    } else {
        std::cout << "Error: File is not opend!\n";
        throw -1;
    }

    std::cout << vecstr.size() << "\n\n";

    for(int i = 0; i < 30; ++i){
        std::cout << vecstr.at(i) << "\n";
    }


    return 0;
}