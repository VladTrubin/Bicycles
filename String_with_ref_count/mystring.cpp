#include <cstring>
#include "mystring.h"


MyString::MyString(const char *str) : pMyCounter(nullptr)
{
    if (str == nullptr || *str == '\0')
        return;

    pMyCounter = Counter::add(str);
}

MyString::MyString(const MyString &other)
{
    pMyCounter = other.pMyCounter;

    if (pMyCounter != nullptr)
        pMyCounter->addOwner();
}

MyString::MyString(MyString &&other)
{
    pMyCounter = other.pMyCounter;
    other.pMyCounter = nullptr;
}

MyString::MyString(Counter *counter) : pMyCounter(counter)
{

}

MyString &MyString::operator=(const MyString &other)
{
    if (pMyCounter != other.pMyCounter)
    {
        if (pMyCounter != nullptr)
            pMyCounter->removeOwner();

        pMyCounter = other.pMyCounter;

        if (pMyCounter != nullptr)
            pMyCounter->addOwner();
    }
    return *this;
}

void MyString::SetNewString(const char *str)
{
    if (str == GetString())
        return;

    if (pMyCounter != nullptr)
        pMyCounter->removeOwner();

    if (str == nullptr || *str == '\0')
    {
        pMyCounter = nullptr;
    }
    else
    {
        pMyCounter = Counter::add(str);
    }
}

MyString &MyString::operator=(MyString &&other)
{
    if (pMyCounter != other.pMyCounter)
    {
        if (pMyCounter != nullptr)
            pMyCounter->removeOwner();

        pMyCounter = other.pMyCounter;
        other.pMyCounter = nullptr;
    }

    return *this;
}

MyString::~MyString()
{
    if (pMyCounter != nullptr)
    {
        pMyCounter->removeOwner();
        pMyCounter = nullptr;
    }
}


bool MyString::operator==(const MyString *other) const
{
    return !strcmp(GetString(), other->GetString());
}

bool MyString::operator==(const char *str) const
{
    return !strcmp(GetString(), str);
}

std::ostream& operator<<(std::ostream &out, const MyString &str)
{
    out << str.GetString();
    return out;
}


MyString& MyString::operator+=(const MyString &other)
{
    if (pMyCounter == nullptr)
    {
        pMyCounter = Counter::add(other.GetString());
    }
    else
    {
        pMyCounter = &pMyCounter->operator+=(other.GetString());
    }

    return *this;
}

MyString& MyString::operator+=(const char *str)
{
    if (pMyCounter == nullptr)
    {
        pMyCounter = Counter::add(str);
    }
    else
    {
        pMyCounter = &pMyCounter->operator+=(str);
    }

    return *this;
}

MyString MyString::operator+(const MyString &other) const
{
    Counter* ret;

    if (pMyCounter == nullptr)
    {
        ret = Counter::add(other.GetString());
    }
    else if (other.pMyCounter == nullptr)
    {
        pMyCounter->addOwner();
        ret = pMyCounter;
    }
    else
    {
        ret = &pMyCounter->operator+(other.GetString());
    }

    return MyString(ret);
}

MyString MyString::operator+(const char *str) const
{
    Counter* ret;

    if (str == nullptr)
    {
        ret = pMyCounter;
    }
    else if (pMyCounter == nullptr)
    {
        ret = Counter::add(str);
    }
    else
    {
        ret = &pMyCounter->operator+(str);
    }

    return MyString(ret);
}

MyString operator+(const char *str, const MyString &myStr)
{
    Counter* ret;

    if (myStr.pMyCounter == nullptr)
    {
        ret = Counter::add(str);
    }
    else
    {
        ret = &(str + *myStr.pMyCounter);
    }

    return MyString(ret);
}

const char* MyString::GetString() const
{
//    if (this == nullptr)
//        return "";

    return pMyCounter == nullptr ? "" : pMyCounter->getStr();
}

bool MyString::isEmpty() const
{
    return (*GetString() == '\0') ? true : false;
}

