#include <iostream>

using namespace std;

template<typename type>
class LL{
struct node{
    type data;
    node *prev;
    node *next;
};

public:
    class iterator{
    public: 
        friend class LL;
        iterator();
        iterator(node*);
        type operator*() const;
        const iterator& operator++(int);
        const iterator& operator--(int);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

    private:
        node * current;
    };

    LL();
    LL(const LL<type>&);
    const LL<type>& operator=(const LL<type>&);
    ~LL();

    void headInsert(const type&);
    void tailInsert(const type&);
    iterator begin() const;
    iterator end() const;
    void swapNodes(iterator&, iterator&);

private:
    node *head;
    node *tail;
};

template<typename type>
LL<type>::iterator::iterator(){
    current = nullptr;
}

template<typename type>
LL<type>::iterator::iterator(node *ptr){
    current = ptr;
}

template<typename type>
type LL<type>::iterator::operator*() const{
    return current->data;
}

template<typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator++(int){
    current = current->next;
    return *this;
}

template<typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator--(int){
    current = current->prev;
    return *this;
}

template<typename type>
bool LL<type>::iterator::operator==(const iterator& rhs) const{
    if(current == rhs.current){
        return true;
    }
    return false;
}

template<typename type>
bool LL<type>::iterator::operator!=(const iterator& rhs) const{
    if(current != rhs.current){
        return true;
    }

    return false;
}

template<typename type>
LL<type>::LL(){
    head = nullptr;
    tail = nullptr;
}

/*
template<typename type>
LL<type>::LL(const LL<type>& copy){

}
*/

/*
template<typename type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs){

    if(rhs.head == nullptr){
        return;
    }

    head = new node;
    head->next = nullptr;
    head->prev = nullptr;
    head->data = rhs.Head->data;
    tail = head;

    node *i1, *i2;
    i1 = rhs.head;
    i2 = head;
    i1 = rhs.head->next;

    while(i1 != nullptr){   
        //tail insert
    }
}
*/
template <typename type>
LL<type>::~LL(){
    while(head != nullptr){
        node *curr = head;
        head = head->next;
        delete curr;
    }

    head = nullptr;
    tail = nullptr;
}

template <typename type>
void LL<type>::headInsert(const type& item){
    //creates pointer and new node
    node *tmp = new node;
    tmp->data = item;
    tmp->prev = nullptr;
    tmp->next = head;
    head->prev = tmp;
    head = tmp;
    tmp = nullptr;
}

template <typename type>
void LL<type>::tailInsert(const type& item){
    if(head == nullptr){
        node *first = new node;
        first->data = item;
        first->prev = nullptr;
        first->next = nullptr;
        head = first;
        tail = first;
    }
    else{
        node *tmp = new node;
        tmp->data = item;
        tmp->prev = tail;
        tmp->next = nullptr;
        tail->next = tmp;
        tail = tmp;
        tmp = nullptr;
    }
    
}

template<typename type>
typename LL<type>::iterator LL<type>::begin() const{
    iterator start(head);
    return start;
}

template<typename type>
typename LL<type>::iterator LL<type>::end() const{
    iterator end(tail);
    return end;
}

template<typename type>
void LL<type>::swapNodes(iterator& it1, iterator& it2){
    //IF EQUAL 
    if(it1 == it2){
        return;
    }

    node *i1 = it1.current;
    node *i1left = i1->prev;
    node *i1right = i1->next;
    node *i2 = it2.current;
    node *i2left = i2->prev;
    node *i2right = i2->next;
    
    //ADJACENT
    if(i1->next == i2){
        if(i2 == tail){
            i1->next = nullptr;
            i1->prev = i2;
            i2->next = i1;
            i2->prev = i1left;
            i1left->next = i2;

            tail = i1;
        }
        
        else if(i1 == head){
            i2->prev = nullptr;
            i2->next = i1;
            i1->prev = i2;
            i1->next = i2right;
            i2right->prev = i1;

            head = i2;
        }
        //GENERAL CASE
        else{
            //moves i1 next to i2 right
            //i1 points back to i2
            i1->next = i2right;
            i1->prev = i2;

            //changes i2 right prev link to i1
            i2right->prev = i1;

            //changes i1 left next link to i2
            i1left->next = i2;

            //moves i2 prev to i1s left
            //moves i2 next to i1
            i2->prev = i1left;
            i2->next = i1;
        }
    }

    //NOT ADJACENT
    else if (i1->next != i2){
        if(i1 == head && i2 == tail){
            i1->prev = i2left;
            i2left->next = i1;

            i2->next = i1right;
            i1right->prev = i2;

            head = i2;
            tail = i1;

            i1->next = nullptr;
            i2->prev = nullptr;
        }
        else if(i1 == head && i2 != tail){
            i2->prev = nullptr;
            i2->next = i1right;
            i1right->prev = i2;

            i1->next = i2right;
            i1->prev = i2left;
            i2left->next = i1;
            i2right->prev = i1;

            head = i2;
        }
        else if(i2 == tail && i1 != head){
            i1->next = nullptr;
            i1->prev = i2left;

            i2->next = i1right;
            i2->prev = i1left;
            i1left->next = i2;
            i1right->prev = i2;
            i2left->next = i1;

            tail = i1;
        }
        //GERNERAL CASE
        else{
            //swaps i1 to i2
            i1->next = i2right;
            i1->prev = i2left;
            i2left->next = i1;
            i2right->prev = i1;

            //swaps i2 to i1
            i2->next = i1right;
            i2->prev = i1left;
            i1left->next = i2;
            i1right->prev = i2;
        }
    }
}