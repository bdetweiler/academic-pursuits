

class Tree
{
    private:
        Tree ( const Tree & );
        const Tree & operator = ( const Tree & );
    public:
        Tree ( void )
            : root (NULL) {;;;}
        ~Tree ( void )
        {
            clear();
        }
        bool empty ( void ) const
        {
            return !root;
        }
        void clear ( void )
        {
            chop(root);
            root = NULL;
        }
        friend ostream & operator << ( ostream & ost ,
                const Tree & t )
        {
            t.print ( t.root, 1, ost );
            return ost;
        }
        bool find ( const int ) const;
        void insert ( const int );
        void remove ( const int );
    private:
        class Node
        {
            public:
                int data;
                Node * left;
                Node * right;
                Node ( const int d = 0 )
                    : data(d), left(NULL), right(NULL) {;;;}
        };
        Node * root;
        Node * trav ( const int, Node * & ) const ;
        void chop ( Node * );
        void print ( Node *, int level, ostream & ) const;
};


