/*****************************************************************************
 * Author:      Brian Detweiler                                              *
 * Filename:    tree.h                                                       *
 * Description: Methods for the Tree class                                   *
 * ************************************************************************* */

#include"tree.h"

/***********/
/* Private */
/***********/

/* chop()
 * ---
 * Input:   Node*
 * Output:  none
 * Return:  none
 * Notes:   Chop down the tree recursively starting at the given node
 */
void Tree::chop(Node *n)
{
    if(n)
    {
        // Recursive function: Chops left then right
        if(n->left)
            chop(n->left);  
        // all the way down the tree. 
        if(n->right)
            chop(n->right);
        // Will finally delete the last node here.
        delete n;
    }
}


/* print()
 * ---
 * Input:   Node*, int, ostream&
 * Output:  The Tree's structure using the elements and setw()
 * Return:  none
 * Notes:   Prints the Tree out sideways using the nodes of the tree
 *          (recursively) and setw() formatting.
 */
void Tree::print(Node *n, int level, ostream &ost) const
{
    char ch[HEX_LEN] = "\0";

    if(n)
    {
        print(n->right, level + 1, ost);
        ost << setw(SETW_LEN + level);
        ost << "      "; 

        // If it's a space, print out the char in hex form
        if(isspace(n->data) || !isascii(n->data))
        {
            snprintf(ch, HEX_LEN, "%#x", n->data);
            ost << ch;
        }
        else
            ost << n->data;

        ost << ":"<< n->freq  <<  endl;
        print(n->left, level + 1, ost);
    }
}


/***********/
/* Public  */
/***********/

/* Default Constructor
 * ---
 * Input:   none
 * Output:  none
 * Return:  none
 * Notes:   Default Constructor: allows for declaration of Tree t;
 */
Tree::Tree(void)
{
    Node* n = new Node(0, '\0');
    root = n;
    for(u_int i = 0; i < TABLE_SIZE; ++i)
        table.push_back(new string());
}

/* Constructor
 * ---
 * Input:   u_short, u_char = '\0'
 * Output:  none
 * Return:  none
 * Notes:   Constructor starting with a freq and optional data
 */
Tree::Tree(u_short freq, u_char data = '\0')
{
    Node* n = new Node(freq, data);
    root = n;
    for(u_int i = 0; i < TABLE_SIZE; ++i)
        table.push_back(new string());
    
    max_freq = freq;

}


/* makeCodeTable()
 * ---
 * Input:   const Node*, string&
 * Output:  none
 * Return:  vector<string*>
 * Notes:   Compile a table with all the codes from the tree.
 *          Codes can be accessesed using the char for which we are
 *          trying to find the code.
 *          
 * Example: If you want the code for 'a', simply do this:
 *          string code = *(table['a']);
 *
 * TODO:    You must include a dummy string, because this is a recursive
 *          function. This is how it builds the strings. There may be
 *          better ways to do this, but this is what I came up with for now.
 */
void Tree::makeCodeTable(const Node* n, string& code)
{
    if(n)
    {
        if(n == root)
            code.clear();
        else
            code.push_back(n->direction);

        // all the way down the tree, left to right
        if(n->left)
            makeCodeTable(n->left, code);  
        if(n->right)
            makeCodeTable(n->right, code);
       
        // At a leaf
        if(!n->left && !n->right)
            table[n->data] = new string(code);
    }
    
    // Remove the end of the code since we are about to move up one level
    code = code.substr(0, code.size() - 1);
}

/* printCodeTable()
 * ---
 * Input:   none
 * Output:  The code table
 * Return:  none
 * Notes:   Prints the u_char and the code it is associated with.
 */
void Tree::printCodeTable(void)
{
    for(u_int i = 0; i < TABLE_SIZE; ++i)
        if((*table[i]).size() > 0)
            cout << printUchar(static_cast<u_char>(i)) << " " << *table[i] << endl;

}

/* toBinary()
 * ---
 * Input:   none
 * Output:  none
 * Return:  string*
 * Notes:   Turns the tree into a binary string representation.
 */
