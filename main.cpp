#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <set>
#include <chrono>


int main(){

    std::ifstream input;

    input.open("Rowling_Harry_Potter_1_Sorcerer's_Stone.txt");

    //input.open("simple.txt");
    std::string str;

    // динамический массив содержащий все слова из файла
    std::vector<std::string> vecstr;

    // динамический массив содержащий
    // уникальные слова
    std::vector<std::string> unicstr;

    // контейнер set для уникальных слов
    std::set<std::string> unicstrset; 

    // массив символов, которые необходимо исключить
    const char *ch = ",.'!?\"";

    // зададим размер массива символов в ручную
    int ch_size = 7;

    //int count{};
    // проверяем получилось ли отрыть файл для чтения
    if(input.is_open()){
        int index{};
        // цикл, для заполнения вектора строк,
        // чтобы все слова хранились в памяти в
        // динамическом массиве
        while(!input.eof()){
            index = 0;
            // получаем слово из файла,
            // разделители для слова это пробелы
            input >> str;
            
            // проверка, есть ли в слове знаки препинания
            for(int i = 0; i < ch_size-1; ++i){
                if (index == -1 || index == 0){
                    index = str.find(ch[i]);
                }
            }
            // если в слове есть, какой либо из знаков
            // то его необходимо исключить
            if(index != -1){
                str = str.substr(0,index);
            }

            // также, можно сразу сделать преобразование
            // регистров символов, раз регистр не имеет
            // значения
            for(int i = 0; i < str.length(); ++i){
                str[i] = std::tolower(str[i]);
            }

            // в результате, полученное слово 
            // помещаем в массив строк
            // используя данный массив будем
            // производить выборку уникальных слов
            vecstr.push_back(str);
        }
    } else {
        std::cout << "Error: File is not opend!\n";
        throw -1;
    }

    // проверим размер получившегося массива
    std::cout << "All numbers of word in dictionary is: " << vecstr.size() << "\n\n";

    // заполнение нового массива уникальнымис словами
    // используем вложенный цикл для сравнения нового слова со
    // всеми уже уникальными добавленными в массив
    bool flag = true;
    // переменная для сохранения системного времени, 
    // точка отсчета начала цикла
    auto start_time_vector = std::chrono::system_clock::now();
    for(int i = 0; i < vecstr.size(); ++i){
        for(int j = 0; j < unicstr.size(); ++j){
            if(vecstr.at(i) == unicstr.at(j)){
                flag = false;
                break;
            }
        }
        if (flag){
            unicstr.push_back(vecstr.at(i));
        }
        flag = true;
    }
    auto end_time_vector = std::chrono::system_clock::now();
    auto diff_time_vector = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_vector - 
    start_time_vector);
    // проверка размера массива уникальных слов
    std::cout << "Using a vector collection.\n";
    std::cout << "Unic word into the file is: " << unicstr.size() << "\n";
    std::cout << "Time for calculation unic list is: " << diff_time_vector.count() << " ms\n\n";


    // теперь используем коллекцию set для подсчета 
    // уникальных слов
    start_time_vector = std::chrono::system_clock::now();
    for(auto &i:vecstr){
        unicstrset.insert(i);
    }
    end_time_vector = std::chrono::system_clock::now();
    diff_time_vector = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_vector - 
    start_time_vector);
    // проверка размера коллекции set уникальных слов
    std::cout << "Using a set collection.\n";
    std::cout << "Unic word into the file is: " << unicstrset.size() << "\n";
    std::cout << "Time for calculation unic list is: " << diff_time_vector.count() << " ms\n";

    return 0;
}