#include <iostream>
#include <memory>
#include <functional>
#include <vector>

using namespace std;

class MyExceptoin : public std::exception {
    int type{};
public:
    MyExceptoin(int type) : std::exception("Error in MyArray "), type{type}{}
    int getType() const { return type; }
};



class MyArray {
    std::unique_ptr<int[]> arr;
    unsigned int size{};
public:
    MyArray(unsigned int size = 10);

    int operator[] (unsigned int ind) const {
        if (ind >= size)
            throw MyExceptoin(1);
        return arr[ind];
    }

    //int& operator[] (int);

    // К значению элемента [I] прибавляем соответствующее значение [I] из второго масссива
    MyArray& operator+= (const MyArray& arr) {

        if (size != arr.size)
            throw MyExceptoin(2);

        for (int i{}; i < size; ++i)
            this->arr[i] += arr[i];

        return *this;
    }
    // От значения элемента [I] вычитаем соответствующее значение [I] из второго масссива
    //MyArray& operator- (const MyArray& arr);
    // Не должно работать с массивами разной длинны

};

MyArray::MyArray(unsigned int size) :size{ size } {
    arr = std::make_unique<int[]>(size);
    
    for (int i{}; i < size; ++i)    
        arr[i] = rand()%100;

    for (int i{}; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}




 
int main11(){
    //std::unique_ptr<A[]> ptr = std::make_unique<A[]>(10);

    MyArray  a{ 10 };
    MyArray  a1{ 10 };
    try {
        cout << a[3] << endl;
        a += a1;
    }
    catch (MyExceptoin ex) {
        cout << ex.what() << endl;
        if (ex.getType() == 1)
            cout << "Out of range" << endl;
        else if (ex.getType() == 2) {
            cout << "Differnd size" << endl;
        }
        else {
            cout << "don`t know" << endl;
        }
    }

    return 0;
}





class A {

public:
    virtual void print() { cout << "Print class A" << endl; };
};

class B :public A {
    int type{99};

public:
    void print() override { cout << "Print class B" << endl; };
    int getType() const { return type; }

};

class D :public A {
    int type{34};

public:
    void print() override { cout << "Print class D" << endl; };
    int getType() const { return type; }

};

class C {
public:
    virtual void print() { cout << "Print class C" << endl; };

};


// Функция для работы с dynamic_cast
void func(A* a) {
    try {
        B* b = dynamic_cast<B*> (a);

        if (b) {
            cout << "OK this class B" << endl;
            cout << b->getType() << endl;

        }
        else {
            D* d = dynamic_cast<D*> (a);
            if (d) {
                cout << "OK this class D" << endl;
                cout << d->getType() << endl;
            }
            else
                cout << "Error" << endl;
        }
    }
    catch (bad_cast e) {
        cout << "1. " << e.what() << endl;
    }
    catch (exception e) {
        cout << e.what() << endl;
    }
}

// Функция для работы с static_cast
void func1(A* a) {
    try {
        B* b = static_cast<B*> (a);

        if (a) {
            cout << "OK" << endl;
            cout << "Type = " << b->getType() << endl;
        }
        else {
            cout << "Error" << endl;
        }
    }
    catch (bad_cast e) {
        cout << "1. " << e.what() << endl;
    }
    catch (exception e) {
        cout << e.what() << endl;
    }
}
void func2(const int& i) {

    int& j = const_cast<int&>(i);

    //const int& j = i;

    j++;
}

int main33()
{
    std::cout << "Hello World!\n";
    
    /*
    //  Пример использования static_cast
    int a = 10;
    double d = (double) a;
    double d1 = static_cast<double>(a);
    

    a += 0.67;
    d += 0.67;
    d1 += 0.67;

    cout << a << "   " << d<< "   " << d1 << endl;

    return 0;
    */

    /*
    // Пример использования dynamic_cast
    func(new B);
    func(new D);
    
    return 0;
      */

    /*
    //  Пример использования static_cast
    func1((A*)new C);
    return 0;
        */
    int i = 100;

    func2(i);
    cout << i << endl;

  


    const int con = 1000;

    int& temp = const_cast<int&> (con);

    temp = 1133;
    cout << temp <<" " << &temp << endl;
    cout << con <<" "<<&con << endl;

    return 0;

}

void fun() {
    cout << "Fun is work" << endl;
}

void fun2() {
    cout << "Fun2 is work" << endl;
}

int sum(int a, int b) {
    return a + b;
}

void fun1(int a) {
    if (a > 10 && a < 40) {
        cout << "fun - " << a << endl;
    }
}

bool fun1b(int a) {
    return (a > 10 && a < 40);
}

void fun3(int a) {
    if (!(a % 2)) {
        cout << "fun3 - " << a << endl;
    }
}

bool fun3b(int a) {
    return (!(a % 2));
}


void fun4(int a) {
    if ((a % 2)) {
        cout << "fun4 - " << a << endl;
    }
}
void doWork(vector<int>& vc, function<void(int)> fun) {

    for (auto v : vc) {
        fun(v);
    }
}

void doWork(vector<int>& vc, vector <function<void(int)>> funcs) {

    for (auto v : vc) {
        for (auto fun : funcs)
            fun(v);
    }
}


void doWork(vector<int>& vc, vector <function<bool(int)>> funcs) {

    for (auto v : vc) {
        bool result{true};
        for (auto fun : funcs)
            if (!fun(v)) {
                result = false;
                break;
            }
        if (result)
            cout << v << endl;
    }
}

int main11111() {

    vector<int> vc = { 1,2,3,45,67,33,221,88,99,22 };

    //doWork(vc);
    //doWork(vc, fun4);

    //vector<function<void(int)>> funcs = { fun1,fun3 };
    //doWork(vc, funcs);

    vector<function<bool(int)>> funcs = { fun1b, fun3b};
    doWork(vc, funcs);

    return 0;

    void (*ptr) ();
    ptr = fun;
    ptr();

    ptr = fun2;
    ptr();

    function<void()> f = fun;

    f();

    function<int(int, int)> f2 = sum;

    cout << f2(10, 70) << endl;

    return 0;
}


void print(function<int(int, int)> f) {

    for (int i{}; i < 10 ; ++i)
        cout << f(i, i*i) << endl;
    
}

// Лямбда выражения
int main() {
    setlocale(LC_ALL, "rus");


    // контекст = & , , ,  mutable, this  -> тип данных
    //[](){};
    //[контекст](передаваемые аргументы){тело функции};

    // = контекст по значению (только для чтения)
    // = контекст по значению (полная копия) mutable
    // &  контекст по ссылке


    int y{};

    double d{ 77.89 };
    
    //function<double(int&)> x 
    auto x = [&](int a, int b) -> int {
        std::cout << "Lambda function " << endl;    
        y++;
        return  a + b;
    };

    //print(x);

    print(
        [&](int a, int b) -> int {
        std::cout << "Lambda function " << endl;
        y++;
        return  a + b;
        }
    );

    cout << "Y = " << y << endl;

    return 0;

    int a = 10;
    //double ddd = x(a);

    std::cout << " Y = " << y << endl;
    std::cout << "a = " << a << endl;



    return 0;



    int p{ 100 };

    function<void(int)> ff = [&p](int u) {
        cout << "Лямбда функция " << u << endl;
        p++;
    };
    ff(100);
    cout << p << endl;


    auto auto_f = [&p](int u) {
        cout << "Лямбда функция " << u << endl;
        p++;
    };

    auto_f(99);


    auto auto_f1 = [&p](int u) {
        cout << "Лямбда функция " << u << endl;
        p++;
        return u + u;
    };
    auto result = auto_f1(99);


    p = 1;
    cout << p << endl;
    auto auto_f2 = [p](int u) mutable -> double {
        cout << "Лямбда функция " << u << endl;
        p++;
        return u + u;
    };

    auto result2 = auto_f2(99);
    cout << p << endl;



    //int p = 0;
    //vector<int> vc = { 1,2,3,45,67,33,221,88,99,22 };
    //doWork(vc, [p](int a)/*mutable*/ {
    //    cout << a << endl;
    //   });



    return 0;
}