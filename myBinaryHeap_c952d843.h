#ifndef MY_BINARY_HEAP
#define MY_BINARY_HEAP

#include<vector>
#include<stdexcept>
using namespace std;

template <typename Comparable>
class myBinaryHeap
{
    public:
    explicit myBinaryHeap( int capacity = 100 ) 
        :array(100), currentSize{0}
    {
        //currentSize = 0;
    }
    explicit myBinaryHeap( const vector<Comparable> & items )
        : array( items.size( ) + 10 ), currentSize{ items.size( ) }
    {
        for( int i = 0; i < items.size( ); ++i )
            array[ i+1]= items[ i ];
        buildHeap( );
    }

    bool isEmpty( ) const
    {
        return array.empty();
    }
    const Comparable & findMin( ) const
    {
        return array[1];
    }

    void insert( const Comparable & x )
    {
        if( currentSize == array.size( )-1)
            array.resize( array.size( ) * 2 );

        // Percolate up
        int hole = ++currentSize;
        Comparable copy = x;

        array[ 0 ] = std::move( copy );
        for( ; x < array[ hole / 2 ]; hole /= 2 )
            array[ hole ] = std::move( array[ hole / 2 ] );
        array[ hole ] = std::move( array[ 0 ] );
    }
    void insert( Comparable && x )
    {
        if( currentSize == array.size( )-1)
            array.resize( array.size( ) * 2 );

        // Percolate up
        int hole = ++currentSize;
        Comparable copy = x;

        array[ 0 ] = std::move( copy );
        for( ; x < array[ hole / 2 ]; hole /= 2 )
            array[ hole ] = std::move( array[ hole / 2 ] );
        array[ hole ] = std::move( array[ 0 ] );
    }
    void deleteMin( )
    {
        if( isEmpty( ) )
            return;

        array[ 1 ] = std::move( array[ currentSize-- ] );
        percolateDown( 1 );
    }
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            return;

        minItem = std::move( array[ 1 ] );
        array[ 1 ] = std::move( array[ currentSize-- ] );
        percolateDown( 1 );
    }
    void makeEmpty( )
    {
        array.clear();
    }

    bool verifyHeapProperty (void)
    {
        bool truth = true;
        for (int i = 2; i <= currentSize; i++){
            if(array[1] > array[i]){
                truth = false;
            }
        }
	    return truth;
    }

    bool increaseKey (const int p, const int d)
    {
        if (p < 1 || p > currentSize){
            return false;
        }else{
            array[p] = array[p]+d;
            percolateDown(p);
            return true;
        }
    }

    bool decreaseKey (const int p, const int d)
    {
	    if (p < 1 || p > currentSize){
            return false;
        }else{
            array[p] = array[p]-d;
            int hole = p;
            Comparable copy = array[p];

            array[ 0 ] = std::move( copy );
            for( ; copy < array[ hole / 2 ]; hole /= 2 )
                array[ hole ] = std::move( array[ hole / 2 ] );
            array[ hole ] = std::move( array[ 0 ] );
            return true;
        }
    }

    myBinaryHeap & merge(myBinaryHeap & rhs)
    {
        for (int i = 1; i <= rhs.currentSize; i++){
            insert(rhs.array[i]);
        }
        //buildHeap();
        return *this;
    }

    void PrintHeap (void)
    {
        for (int i = 1; i <= currentSize; i++){
            std::cout << array[i] << " ";
        }
	    return;
    }
    private:
    int currentSize; // Number of elements in heap
    vector<Comparable> array; // The heap array

    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; --i )
        percolateDown( i );
    }
    void percolateDown( int hole )
    {
        int child;
        Comparable tmp = std::move( array[ hole ] );

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child +1]< array[ child ] )
                ++child;
            if( array[ child ] < tmp )
                array[ hole ] = std::move( array[ child ] );
            else
                break;
        }
        array[ hole ] = std::move( tmp );
    }
};

#endif