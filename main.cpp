#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

const size_t atomic_len = 8;
typedef union{
    uint64_t num;
    u_char atomic_num[atomic_len];
}number;

uint64_t entropy(uint64_t num, uint8_t param){
    number n;
    n.num = num;
    size_t index = 0;
    if (num % 2)
        index = 1;
    for (;index < sizeof (uint64_t); index +=2)
        n.atomic_num[index]*=param;
    return n.num;
}

int main(int argc, char* argv[]) {

    std::string filename;
    int numbilets, parameter;

    std::string file = "--file";
    std::string num_b = "--numbilets";
    std::string param = "--parameter";

    if (argc > 7){
        return 1;
    }else{
        if (argv[1] == file){
            filename = argv[2];
        }
        if(argv[3] == num_b){
            numbilets = atoi(argv[4]);
        }
        if(argv[5] == param) {
            parameter = atoi(argv[6]);
        }
    }

    std::string buf;
    std::hash<std::string> hasher;
    std::ifstream fio_file("fiofile");
    while(std::getline(fio_file, buf)){
        std::cout << buf << ": " << entropy(hasher(buf), parameter) % numbilets << std::endl;
    }

    return 0;
}