string* Tree::toBinary(void)
{
    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n"<< endl;

    static string code;
    code.clear();

    // Get the structure of the tree
    *treeToBin(root, code);
   
    // Padding size
    codePadSize = CHAR_BITS - (code.size() % CHAR_BITS); 

    if(codePadSize == 8)
        codePadSize = 0;
    
    DEBUG cout << "codePadSize = " << codePadSize << endl;

    // Add Padding
    code.append(codePadSize, '0');
    
    DEBUG cout << "tree code with padding: " << code << endl;

    // Prepend codePadSize, so we know 
    // how much to knock off the end when we read it in again
    code = charToString(codePadSize) + code;

    // Adding a "magic number" (key and value) to make sure that we are
    // decoding a file we wrote. Otherwise, it won't work, so why try?
    srand(time(NULL));
    key = rand() % TABLE_SIZE;

    value = hashish(key);

    VERBOSE cout << "key: " << charToString(key) << endl;
    VERBOSE cout << "value: " << charToString(value) << endl;

    // Insert the key and value
    code.insert(0, charToString(value));
    code.insert(0, charToString(key));
    
    /* Finally, at the very front, tell us how many
     * Bytes represents the tree. We will be reading
     * in Bytes, so if the first byte is 000000110, 
     * we know we need to read in 8 bytes.
     */
    code.insert(0, decToBin(static_cast<u_short>
                            (ceil(code.size() / CHAR_BITS))));
   
    // Get the size of the binarized tree
    treeSize = code.size() / CHAR_BITS;
   
    /* Structure of the tree in binary form:
     *
     *    2 bytes   1 byte   1 byte    1 byte         x bytes     PAD_SIZE bits
     * |_TREE_SIZE_|__KEY__|__VALUE__|__PAD_SIZE__|___TREE_CODE___|___PADDING__|
     */
    DEBUG cout << "tree size prepended to code: " << code << endl;
    DEBUG cout << "\n_____" << __PRETTY_FUNCTION__ << "_____\n"<< endl;
    
    return &code;
}

/* treeToBin()
 * ---
 * Input:   const Node*, string&
 * Output:  none
 * Return:  string*
 * Notes:   Returns a string of a binary representation of the tree.
 *          
 * Example: 
 *
 *      Say we are using the following tree:
 *
 *                           :9_________
 *                         /            \
 *                        :4            :5
 *                      /  \          /   \
 *                    b:2  :2        :2   c:3
 *                        /   \     /   \
 *                      0xa:1 d:1 e:1   a:1
 *
 * tree:   00001000       
 *         max_tree_size  
 *
 *                    01   01100010 01   00001010    
 * start root->left:  leaf b        leaf 0xa (LF)  
 *
 *                    1    01100100 001  01100101
 *                    leaf d        leaf e      
 *                           
 *                    1    01100001 1    01100011
 *                    leaf a        leaf c
 *         000000
 *         padding
 * 
 * final code:
 *
 * 0000 1000 0101 1000 1001 0000 1010 1011 
 * 0010 0001 0110 0101 1011 0000 1101 1000 
 * 1100 0000
 *
 * Note: We don't need to include the root. This is implied.
 *
 *       We recurse starting from the root from left to right. 
 *       Read until we hit a leaf (1) and the next CHAR_BITS bits are the data.
 *       Then continue recursing until we hit another leaf, or the end. 
 *       The padding is so we can read it in nice CHAR_BITS bit chunks. 
 *
 *       TODO: Check and prove below:
 *       The very biggest this will ever be, is 1,790 bits (224 Bytes). 
 *
 *       The Math: 
 *          The Huffman Tree needs 2n - 1 + n(ceil(lg(n))), where n is
 *          the number of symbols. In this case we have:
 *              n = 256
 *              ceil(2(256) + 1 + n(ceil(lg(256)))) = 224 Bytes.
 *          
 *       Why:
 *          There are 2n - 1 nodes in a binary tree where every parent
 *          has exactly 2 children.
 *
 *          The fixed-length ascii characters can be represented in 
 *          ceil(lg(n)) ways.
 *
 *       Since we will be writing in nice CHAR_BITS bit chunks (bytes), 
 *       we can write this at the very beginning. We need CHAR_BITS bits 
 *       for this. 1100 0000 (max). 
 */
