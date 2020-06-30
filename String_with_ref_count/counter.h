#ifndef COUNTER_H
#define COUNTER_H

#include <cstring>

class Counter
{
private:
    static size_t   _curCounters;
    static Counter* pHead;

    Counter*     pNext;
    char*        pStr;
    mutable unsigned int nOwners;

    explicit Counter(char* && str);
    static Counter* add(char *&& str);

public:
    explicit Counter(const char* str);
    Counter(Counter&& other)      = delete;
    Counter(const Counter& other) = default;
    Counter& operator=(const Counter& other) = default;
    ~Counter();

    static Counter* add(const char* str);
    void addOwner() const;
    void removeOwner();
    bool contains(Counter** head, Counter* compared) const;

    inline const char* getStr() const { return pStr; }

    Counter& operator+=(const char* str);
    Counter& operator+(const char* str);

    void PrintAll()       const;
    void PrintAllAlf()    const;
    void PrintAllOrder()  const;
    void toUpper();
    void toLower();
    void Sort();

    friend Counter& operator+(const char* str, const Counter& counter);

private:
    char* _cpy(const char* str) const;
    void  _init();
    void  _addCopy(Counter* copy);
};

Counter& operator+(const char* str, const Counter& counter);

#endif // COUNTER_H
