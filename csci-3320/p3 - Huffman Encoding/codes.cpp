/*****************************************************************************
 * Author:      Brian Detweiler                                              *
 * Filename:    codes.cpp                                                    *
 * Description: Methods for Codes class                                      *
 * ************************************************************************* */

#include"codes.h"
using namespace std;

/***********
 * PRIVATE *
 ***********/


/* binToCharPtr()
 * ---
 * Input:   string, bool
 * Output:  none
 * Return:  char*
 * Notes:   Turns a given binary string into printable chars. 
 */
char* Codes::binToCharPtr(string code, bool isTree)
{
    DEBUG cout << "\n\n_____ " << __PRETTY_FUNCTION__ << "_____\n" << endl;

    // Code must be a multiple of 8, or you will not get the
    // desired result
    if(code.size() % 8)
        exit(BADSTRINGSIZE);

    // Array to hold the char-converted binary string
    static char* codeArr = NULL;

    size_t stringSize = CODE_SIZE * sizeof(char);

    DEBUG cout << "malloc'd char* codeArr[" 
               << CODE_SIZE * sizeof(char) << "]" << endl;

    codeArr = (char*) malloc(CODE_SIZE * sizeof(char));
    assert(codeArr);

    u_int i = 0;
    u_int j = 0;
    u_int k = BYTE_LEN;

    // Convert the binary string to writable chars.
    for(i = 0; i < (code.size() / BYTE_LEN); ++i)
    {
        // If codeArr is almost out of space
        if(i >= (stringSize - 1))
        {
            // Reset stringSize
            stringSize = REALLOC_SIZE * i * sizeof(char);

            DEBUG cout << "Running out of space. realloc-ing to " 
                       << stringSize << " bytes" << endl;

            // Reallocate to REALLOC_SIZE * the current size
            codeArr = (char*) realloc((char*)codeArr, stringSize);

            assert(codeArr);

            DEBUG cout << "Realloc successful" << endl;
                                      
        }

        // Set the current position to the desired char
        codeArr[i] = stringToChar(code.substr(j, k));

        j += BYTE_LEN;
        k += BYTE_LEN;
    }
  
    if(isTree)
        treeSize = i;
    else
        codeSize = i;


    // Null terminate the string
    codeArr[i] = '\0';

    DEBUG cout << "_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
    return codeArr;
}

/* exportTree()
 * ---
 * Input:   Tree&, const char*
 * Output:  none
 * Return:  none
 * Notes:   Write the generated Huffman tree out as an encoded binary string.
 *          The way we do this is by using 0s for nodes, 1s for leaves, and
 *          then using the char data right after the leaves. 
 *
 *          Then we convert the generated binary string to an equivalent char 
 *          string and print it out as chars to a binary file.
 */
void Codes::exportTree(const char* out_file)
{
    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
  

    treeCode.clear();


    DEBUG cout << "Get tree code." << endl;
    // Grab the binary representation of the tree
    treeCode = *(tree.toBinary());
    
    /* To output this code, we need to turn each BYTE_LEN bit string into
     * a char using stringToChar(). And when decoding, need to read
     * in each char and change it to a binary string.
     */
    DEBUG cout << "Sending treeCode into binToCharPtr()" << endl;
    
    // Convert the binary string and store it in the char array
    char* treeCodeArr = binToCharPtr(treeCode, true);

    ofstream out(out_file, ios::out | ios::binary | ios::trunc);

    DEBUG cout << "Writing tree code to file" << endl;

    out.write((char*)treeCodeArr, (treeSize * sizeof(char)));
    out.close();

    DEBUG cout << "Freeing treeCodeArr" << endl;
    free(treeCodeArr);

    DEBUG cout << "\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
}


/* importTree()
 * ---
 * Input:   Tree&, const char*
 * Output:  none
 * Return:  none
 * Notes:   Read the given input file and grab the tree data and create
 *          the tree using the given data.
 */
