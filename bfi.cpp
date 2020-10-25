#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stack>

using namespace std;

class InfiniteArray {

public:
    InfiniteArray(){
        ptr = 0;
        data.push_back(0);
    }

    void go_next(){
        ptr ++;
        if(data.size() <= ptr){
            data.push_back(0);
        }
    }

    void go_back(){
        if(ptr > 0){
            ptr --;
        }
    }

    void increment(){
        data[ptr]++;
    }

    void decrement() {
        data[ptr]--;
    }

    int8_t get_value() {
        return data[ptr];
    }

    void set_value(int8_t value) {
        data[ptr] = value;
    }

    /**
    * Debug
    **/
    void print(){
        for(auto &x : data) cout << x << " ";
        cout << endl;
    }

    /**
    * Debug
    **/
    size_t get_ptr() { return ptr; }


private:
    size_t ptr;
    vector<int8_t> data;
};

typedef struct {
    stack<size_t> loops;

    Looper(){}

    void register_loop(const size_t ptr){
        loops.push(ptr);
    }

    void evaluate(InfiniteArray* iarray , size_t &ptr){
        if(iarray -> get_value() == 0){
            loops.pop();
        } else {
            ptr = loops.top();
        }
    }

} Looper;

void read_and_exec(char* file_name);
void file_not_found(char* file_name);
void print_help();

void read_and_exec(char* file_name){
    ifstream fin(file_name);
    if(!fin.is_open()){
        file_not_found(file_name);
        return;
    }

    Looper* looper = new Looper();
    InfiniteArray* iarray = new InfiniteArray();
    char c;
    size_t i {0};
    while(fin >> c){
        if(c == '.') {
            cout << iarray -> get_value()<< endl;
        } else if(c == ',') {
            char in;
            cin >> in;
            iarray -> set_value(in);
        } else if (c == '>') {
            iarray -> go_next();
        } else if (c == '<') {
            iarray -> go_back();
        } else if (c == '+') {
            iarray -> increment();
        } else if (c == '-') {
            iarray -> decrement();
        } else if (c == '[') {
            looper -> register_loop(i);
        } else if(c == ']') {
            looper -> evaluate(iarray, i);
        }
        i++;
    }
    fin.close();
}

void print_help(){
    cout << "\tBFI by Mattia Girolimetto!" << endl << endl << endl;
    cout << "\tUsage:" << endl;
    cout << "\tbfc <file_name>" << endl << endl;
    cout << "\tOptions:" << endl;
    cout << "\t-h (--help): Get help" << endl << endl;
    cout << "\tYou can get more info at: https://github.com/specialfish9/BFC-brain-fuck-interpreter" << endl;
}

void file_not_found(char *file_name){
    cout << "[ERROR] File " << file_name << " not found!" << endl;
}

int main(int argc, char *argv[]){
    if(argc == 1){
        print_help();
    } else if(argc > 2) {
        cout << "Unknown parameter " << argv[2] << " check -h flag for help" << endl;
    } else {
        if(!(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))){
            print_help();
        } else {
            read_and_exec(argv[1]);
        }
    }
    return 0;
}
