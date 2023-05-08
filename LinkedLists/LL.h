/******************************************
 * Assignment01.h Does the Following: 
 * implementation file
 * establishes the body of Card class and Deck class functions
******************************************/
#include <iostream>
using namespace std;
template <typename type>
class LL
{
    struct node
    {
        type data;
        node * prev;
        node * next;
    };
    
    public:
        class iterator
        {
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
        node * head;
        node * tail;
};

/**********************************************
 *  iterator
 *      default constructor
 *      if there are no parameters upon calling this function, set current pointer to NULL
**********************************************/ 
template <typename type>
LL<type>::iterator::iterator(){
    current = NULL;
}

/**********************************************
 *  iterator
 *      constructor with parameter
 *      given a pointer as a parameter,
 *      
**********************************************/ 
template <typename type>
LL<type>::iterator::iterator(node * ptr){
    current = ptr;
}

/**********************************************
 *  operator*
 *      dereference operator
 *      returns data within the pointer
**********************************************/ 
template <typename type>
type LL<type>::iterator::operator*() const{
    return current->data;
}

/**********************************************
 *  operator++
 *      increment operator
 *      moves pointer to the next node in the LL
**********************************************/ 
template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator++(int){
    current = current->next;
    return *this;
}

/**********************************************
 *  operator--
 *      decrement operator
 *      moves pointer to the previous node in the LL
**********************************************/ 
template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator--(int){
    current = current->prev;
    return *this;
}

/**********************************************
 *  operator==
 *      comparator operator
 *      compares two iterators, this iterator, and the right hand side iterator
 *      checks to see if they are the same
**********************************************/ 
template <typename type>
bool LL<type>::iterator::operator==(const iterator& rhs) const{
    if (this->current == rhs.current){
        return true;
    }

    return false;
}

/**********************************************
 *  operator!=
 *      comparator operator
 *      compares two iterators, this iterator, and the right hand side iterator
 *      checks to see if they are the different
**********************************************/ 
template <typename type>
bool LL<type>::iterator::operator!=(const iterator& rhs) const{
        if (this->current != rhs.current){
        return true;
    }

    return false;
}

/**********************************************
 *  LL
 *      default constructor
 *      given no parameters, set the head and tail to NULL
**********************************************/ 
template <typename type>
LL<type>::LL(){
    head = NULL;
    tail = NULL;
}

/**********************************************
 *  LL
 *      copy constructor with parameters
 *      given a LL to copy from as a paramter
 *      deep copy the parameter LL to this->LL
**********************************************/ 
template <typename type>
LL<type>::LL(const LL<type>& copy){
    //proceed to deep copy other LL to this->LL
    if (copy.head == NULL){
        return;
    }

    //allocate memory for data
    head = new node;
    //copy in the data into the new linked list
    head->data = copy.head->data;
    head->next = NULL;
    //establish iterators that will traverse the linked list
    node * iter1, * iter2, * iter3;
    //iter1 traverses the LL we will copy
    iter1 = copy.head;
    //iter2 traverses this->LL
    iter2 = this->head;
    //iter3 keeps track of the prev node in this->LL
    iter3 = this->head;
    iter1 = iter1->next;

    //loop and copy entire linked list until iter1 traversed the whole LL
    while (iter1 != NULL){
        //allocate mem for new node
        iter2->next = new node;
        //move pointer to the new node
        iter2 = iter2->next;
        //insert data from the copy LL
        iter2->data = iter1->data;
        //set previous pointer
        iter2->prev = iter3;
        //move iter3 up for next iteration
        iter3 = iter3->next;
        //move iter1 for next iteration
        iter1 = iter1->next;
        //set the tail
        tail = iter2;
        //mark the end of the LL
        iter2->next = NULL;
    }
}

/**********************************************
 *  operator=
 *      check if this->LL is empty
 *      if its not empty, deallocate the entire LL
 *      call the copy constructor
**********************************************/ 
template <typename type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs){

    if(this->head == rhs.head){
        return *this;
    }
    //clear this->LL
    if (this->head != NULL){
        node * del;

        //delete until this->LL is empty
        while (head != NULL){
            //point to the head
            del = head;
            //move the head up
            head = head->next;
            //delete the pointer
            delete del;
        }

        head = NULL;
    }

    //proceed to deep copy other LL to this->LL
    if (rhs.head == NULL){
        return *this;
    }

    //allocate memory for data
    head = new node;
    //copy in the data into the new linked list
    head->data = rhs.head->data;
    head->next = NULL;
    //establish iterators that will traverse the linked list
    node * iter1, * iter2, * iter3;
    //iter1 traverses the LL we will copy
    iter1 = rhs.head;
    //iter2 traverses this->LL
    iter2 = this->head;
    //iter3 keeps track of the prev node in this->LL
    iter3 = this->head;
    iter1 = iter1->next;

    //loop and copy entire linked list until iter1 traversed the whole LL
    while (iter1 != NULL){
        //allocate mem for new node
        iter2->next = new node;
        //move pointer to the new node
        iter2 = iter2->next;
        //insert data from the copy LL
        iter2->data = iter1->data;
        //set previous pointer
        iter2->prev = iter3;
        //move iter3 up for next iteration
        iter3 = iter3->next;
        //move iter1 for next iteration
        iter1 = iter1->next;
        //set the tail
        tail = iter2;
        //mark the end of the LL
        iter2->next = NULL;
    }

    return *this;
}

