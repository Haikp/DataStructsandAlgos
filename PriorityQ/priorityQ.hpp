/******************************************
 * implementation file
 * contains priorityQ class to manage insertion and sorting the array according to a max heap
******************************************/
#include <iostream>
using namespace std;

template <typename type>
class priorityQ
{
public:
    priorityQ(int = 10);
    priorityQ(const priorityQ<type> &);
    ~priorityQ();
    const priorityQ<type> &operator=(const priorityQ<type> &);
    void insert(const type &);
    void deleteHighestPriority();
    type getHighestPriority() const;
    bool isEmpty() const;
    void bubbleUp(int);
    void bubbleDown(int);
    int getSize() const;

private:
    int capacity;
    int items;
    type *heapArray;
};

/**********************************************
 *  priorityQ(int capacity)
 *      parameter: capacity, size of array
 *      creates a new heap array
**********************************************/
template <typename type>
priorityQ<type>::priorityQ(int capacity)
{
    this->capacity = capacity;
    //dynamically allocate an array
    heapArray = new type[capacity];
    priorityQ::items = 0;
}

/**********************************************
 *  priorityQ(const priorityQ<type>& copy)
 *      parameter: another heapArray
 *      copies the list of values
**********************************************/
template <typename type>
priorityQ<type>::priorityQ(const priorityQ<type>& copy)
{
    //copy the capacity and items amount
    priorityQ::capacity = copy.capacity;
    priorityQ::items = copy.items;

    //create a new array
    this->heapArray = new type[capacity];
    //for loop and copy the entire array
    for (int i = 0; i < priorityQ::items; i++)
    {
        this->heapArray[i] = copy.heapArray[i];
    }
}

/**********************************************
 *  ~priorityQ()
 *      parameter: none
 *      destructor, deletes array
**********************************************/
template <typename type>
priorityQ<type>::~priorityQ()
{
    delete [] heapArray;
    heapArray = NULL;
}

/**********************************************
 *  operator=(const priorityQ<type>& rhs)
 *      parameter: rhs
 *      deletes this array
 *      deep copy of the array on the right hand side
 *      return *this
**********************************************/
template <typename type>
const priorityQ<type> &priorityQ<type>::operator=(const priorityQ<type>& rhs)
{
    //delete the contents of this array
    delete [] heapArray;

    //copy the capacity and items amount
    priorityQ::capacity = rhs.capacity;
    priorityQ::items = rhs.items;

    //create a new array
    this->heapArray = new type[capacity];
    //for loop and copy the entire array
    for (int i = 0; i < priorityQ::items; i++)
    {
        this->heapArray[i] = rhs.heapArray[i];
    }

    return *this;
}

/**********************************************
 *  insert(const type& element)
 *      parameter: element
 *      resizes if necessary
 *      inserts in to the new array
 *      increments the amount of items
 *      bubbleUp the element in to its correct spot
**********************************************/
template <typename type>
void priorityQ<type>::insert(const type& element)
{
    //resize if items exceed the capacity
    if(items >= capacity)
    {
        capacity *= 2;
    }

    //increment amount items
    priorityQ::items++;
    //insert the element into array
    heapArray[items] = element;
    priorityQ::bubbleUp(items);
}

/**********************************************
 *  deleteHighestPriority()
 *      parameter: none
 *      change the head of the heap into the last value in the array
 *      bubble down that value back down
 *      decrement the amount of items
**********************************************/
template <typename type>
void priorityQ<type>::deleteHighestPriority()
{
    //return if the array is empty
    if (priorityQ::isEmpty())
    {
        return;
    }

    //replace the head
    heapArray[0] = heapArray[items];
    //decrement amount of items
    priorityQ::items--;
    priorityQ::bubbleDown(0);
}

/**********************************************
 *  getHighestPriority() const
 *      parameter: none
 *      return the head of the heapArray
**********************************************/
template <typename type>
type priorityQ<type>::getHighestPriority() const
{
    return heapArray[0];
}

/**********************************************
 *   isEmpty() const
 *      parameter: none
 *      check if the array is empty, return true if it is empty
**********************************************/
template <typename type>
bool priorityQ<type>::isEmpty() const
{
    if (priorityQ::items == 0)
    {
        return true;
    }

    return false;
}

/**********************************************
 *  bubbleUp(int index)
 *      parameter: index
 *      use the index in the array to move the node up
 *      only move the node up if it is larger than its parent
**********************************************/
template <typename type>
void priorityQ<type>::bubbleUp(int index)
{
    //if the child node is larger than the parent node
    if (heapArray[index] > heapArray[index/2])
    {
        //being swapping the nodes
        int temp = heapArray[index];
        heapArray[index] = heapArray[index/2];
        heapArray[index/2] = temp;
        //recursively call bubble up until the child is smaller than the parent
        priorityQ<type>::bubbleUp(index/2);
    }
}

/**********************************************
 *  bubbleDown(int index)
 *      parameter: index
 *      checks if a child node exists
 *      check which child node is larger than the other
 *      swap the parent with the larger child node
**********************************************/
template <typename type>
void priorityQ<type>::bubbleDown(int index)
{
    //if a child node exists
    if (2*index < priorityQ::items)
    {
        int temp = heapArray[index];
        //if the left child is larger than the right child
        if (heapArray[2*index] > heapArray[2*index + 1])
        {
            //swap the parent and the left child
            heapArray[index] = heapArray[2*index];
            heapArray[2*index] = temp;
            //recursively call bubbleDown until there are no child nodes avaliable, becoming a leaf
            priorityQ::bubbleDown(2*index);
        }
        else
        {
            //else swap with the right node
            heapArray[index] = heapArray[2*index + 1];
            heapArray[2*index + 1] = temp;
            //recursively call bubbleDown until there are no child nodes avaliable, becoming a leaf
            priorityQ::bubbleDown(2*index + 1);
        }
    }
}

/**********************************************
 *  getSize() const
 *      parameter: none
 *      return the amount of items in the array
**********************************************/
template <typename type>
int priorityQ<type>::getSize() const
{
    return priorityQ::items;
}
