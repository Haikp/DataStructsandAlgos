template <typename t1, typename t2>
int hashMap<t1, t2>::h1(std::string key) const
{
    int sum = 0;

    for (int i = 0; i < key.length(); i += 2)
        sum += static_cast<int>(key[i]);

    return sum % tableSize;
}

template <typename t1, typename t2>
int hashMap<t1, t2>::h2(std::string key) const
{
     int sum = 0;

    for (int i = 1; i < key.length(); i += 2)
        sum += static_cast<int>(key[i]);

    return sum % tableSize;
}