/**********************************************
 *  ~LL
 *      destructor
 *      deallocate the entire LL
**********************************************/ 
template <typename type>
LL<type>::~LL(){
    node * del;

    //delete until this->LL is empty
    while (head != NULL){
        //point to the head
        del = head;
        //move the head up
        head = head->next;
        //delete the pointer
        delete del;
    }
}

/**********************************************
 *  headInsert
 *      parameter of an item to insert to linked list
 *      takes parameter, place it at the front of the LL
 *      connect head to new node accord to doubly LL
**********************************************/ 
template <typename type>
void LL<type>::headInsert(const type& item){
    node * ins;
    ins = new node;
    if (head == NULL){
        head = ins;
        tail = ins;

        head->prev = NULL;
        tail->next = NULL;
    }

    head->prev = NULL;
    tail->next = NULL;

    //store item into a new node
    ins->data = item;
    //set node behind the head
    ins->next = head;
    //connect head to new node for doubly linked list
    head->prev = ins;
    //establish node as the new head
    ins->prev = NULL;
    head = ins;
    ins = NULL;
}

/**********************************************
 *  tailInsert
 *      parameter of an item to insert to linked list
 *      takes parameter, place it in the back of the LL
 *      connect tail to new node accord to doubly LL
**********************************************/ 
template <typename type>
void LL<type>::tailInsert(const type& item){
    node * ins;
    ins = new node;
    if (tail == NULL){
        tail = ins;
        head = ins;

        head->prev = NULL;
        tail->next = NULL;
    }

    head->prev = NULL;
    tail->next = NULL;

    //store item into a new node
    ins->data = item;
    //set node after tail
    ins->prev = tail;
    //connect tail to node for doubly LL
    tail->next = ins;
    //establish node as new tail
    ins->next = NULL;
    tail = ins;
    ins = NULL;
}

/**********************************************
 *  begin
 *      creates a pointer under iterator class
 *      sets pointer to head
 *      return the pointer
**********************************************/ 
template <typename type>
typename LL<type>::iterator LL<type>::begin() const{
    iterator start(head);
    return start;
}

/**********************************************
 *  end
 *      creates a pointer under iterator class
 *      sets pointer to tail
 *      return the pointer
**********************************************/ 
template <typename type>
typename LL<type>::iterator LL<type>::end() const{
    iterator last(tail);
    return last;
}

/**********************************************
 *  swapNodes
 *      check if the two iterators passed in is the same
 *      establish nodes to traverse LL
 *      depending on the conditions of the two iterator parameters, use different algorithm accordingly
 *      check if two nodes are adjacent
 *      check if either iterators are the head or tail
 *      move the head and tail pointer when necessary
**********************************************/ 
template <typename type>
void LL<type>::swapNodes(iterator& it1, iterator& it2){
    //if they are the same nodes, return
    if (it1 == it2){
        return;
    }

    node * i1Prev, * i1, * i1Next, * i2Prev, * i2, * i2Next;

    //establish pointers
    i1 = it1.current;
    i1Prev = i1->prev;
    i1Next = i1->next;
    i2 = it2.current;
    i2Prev = i2->prev;
    i2Next = i2->next;
    
    bool adjacent = i1->next == i2 || i2->next == i1;
    
    //swaps nodes through this algorithm if they aren't adjacent
    if (!adjacent){
        //check to see if i2 is potenially the tail
        if (i2 != tail){
            i1->next = i2Next;
            i2Next->prev = i1;
        }

        //check to see if i2 is the head
        if (i2 != head){
            i2Prev->next = i1;
            i1->prev = i2Prev;
        }

        //check to see if i1 is the tail
        if (i1 != tail){
            i2->next = i1Next;
            i1Next->prev = i2;
        }

        //check to see if i1 is the head
        if (i1 != head){
            i1Prev->next = i2;
            i2->prev = i1Prev;
        }
    }
    
    //swaps nodes through this algorithm if they are adjacent
    if (adjacent){
        //if i2 is to the right of i1
        if (i1->next == i2){
            //check if i2 is the tail
            if (i2 != tail){
                i1->next = i2Next;
                i2Next->prev = i1;
            }

            i2->next = i1;
            i1->prev = i2;

            //check if i1 is the head
            if (i1 != head){
                i1Prev->next = i2;
                i2->prev = i1Prev;
            }
        }

        //if i1 is to the right of i2
        else if (i2->next == i1){
            //check if i1 is the tail
            if (i1 != tail){
                i2->next = i1Next;
                i1Next->prev = i2;
            }

            i1->next = i2;
            i2->prev = i1;

            //check if i2 is the head
            if (i2 != head){
                i2Prev->next = i1;
                i1->prev = i2Prev;
            }
        }
    }

    //after nodes have swapped, check if any of them are the head or tail
    //if i1 is originally the head preswap, make head point to i2
    if (i1 == head){
        head = i2;
        i2->prev = NULL;
    }

    //if i2 is originally the head preswap, make head point to i1
    else if (i2 == head){
        head = i1;
        i1->prev = NULL;
    }

    //if i1 is originally the tail preswap, make tail point to i2
    if (i1 == tail){
        tail = i2;
        i2->next = NULL;
    }

    //if i2 is originally the tail preswap, make tail point to i1
    else if (i2 == tail){
        tail = i1;
        i1->next = NULL;
    }
}
