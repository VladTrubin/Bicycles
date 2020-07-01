#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "circle.h"



class List
{
private:
    using Data = Circle;

private:
    class Node
    {
    public:
        Node(const Data& data = Data(), Node* next = nullptr, Node* prev = nullptr);

        Node* pPrev;
        Node* pNext;
        Data _data;
    };

private:
    Node*   pHead;
    Node*   pTail;
    size_t  _size;

public:
    List();
    List(std::initializer_list<Data> args);
    List(const List& other);
    List(List&& other);
    ~List();

    Data* operator[](size_t index);
    List& operator=(const List& other);
    List& operator=(List&& other);

    inline size_t   getSize() const { return _size;      }
    inline bool     isEmpty() const { return _size == 0; }

    void move(List&& other);
    void clear();
    bool pop_front();
    bool pop_back();
    void push_front(Data& data);
    void push_back(Data& data);

    void    insert(Data data, size_t index);
    bool    removeAt(size_t index);
    size_t  removeAll(const Data& data);

    Data* first();
    const Data* first() const;
    Data* last();
    const Data* last() const;

    void selectSort();

    void toFile();


    friend std::ostream& operator<<(std::ostream& os, const List& list);

private:
    void _fill(const List& other);
};

std::ostream& operator<<(std::ostream& os, const List& list);

#endif // LIST_H