u_int Codes::importTree(const char* in_file)
{
    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
    u_int streamPos;
    u_char tmp;
    u_char tmp1;

    char chPtr[CHAR_SIZE_BUF];
    chPtr[0] = '\0';
    chPtr[1] = '\0';

    ifstream binIn(in_file, ios::in | ios::binary);

    if(binIn.bad())
        exit(BADBIN);

    DEBUG cout << "Reading the first 2 bytes (tree size) from the file" << endl;

    // Read the first 2 bytes, which is the tree size
    // Advance get pointer to the next 2 bytes
    binIn.seekg(0);

    // Read first byte
    binIn.read(chPtr, sizeof(char));
    
    // Store it
    tmp = static_cast<u_char>(chPtr[0]);
    chPtr[0] = '\0';
    chPtr[1] = '\0';
   
    // Read second byte
    binIn.read(chPtr, sizeof(char));
    
    tmp1 = static_cast<u_char>(chPtr[0]);

    // Get the actual tree size
    chPtr[0] = '\0';
    chPtr[1] = '\0';

    /* Need to read the two bytes as a single number
     * Example:
     *      tmp == 00000001
     *      tmp1 == 00000101
     *
     *      To do this, we shift tmp left 8 places, and then add the two.
     *      (tmp << 8) == 1 00000000
     *      (tmp + tmp1) == 1 00000101
     */
    treeSize = (static_cast<size_t>(tmp) << 8) + static_cast<size_t>(tmp1);
  
    // Read Key 
    binIn.read(chPtr, sizeof(char));
    
    // Store it
    key = static_cast<u_char>(chPtr[0]);
    chPtr[0] = '\0';
    chPtr[1] = '\0';
    
    // Read Value
    binIn.read(chPtr, sizeof(char));
    
    // Store it
    value = static_cast<u_char>(chPtr[0]);
    chPtr[0] = '\0';
    chPtr[1] = '\0';

    // Verify the key
    if(value != hashish(key))
    {
        cerr << "Keys do not match." <<
                "This file was not encoded with this program." << endl;
        exit(BADKEY);
    }
    
    binIn.seekg(2);  

    DEBUG cout << "Tree Size = " << treeSize << " bytes" << endl;

    // Buffer to hold the tree of size treeSize
    char treeBuf[treeSize + 1];

    DEBUG cout << "Reading in tree from file" << endl;
    // Read in treeSize bytes into treeBuf
    binIn.read(treeBuf, treeSize);
    
    DEBUG cout << "Tree code before conversion: " << treeBuf << endl;
    streamPos = binIn.tellg();
    DEBUG cout << "Stream position where body code starts: " 
               << streamPos << endl;

    // Start fresh with our tree code
    treeCode.clear();

    // Build tree code
    for(u_int i = 0; i < treeSize; ++i)
        treeCode += charToString(treeBuf[i]);

    DEBUG cout << "Tree Code after conversion: " << treeCode << endl;

    DEBUG cout << "Building tree from code" << endl;
    // Build the actual tree using the code we just got.
    tree.fromBinary(treeCode);

    VERBOSE cout << tree << endl;

    // Done with the treeCode. Clear it.
    treeCode.clear();

    binIn.close();
    
    DEBUG cout << "\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
    // Return the starting position in the stream
    return streamPos - 1;
}


/**********
 * PUBLIC *
 **********/

/* encode()
 * ---
 * Input:   string, string
 * Output:  none
 * Return:  none
 * Notes:   Encode a file using the Huffman algorithm
 *          
 */
void Codes::encode(string in, string out)
{
    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
    cout << "Running in encypher mode" << endl;


    u_int table[TABLE_SIZE];
    char ch = 0x00;
    char chPtr[CHAR_SIZE_BUF];
    chPtr[0] = '\0';
    chPtr[1] = '\0';

    for(u_int i = 0; i < TABLE_SIZE; ++i)
        table[i] = 0; 


    ifstream binIn(in.c_str(), ios::in | ios::binary);

    if(binIn.bad())
        exit(BADBIN);

    /**************************************************************************
     *                           BUILD HUFFMAN TREE                           *
     **************************************************************************/
    
    // Build a table of chars and their freqs
    while(binIn.get(ch))
        ++(table[static_cast<u_char>(ch)]);

    DEBUG cout << "Built table of chars and their frequencies from the input." 
               << endl;

    // Done reading the file
    binIn.close();

    // Insert all the letters on the heap as trees
    for(u_int i = 0; i < TABLE_SIZE; ++i)
        if(table[i])
            heap.insert(new Tree(table[i], i));

    DEBUG cout << "Pushed all nodes on heap" << endl;

    // Build the Huffman tree
    while(heap.size() > 1)
        heap.insert((*heap.remove()).merge(*(heap.remove())));

    tree = *heap.remove();
    
    DEBUG cout << "Merged all tree pointers to a single tree" << endl;

    VERBOSE cout << tree << endl;
    
    // Dummy code for tree.makeCodeTable()
    string dummyCode;
    dummyCode.clear();

    DEBUG cout << "Creating code table" << endl;
    // Generate the code table from the Huffman tree
    tree.makeCodeTable((*heap.getRoot()).getRoot(), dummyCode);

    // If verbose is set, print the code table
    VERBOSE tree.printCodeTable();

    DEBUG cout << "Exporting tree to the output file" << endl;
    // Export the Tree to the output file
    exportTree(out.c_str());

    // Keep track of the size of the output file
    outFileSize = tree.binSize();

    /**************************************************************************
     *                              ENCODE FILE                               *
     *************************************************************************/

    // Reread the file, and encode it using the newly generated Hufman Tree.
    binIn.open(in.c_str(), ios::in | ios::binary); 

    // Open the output file.
    ofstream binOut(out.c_str(), ios::out | ios::binary | ios::app);

    string code;
    code.clear();

    // Read in a byte at a time, building the the code from the tree's table
    DEBUG cout << "Reread in the file and build a code based on our code table"
               << endl;
    
    inFileSize = 0;

    cerr << "Encoding - This may take a few moments." << endl;
    for(binIn.read((char*)chPtr, sizeof(char)); 
        binIn.good(); 
        binIn.read((char*)chPtr, sizeof(char)))
    {
        code += tree.getCode(static_cast<u_char>(chPtr[0]));
        chPtr[0] = '\0';
        chPtr[1] = '\0';

        // Keep track of the input file size
        ++inFileSize;
    }


    DEBUG cout << "Encoded file: " << code << endl;
    VERBOSE cout << "\n" << inFileSize << " bytes encoded" << endl;

    // Pad with zeroes at the end 
    codePadSize = ((BYTE_LEN - (code.size() % BYTE_LEN)));
    if(codePadSize == 8)
        codePadSize = 0;

    DEBUG cout << "Padding code with " << codePadSize << "0s" << endl;
    DEBUG cout << "Prepending padSize to code" << endl;
    code = charToString(static_cast<char>(codePadSize)) + code;

    code.append(codePadSize, '0');

    // Keep track of the output file size
    outFileSize += code.size() / 8;

    DEBUG cout << "Final code: " << code << endl;

    // Convert the string to printable characters
    char* codeArr = binToCharPtr(code, false);
    
    DEBUG cout << "Writing out the converted code: " << codeArr << endl;

    binOut.write((char*)codeArr, (codeSize * sizeof(char)));
   
    binIn.close();
    binOut.close();

    DEBUG cout << "Freeing codeArr" << endl;
    free(codeArr);

    // If the output file is greater than the input file, warn the user
    if(outFileSize > inFileSize)
    {
        cerr << "\nWarning: " << out << " is larger than " << in << endl;

#if NO_BIGGER_OUTFILE
        cerr << "\nERROR: The compressed file " <<
                "is larger than the input file.\n" << endl;

        string command = "rm -f " + out;
        system(command.c_str());
        exit(LARGER_OUT_FILE);
#endif
    }
    else
    {
        compressionRatio = ((static_cast<float>(inFileSize) - 
                             static_cast<float>(outFileSize)) 
                           / static_cast<float>(inFileSize)) * 100;
        cerr << "\n\nCompressed file by " << compressionRatio << "%" << endl;
        cerr << "\n" << endl;
    }

    DEBUG cout << "\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
}


