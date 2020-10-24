#include <iostream>
#include <vector>
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

int main(){
    char program[] = ",+.";
    Looper* looper = new Looper();
    InfiniteArray* iarray = new InfiniteArray();
    for(size_t i{0}; i < 3; i++){
        char c = program[i];

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
    }
    return 0;
}
