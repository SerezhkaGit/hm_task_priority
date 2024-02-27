
#include <iostream>
using namespace std;

template<class T>
class MyQueue
{
private:
    pair<T*, int>* data;


public:
    MyQueue() : data{ new pair<T*, int>[5] }
    {
        for (int i = 0; i < 5; i++)
        {
            data[i].first = nullptr;
            data[i].second = 0;
        }
    }

    MyQueue(int size_) : data{ new pair<T*, int>[5] }
    {
        for (int i = 0; i < 5; i++)
        {
            data[i].second = size_;
            data[i].first = new T[size_];
        }
    }

    MyQueue(const MyQueue& ex) : data{ new pair<T*, int>[5] }
    {
        for (int i = 0; i < 5; ++i)
        {
            int size = ex.data[i].second;
            data[i].second = size;
            data[i].first = new T[size];

            for (int j = 0; j < size; ++j)
            {
                data[i].first[j] = ex.data[i].first[j];
            }
        }
    }


    ~MyQueue()
    {
        clear();
    }

    void clear()
    {
        delete[]data;
    }

    friend ostream& operator<<(ostream& out, MyQueue& ex)
    {
        for (int i = 0; i < 5; ++i)
        {
            int size = ex.data[i].second;

            for (int j = 0; j < size; ++j)
            {
                out << ex.data[i].first[j] << ' ';
            }
            cout << endl;
        }
        return out;
    }

    void push_back(int priority, T num)
    {
        int new_size = data[priority - 1].second + 1;
        T* tmp = new T[new_size];
        for (int i = 0; i < new_size; i++)
        {
            if (i == new_size - 1)
            {
                tmp[i] = num;
            }
            else
            {
                tmp[i] = data[priority - 1].first[i];
            }
        }
        delete[]data[priority - 1].first;
        data[priority - 1].first = tmp;
        data[priority - 1].second = new_size;
    }

    void pop_back(int priority)
    {
        int new_size = data[priority - 1].second - 1;
        T* tmp = new T[new_size];

        for (int i = 0; i < new_size; i++)
        {
            tmp[i] = data[priority - 1].first[i];
        }
        delete[]data[priority - 1].first;
        data[priority - 1].first = tmp;
        data[priority - 1].second = new_size;
    }

    bool Is_Empty(int priority)
    {
        if (data[priority - 1].second == 0)
        {
            return true;
        }
        else { return false; }
    }

    bool Is_Full(int priority)
    {
        if (!Is_Empty(priority))
        {
            return true;
        }
        else { return false; }
    }

    T get_first()
    {
        for (int i = 0; i < 5; i++)
        {
            if (data[i].first != nullptr)
            {
                return data[i].first[0];
            }
        }
    }

    T get_last()
    {
        for (int i = 4; i >= 0; i--)
        {
            if (data[i].first != nullptr)
            {
                for (int j = 0; j < data[i].second; j++)
                {
                    return data[i].first[data[i].second - 1];
                }
            }
        }
    }

    bool operator>(const MyQueue& right)
    {
        int sum_left = 0, sum_right = 0;
        for (int i = 0; i < 5; ++i) {
            sum_left += data[i].second;
            sum_right += right.data[i].second;
        }
        return sum_left > sum_right;
    }

    bool operator<(const MyQueue& right)
    {
        return right > *this;
    }
};

int main()
{
    MyQueue<int> l;
    l.push_back(1, 1);
    l.push_back(2, 2);
    l.push_back(3, 3);
    l.push_back(4, 4);
    l.push_back(5, 5);
    cout << l;
    cout << endl;

    cout << l.Is_Full(3);
    cout << l.Is_Empty(3);

    cout << endl;
    MyQueue<int> k(l);

    cout << k;
}