string* Tree::treeToBin(const Node* n, string& code)
{
    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n"<< endl;
    // If the node exists
    if(n)
    {
        DEBUG cout << "node exists" << endl;
        // If it's a leaf node
        if(!n->left && !n->right)
        {
            DEBUG cout << "node is leaf" << endl;
            // Spit out a 1 to indicate a leaf node
            code.append(1, '1');
            
            DEBUG cout << "code:\n" << code << " " << charToString(n->data) << endl;
            // Spit out the char in binary form
            code.append(charToString(n->data));

        
        }
        // If it's not a leaf node, and it's not root
        else if(n != root)
            code.append(1, '0');

        // Recurse left then right
        treeToBin(n->left, code);
        treeToBin(n->right, code);
    }
    
    DEBUG cout << "\n_____" << __PRETTY_FUNCTION__ << "_____\n"<< endl;
    return &code;
}


/* fromBinary()
 * ---
 * Input:   string&
 * Output:  none
 * Return:  none
 * Notes:   Wrapper to build a tree from a binary string
 */
void Tree::fromBinary(string& code)
{
    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n"<< endl;
    // Start fresh
    clear();

    // Check magic number
    code = code.substr(CHAR_BITS * 2, code.size());
    
    // Take care of padding.
    // Substring the code between the padSize and the padding
    code = code.substr(CHAR_BITS, 
                       code.size() - 
                       CHAR_BITS   - 
                       static_cast<size_t>(
                           stringToChar(code.substr(0, CHAR_BITS))));

    binToTree(root, code);
    DEBUG cout << "\n_____" << __PRETTY_FUNCTION__ << "_____\n"<< endl;
}

/* binToTree()
 * ---
 * Input:   Node*, string&
 * Output:  none
 * Return:  none
 * Notes:   Build a tree from a binary string. 
 *
 *          This is a recursive function, because it calls itself several times.
 *          However, unlike print(), it uses the par pointer to move back up,
 *          instead of "unwinding". For this reason, there is a "return"
 *          statement after each recursion, because we want it to stop 
 *          executing immediately after that. 
 */
void Tree::binToTree(Node* n, string& code)
{
    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n"<< endl;
    if(code.size() > CHAR_BITS)
    {
        DEBUG cout << "code size = " << code.size() << endl;
        int isLeaf = '\0';
       
        if(!n->left || !n->right)
        {
            // If we still have leaf nodes left (not padding)
            // Current node
            Node* curr = new Node(0, '\0', false);
               
            // curr is child of n
            curr->par = n;
            // Read the node (0 for regular node, 1 for leaf)
            isLeaf = code.at(0);
        
            // Remove the node we just read
            code = code.substr(1);
            
            if(isLeaf == '1')
            {
                // Set up the data in the leaf
                curr->data = stringToChar(code.substr(0, CHAR_BITS));

                DEBUG cout << "Data: " << curr->data << endl;
               
                // Remove the data we just read
                code = code.substr(CHAR_BITS);
            }

            // If the the left side is open
            if(!n->left)
            {
                DEBUG cout << "Making curr a left child" << endl;
                
                n->left = curr;

                // Set the direction to remake the codes
                curr->direction = '0';

                if(isLeaf == '1')
                    binToTree(n, code);
                else
                    binToTree(curr, code);


            }
            // else if the right side is open
            if(!n->right)
            {
                DEBUG cout << "Making curr a right child" << endl;
               
                n->right = curr;

                // Set the direction to remake the codes
                curr->direction = '1';
                if(isLeaf == '1')
                    binToTree(n, code);
                else
                    binToTree(curr, code);
            }
        }
        // If both left and right sides are full, move up a level
        else if(n->par)
            binToTree(n->par, code);
        // If both sides of root are full, end.
        else
            return;
    }
}


/* clear()
 * ---
 * Input:   none
 * Output:  none
 * Return:  none
 * Notes:   clears the tree of all data and resets it
 */
void Tree::clear(void)
{
    chop(root->right);
    chop(root->left);
    root->freq = 0;
    root->data = '\0';
    root->direction = 0;
    max_freq = 0;
    
    for(u_int i = 0; i < TABLE_SIZE; ++i)
        (*table[i]).clear();
}

/* getChar()
 * ---
 * Input:   string
 * Output:  none
 * Return:  const u_char
 * Notes:   Get the char from the leaf using the given code
 */
