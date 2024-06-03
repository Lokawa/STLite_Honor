#include<iostream>
#include<cstdio>
#define USE_OS

using namespace std;
class error : public std::exception {

private:
    std::string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};


template<typename T>
class ArrayList
{
    
public:
    T *data;
    int length;
    ArrayList(T *arr, int len)
    {
        if (len<0) throw error("invalid length");
        length=len;
        data=new T[length];
        int i;
        for (i=0;i<length;i++)
            data[i]=arr[i];

    }
    ArrayList(int len)
    {
        if (len<0) throw error("invalid length");
        length=len;
        data=new T[length];
    }
    ArrayList(const ArrayList &b)
    {
        if (b.length<0) throw error("invalid length");
        length=b.length;
        data=new T[length];
        int i;
        for (i=0;i<length;i++)
            data[i]=b.data[i];
    }
    ~ArrayList()
    {
        length=0;
        delete []data;
    }
    int size()
    {
        if (length<0) throw error("invalid length");
        return this->length;
    }
    const T &operator[](int index) const
    {
        if (index>=this->length || index<0) throw error("index out of bound");
        return this->data[index];
    }
    T &operator[](int index)
    {
        if (index>=this->length || index<0) throw error("index out of bound");
        return this->data[index];
    }
    bool operator==(const ArrayList &b)
    {
        if (!(b.length==this->length)) return false;
        int i;
        for (i=0;i<this->length;i++)
            if (!(this->data[i]==b.data[i])) return false;
        return true;
    }
    bool operator!=(const ArrayList &b)
    {
        if (!(b.length==this->length)) return true;
        int i;
        for (i=0;i<this->length;i++)
            if (!(this->data[i]==b.data[i])) return true;
        return false;
    }
    ArrayList &operator=(const ArrayList &a)
    {
        int i;
        if (*this==a) return *this;
        delete []data;
        length=a.length;
        data=new T[a.length];
        for (i=0;i<a.length;i++) this->data[i]=a.data[i]; 
        return *this;
    }
};
template<typename T>
ArrayList<T> operator+(const ArrayList<T> &a,const ArrayList<T> &b)
    {
        ArrayList<T> t(a.length+b.length);
        int i;
        for (i=0;i<a.length;i++) t.data[i]=a.data[i];
        for (i=a.length;i<a.length+b.length;i++) t.data[i]=b.data[i-a.length];
        return t;
    }


template<typename T>
ostream &operator <<(ostream &os, const ArrayList<T> &obj)
{
    int i;
    for (i=0;i<obj.length;i++) os<<obj.data[i]<<' ';
    return os;
}

template<typename T>
void printList(ArrayList<T> list) 
{
    #ifdef USE_OS
    std::cout << list << "\n";
        #else
    list.print();
    std::cout << "\n";
    #endif
}

int main()
{
    try {
        ArrayList<char> list_err(-1);
    } catch (error &e) {
        std::cout << e.toString() << std::endl;
    }

    ArrayList<int> list(5);

    try {
        list[-1];
    } catch (error &e) {
        std::cout << e.toString() << std::endl;
    }
    try {
        list[2000];
    } catch (error &e) {
        std::cout << e.toString() << std::endl;
    }

    for (int i = 0; i < list.size(); i++) list[i] = i;
    printList(list);
    ArrayList<int> temp = list;
    printList(temp);
    temp = list;
    printList(temp);
    if (temp == list) std::cout << "true" << std::endl;

    int arr[5] = {4, 215, 12, 84, 76};
    const ArrayList<int> list_const(arr, 5);
    std::cout << list_const[3] << std::endl;
    printList(list_const);

    printList(list_const + list);
    system("pause");
    return 0;
}
