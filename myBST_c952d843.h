#ifndef MY_BST_H
#define MY_BST_H

using namespace std;

template <typename Comparable>
class myBST
{
    public:
    myBST( )
    {
        root = nullptr;
    }
    myBST( const myBST & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    myBST( myBST && rhs ): root{ rhs.root}
    { }

    ~myBST( )
    {
        makeEmpty();
    }

    const Comparable & findMin( ) const
    {
        return findMin(root)->element;
    }
    const Comparable & findMax( ) const
    {
        return findMax(root)->element;
    }
    bool contains( const Comparable & x ) const
    {
        return contains(x, root);
    }
    bool isEmpty( ) const
    {
        if (root == nullptr){
            return true;
        }
        return false;
    }
    
    void printPreOrder(void)
    {
        printTree(root, cout, "pre");
        cout << endl;
    }

    void printPostOrder(void)
    {
        printTree(root, cout, "post");
        cout << endl;
    }

    void makeEmpty( )
    {
        makeEmpty(root);
    }
    void insert( const Comparable & x )
    {
        insert(x, root);
    }
    void insert( Comparable && x )
    {
        insert(x, root);
    }
    void remove( const Comparable & x )
    {
        remove(x, root);
    }

    myBST & operator=( const myBST & rhs )
    {
        myBST copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    myBST & operator=( myBST && rhs )
    {
        std::swap(root, rhs.root);

        return *this;
    }


    private:
    struct BinaryNode
    {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ theElement }, left{ lt }, right{ rt } { }

    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;

    void insert( const Comparable & x, BinaryNode *&t)
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ; // Duplicate; do nothing
    }
    void insert( Comparable && x, BinaryNode *&t)
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ; // Duplicate; do nothing
    }
    void remove( const Comparable & x, BinaryNode *&t)
    {
        if( t == nullptr )
            return; // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true; // Match
    }
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
        }
        t = nullptr;
    }
    void printTree( BinaryNode *t, ostream & out, std::string order ) const
    {
        if( t != nullptr )
        {
            if (order == "pre"){
                out << t->element << " ";
                printTree( t->left, out, "pre" );
                printTree( t->right, out, "pre"  );
            }else if (order == "post"){
                printTree( t->left, out, "post" );
                printTree( t->right, out, "post" );
                out << t->element << " ";
            }
        }
    }
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
        return nullptr;
        else
        return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif