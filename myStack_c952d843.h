#ifndef MYSTACK_C952D843_H
#define MYSTACK_C952D843_H

#include <algorithm>

template <typename Object>
class myStack
{
    public:
        myStack(const int& size)
        {
            theArray = new Object[size];
            m_size = size;
            topOfStack = -1;
        }

        myStack(const myStack<Object> & rhs): m_size{rhs.m_size},
            topOfStack{ rhs.topOfStack}, theArray {nullptr}
        {
            theArray = new Object[ m_size];
            for( int k = 0; k < m_size; ++k)
                theArray[ k ] = rhs.theArray[ k ];
        }


        myStack& operator= ( const myStack & rhs)
        {
            myStack copy = rhs;
            std::swap(*this, copy);
            return *this;
        }


        myStack( myStack<Object> && rhs): m_size{ rhs.m_size},
            topOfStack{ rhs.topOfStack}, theArray{ rhs.theArray}
        { }


        myStack& operator= ( myStack && rhs)
        {
            std::swap( m_size, rhs.m_size);
            std::swap(topOfStack, rhs.topOfStack);
            std::swap(theArray, rhs.theArray);

            return *this;
        }


        ~myStack(void)
        {
            delete [] theArray;
        }

        void reserve (const int & capacity)
        {
            Object *newArray = new Object[ m_size+capacity];
            for (int k = 0; k <= topOfStack; ++k)
                newArray[k] = std::move(theArray[k]);
            
            m_size = m_size+capacity;
            std::swap(theArray, newArray);
            delete [ ] newArray;


        }

        void push (const Object & rhs)
        {
            if (topOfStack+1 == m_size)
            {
                reserve(m_size*2);
            }
            topOfStack++;
            theArray[topOfStack] = rhs;
        }

        void pop(void)
        {
            topOfStack--;
        }

        Object & top(void)
        {
            return theArray[topOfStack];
        }

        int size(void)
        {
            return (topOfStack+1);
        }

        bool empty(void)
        {
            return (topOfStack == -1);
        }

    private:
        Object* theArray = nullptr;
        int m_size;
        int topOfStack;
};

#endif