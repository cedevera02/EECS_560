#ifndef MY_DISJOINT_SET_H
#define MY_DISJOINT_SET_H

#include <vector>

using namespace std;

class myDisjointSets
{
    public:
    explicit myDisjointSets( int numElements ): s(numElements, -1)
    {
    }
    
    int find( int x )
    {
        if( s[ x ] < 0 )
            return x;
        else
            return s[x]= find( s[ x ] );
    }
    void unionSets( int root1, int root2 )
    {
        if( s[ root2 ] < s[ root1 ] ) // root2 is deeper
            s[ root1 ] = root2; // Make root2 new root
        else
        {
            if( s[ root1 ] == s[ root2 ] )
                --s[ root1 ]; // Update height if same
            s[ root2 ] = root1; // Make root1 new root
        }

        // if( s[ root2 ] < s[ root1 ] ){ // root2 is deeper
        //     s[ root1 ] = root2; // Make root2 new root
        //     // if (sizes[root1] == -1)
        //     //     sizes[root2] = sizes[root2]+1;
        //     // else
        //         sizes[root2] = sizes[root2]+sizes[root1];
        //     sizes[root1] = -1;
        // }
        // else
        // {
        //     if( s[ root1 ] == s[ root2 ] )
        //         --s[ root1 ]; // Update height if same
        //     s[ root2 ] = root1; // Make root1 new root
        //     sizes[root1] = sizes[root2]+sizes[root1];
        //     sizes[root2] = -1;
        // }
    }

    int getSetSize(int x) const
    {
        if (s[x] == -1 || s[x] > 0)
            return (-1);
        else 
            return (-1)*s[x];
    }

    // vector<int> getVect (){
    //     return s;
    // }

    protected:
    vector<int> s;
};

#endif