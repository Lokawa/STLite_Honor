#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>
#include<iostream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

struct Node
    {
        Node *next;
        int address;
        Node():next(NULL){}
        ~Node(){}
    };

template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    Node *head;
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        head=nullptr;
    }

    //������n��int��ֵ����tmp��1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.open(file_name, std::ios::in);
        file.seekg((n-1)*sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        /* your code here */
    }

    //��tmpд���n��int��λ�ã�1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name, std::ios::in | std::ios::out);
        file.seekp((n-1)*sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        /* your code here */
    }

    //���ļ�����λ��д�������t��������д���λ������index
    //λ��������ζ�ŵ�������ȷ��λ������index�����������������ж���˳�����ҵ�Ŀ�������в���
    //λ������index����ȡΪ����д�����ʼλ��
    int write(T &t) {
        file.open(file_name, std::ios::in|std::ios::out);
        if (!head) file.seekp(0,std::ios::end);
        else 
        {
            file.seekp(head->address,std::ios::beg);
            Node *p=new Node;
            p=head;
            head=head->next;
            delete p;
        }
        int index=file.tellp();
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
        return index;
        /* your code here */
    }

    //��t��ֵ����λ������index��Ӧ�Ķ��󣬱�֤���õ�index������write��������
    void update(T &t, const int index) {
        file.open(file_name, std::ios::in|std::ios::out);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
        /* your code here */
    }

    //����λ������index��Ӧ��T�����ֵ����ֵ��t����֤���õ�index������write��������
    void read(T &t, const int index) {
        file.open(file_name, std::ios::in);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
        /* your code here */
    }

    //ɾ��λ������index��Ӧ�Ķ���(���漰�ռ����ʱ���ɺ��Դ˺���)����֤���õ�index������write��������
    void Delete(int index) {
        Node *p=new Node;
        p->address=index;
        if (head)
        {   
            p->next=head->next;
            head=p;
        }
        else 
        {
            head=p;
            head->next=nullptr;
        }
        /* your code here */
    }
};


#endif //BPT_MEMORYRIVER_HPP