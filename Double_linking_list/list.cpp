#include "list.h"
#include <fstream>

List::List() : pHead(nullptr), pTail(nullptr), _size(0)
{

}

List::List(std::initializer_list<List::Data> args) : pHead(nullptr), pTail(nullptr), _size(0)
{
    for (auto el : args)
    {
        push_back(el);
    }
}

List::List(const List &other) : pHead(nullptr), pTail(nullptr), _size(0)
{
    _fill(other);
}

List::List(List &&other) : pHead(nullptr), pTail(nullptr), _size(0)
{
    move(std::move(other));
}

List::~List()
{
    while (pHead != nullptr)
    {
        Node* toDelete = pHead;
        pHead = pHead->pNext;
        delete toDelete;
    }
}

List& List::operator=(const List &other)
{
    _size = other._size;

    Node* currOth = other.pHead;
    Node* currOwn = pHead;

    while (currOwn != nullptr && currOth != nullptr)
    {
        currOwn->_data = currOth->_data;
        currOwn = currOwn->pNext;
        currOth = currOth->pNext;
    }

    while (currOth != nullptr)
    {
        push_back(currOth->_data);
        currOth = currOth->pNext;
    }

    while (currOwn != nullptr)
    {
        currOwn->pPrev = currOwn->pNext;
        Node* toDelete = currOwn;
        currOwn = currOwn->pNext;
        delete toDelete;
    }

    return *this;
}

List& List::operator=(List&& other)
{
    move(std::move(other));

    return *this;
}

void List::move(List &&other)
{
    pHead = other.pHead;    other.pHead = nullptr;
    pTail = other.pTail;    other.pTail = nullptr;
    _size = other._size;    other._size = 0;
}

void List::_fill(const List &other)
{
    Node* curr = other.pHead;

    while (curr != nullptr)
    {
        push_back(curr->_data);
        curr = curr->pNext;
    }
}


List::Node::Node(const Data& data, List::Node *next, List::Node *prev) :
    pPrev(prev), pNext(next), _data(data)
{

}

void List::clear()
{
    while (_size)
    {
        pop_front();
    }
}

bool List::pop_front()
{
    if (_size == 0)
        return false;

    if (_size > 1)
    {
        Node* temp = pHead;
        pHead = pHead->pNext;
        delete temp;
    }
    else
    {
        Node* temp = pHead;
        pTail = pHead = pHead->pNext;
        delete temp;
    }

    --_size;
    return true;
}

bool List::pop_back()
{
    if (_size == 0)
        return false;

    if (_size > 1)
    {
        Node* temp = pTail;
        pTail = pTail->pPrev;
        delete temp;
    }
    else
    {
        Node* temp = pTail;
        pTail = pHead = pTail->pPrev;
        delete temp;
    }

    --_size;
    return true;
}

void List::push_front(List::Data& data)
{
    if (_size > 1)
    {
        Node* temp = pHead;
        pHead = new Node(data, pHead);
        temp->pPrev = pHead;
    }
    else if (_size == 1)
    {
        pHead = new Node(data, pHead);
        pTail->pPrev = pHead;
    }
    else
    {
        pHead = pTail = new Node(data, pHead, pTail);
    }
    ++_size;
}

void List::push_back(Data &data)
{
    if (_size > 1)
    {
        Node* temp = pTail;
        pTail = new Node(data, nullptr, pTail);
        temp->pNext = pTail;
    }
    else if (_size == 1)
    {
        pTail = new Node(data, nullptr, pTail);
        pHead->pNext = pTail;
    }
    else
    {
        pHead = pTail = new Node(data, pHead, pTail);
    }
    ++_size;
}

void List::insert(Data data, size_t index)
{
    if (index == 0)
    {
        push_front(data);
        return;
    }

    else if (index >= _size)
    {
        push_back(data);
        return;
    }

    else if (index <= _size / 2)
    {
        Node* previous = pHead;

        for (size_t i = 0; i < index; ++i)
        {
            previous = previous->pNext;
        }

        Node* newNode = new Node(data, previous->pNext, previous);

        previous->pNext = newNode;
        newNode->pNext->pPrev = newNode;
    }
    else /*if (index > _size / 2)*/
    {
        Node* next = pTail;

        for (size_t i = _size-1; index < i; --i)
        {
            next = next->pPrev;
        }

        Node* newNode = new Node(data, next, next->pPrev);

        next->pPrev = newNode;
        newNode->pPrev->pNext = newNode;
    }

    ++_size;
}