/* decode()
 * ---
 * Input:   string, string
 * Output:  none
 * Return:  none
 * Notes:   Decode a Huffman-encoded file
 *          
 */
void Codes::decode(string in, string out)
{
    /**************************************************************************
     *                               GET TREE                                 *
     **************************************************************************/

    DEBUG cout << "\n\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;

    u_int startPos;
    char chPtr[CHAR_SIZE_BUF];
    
    cout << "Running in decypher mode" << endl;

    DEBUG cout << "Import tree from file, and set start position." << endl;
    
    // Import the tree from the file, and set the start position
    startPos = importTree(in.c_str());

    /**************************************************************************
     *                          READ AND DECODE FILE                          *
     *************************************************************************/

    ifstream binIn(in.c_str(), ios::in | ios::binary);

    DEBUG cout << "startPos = " << startPos << endl;
    // Advance the pointer past the tree, starting at the body code 
    //binIn.seekg(startPos + 1);
    binIn.seekg(startPos + 1);
  
    DEBUG cout << "Reading at " << startPos + 1 << endl;

    // Read in the pad size
    binIn.read((char*)chPtr, sizeof(char));

    // Save code pad size
    codePadSize = static_cast<size_t>(chPtr[0]);
    chPtr[0] = '\0';
    chPtr[1] = '\0';
    
    DEBUG cout << "The padsize of the main code: " << codePadSize << endl;
    if(binIn.bad())
        exit(BADBIN);

    DEBUG cout << "Building code for main body" << endl;
    // Build code from the body
    for(binIn.read((char*)chPtr, sizeof(char));
        binIn.good();
        binIn.read((char*)chPtr, sizeof(char)))
    {
        codeIn += charToString(static_cast<u_char>(chPtr[0]));
        chPtr[0] = '\0';
        chPtr[1] = '\0';
    }

    DEBUG cout << "Main body code: " << codeIn << endl;

    // Remove padding
    codeIn = codeIn.substr(0, codeIn.size() - codePadSize);

    DEBUG cout << "Main body code after removing padding: " << codeIn << endl;

    // Open out file for writing
    ofstream binOut(out.c_str(), ios::out | ios::binary | ios::trunc);

    DEBUG cout << "Decode the main body using the tree we built." << endl;

    // While codeIn is not empty, get the character from the code and write it
    // Note: The code string is modified in tree.getChar()

    cerr << "Decoding - This may take a few moments." << endl;
    do
        binOut.put(tree.getChar(&codeIn));
    while(!codeIn.empty());

    DEBUG cout << "\n_____" << __PRETTY_FUNCTION__ << "_____\n" << endl;
}


