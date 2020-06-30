#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include "counter.h"

class MyString
{
private:
    Counter* pMyCounter;
    MyString(Counter* counter);

public:
    MyString(const char* str = nullptr);
    MyString(const MyString& other);
    MyString(MyString&& other);
    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other);
    ~MyString();

    bool      operator==(const MyString* other) const;
    bool      operator==(const char* str)       const;
    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* str);
    MyString  operator+(const MyString& other)  const;
    MyString  operator+(const char* str)  const;

    void        SetNewString(const char* str);
    const char* GetString()   const;
    inline void PrintAll()    const  { if (pMyCounter != nullptr) pMyCounter->PrintAll();      }
    inline void PrintAllAlf() const  { if (pMyCounter != nullptr) pMyCounter->PrintAllOrder(); }
    inline void toUpper()            { if (pMyCounter != nullptr) pMyCounter->toUpper();       }
    inline void toLower()            { if (pMyCounter != nullptr) pMyCounter->toLower();       }
    inline void SortAll()            { if (pMyCounter != nullptr) pMyCounter->Sort();          }

    bool isEmpty() const;
    void clear();

    friend MyString operator+(const char* str, const MyString& myStr);
    friend std::ostream& operator<<(std::ostream& out, const MyString& str);
};

    MyString operator+(const char* str, const MyString& myStr);
    std::ostream& operator<<(std::ostream& out, const MyString& str);

#endif // MYSTRING_H
