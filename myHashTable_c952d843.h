#ifndef MY_HASH_TABLE_H
#define MY_HASH_TABLE_H

#include <vector>
#include <algorithm>
#include <list>
using namespace std;

template <typename HashedObj>
class myHashTable 
{
    public:
        explicit myHashTable (int size = 101)
        {  
            vector<list<HashedObj>> Table(size);
            hashTable = Table;
            makeEmpty();
        }

        size_t strToHashValue (const std::string & str)
        {
            size_t hashVal = 0;
            for( char ch : str )
                hashVal = 3 * hashVal + ch;

            return hashVal;
        }

        int universalHash(int x, int A, int B, int M)
        {
            const int DIGS = 31;
            const int mersennep = (1<<DIGS) - 1;
            long long hashVal = static_cast<long long>( A ) * x + B;
            
            hashVal = ( ( hashVal >> DIGS ) + ( hashVal & mersennep ) );
            if( hashVal >= mersennep )
            hashVal -= mersennep;
            
            return static_cast<int>( hashVal ) % M;
        }

        bool contains (const HashedObj & x)
        {
            auto & whichList = hashTable[ strToHashValue( x.getKey() )%hashTable.size() ];
            return find( begin( whichList ), end( whichList ), x ) != end( whichList );
        }

        bool insert (const HashedObj & x)
        {
            auto & whichList = hashTable[ strToHashValue( x.getKey() )%hashTable.size() ];
            if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
                return false;
            whichList.push_back( x );
            m_elements++;
                if( ((double)m_elements/hashTable.size()) > 0.5 )
                    rehash( );

            return true;
        }

        bool insert (HashedObj && x)
        {
            auto & whichList = hashTable[ strToHashValue( x.getKey() )%hashTable.size() ];
            if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
                return false;
            whichList.push_back( x );
            m_elements++;
            if( ((double)m_elements/hashTable.size()) > 0.5 )
                rehash( );

            return true;
        }

        bool remove (const HashedObj & x)
        {
            auto & whichList = hashTable[ strToHashValue( x.getKey() )%hashTable.size() ];
            auto itr = find( begin( whichList ), end( whichList ), x );

            if( itr == end( whichList ) )
            return false;

            whichList.erase( itr );
            --m_elements;
            if( ((double)m_elements/hashTable.size()) < 0.25 )
                rehash( );
            return true;
        }
    private:
        int m_elements;
        vector<list<HashedObj>> hashTable;

        void rehash(){
            vector<list<HashedObj>> oldLists = hashTable;

            if (((double)m_elements/hashTable.size()) > 0.5){
                hashTable.resize( nextPrime(2 * hashTable.size()) );
                for( auto & thisList : hashTable )
                    thisList.clear( );

                m_elements = 0;
                for( auto & thisList : oldLists )
                    for( auto & x : thisList )
                        insert( std::move( x ) );
            }else if (((double)m_elements/hashTable.size()) < 0.25){
                hashTable.resize( nextPrime(hashTable.size()/2) );
                for( auto & thisList : hashTable )
                    thisList.clear( );

                m_elements = 0;
                for( auto & thisList : oldLists )
                    for( auto & x : thisList )
                        insert( std::move( x ) );
            }
        }

        //next functions where found online, as it is said to be fine by instructor/gta
        bool isPrime(int n)
        {
            if (n <= 1)  return false;
            if (n <= 3)  return true;
            if (n%2 == 0 || n%3 == 0) return false;
            for (int i=5; i*i<=n; i=i+6)
                if (n%i == 0 || n%(i+2) == 0)
                return false;
            return true;
        }

        int nextPrime(int N)
        {
            if (N <= 1)
                return 2;
            int prime = N;
            bool found = false;
            while (!found) {
                prime++;
                if (isPrime(prime))
                    found = true;
            }
            return prime;
        }

        void makeEmpty( )
        {
            for( auto & thisList : hashTable )
            thisList.clear( );
        }
};

#endif