//D:/learn/c++/c++_experiment/U201714480_4
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

class STACK
{
    int *const elems; //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;          //栈实际已有元素个数，栈空时pos=0;
public:
    STACK() : elems(nullptr), max(0), pos(0){}; //默认构造函数
    STACK(int m);                               //初始化栈：最多存m个元素
    STACK(const STACK &s);                      //用栈s拷贝初始化栈
    STACK(STACK &&s);                           //移动构造
    virtual int size() const;                   //返回栈的最大元素个数max
    virtual operator int() const;               //返回栈的实际元素个数pos
    virtual int operator[](int x) const;        //取下标x处的栈元素，第1个元素x=0
    virtual STACK &operator<<(int e);           //将e入栈,并返回栈
    virtual STACK &operator>>(int &e);          //出栈到e,并返回栈
    virtual STACK &operator=(const STACK &s);   //赋s给栈,并返回被赋值栈
    virtual STACK &operator=(STACK &&s);        //移动赋值
    virtual void print() const;                 //打印栈
    virtual ~STACK();                           //销毁栈
};

// STACK(int m); //初始化栈：最多存m个元素
STACK::STACK(int m) : elems(new int[m]), max(m), pos(0)
{
}
// STACK(const STACK &s); //用栈s拷贝初始化栈
STACK::STACK(const STACK &s) : elems(new int[s.max]), max(s.max), pos(s.pos)
{
    for (int i = 0; i < this->pos; i++)
    {
        this->elems[i] = s.elems[i];
    }
}
// STACK(STACK &&s); //移动构造
STACK::STACK(STACK &&s) : elems(s.elems), max(s.max), pos(s.pos)
{
    int **p = (int **)&(s.elems);
    *p = nullptr;
}
// virtual int size() const; //返回栈的最大元素个数max
int STACK::size() const
{
    return this->max;
}
// virtual operator int() const; //返回栈的实际元素个数pos
STACK::operator int() const
{
    return this->pos;
}
// virtual int operator[](int x) const; //取下标x处的栈元素，第1个元素x=0
int STACK::operator[](int x) const
{
    return this->elems[x];
}
// virtual STACK &operator<<(int e); //将e入栈,并返回栈
STACK &STACK::operator<<(int e)
{
    if (this->pos == this->max)
        cout << "push failed!" << endl;
    else
    {
        this->elems[pos] = e;
        this->pos++;
    }
    return *this;
}
// virtual STACK &operator>>(int &e); //出栈到e,并返回栈
STACK &STACK::operator>>(int &e)
{
    if (this->pos == 0)
        cout << "pop failed!" << endl;
    else
    {
        this->pos--;
        e = this->elems[pos];
    }
    return *this;
}
// virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值栈
STACK &STACK::operator=(const STACK &s)
{
    if (s.max != this->max)
    {
        if (this->elems)
            delete this->elems;
        int **p = (int **)&(this->elems);
        *p = new int[s.max];
        int *q = (int *)&(this->max);
        *q = s.max;
    }
    this->pos = s.pos;
    for (int i = 0; i < this->pos; i++)
    {
        this->elems[i] = s.elems[i];
    }
    return *this;
}

//virtual STACK &operator=(STACK &&s); //移动赋值

STACK &STACK::operator=(STACK &&s)
{
    this->pos = s.pos;
    int **p = (int **)(&(this->elems));
    int **q = (int **)(&(s.elems));
    int *r = (int *)(&(this->max));
    *p = s.elems;
    *q = nullptr;
    *r = s.max;
    return *this;
}

//virtual void print() const; //打印栈
void STACK::print() const
{
    for (int i = 0; i < this->pos; i++)
        printf("%d  ", this->elems[i]);
}

//virtual ~STACK(); //销毁栈
STACK::~STACK()
{
    delete[] this->elems;
    this->pos = 0;
    int **p = (int **)(&(this->elems));
    int **q = (int **)(&(this->max));
    *p = nullptr;
    *q = 0;
}


class QUEUE:public STACK
{
    STACK s;
public:
    QUEUE(int m);                             //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    QUEUE(const QUEUE &q);                    //用队列q拷贝初始化队列
    QUEUE(QUEUE &&q);                         //移动构造
    virtual operator int() const;             //返回队列的实际元素个数
    virtual int full() const;                 //返回队列是否已满，满返回1，否则0
    virtual int operator[](int x) const;      //取下标为x的元素，第1个元素下标为0
    virtual QUEUE &operator<<(int e);         //将e入队列,并返回队列
    virtual QUEUE &operator>>(int &e);        //出队列到e,并返回队列
    virtual QUEUE &operator=(const QUEUE &q); //赋q给队列,并返回被赋值队列
    virtual QUEUE &operator=(QUEUE &&q);      //移动赋值
    virtual void print() const;               //打印队列
    virtual ~QUEUE();                         //销毁队列
    void debug()
    {
        cout << "s1.size: " << STACK::size() << "   s1.pos: " << STACK::operator int()<< "   ---";
        STACK::print();
        cout << endl;
        cout << "s2.size: " << s.size() << "   s2.pos: " << int(s) << "   ---";
        s.print();
        cout << endl;
    }
};
// QUEUE(int m);                             //每个栈最多m个元素，要求实现的队列最多能入2m个元素
QUEUE::QUEUE(int m) : STACK(m), s(STACK(m))
{
    //s = STACK(m);
}

// QUEUE(const QUEUE &q);                    //用队列q拷贝初始化队列
QUEUE::QUEUE(const QUEUE &q):STACK(q),s(q.s)
{
}
// QUEUE(QUEUE &&q);                         //移动构造
QUEUE::QUEUE(QUEUE &&q) : STACK(move(q)), s(move(q.s))
{
    //s = move(q.s);
}
// virtual operator int() const;             //返回队列的实际元素个数
QUEUE::operator int() const
{
    return int(s) + STACK::operator int();
}
// virtual int full() const;                 //返回队列是否已满，满返回1，否则返回0
int QUEUE::full() const
{
    if (STACK::size() == STACK::operator int() && int(s) > 0)
        return 1;
    else
        return 0;
}
// virtual int operator[](int x) const;      //取下标为x的元素,第1个元素下标为0
int QUEUE::operator[](int x) const
{
    // cout << "s1.size: " << STACK::size() << "   s1.pos: " << STACK::operator int() << "   ---";
    // STACK::print();
    // cout << endl;
    // cout << "s2.size: " << s.size() << "   s2.pos: " << int(s) << "   ---";
    // s.print();
    // cout << endl;
    //cout<<"int s:   "<<int(s);
    if (x < int(s))
        {
            return s[int(s) - x - 1];
           // cout<<"s2....\n";
        }
    else if (x < int(s) + STACK::operator int())
        {
        return STACK::operator[](x - int(s));
          //  cout<<"s1...\n";
        }
    else
        return -1;
}
// virtual QUEUE &operator<<(int e);         //将e入队列,并返回队列
QUEUE &QUEUE::operator<<(int e)
{
    // debug();
    if (STACK::operator int() < STACK::size())
    {
        STACK::operator<< (e);
        return *this;
    }
    else if (int(s) == 0)
    {
        for (int i = 0; i < STACK::size(); i++)
        {
            int temp = 0;
            STACK::operator>> (temp);
            s<< temp;
        }
        STACK::operator<< (e);
        return *this;
    }
    else
    {
        cout << "push faled!";
        return *this;
    }
}
// virtual QUEUE &operator>>(int &e);        //出队列到e,并返回队列
QUEUE &QUEUE::operator>>(int &e)
{
    //debug();
    if (int(s) > 0)
    {
        s >> e;
        return *this;
    }
    else if (STACK::operator int() > 0)
    {
        for (int i = 0, length = STACK::operator int(); i < length; i++)
        {
            //debug();
            int temp = 0;
            STACK::operator>>(temp);
            s << temp;
        }
        s >> e;
        return *this;
    }
    else
    {
        cout << "pop failed";
        return *this;
    }
}
// virtual QUEUE &operator=(const QUEUE &q); //赋q给队列,并返回被赋值的队列
QUEUE &QUEUE::operator=(const QUEUE &q)
{
    s = q.s;
    STACK::operator= (q);
    return *this;
}
// virtual QUEUE &operator=(QUEUE &&q);      //移动赋值
QUEUE &QUEUE::operator=(QUEUE &&q)
{
    s = move(q.s);
    STACK::operator=(q);
    return *this;
}
// virtual void print() const;               //打印队列
void QUEUE::print() const
{

    for (int i = int(s) - 1; i >= 0; i--)
        printf("%d  ", s[i]);
    for (int i = 0; i < STACK::operator int(); i++)
        printf("%d  ", STACK::operator[](i));
}
// virtual ~QUEUE();                         //销毁队列
QUEUE::~QUEUE()
{
}

