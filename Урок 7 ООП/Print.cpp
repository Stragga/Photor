#include <iostream>  
#include <ctime>       
#include <iomanip>
#define STOP_CMD system("pause"); 
#define COLOR_CMD system("color 0A");
//----------------------------------------------------------------------
template<typename T>class Queue
{
public:
    Queue(int SIZE);
    ~Queue();
    void addElement(T Element);
    void deleteElementQueue(); 
    void deleteElementQueueRing(); 
    void deleteElementQueuePriority(); 
    bool checkQueue();
    void showQueue();
    void queueRand(int min, int max);
    int sizeQueue();
    void showStatistic();
    void deleteQueue();
private:
    T* arr;
    int SIZE;
    int counter;
};
template<typename T> Queue<T>::Queue(int SIZE)
{
    try
    {
        this->SIZE = SIZE;
        arr = new T[this->SIZE]();
        counter = 0;
    }
    catch (std::bad_alloc& memoryAllocationException)
    {
        std::cerr << "Произошло исключение: [ПАМЯТЬ ОШИБОК]" << memoryAllocationException.what() << std::endl; 
        STOP_CMD
    }
}
template<typename T> Queue<T>::~Queue()
{
    delete[] arr;
    arr = NULL;
}
template<typename T>void Queue<T>::addElement(T Element)
{
    if (this->checkQueue() != false)
    {
        this->arr[this->counter] = Element;
        this->counter++;
    }
}
template<typename T>void Queue<T>::deleteElementQueue() 
{
    if (this->counter != 0)
    {
        T* buf = new T[this->counter]();
        for (size_t i = 0; i < this->counter; i++)
        {
            buf[i] = this->arr[i];
            this->arr[i] = 0;
        }
        for (size_t i = 0; i < this->counter - 1; i++)
        {
            this->arr[i] = buf[i + 1];
        }
        this->counter--;
        delete[] buf;
    }
    else
    {
        this->checkQueue();
    }
}
template<typename T>void Queue<T>::deleteElementQueueRing() 
{
    if (this->counter != 0)
    {
        T temp = this->arr[0];
        for (size_t i = 1; i < this->counter; i++) 
        {
            this->arr[i - 1] = this->arr[i];
        }
        this->arr[this->counter - 1] = temp;
    }
    else
    {
        this->checkQueue();
    }
}
template<typename T>void Queue<T>::deleteElementQueuePriority() 
{
    if (this->counter != 0)
    {
        T* buf = new T[this->counter - 1];
        T temp = this->arr[0];
        size_t count = 0, valueSameElements = 0;
        for (size_t i = 0; i < this->counter; i++) 
        {
            if (temp < arr[i])
            {
                temp = arr[i];
            }
        }
        for (size_t i = 0; i < this->counter; i++) 
        {
            if (arr[i] == temp)
                valueSameElements++;
        }
        for (size_t i = 0; i < this->counter; i++) 
        {
            if (this->arr[i] != temp)
            {
                buf[count] = this->arr[i];
                count++;
            }
            if (this->arr[i] == temp && valueSameElements > 1) 
            {
                buf[count] = this->arr[i];
                count++;
                valueSameElements--;
            }
        }
        for (size_t i = 0; i < this->counter - 1; i++) // Set array in main arr
        {
            this->arr[i + 1] = buf[i];
        }
        this->arr[0] = temp; 
        deleteElementQueue(); 
        delete[] buf;
        count = 0;
    }
    else
    {
        this->checkQueue();
    }
}
template<typename T>bool Queue<T>::checkQueue()
{
    if (this->counter < this->SIZE)
    {
        return true;
    }
    else
    {
        //std::cerr << "Queue full:" << std::endl; 
        return false;
    }

}
template<typename T>void Queue<T>::showQueue()
{
    this->checkQueue();
    for (size_t i = 0; i < this->counter; i++)
    {
        std::cout << this->arr[i] << "\t";
    }
    std::cout << std::endl;
}
template<typename T>void Queue<T>::queueRand(int min, int max)
{
    for (size_t i = 0; i < this->SIZE; i++)
    {
        this->arr[i] = min + rand() % (max - min + 1);
    }
    this->counter = this->SIZE;
}
template<typename T>void Queue<T>::deleteQueue()
{
    for (size_t i = 0; i < this->counter; i++)
    {
        arr[i] = 0;
    }
    this->counter = 0;
}
template<typename T>int Queue<T>::sizeQueue()
{
    std::cout << "Размер очереди -> " << this->SIZE << std::endl;
    std::cout << "Элементы в очереди -> " << this->counter << std::endl;
    return this->SIZE;
}
//----------------------------------------------------------------------
class Time
{
public:
    Time() :minutes(0), hours(0), seconds(0) {}
    Time(int h, int m, int s) {
        this->hours = h;
        this->minutes = m;
        this->seconds = s;
    }
    void show() { std::cout << "Час -> " << hours << ":" << minutes << ":" << seconds << std::endl; }
    void setHours(int h) { if (h <= 12 && h >= 0 || h <= 24 && h >= 0) this->hours = h; }
    void setMinutes(int m) { if (m <= 60 && m >= 0) this->minutes = m; }
    void setSeconds(int s) { if (s <= 60 && s >= 0) this->seconds = s; }
    int getHours() { return this->hours; }
    int getMinutes() { return this->minutes; }
    int getSeconds() { return this->seconds; }
private:
    int minutes;
    int hours;
    int seconds;
};

