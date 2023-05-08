/******************************************
 * implementation file
 * contains hashMap class to manage array of keys and values
******************************************/
#include <iostream>
using namespace std;

template <typename t1, typename t2>
class hashMap
{
public:
    hashMap();
    hashMap(const hashMap<t1, t2> &);
    const hashMap &operator=(const hashMap<t1, t2> &);
    ~hashMap();
    t2 &operator[](t1);

private:
    int items;
    int tableSize;

    struct tableItem
    {
        t1 key;
        t2 value;
    };

    tableItem *table1;
    tableItem *table2;

    int h1(char) const;
    int h2(char) const;

    void resize();
};

/**********************************************
 *  hashMap<t1, t2>::h1(key)
 *      parameter: key
 *      hashes the parameter
**********************************************/
template <typename t1, typename t2>
int hashMap<t1, t2>::h1(char key) const
{
    if (key >= 'A')
    {
        return (key - 50) % hashMap::tableSize;
    }

    return (key + 20) % hashMap::tableSize;
}

/**********************************************
 *  hashMap<t1, t2>::h2(char key)
 *      parameter: key
 *      second hash function if conflicts arise in the first hash method
**********************************************/
template <typename t1, typename t2>
int hashMap<t1, t2>::h2(char key) const
{
    if (key >= 'a')
    {
        return (key - 90) % hashMap::tableSize;
    }

    return (key + 50) % hashMap::tableSize;
}

/**********************************************
 *  hashMap<t1, t2>::resize()
 *      parameter: none
 *      create a larger table
 *      input the contents from the smaller table to the larger table
 *      rehash the previous hash table in to the larger hashMap
**********************************************/
template <typename t1, typename t2>
void hashMap<t1, t2>::resize()
{
    //reset items to 0
    hashMap::items = 0;
    //create pointers to hold the previous table
    tableItem *oldTable1, *oldTable2;
    oldTable1 = table1;
    oldTable2 = table2;
    
    //create new tables with the previous pointers
    int oldTableSize = tableSize;
    hashMap::tableSize = tableSize*2;
    table1 = new tableItem[tableSize];
    table2 = new tableItem[tableSize];

    //loop to insert the previous elements 
    for (int i = 0; i < oldTableSize; i++)
    {
        table1[i] = oldTable1[i];
        table2[i] = oldTable2[i];
    }

    //if the key is not empty, rehash the content
    for (int i = 0; i < oldTableSize; i++)
    {
        if (oldTable1[i].key != t1())
        {
        (*this)[oldTable1[i].key] = oldTable1[i].value;
        }

        if (oldTable2[i].key != t1())
        {
        (*this)[oldTable2[i].key] = oldTable2[i].value;
        }
    }

    //delete the previous files
    delete [] oldTable1;
    delete [] oldTable2;
    //set them to NULL accordingly
    oldTable1 = oldTable2 = NULL;
}

/**********************************************
 *  hashMap<t1, t2>::hashMap()
 *      default constructor
 *      parameter: none
 *      by default, set items to 0 with a tablesize of 10, create an array
**********************************************/
template <typename t1, typename t2>
hashMap<t1, t2>::hashMap()
{
    hashMap::items = 0;
    hashMap::tableSize = 10;
    table1 = new tableItem[tableSize];
    table2 = new tableItem[tableSize];
    
    for (int i = 0; i < tableSize; i++)
    {
        table1[i].key = table2[i].key = t1();
        table1[i].value = table2[i].value = t2();
    }
}

/**********************************************
 *  hashMap<t1, t2>::hashMap(const hashMap<t1, t2> &copy)
 *      parameter: value and key to copy
 *      deep copies the hashMap to *this map
**********************************************/
template <typename t1, typename t2>
hashMap<t1, t2>::hashMap(const hashMap<t1, t2> &copy)
{
    //copy the same values
    hashMap::items = copy.items;
    hashMap::tableSize = copy.tableSize;

    //create new tables
    this->table1 = new tableItem[tableSize];
    this->table2 = new tableItem[tableSize];

    //copy the data to the new tables
    for (int i = 0; i < copy.tableSize; i++)
    {
        table1[i].key = copy.table1[i].key;
        table1[i].value = copy.table1[i].value;
        table2[i].key = copy.table2[i].key;
        table2[i].value = copy.table2[i].value;
    }
}

/**********************************************
 *  hashMap<t1, t2>::operator=(const hashMap<t1, t2> &rhs)
 *      parameter: hashMap
 *      deallocate *this hashmap
 *      deep copies hashMap on rhs to *this map
**********************************************/
template <typename t1, typename t2>
const hashMap<t1, t2> &hashMap<t1, t2>::operator=(const hashMap<t1, t2> &rhs)
{
    delete [] table1;
    delete [] table2;

    //copy the same values as the rhs
    hashMap::items = rhs.items;
    hashMap::tableSize = rhs.tableSize;

    //create new tables
    this->table1 = new tableItem[tableSize];
    this->table2 = new tableItem[tableSize];

    //copy the values of the rhs table to the current table
    for (int i = 0; i < tableSize; i++)
    {
        table1[i].key = rhs.table1[i].key;
        table1[i].value = rhs.table1[i].value;
        table2[i].key = rhs.table2[i].key;
        table2[i].value = rhs.table2[i].value;
    }

    return *this;

}

/**********************************************
 *  hashMap<t1, t2>::~hashMap()
 *      destructor
 *      parameter: none
 *      delete tables once program finishes, set pointers to NULL
**********************************************/
template <typename t1, typename t2>
hashMap<t1, t2>::~hashMap()
{
    delete [] table1;
    table1 = NULL;
    delete [] table2;
    table2 = NULL;
}

/**********************************************
 *  hashMap<t1, t2>::operator[](t1 key)
 *      parameter: key
 *      hashing the key through two methods
 *      check on table one if there is a possible location for the hashing
 *      if so, place it there, otherwise try method two
 *      resize if half the table is full
**********************************************/
template <typename t1, typename t2>
t2 &hashMap<t1, t2>::operator[](t1 key)
{
    int x = 0;
    //hash the key with the first method
    x = h1(key);
    int y = 0;
    //hash they key with the second method
    y = h2(key);

    //if half the table is full, resize the table
    //cout << "ratio: " << static_cast<double>(items) / static_cast<double>(tableSize) << endl;
    if (static_cast<double>(items) / static_cast<double>(tableSize) >= .5)
    {
        resize();
    }

    int i = 0;
    int j = 0;
    //loop through the hash table to check of available hashing locations
    while(true)
    {
        //if there is a spot for hashing method one, place the key there
        if (table1[(x + i * y) % tableSize].key == t1())
        {
            table1[(x + i * y) % tableSize].key = key;
            items++;
            return table1[(x + i * y) % tableSize].value;
        }

        //if the key already exists, then return
        if (table1[(x + i * y) % tableSize].key == key)
        {
            return table1[(x + i * y) % tableSize].value;
        }

        //if there is a spot for hashing method two, place the key there
        if (table2[(y + i * x) % tableSize].key == t1())
        {
            table2[(y + i * x) % tableSize].key = key;
            items++;
            return table2[(y + i * x) % tableSize].value;
        }

        //if the key already exists, then return
        if (table2[(y + i * x) % tableSize].key == key)
        {
            return table2[(y + i * x) % tableSize].value;
        }

        //if there are no possible locations or there are collisions, change the i value and retry the hashing
        if (j % 2 == 0)
        {
            i += x;
        }
        else
        {
            i += y;
        }

        j++;
    }
}