void print_file(const QUEUE &s, ofstream &outfile)
{
    for (int i = 0; int(s)>0&&i<int(s); i++)
        outfile << s[i] << "  ";
    // for (int i = int(s) - 1; i >= 0; i--)
    //     outfile << s[i] << "  ";
    // for (int i = 0; i < s.STACK::operator int(); i++)
    //     outfile << s.STACK::operator[](i) << "  ";
}

int main(const int argc, const char **argv)
{
     string filename=argv[0];
    int temp=filename.find(".exe");
    if (temp != filename.npos )
    {
        string s =filename.substr(0,temp);
        filename = s;
    }
    filename += ".txt";
    ofstream outfile(filename);

    QUEUE *s = nullptr;
    outfile << "S  " << atoi(argv[2]) << "  ";
    QUEUE s1(atoi(argv[2]));
    print_file(s1, outfile);

    // s1.debug();

    s = &s1;

    for (int i = 3; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 'I':
            {
                bool isoverflow = false;
                outfile << "I  ";
                for (int j = i + 1; j < argc && argv[j][0] != '-'; j++, i++)
                {
                    if (argv[j][0] != '-')
                    {
                        //(*s).debug();
                        if ((*s).full())
                            isoverflow = true;
                        else
                            *s << atoi(argv[j]);
                    }
                }
                if (isoverflow == true)
                {
                    outfile << 'E' << "  ";
                    i = argc - 1;
                    break;
                }
                print_file(*s, outfile);
                break;
            }
            case 'O':
            {
                bool isoverflow = false;
                outfile << "O  ";
                int e;
                for (int j = 0; j < atoi(argv[i + 1]); j++)
                {
                    if (int(*s) > 0)
                        *s >> e;
                    else
                        isoverflow = true;
                }
                i++;
                if (isoverflow == true)
                {
                    outfile << 'E' << "  ";
                    i = argc - 1;
                    break;
                }
                print_file(*s, outfile);
                break;
            }
            case 'C':
            {
                outfile << "C  ";
                QUEUE s_temp(*s);
                s1 = move(s_temp);
                s = &s1;
                // cout<<"ccccc:::\n";
                // (*s).debug();
                print_file(*s, outfile);
                break;
            }
            case 'A':
            {
                outfile << "A  ";
                i++;
                QUEUE s_temp(atoi(argv[i + 1]));
                s_temp = *s;
                s1 = move(s_temp);
                s = &s1;
                print_file(*s, outfile);
                break;
            }
            case 'N':
            {
                outfile << "N  " << int(*s) << "  ";
                break;
            }
            case 'G':
            {
                outfile << "G  ";
                if (atoi(argv[i + 1]) < int(*s) && atoi(argv[i + 1]) >= 0)
                    outfile << (*s)[atoi(argv[i + 1])] << "  ";
                else
                {
                    outfile << 'E' << "  ";
                    i = argc - 1;
                }
                break;
            }
            }
        }
    }
    outfile.close();
    return 0;
}