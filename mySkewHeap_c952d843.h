#ifndef MY_SKEW_HEAP
#define MY_SKEW_HEAP

#include <iostream>
using namespace std;

template <typename Comparable>
class mySkewHeap
{
    public:
    mySkewHeap( )
    {
        root = nullptr;
    }
    mySkewHeap( const mySkewHeap & rhs ) : root{nullptr}
    {
        root = clone(rhs.root);
    }
    mySkewHeap( mySkewHeap && rhs ) : root{rhs.root}
    {
        
    }

    ~mySkewHeap( )
    {
        makeEmpty();
    }

    mySkewHeap & operator=( const mySkewHeap & rhs )
    {
        mySkewHeap copy = rhs;
        std::swap(*this, copy);
        return *this;

    }
    mySkewHeap & operator=( mySkewHeap && rhs )
    {
        std::swap(root, rhs.root);

        return *this;
    }

    bool isEmpty( ) const
    {
        if (root == nullptr){
            return true;
        }
        else{
            return false;
        }
    }
    const Comparable & findMin( ) const
    {
        return root->element;
    }

    void insert( const Comparable & x )
    {
        root = merge( new SkewNode{ x }, root );
    }
    void insert( Comparable && x )
    {
        root = merge( new SkewNode{ std::move(x) }, root );
    }
    void deleteMin( )
    {
        if( isEmpty( ) )
            return;

        SkewNode *oldRoot = root;
        root = merge( root->left, root->right );
        delete oldRoot;
    }
    void deleteMin( Comparable & minItem )
    {
        minItem = findMin( );
        deleteMin( );
    }
    void makeEmpty( )
    {
        makeEmpty(root);
    }
    void merge( mySkewHeap & rhs )
    {
        if( this == &rhs ) // Avoid aliasing problems
            return;

        root = merge( root, rhs.root );
        rhs.root = nullptr;
    }

    void printPreOrder(void)
    {
        printTree(root);
        cout << endl;
    }



    private:
    struct SkewNode
    {
        Comparable element;
        SkewNode *left;
        SkewNode *right;
        int npl;

        SkewNode( const Comparable & e, SkewNode *lt = nullptr,
            SkewNode *rt = nullptr, int np=0)
            : element{ e }, left{ lt }, right{ rt }, npl{ np}{}

        SkewNode( Comparable && e, SkewNode *lt = nullptr,
            SkewNode *rt = nullptr, int np=0)
            : element{ std::move( e ) }, left{ lt }, right{ rt }, npl{ np}{}
    };

    SkewNode *root;

    SkewNode * merge( SkewNode *h1, SkewNode *h2 )
    {
        if( h1 == nullptr )
            return h2;
        if( h2 == nullptr )
            return h1;
        if( h1->element < h2->element )
            return merge1( h1, h2 );
        else
            return merge1( h2, h1 );
    }
    SkewNode * merge1( SkewNode *h1, SkewNode *h2 )
    {
        if( h1->left == nullptr ) // Single node
            h1->left = h2; // Other fields in h1 already accurate
        else
        {
            h1->right = merge( h1->right, h2 );
            swapChildren( h1 );
        }
        return h1;
    }

    void swapChildren( SkewNode *t )
    {
        SkewNode * copy = t->right;
        t->right = t->left;
        t->left = copy;
    }
    void reclaimMemory( SkewNode *t )
    {
        return;
    }
    SkewNode * clone( SkewNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new SkewNode{ t->element, clone( t->left ), clone( t->right ) };

    }

    void makeEmpty( SkewNode * & t )
    {
        if( t != nullptr )
        {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
        }
        t = nullptr;
    }

    void printTree( SkewNode *t) const
    {
        if( t != nullptr )
        {
            std::cout << t->element << " ";
            printTree( t->left);
            printTree( t->right);
        }
    }
};

#endif