const u_char Tree::getChar(string* code)
{
    u_char rval = 0;

    if((*code).size() > 0)
    {
        // Start traversing at root
        Node* curr = root;

        // While curr exists, and it's not a leaf
        u_int i;
        for(i = 0; i < (*code).size() && 
                   (curr->left || curr->right); ++i)
        {
            // Go right
            if((*code)[i] == '1')
                curr = curr->right;
            else
                curr = curr->left;
        }

        *code = (*code).substr(i);

        rval = curr->data;
    }

    // Return the letter from the code, or 0 if code was empty
    return rval;
}

/* getCode()
 * ---
 * Input:   string
 * Output:  none
 * Return:  const u_char
 * Notes:   Get the char from the leaf using the given code
 */
string Tree::getCode(const u_char ch)
{
    // Return the code
    return *(table[ch]);
}
/* getRoot()
 * ---
 * Input:   none
 * Output:  none
 * Return:  const Node*
 * Notes:   Get a non-modifiable version of the root node
 */
const Tree::Node* Tree::getRoot(void) const
{
    return root;
}

/* getMRoot()
 * ---
 * Input:   none
 * Output:  none
 * Return:  Node*
 * Notes:   Get a modifiable version of the root node
 */
Tree::Node* Tree::getMRoot(void)
{
    return root;
}

/* empty()
 * ---
 * Input:   none
 * Output:  none
 * Return:  bool
 * Notes:   Return a bool whether or not the tree is empty
 */
bool Tree::empty(void) const
{
    return !root;
}

bool Tree::operator== (const Tree& t) const
{
    return root->freq == t.getRoot()->freq; 
}

bool Tree::operator!= (const Tree& t) const
{
    return !(*this == t);
}

bool Tree::operator< (const Tree& t) const
{
    return root->freq < t.getRoot()->freq; 
}

bool Tree::operator> (const Tree& t) const
{
    return !(*this < t || *this == t);
}

bool Tree::operator<= (const Tree& t) const
{
    return (*this < t || *this == t);
}

bool Tree::operator>= (const Tree& t) const
{
    return (*this > t || *this == t);
}

/* merge()
 * ---
 * Input:   Tree&
 * Output:  none
 * Return:  Tree*
 * Notes:   Merges two trees, creating a new root, and making the two trees'
 *          roots its children.
 *
 * TODO:    This may be better if we just insert t's root without
 *          resetting the children.
 *
 * Example:
 *
 *        this                t
 *         *:2               i:2
 *        /   \
 *      x:1  p:1
 *
 *             this after merge
 *                   *:4
 *                  /   \
 *                *:2   i:2
 *               /   \
 *             x:1  p:1
 */
Tree::Tree* Tree::merge(Tree& t)
{
    Node* newRoot = new Node(0, '\0', false);

    // Assign the sum of the two roots' freqs to the the new root.
    newRoot->freq = root->freq + t.getRoot()->freq;


    // Decide which goes on the right and left
    if(t.getRoot()->freq > getRoot()->freq)
    {
        // t
        newRoot->right = t.getMRoot();
        t.getMRoot()->par = newRoot;
        t.getMRoot()->direction = '1';

        // this
        newRoot->left = root;
        root->par = newRoot;
        root->direction = '0';
    }
    else
    {
        // this
        newRoot->right = root;
        root->par = newRoot;
        root->direction = '1';

        // t
        newRoot->left = t.getMRoot();
        t.getMRoot()->par = newRoot;
        t.getMRoot()->direction = '0';
    }

    if(t.getMaxFreq() > getMaxFreq())
        max_freq = t.getMaxFreq();
    
    root = newRoot;
    return this;
}


// Gets the size of the binarized version of the tree
size_t Tree::binSize(void)
{
    return treeSize;
}

// Returns the largest frequency in the tree
const u_short Tree::getMaxFreq(void)
{
    return max_freq;
}

/* Destructor
 * ---
 * Input:   none
 * Output:  none
 * Return:  none
 * Notes:   chop the tree when it goes out of scope.
 */
Tree::~Tree(void)
{
    if(!root->par)
        chop(root);
}

/* operator<<()
 * ---
 * Input:   ostream&, const Tree&
 * Output:  none
 * Return:  ostream&
 * Notes:   for printing using standard ostream operators (<<)
 */
ostream& operator<< (ostream& ost, const Tree& t)
{
    t.print(t.root, 1, ost);
    return ost;
}