bool List::removeAt(size_t index)
{
    if (index == 0)
    {
        return pop_front();
    }
    else if (index >= _size)
    {
        std::cout << "index(" << index << ") must be < size(" << _size << ")!" << std::endl;
        return false;   // pop_back()
    }

    else if (index <= _size / 2)
    {
        Node* previous = pHead;

        for (size_t i = 0; i < index; ++i)
        {
            previous = previous->pNext;
        }

        Node* toDelete = previous->pNext;

        previous->pNext = toDelete->pNext;
        toDelete->pNext->pPrev = previous;

        delete toDelete;
    }
    else /*if (index > _size / 2)*/
    {
        Node* next = pTail;

        for (size_t i = _size-1; index < i; --i)
        {
            next = next->pPrev;
        }

        Node* toDelete = next->pPrev;

        next->pPrev = toDelete->pPrev;
        toDelete->pPrev->pNext = next;

        delete toDelete;
    }

    --_size;
    return true;
}

size_t List::removeAll(const List::Data &data)
{
    if (_size == 0)
        return 0;

    size_t toReturn = 0;

    Node* curr = pHead;
    for (size_t i = 0; i < _size; ++i)
    {
        if ((curr != nullptr) && (curr->_data == data))
        {
            Node* toDelete = curr;

            if (curr == pHead)
            {
                curr->pNext->pPrev = nullptr;
                curr = pHead = pHead->pNext;
                delete toDelete;
            }
            else if (curr == pTail)
            {
                curr->pPrev->pNext = nullptr;
                pTail = curr->pPrev;
                delete toDelete;
                curr = nullptr;
            }
            else
            {
                curr->pPrev->pNext = curr->pNext;
                curr->pNext->pPrev = curr->pPrev;

                curr = curr->pNext;
                delete toDelete;
            }

            ++toReturn;
        }
        else
        {
            curr = curr->pNext;
        }
    }

    _size -= toReturn;

    if (_size == 0) pHead = pTail = nullptr;

    return toReturn;
}


List::Data* List::operator[](size_t index)
{
    if (index >= _size)
    {
        std::cout << "index(" << index << ") must be < size(" << _size << ")!" << std::endl;
        return nullptr;
    }

    Node* curr = nullptr;

    if (index <= _size / 2)
    {
        curr = pHead;
        for (size_t i = 0; i <= index; ++i)
        {
            curr = curr->pNext;
        }
    }
    else /*if (index > _size / 2)*/
    {
        curr = pTail;
        for (size_t i = _size-1; index <= i; --i)
        {
            curr = curr->pPrev;
        }
    }

    return &curr->_data;
}


List::Data *List::first()
{
    if (_size == 0)
        return nullptr;

    return &pHead->_data;
}

const List::Data *List::first() const
{
    if (_size == 0)
        return nullptr;

    return &pHead->_data;
}

List::Data *List::last()
{
    if (_size == 0)
        return nullptr;

    return &pTail->_data;
}

const List::Data *List::last() const
{
    if (_size == 0)
        return nullptr;

    return &pTail->_data;
}

void List::selectSort()
{
    for (Node* curr = pHead; curr != pTail; )
    {
        Node* min = curr;

        for (Node* next = curr->pNext; next != nullptr; next = next->pNext)
        {
            if (next->_data < min->_data)
            {
                min = next;
            }
        }

        if (min != curr)
        {
            if (curr == pHead)
            {
                pHead = min;
            }
            if (min == pTail)
            {
                pTail = curr;
            }

            if (min->pNext != nullptr)
            {
                min->pNext->pPrev = curr;
            }
            if (curr->pPrev != nullptr)
            {
                curr->pPrev->pNext = min;
            }

            if (curr->pNext == min)
            {
                curr->pNext = min->pNext;
                Node* currPrev = curr->pPrev;
                curr->pPrev = min;
                min->pNext = curr;
                min->pPrev = currPrev;
            }
            else
            {
                min->pPrev->pNext  = curr;
                curr->pNext->pPrev = min;

                std::swap(min->pPrev, curr->pPrev);
                std::swap(min->pNext, curr->pNext);
            }

            curr = min->pNext;

//            std::cout << *this;
        }
        else
        {
            curr = curr->pNext;
        }
    }
}

void List::toFile()
{
    std::ofstream fout("listFile.txt");

    if (!fout)
    {
        std::cerr << "File not open!" << std::endl;
    }
    else
    {
        fout << *this;
    }

    fout.close();
}


std::ostream &operator<<(std::ostream &os, const List &list)
{
    if (list._size == 0)
    {
        os << "List is Empty!\n";
        return os;
    }

    os << "List:\n";

    List::Node* curr = list.pHead;

    for (size_t i = 0; i < list._size; ++i)
    {
        os << curr->_data;
        curr = curr->pNext;
    }
    os << std::endl;

    return os;
}

