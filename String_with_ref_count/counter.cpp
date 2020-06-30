#include "counter.h"
#include <utility>
#include <iostream>
#include <ctype.h>
#include <QSet>

size_t   Counter::_curCounters = 0;
Counter* Counter::pHead        = nullptr;

Counter::Counter(const char *str) : pNext(nullptr), pStr(nullptr), nOwners(1)
{
    _init();
    pStr = new char[strlen(str) + 1];
    strcpy(pStr, str);
}

Counter::Counter(char*&& str) : pNext(nullptr), pStr(nullptr), nOwners(1)
{
    _init();
    std::swap(pStr, str);
}

void Counter::_init()
{
    pNext = pHead;
    pHead = this;

    ++_curCounters;
}

void Counter::removeOwner()
{
    if (--nOwners > 0)
        return;

    if (--_curCounters != 0)
    {
        if (pHead != this)
        {
            Counter* prev = pHead;

            while (prev->pNext != this)
            {
                prev = prev->pNext;
            }
            prev->pNext = this->pNext;
        }
        else
        {
            pHead = this->pNext;
        }
    }

    delete this;
}

Counter::~Counter()
{
    delete [] pStr; /*pStr = nullptr;*/
}

Counter* Counter::add(const char* str)
{
    Counter* curr = pHead;

    while (curr != nullptr)
    {
        if (!strcmp(str, curr->pStr))
        {
            ++curr->nOwners;
            return curr;
        }

        curr = curr->pNext;
    }

    curr = new Counter(str);
    return curr;
}

Counter* Counter::add(char* && str)
{
    Counter* curr = pHead;

    while (curr != nullptr)
    {
        if (!strcmp(str, curr->pStr))
        {
            ++curr->nOwners;
            delete [] str;         str = nullptr;
            return curr;
        }

        curr = curr->pNext;
    }

    curr = new Counter(std::move(str));
    return curr;
}

void Counter::addOwner() const
{
    ++nOwners;
}

Counter& Counter::operator+=(const char *str)
{
    char* temp = _cpy(str);

    Counter* curr = add(std::move(temp));

    removeOwner();

    return *curr;
}

Counter& Counter::operator+(const char *str)
{
    char* temp = _cpy(str);

    Counter* curr = add(std::move(temp));

    return *curr;
}

void Counter::PrintAll() const
{
    std::cout << "All strings: \n";

    Counter* curr = pHead;
    while (curr != nullptr)
    {
        std::cout << curr->pStr << " amount: " << curr->nOwners << "    ";
        curr = curr->pNext;
    }
    std::cout << std::endl;
}

void Counter::PrintAllAlf() const
{
    std::cout << "All strings in alphabetical order: \n";

    QSet<Counter*> unique;  unique.reserve(static_cast<int>(_curCounters));

    Counter* curr = pHead;

    while (curr != nullptr)
    {
        if (unique.contains(curr))
        {
            curr = curr->pNext;
            continue;
        }

        Counter* toPrint = curr;
        Counter* forCmp  = curr->pNext;

        while (forCmp != nullptr)
        {
            if ((strcmp(forCmp->pStr, toPrint->pStr) == -1) && !unique.contains(forCmp))
            {
                toPrint = forCmp;
            }

            forCmp = forCmp->pNext;
        }

        if (!unique.contains(toPrint))
        {
            std::cout << toPrint->pStr << " amount: " << curr->nOwners << "    ";
            unique.insert(toPrint);
        }

        if (curr == toPrint)
        {
            curr = curr->pNext;
        }
    }
    std::cout << std::endl;
}

void Counter::PrintAllOrder() const
{
    std::cout << "All strings in alphabetical order: \n";

    Counter* curr = pHead;
    Counter** uniques = new Counter*[_curCounters];
    for (size_t i = 0; i < _curCounters; ++i)
    {
        uniques[i] = nullptr;
    }

    while (curr != nullptr)
    {
        if (contains(uniques, curr))
        {
            curr = curr->pNext;
            continue;
        }

        Counter* toPrint = curr;
        Counter* forCmp  = curr->pNext;

        while (forCmp != nullptr)
        {
            if ((strcmp(forCmp->pStr, toPrint->pStr) == -1) && !contains(uniques, forCmp))
            {
                toPrint = forCmp;
            }

            forCmp = forCmp->pNext;
        }

        std::cout << toPrint->pStr << "    ";

        for (size_t i = 0; i < _curCounters; ++i)
        {
            if (uniques[i] == nullptr)
            {
                uniques[i] = toPrint;
                break;
            }
        }

        if (curr == toPrint)
        {
            curr = curr->pNext;
        }
    }
    std::cout << std::endl;

    delete [] uniques;
}

bool Counter::contains(Counter** head, Counter* compared) const
{
    if (*head == nullptr || compared == nullptr)
        return false;

    for (size_t i = 0; i < _curCounters; ++i)
    {
        if (head[i] == nullptr)
            return false;

        if (head[i] == compared)
        {
            return true;
        }
    }

    return false;
}

void Counter::toUpper()
{
    Counter* curr = pHead;
    while (curr != nullptr)
    {
        char* str = curr->pStr;

        while (*str)
        {
            *str = static_cast<char>(toupper(*str));
            ++str;
        }

        curr = curr->pNext;
    }
}

void Counter::toLower()
{
    Counter* curr = pHead;
    while (curr != nullptr)
    {
        char* str = curr->pStr;

        while (*str)
        {
            *str = static_cast<char>(tolower(*str));
            ++str;
        }

        curr = curr->pNext;
    }
}

void Counter::Sort()
{
    Counter* newHead = nullptr;
    Counter* global    = pHead;

    while (global != nullptr)
    {
        Counter* from = global;
        global = global->pNext;

        if (newHead == nullptr || (strcmp(from->pStr, newHead->pStr) <= 0))
        {
            from->pNext = newHead;
            newHead = from;
        }
        else
        {
            Counter* to = newHead;
            while (to->pNext != nullptr && !(strcmp(from->pStr, to->pNext->pStr) <= 0))
            {
                to = to->pNext;
            }

            from->pNext = to->pNext;
            to->pNext = from;
        }
    }

    if (newHead != nullptr)
        pHead = newHead;
}

Counter& operator+(const char *str, const Counter &counter)
{
    size_t sizeLeft  = strlen(str);
    size_t sizeRight = strlen(counter.pStr);

    char* temp = new char[sizeLeft + sizeRight + 1];

    strncpy(temp, str, sizeLeft);
    strncpy(temp + sizeLeft, counter.pStr, sizeRight + 1);

    Counter* curr = Counter::add(std::move(temp));

    return *curr;
}


char* Counter::_cpy(const char *str) const
{
    size_t sizeOwn = strlen(pStr);
    size_t sizeOth = strlen(str);

    char* temp = new char[sizeOwn + sizeOth + 1];

    strncpy(temp, pStr, sizeOwn);
    strncpy(temp + sizeOwn, str, sizeOth + 1);

    return temp;
}