class Users
{
public:
    Users();
    Users(std::string name, std::string surname, int age, int numberSheets, Time* time, int priority);
    void show();
    void setName(std::string name);
    std::string getName();
    void setSurname(std::string surname);
    std::string getSurname();
    void setAge(int age);
    int getAge();
    void setNumberSheets(int numberSheets);
    int getNumberSheets();
    void setTime(int h, int m, int s);
    Time& getTime();
    void setPriority(int priority);
    int getPriority();
private:
    std::string name;
    std::string surname;
    int age;
    int numberSheets;
    Time* time;
    int priority;
};


Users::Users(std::string name, std::string surname, int age, int numberSheets, Time* time, int priority)
{
    this->name = name;
    this->surname = surname;
    this->age = age;
    this->numberSheets = numberSheets;
    this->time = time;
    this->priority = priority;
}
void Users::show()
{
    std::cout << "Пользователь" << std::endl;
    std::cout << "имя -> " << this->getName() << std::endl;
    std::cout << "Фамилия -> " << this->getSurname() << std::endl;
    std::cout << "Возраст -> " << this->getAge() << std::endl;
    std::cout << "Отправлено на принтер -> " << this->getNumberSheets() << std::endl;
    this->time->show();
    std::cout << "Приоритет -> " << this->getPriority() << std::endl;
}
void Users::setName(std::string name)
{
    this->name = name;
}
std::string Users::getName()
{
    return this->name;
}
void Users::setSurname(std::string surname)
{
    this->surname = surname;
}
std::string Users::getSurname()
{
    return this->surname;
}
void Users::setAge(int age)
{
    this->age = age;
}
int Users::getAge()
{
    return this->age;
}
void Users::setNumberSheets(int numberSheets)
{
    this->numberSheets = numberSheets;
}
int Users::getNumberSheets()
{
    return this->numberSheets;
}
void Users::setTime(int h, int m, int s)
{
    this->time->setHours(h);
    this->time->setMinutes(m);
    this->time->setSeconds(s);
}
Time& Users::getTime() {
    return *time;
}
void Users::setPriority(int priority)
{
    this->priority = priority;
}
int Users::getPriority()
{
    return this->priority;
}


int main() {
    setlocale(LC_ALL, "Rus");
    COLOR_CMD

        char symbol = 0;

    std::cout << "--------------------------------------" << std::endl;
    Time time(12, 52, 35);
    Users u = { "Игорь", "Петровыч", 29, 35,  &time, 15 };
    u.show();
    std::cout << "--------------------------------------" << std::endl;
    Time time1(10, 24, 27);
    Users u1 = { "Елена", "Юривна", 28, 78,  &time1, 25 };
    u1.show();
    std::cout << "--------------------------------------" << std::endl;
    Time time2(12, 52, 35);
    Users u2 = { "Петро", "Генадиовыч", 35, 15,  &time2, 8 };
    u2.show();
    std::cout << "--------------------------------------" << std::endl;

    std::cout << "Отправить документ на принтер введите [e]:" << std::endl;
    std::cin >> symbol;
    if (symbol == 'e')
    {
        Queue<int> printer(3);
        printer.addElement(u.getPriority());
        printer.addElement(u1.getPriority());
        printer.addElement(u2.getPriority());
        std::cout << "--------------------------------------" << std::endl;
        printer.showQueue();
        std::cout << "--------------------------------------" << std::endl;
        printer.deleteElementQueuePriority();
        std::cout << "--------------------------------------" << std::endl;
        printer.showQueue();
        std::cout << "--------------------------------------" << std::endl;
        printer.deleteElementQueuePriority();
        std::cout << "--------------------------------------" << std::endl;
        printer.showQueue();
        std::cout << "--------------------------------------" << std::endl;
        printer.deleteElementQueuePriority();
        std::cout << "--------------------------------------" << std::endl;
        printer.showQueue();
        std::cout << "--------------------------------------" << std::endl;
    }
    else
    {
        std::cerr << "Ввод ошибки!" << std::endl;
    }
    STOP_CMD
        return 0;
}