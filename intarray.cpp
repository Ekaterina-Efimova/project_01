#include <iostream>
#include <cassert>
class IntArray {
    private:
        int size;
        int* data;
    public:
        IntArray(int size = 0, int *data = nullptr){
            this -> size = size;
            assert(size > 0 && "IntArray size must be > 0");
            this -> data = new int[size] {0};
        };
        IntArray& operator= (const IntArray& other){
            if(this == &other){
                return *this;
            }
            delete[] this->data;
            this->size = other.size;
            if (other.data && other.size > 0){
                this->data = new int[this->size];
                for(int i = 0; i < this->size; i++){
                    this->data[i] = other.data[i];
                } 
            } else {
                this->data = nullptr;
            }
            return *this;
        };
        IntArray(const IntArray& other){
            this->size = other.size;
            if (other.data && other.size > 0){
                this->data = new int[this->size];
                for(int i = 0; i < this->size; i++){
                    this->data[i] = other.data[i];
                } 
            } else {
                this->data = nullptr;
            }
        };
        ~IntArray(){
            delete[] this->data;
        }
        friend std::ostream& operator<<(std::ostream& out, const IntArray& array);
        int& operator[] (int index){
            assert (index >= 0 && index < this->size);
            return this->data[index];
        }
};
std::ostream& operator<<(std::ostream& out, const IntArray& array){
    for(int i = 0; i < array.size; i++){
        out << array.data[i] << ' ';
    }
    return out;
};
IntArray fill (){
    IntArray a(6);
    a[0] = 6;
    a[1] = 7;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    a[5] = 8;
    return a;
}
int main(){
    IntArray a = fill();
    std::cout << a << '\n';
    IntArray b(1);
    a = a;
    b = a;
    std::cout << b << '\n';
    return 0;
}