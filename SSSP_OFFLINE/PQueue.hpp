#include <bits/stdc++.h>
using namespace std;

template <typename key, typename value>
class PQueue
{
    int n;
    int last;
    pair<key, value> *heap;
    int *trace;
    int *availableKey;

public:
    PQueue(int n = 1);
    ~PQueue();
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    void heapifyDown(int i)
    {
        int min = i;
        if (left(i) < last and heap[left(i)].second < heap[min].second)
            min = left(i);
        if (right(i) < last and heap[right(i)].second < heap[min].second)
            min = right(i);
        if (min != i)
        {
            swap(trace[heap[min].first], trace[heap[i].first]);
            swap(heap[i], heap[min]);
            heapifyDown(min);
        }
    }
    void heapifyUp(int i)
    {
        if (heap[parent(i)].second > heap[i].second)
        {
            swap(trace[heap[parent(i)].first], trace[heap[i].first]);
            swap(heap[parent(i)], heap[i]);
            heapifyUp(parent(i));
        }
    }
    void insertKey(key K, value V)
    {
        if (last == n)
            return;
        heap[last++] = make_pair(K, V);
        availableKey[K] = 1;
        trace[K] = last - 1;
        heapifyUp(last - 1);
    }
    void decreaseKey(key K, value V)
    {
        if (heap[trace[K]].second <= V)
            return;
        heap[trace[K]].second = V;
        heapifyUp(trace[K]);
    }
    void extractMin()
    {
        if (last == 0)
            return;
        pair<key, value> min = heap[0];
        heap[0] = heap[last-1];
        //cout<<"Min First Trace"<<endl;
        availableKey[min.first] = 0;
        swap(trace[min.first],trace[heap[0].first]);
        last--;
        heapifyDown(0);
    }
    int size() { return last; }
    pair<key, value> getMin() { return heap[0]; }
    int isAvailable(key K){ return availableKey[K]; }
    void print()
    {
        for (int i = 0; i < last; i++)
            cout << heap[i].second << "("<<heap[i].first<<")("<<trace[heap[i].first]<<") ";
        cout << endl;
    }
};
template <typename key, typename value>
PQueue<key, value>::PQueue(int n)
{
    this->n = n;
    last = 0;
    heap = new pair<key, value>[n];
    trace = new int[n];
    availableKey = new int[n]{0};
}
template <typename key, typename value>
PQueue<key, value>::~PQueue()
{
    delete heap;
    delete trace;
    delete availableKey;
}
