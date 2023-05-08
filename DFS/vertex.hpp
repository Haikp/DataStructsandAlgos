/******************************************
 * vertex implementation file
 * accompanies depth first search
******************************************/
#include <iostream>
using namespace std;

template <class type>
class vertex
{
    struct node
    {
        type item;
        node *link;
    };

public:
    class edgeIterator
    {
    public:
        friend class vertex;
        edgeIterator();
        edgeIterator(node *);
        edgeIterator operator++(int);
        type operator*();
        bool operator==(const edgeIterator &);
        bool operator!=(const edgeIterator &);

    private:
        node *current;
    };

    vertex();
    vertex(const vertex<type> &);
    const vertex &operator=(const vertex<type> &);
    ~vertex();
    edgeIterator begin();
    edgeIterator end();
    void addEdge(const type &);

private:
    node *neighbors;
};

/**********************************************
 *  vertex<type>::edgeIterator::edgeIterator()
 *      default constructor
 *      parameter: none
 *      sets current node to NULL;
**********************************************/
template <class type>
vertex<type>::edgeIterator::edgeIterator()
{
    edgeIterator::current = NULL;
}

/**********************************************
 *  vertex<type>::edgeIterator::edgeIterator(vertex<type>::node *edge)
 *      parameter: edge, door between locations
 *      sets current node to edge assigned
**********************************************/
template <class type>
vertex<type>::edgeIterator::edgeIterator(vertex<type>::node *edge)
{
    edgeIterator::current = edge;
}

/**********************************************
 *  typename vertex<type>::edgeIterator vertex<type>::edgeIterator::operator++(int)
 *      parameter: int
 *      increments the iterator
 *      move the player to the next room
**********************************************/
template <class type>
typename vertex<type>::edgeIterator vertex<type>::edgeIterator::operator++(int)
{
    return current = current->link;
}

/**********************************************
 *  vertex<type>::edgeIterator::operator*()
 *      parameter: pointer
 *      dereference operator, return the room name
**********************************************/
template <class type>
type vertex<type>::edgeIterator::operator*()
{
    return current->item;
}

/**********************************************
 *  vertex<type>::edgeIterator::operator==(const vertex<type>::edgeIterator &rhs)
 *      parameter: rhs edgeIterator
 *      checks if two rooms/edges are the same
**********************************************/
template <class type>
bool vertex<type>::edgeIterator::operator==(const vertex<type>::edgeIterator &rhs)
{
    if (current == rhs.current)
    {
        return true;
    }

    return false;
}

/**********************************************
 *  vertex<type>::edgeIterator::operator!=(const vertex<type>::edgeIterator &rhs)
 *      parameter: rhs edgeIterator
 *      checks if two rooms/edges are NOT the same
**********************************************/
template <class type>
bool vertex<type>::edgeIterator::operator!=(const vertex<type>::edgeIterator &rhs)
{
    if (current != rhs.current)
    {
        return true;
    }

    return false;
}

/**********************************************
 *  vertex<type>::vertex()
 *      default constructor
 *      parameter: none
 *      sets neighbor to NULL
**********************************************/
template <class type>
vertex<type>::vertex()
{
    vertex::neighbors = NULL;
}

/**********************************************
 *  vertex<type>::vertex(const vertex<type> &copy)
 *      parameter: vertex to copy
 *      copies vertex room
**********************************************/
template <class type>
vertex<type>::vertex(const vertex<type> &copy)
{
    neighbors = NULL;
    //check if there is a vertex to copy
    if (copy.neighbors != NULL)
    {
        //establish pointer to maintain the head
        node *head;
        //iterate through rhs vertex
        node *iter = copy.neighbors;
        //temp pointer to copy data over
        node *temp;
        //while there is still something to copy
        while(iter != NULL)
        {
            //create new node
            temp = new node;
            //take data from rhs
            temp->item = iter->item;
            temp->link = NULL;
            //if the node is empty, take the temp node as the head
            if (neighbors == NULL)
            {
                neighbors = temp;
                head = neighbors;
            }
            //else tail insert
            else
            {
                neighbors->link = temp;
                neighbors = neighbors->link;
            }

            //prep for next iteration to copy
            iter = iter->link;
        }

        //move neighbor back to head
        neighbors = head;
    }
}

/**********************************************
 *  const vertex<type> &vertex<type>::operator=(const vertex<type> &rhs)
 *      assignment operator
 *      parameter: rhs vertex
 *      copies rhs data
**********************************************/
template <class type>
const vertex<type> &vertex<type>::operator=(const vertex<type> &rhs)
{
    //check if rhs is empty
    if (rhs.neighbors == NULL)
    {
        return *this;
    }

    //deallocate entire linked list
    node *del;
    while (neighbors != NULL)
    {
        del = this->neighbors;
        this->neighbors = this->neighbors->link;
        delete del;
    }

    del = NULL;
    
    
    //establish pointer to maintain the head
    node *head;
    //iterate through rhs vertex
    node *iter = rhs.neighbors;
    //temp pointer to copy data over
    node *copy;
    //while there is still something to copy
    while(iter != NULL)
    {
        //create new node
        copy = new node;
        //take data from rhs
        copy->item = iter->item;
        copy->link = NULL;
        //if the node is empty, take the temp node as the head
        if (neighbors == NULL)
        {
            neighbors = copy;
            head = neighbors;
        }
        //else tail insert
        else
        {
            neighbors->link = copy;
            neighbors = neighbors->link;
        }

        //prep for next iteration to copy
        iter = iter->link;
    }

    //move neighbor back to head
    neighbors = head;

    return *this;
}

/**********************************************
 *  vertex<type>::~vertex()
 *      destructor
 *      parameter: none
 *      deletes linked list
**********************************************/
template <class type>
vertex<type>::~vertex()
{
    node *del;

    //delete node until no node exists after
    while (neighbors != NULL)
    {
        del = neighbors;
        neighbors = neighbors->link;
        delete del;
    }

    del = NULL;
}

/**********************************************
 *  vertex<type>::edgeIterator vertex<type>::begin()
 *      parameter: none
 *      returns the current room
**********************************************/
template <class type>
typename vertex<type>::edgeIterator vertex<type>::begin()
{
    edgeIterator start(neighbors);
    return start;
}

/**********************************************
 *  vertex<type>::edgeIterator vertex<type>::end()
 *      parameter: none
 *      returns the end goal, NULL
**********************************************/
template <class type>
typename vertex<type>::edgeIterator vertex<type>::end()
{
    edgeIterator iter(NULL);
    return iter;
}

/**********************************************
 *  vertex<type>::addEdge(const type &edge)
 *      parameter: edge/room name
 *      creates a link between the one who called the function, and the parameter
**********************************************/
template <class type>
void vertex<type>::addEdge(const type &edge)
{
    node *ins;
    ins = new node;

    //if there is no neighbor
    if(neighbors == NULL)
    {
        ins->item = edge;
        ins->link = NULL;
    }
    //else make a link to the neighbor
    else
    {
        ins->item = edge;
        ins->link = neighbors;
    }

    neighbors = ins;
}
