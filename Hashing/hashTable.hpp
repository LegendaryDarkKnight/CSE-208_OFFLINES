#include <bits/stdc++.h>
using namespace std;

#define EMPTY 0
#define FILLED 1
#define DELETED 2
#define MAXN 1000000
#define BASE1 31
#define BASE2 67
#define SEP_CHAIN 'C'
#define DBL_HASH 'D'
#define CSTM_PROB 'P'
#define C1 47
#define C2 53
typedef unsigned long ll;

bool isPrime[MAXN];
vector<ll> primeNumbers;

void seive()
{
    for (ll i = 2; i < MAXN; i++)
        isPrime[i] = true;
    for (ll i = 4; i < MAXN; i += 2)
    {
        isPrime[i] = false;
    }
    for (ll i = 3; i * i < MAXN; i += 2)
    {
        if (isPrime[i])
        {
            for (ll j = i * i; j < MAXN; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    for (ll i = 2; i < MAXN; i++)
        if (isPrime[i])
            primeNumbers.push_back(i);
}

ll nearPrime(ll n)
{
    auto it1 = binary_search(primeNumbers.begin(), primeNumbers.end(), n);
    if (it1)
        return n;
    auto it = upper_bound(primeNumbers.begin(), primeNumbers.end(), n);
    if (it != primeNumbers.end())
        return (*it);
    else
        return n;
}

class hashTable
{
public:
    list<pair<string, ll>> *Table;
    char collRes;
    ll capacity;
    ll elements;
    short hashType;
    short *marker;


    hashTable(ll N, short hashType, char collRes) // hash is 1 or 2
    {
        this->collRes = collRes;
        capacity = nearPrime(N);
        elements = 0;
        this->hashType = hashType;
        marker = new short[capacity]{EMPTY};
        Table = new list<pair<string, ll>>[capacity];
    }
    ~hashTable()
    {
        for (ll i = 0; i < capacity; i++)
            Table[i].clear();
        delete[] Table;
    }

    ll resizeTable()
    {
        list<pair<string, ll>> *temp = new list<pair<string, ll>>[capacity];
        for (ll i = 0; i < capacity; i++)
        {
            temp[i] = Table[i];
        }
        for (ll i = 0; i < capacity; i++)
            Table[i].clear();
        delete[] Table;
        delete[] marker;

        ll oldcapacity = capacity;
        capacity = nearPrime(2 * capacity);
        elements = 0;
        // resizing
        marker = new short[nearPrime(2 * capacity)]{EMPTY};
        Table = new list<pair<string, ll>>[nearPrime(2 * capacity)];
        // rehashing

        ll collision = 0;
        for (ll i = 0; i < oldcapacity; i++)
        {
            collision += insert(temp[i].front().first, temp[i].front().second);
        }
        //
        for (ll i = 0; i < oldcapacity; i++)
            temp[i].clear();
        cout<<"resize"<<" "<<collision<<endl;
        delete[] temp;
        return collision;
    }

    ll Hash1(const string &key)
    {
        ll hash = 0;
        ll base_power = 1;

        for (char c : key)
        {
            hash = (hash + (c - 'a' + 1) * base_power)%capacity;
            base_power = (base_power * BASE1) ;
        }

        return hash%capacity;
    }
    ll Hash2(const string &key)
    {
        const ll A = 54059; 
        const ll B = 76963; 
        ll hash = BASE1;     

        for (char c : key)
        {
            hash = (hash * A) ^ (c * B);
        }

        return hash % capacity;
    }

    ll auxHash(const std::string &key)
    {
        ll hash = 0;

        for (char c : key)
        {
            hash = (hash * BASE2 + c) % capacity;
        }
        if(hash == 0){
            hash+=1;
        }
        return hash;
    }
    ll doubleHash(ll initialHash, ll auxHashValue, ll i)
    {
        return (initialHash + auxHashValue * i ) % capacity;
    }
    ll customHash(ll initialHash, ll auxHashValue, ll i)
    {
        return (initialHash + C1 * auxHashValue * i + C2 * i * i) % capacity;
    }

    pair<ll, ll> find(string key)
    {
        switch (collRes)
        {
        case SEP_CHAIN:
            return chainFind(key);
            break;
        case DBL_HASH:
            return doubleHashFind(key);
            break;
        case CSTM_PROB:
            return customProbingFind(key);
            break;
        default:
            break;
        }
        return {0, 0};
    }
    pair<ll, ll> chainFind(string key)
    {
        ll hash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll probes = 0;
        for (auto p : Table[hash])
        {
            probes++;
            if (p.first == key)
                return {p.second, probes};
        }
        return {0, probes};
    }
    pair<ll, ll> doubleHashFind(string key)
    {
        ll auxHashValue = auxHash(key);
        ll initialHash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll hash = initialHash;
        // cout<<hash<<endl;
        ll i = 0;
        ll probes = 0;
        while (marker[hash] != EMPTY)
        {
            probes++;
            if (Table[hash].size() and Table[hash].front().first == key)
            {
                return {Table[hash].front().second, probes};
            }
            i++;
            hash = doubleHash(initialHash, auxHashValue, i);
        }
        return {0, probes};
    }
    pair<ll, ll> customProbingFind(string key)
    {
        ll auxHashValue = auxHash(key);
        ll initialHash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll hash = initialHash;
        // cout<<hash<<endl;
        ll i = 0;
        ll probes = 0;
        while (marker[hash] != EMPTY)
        {
            probes++;
            if (Table[hash].size() and Table[hash].front().first == key)
            {
                return {Table[hash].front().second, probes};
            }
            i++;
            hash = customHash(initialHash, auxHashValue, i);
        }
        return {0, probes};
    }

    ll insert(string key, ll value)
    {
        if (find(key).first)
            return 0;
        ll collision = 0;
        if (elements == capacity and collRes != SEP_CHAIN)
        {
            collision = resizeTable();
        }
        elements++;
        switch (collRes)
        {
        case SEP_CHAIN:
            collision += chainInsert(key, value);
            break;
        case DBL_HASH:
            collision += doubleHashInsert(key, value);
            break;
        case CSTM_PROB:
            collision += customProbingInsert(key, value);
            break;
        default:
            break;
        }
        return collision;
    }
    ll chainInsert(string key, ll value)
    {
        ll hash = (hashType == 1) ? Hash1(key) : Hash2(key);
        Table[hash].push_back({key, value});
        return (Table[hash].size()>1);
    }
    ll doubleHashInsert(string key, ll value)
    {
        ll auxHashValue = auxHash(key);
        ll initialHash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll hash = initialHash;
        ll i = 0;
        ll collision = 0;
        while (Table[hash].size())
        {
            ++i;
            ++collision;
            hash = doubleHash(initialHash, auxHashValue, i);
        }
        Table[hash].push_back({key, value});
        marker[hash] = FILLED;
        return collision;
    }
    ll customProbingInsert(string key, ll value)
    {
        ll auxHashValue = auxHash(key);
        ll initialHash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll hash = initialHash;
        ll i = 0;
        ll collision = 0;
        while (Table[hash].size())
        {
            ++i;
            ++collision;
            hash = customHash(initialHash, auxHashValue, i);
        }
        Table[hash].push_back({key, value});
        marker[hash] = FILLED;
        return collision;
    }

    void Delete(string key)
    {
        switch (collRes)
        {
        case SEP_CHAIN:
            chainDelete(key);
            break;
        case DBL_HASH:
            doubleHashDelete(key);
            break;
        case CSTM_PROB:
            customProbingDelete(key);
            break;
        default:
            break;
        }
    }
    void chainDelete(string key)
    {
        ll auxHashValue = auxHash(key);
        ll initialHash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll hash = initialHash;
        for (auto p : Table[hash])
        {
            if (p.first == key)
            {
                Table[hash].remove(p);
                elements--;
                break;
            }
        }
    }
    void doubleHashDelete(string key)
    {
        ll auxHashValue = auxHash(key);
        ll initialHash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll hash = initialHash;
        ll i = 0;
        while (marker[hash] != EMPTY and Table[hash].front().first != key)
        {
            ++i;
            hash = doubleHash(initialHash, auxHashValue, i);
        }
        if (Table[hash].front().first == key)
        {
            elements--;
            marker[hash] = DELETED;
            Table[hash].pop_back();
        }
    }
    void customProbingDelete(string key)
    {
        ll auxHashValue = auxHash(key);
        ll initialHash = (hashType == 1) ? Hash1(key) : Hash2(key);
        ll hash = initialHash;
        ll i = 0;
        while (marker[hash] != EMPTY and Table[hash].front().first != key)
        {
            ++i;
            hash = customHash(initialHash, auxHashValue, i);
        }
        if (Table[hash].front().first == key)
        {
            elements--;
            marker[hash] = DELETED;
            Table[hash].clear();
        }
    }
};
