#ifndef MYQUEUE_C952D843_H
#define MYQUEUE_C952D843_H

#include<algorithm>

template <typename Object>
class myQueue
{
    public:
        myQueue(const int& size)
        {
            theArray = new Object[size];
            currentSize = 0;
            m_capacity = size;
            m_front = m_capacity-2;
            m_back = m_capacity-1;
        }

        myQueue(const myQueue<Object> & rhs): currentSize{rhs.currentSize},
            m_capacity{ rhs.m_capacity}, theArray {nullptr}, m_back{rhs.m_back},
            m_front{ rhs.m_front}
        {
            theArray = new Object[ m_capacity];
            for( int k = 0; k < m_capacity; ++k)
                theArray[ k ] = rhs.theArray[ k ];
        }

        myQueue& operator= (const myQueue & rhs)
        {
            myQueue copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        myQueue ( myQueue<Object> && rhs): currentSize{rhs.currentSize},
            m_capacity{ rhs.m_capacity}, theArray {rhs.theArray}, m_back{rhs.m_back},
            m_front{ rhs.m_front}
        { }

        myQueue& operator= ( myQueue && rhs)
        {
            std::swap( currentSize, rhs.currentSize);
            std::swap(m_capacity, rhs.m_capacity);
            std::swap( m_front, rhs.m_front);
            std::swap(m_back, rhs.m_back);
            std::swap(theArray, rhs.theArray);

            return *this;
        }

        ~myQueue(void)
        {
            delete [] theArray;
        }

        void reserve(const int & capacity)
        {
            Object *newArray = new Object[ currentSize+capacity];

            for (int k = 0; k < currentSize; ++k){
                newArray[(k+m_front)%(currentSize+capacity)] = std::move(theArray[(k+m_front)%currentSize]);
                m_back = (k+m_front)%(currentSize+capacity);
            }
            
            m_capacity = currentSize+capacity;
            
            std::swap(theArray, newArray);
            delete [ ] newArray;
        }

        void enqueue (const Object & rhs)
        {
            if ((m_back+1)%m_capacity == m_front)
            {
                reserve(m_capacity*2);
            }
            if (currentSize == 0)
            {
                theArray[m_front] = rhs;
                currentSize++;
            }else{
                m_back = (m_back +1)%m_capacity;
                theArray[m_back] = rhs;
                currentSize++;
            }
        }

        void dequeue(void)
        {
            m_front = (m_front++)%m_capacity;
            currentSize--;
        }

        Object & front(void)
        {
            return theArray[m_front];
        }

        int size(void)
        {
            return currentSize;
        }

        bool empty(void)
        {
            return (currentSize == 0);
        }
    private:
        Object* theArray;
        int currentSize;
        int m_capacity;
        int m_back;
        int m_front;
};

#endif