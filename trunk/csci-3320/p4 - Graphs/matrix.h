/****************************************************************************
 * File:    matrix.h                                                        *
 * Authors: Ulrich Breymann                                                 *
 *          Brian Detweiler                                                 *
 * Use:     This is a matrix class. A matrix is a vector of vectors. Use    *
 *          this like you would a 2-D array.                                *
 * Source:  This code was modified from                                     *
 *          Designing Components with the C++ STL                           *
 *          by Ulrich Breymann                                              *
 * Note:    Must init() Matrix after first declaration!!!                   *
 *          matrix.init(0)                                                  *
 ***************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

// Lists of column and row names
// A list was used for the find() and findFirstOf() methods
#include"list.h"
#include"cvector.h"

// matrixutils.h has functions for converting strings into numbers,
// and vice-versa. Also for printing purposes.
#include"matrixutils.h"

#include<iostream>
using namespace std;


namespace brd
{
// Inherits from cVector which inherits from vector
template<class TITLE_TYPE, class VAL_TYPE>
class Matrix : public brd::cVector<brd::cVector<VAL_TYPE> >
{
	public:

        typedef typename std::vector<VAL_TYPE>::size_type size_type;

        // Must have at least a 1x1 matrix
        Matrix(size_type x = 1, size_type y = 1)
            : brd::cVector<brd::cVector<VAL_TYPE> >(x, brd::cVector<VAL_TYPE>(y)), 
              rows(x), cols(y) 
              {;;;}

        // Initialize the entire matrix with a given value
        void init(const VAL_TYPE& val)
        {
            // We keep this value as a class member
            initVal = val;
            
            /* Gotta at least do the 1x1 matrix
             * 
             * Iterate down the rows, then columns.
             *
             * |x x x x x
             * |x x x x x
             * |x x x x x
             * V----> x x
             *  x x x x x
            */
            for(size_type i = 0; i < rows; ++i)
                for(size_type j = 0; j < cols; ++j)
                    operator[](i)[j] = val; // a.k.a. (*this)[i][j]
           
            // TODO: This is only for string type (not really templated)
            colList.push_back("");
            rowList.push_back("");
            
            // Size of the largest cell for printing purposes
            printCellSize.push_back(0);
        }

        // The identity matrix for the current size of matrix
        Matrix<VAL_TYPE, TITLE_TYPE>& I(void)
        {
            for(size_type i = 0; i < rows; ++i)
                for(size_type j = 0; j < cols; ++j)
                    operator[](i)[j] = (i == j) ? VAL_TYPE(i) : VAL_TYPE("");
            return *this;
        }

        // NxN matrix = N^2 elements
        size_type size(void)
        { return rows * cols; }

        size_type rowSize(void)
        { return rows; }

        size_type colSize(void) const
        { return cols; }

        bool cellEmpty(size_type r, size_type c)
        { return (operator[](r)[c]).empty(); }

    /* insert_at()
     * ---
     * Input:   size_type, size_type, VAL_TYPE
     * Output:  none
     * Return:  none
     * Big-O:   O(n^2), because of the nested FOR loops
     * Notes:   Allows for a dynamic matrix. Insert a value anywhere
     *          in the matrix without having to worry about going
     *          out of bounds.
     * Example:     Matrix<int, string> matrix(3, 3);
     *              matrix.init(0);
     *
     *          Result:
     *              
     *              0 0 0 0
     *              0 0 0 0
     *              0 0 0 0
     *              0 0 0 0
     *          
     *          The matrix is formed with the preliminary 4x4 size.
     *
     *              matrix.insert_at(6, 8, 20);
     *
     *          This will insert the value 20 at the zero-indexed 
     *          position (6, 8);
     *          
     *          Result:
     *              0 0 0 0 0 0 0 0 0
     *              0 0 0 0 0 0 0 0 0
     *              0 0 0 0 0 0 0 0 0
     *              0 0 0 0 0 0 0 0 0
     *              0 0 0 0 0 0 0 0 0
     *              0 0 0 0 0 0 0 0 0
     *              0 0 0 0 0 0 0 0 20 
     */
        void insert_at(size_type r,             // Row position
                       size_type c,             // Col position
                       VAL_TYPE val,            // Actual value to enter
                       TITLE_TYPE rTitle = "",  // Row title
                       TITLE_TYPE cTitle = "")  // Col title
        {
            // Extend the rows if necessary and give it an optional title
            if(r > rows - 1)
                initRow(r, rTitle);

            // If the row title is not blank
            else if(rTitle.size() > 0)
            {
                /* The position we are currently writing to may already
                 * have a row title. So we need to see if that exists
                 * and erase it, because it may be changing, since we
                 * are going to be changing the row title.
                 */
                if(printCellSize.find(rowList[r].size()))
                    printCellSize.erase(printCellSize.findFirstOf(
                                            rowList[r].size()));

                // Push back the new row title size
                printCellSize.push_back(rTitle.size());
                printCellSize.sort();

                // Overwrite the row title
                rowList.overwrite(r, rTitle);
            }
          
            // Extend the columns if necessary and give it an optional title
            if(c > cols - 1)
                initCol(c, cTitle);


            // If they gave us a col title
            else if(cTitle.size() > 0)
            {
                /* The position we are currently writing to may already
                 * have a col title. So we need to see if that exists
                 * and erase it, because it may be changing, since we
                 * are going to be changing the col title.
                 */
                if(printCellSize.find(colList[c].size()))
                    printCellSize.erase(printCellSize.findFirstOf(
                                            colList[c].size()));

                // Push back the new size (for printing)
                printCellSize.push_back(cTitle.size());
                printCellSize.sort();
                
                // Overwrite the column title
                colList.overwrite(c, cTitle);
            }
        
            // Need to erase the current value's size, 
            // because it may be changing.
            /*
            if(printCellSize.find(numToString(val).size()))
                printCellSize.erase(printCellSize.findFirstOf(
                                        numToString(operator[](r)[c]).size()));
            */

            // Push back the new value's size (for printing)
            // TODO: This is not templated
            printCellSize.push_back(val.size());
            printCellSize.sort();


            // Insert the desired value
            operator[](r)[c] = val;

        }

    /* initRow()
     * ---
     * Input:   size_type
     * Output:  none
     * Return:  none
     * Big-O:   O(n)
     * Notes:   Initializes an entire row in the matrix
     *          This is a very forgiving matrix.
     *          If the target row (r) is out of bounds, then
     *          we are going to add enough rows so that it is not OOB.
     * TODO:    Find out about type-inspecific initializing
     *          For now, TITLE_TYPE is assumed to be string
     */
        void initRow(size_type r, TITLE_TYPE title = "")
        {
            if(r > rows - 1)
            {
                for(size_type i = rows - 1; i < r; ++i)
                {
                    push_back(brd::cVector<VAL_TYPE>(cols));

                    for(size_type j = 0; j <= cols; ++j)
                        // Initialize the columns
                        (operator[](i)).push_back(initVal);
                }
            
                // If we just added a row, that is now the number of rows.
                // The matrix is ZERO-INDEXED.
                rows = r + 1;
            }
            else
                // Initialize the row
                for(size_type i = 0; i < cols; ++i)
                    operator[](r)[i] = initVal;

            // If we are extending the rows, we need to keep the rowList
            // up to speed, so we insert blank titles.
            for(u_int i = rowList.size(); i <= r; ++i)
                rowList.push_back("");
            
            /* If there was a title specified, insert it in the list,
             * other wise just insert a blank TITLE_TYPE
             * rowNames.insert(make_pair<TITLE_TYPE, size_type>(title, r));
             */
            rowList.overwrite(r, title);
            
            printCellSize.push_back(title.size());
            printCellSize.sort();
        }
    
    /* initCol()
     * ---
     * Input:   size_type
     * Output:  none
     * Return:  none
     * Big-O:   O(n)
     * Notes:   Initializes an entire column in the matrix
     *          This is a very forgiving matrix.
     *          If the target row (r) is out of bounds, then
     *          we are going to add enough rows so that it is not OOB.
     * TODO:    Find out about type-inspecific initializing
     *          For now, TITLE_TYPE is assumed to be string
     */
        void initCol(size_type c, TITLE_TYPE title = "")
        {
            if(c > cols - 1)
            {
                // Extend columns first
                if(c > cols - 1)
                {
                    // Rows
                    for(size_type i = 0; i < rows; ++i)
                        // Columns
                        for(size_type j = cols; j <= c; ++j)
                            // Initialize the columns
                            (operator[](i)).push_back(initVal);

                    // Columns are set
                }
                cols = c + 1;
            }
            else
                // Initialize the column
                for(size_type i = 0; i < cols; ++i)
                    operator[](i)[c] = initVal;

            // If we are extending the rows, we need to keep the rowList
            // up to speed, so we insert blank titles.
            for(u_int i = colList.size(); i <= c; ++i)
                colList.push_back("");
            
            // If there was a title specified, insert it in the list,
            // other wise just insert a blank TITLE_TYPE
            // colNames.insert(make_pair<TITLE_TYPE, size_type>(title, c));
            colList.overwrite(c, title);

            printCellSize.push_back(title.size());
            printCellSize.sort();
        }

    /* zero()
     * ---
     * Input:   none
     * Output:  none
     * Return:  none
     * Big-O:   O(n^2), because of the nested FOR loops
     * Notes:   Zeros out a matrix
     */
        void zero(void)
        { init(VAL_TYPE()); }
       
    /* clear()
     * ---
     * Input:   none
     * Output:  none
     * Return:  none
     * Big-O:   O(n) - Must erase every element in the main cVector
     *                 Also, the other clear() functions run in linear time.
     * Notes:   Clears a matrix
     */
        void clear(void)
        { 
            while(!this->empty())
                this->erase(this->begin());

            rows = 0;
            cols = 0;

            colList.clear();
            rowList.clear();

            initVal = "";
        }

      
        // The last element in the list will be our print size.
        size_t getPrintCellSize(void)
        { return printCellSize[printCellSize.size() - 1]; }

        List::List<TITLE_TYPE> getColList(void)
        { return colList; }

        List::List<TITLE_TYPE> getRowList(void)
        { return rowList; }

    protected:
        size_type rows;
        size_type cols;
        VAL_TYPE initVal;
        
        // Keeps track of where our titles are
        // map<TITLE_TYPE, u_int> colNames;
        // map<TITLE_TYPE, u_int> rowNames;
       
        // Holds the nodes in order of their position in the matrix.
        List::List<TITLE_TYPE> colList;
        List::List<TITLE_TYPE> rowList;

        /* Keeps a list of cell sizes so we know what the largest element
         * in the matrix is. This is how we print it out all nice and pretty.
         */
        List::List<size_t> printCellSize;

#if 0
        //select a row
        vector& operator[](const int i);

        //arithmetic operations
        vector operator*(const vector&);

        friend matrix operator*(const double, const matrix);
        friend matrix operator*(const matrix, const double);
        
        matrix matrix::operator*(const matrix a);
        matrix operator+(const matrix& a);
        matrix operator-(const matrix& a);
        //friend void ludcmp(matrix& a, ivector& indx,double& d);
        //friend void lubksb(matrix&a,iVector& indx,Vector&b);

#endif
};


/* TODO: Need to make this so it checks to see if total column width 
 *       is greater than 80. If so, we need to start scrunching it
 *       down. If it starts getting too big, we'll print up to 80 chars
 *       wide, and 80 down. Then we'll page it, and print until the 
 *       last Y-axis node has been printed. Then we'll go right and
 *       start doing it over.
 */
template<class TITLE_TYPE, class VAL_TYPE>
inline std::ostream& operator<< (std::ostream& s, Matrix<VAL_TYPE, TITLE_TYPE>& m)
{
    /* EXAMPLE:
     * ---
     *  This will be our sample matrix:
     *      
     * 1.          one  two three four five
     * 2.        ______________________________
     * 3.    one |  4    5    0    7    3 
     * 4.    two |  5    6    3    2    1
     * 5.  three |  0    2    1    5    7  
     * 6.   four |  1    2    3    4    5
     * 7.   five | 10   11    2    2    3
     *
     *  Below will show which line of code is responsible for each piece of 
     *  this matrix.
     */
    
    typedef typename Matrix<VAL_TYPE, TITLE_TYPE>::size_type size_type;
    
    // typename map<TITLE_TYPE, u_int>::iterator iter;

    string element = "";

    s << std::endl;
   
    /* Piece of Matrix: 
     * 1.          one  two three four five
     *
     * Spacing for where the first column header should start
     */
    for(u_int i = 0; i <= m.getPrintCellSize() + 1; ++i)
        s << " ";

    /* Piece of Matrix: 
     * 1.          one  two three four five
     * 
     * Print out the node names along the top of the matrix
     */
    for(u_int i = 0; i < m.colSize(); ++i)
        s << cell(m.getColList()[i], m.getPrintCellSize()) << " ";
   

    /* Piece of Matrix:
     * 2.
     *
     * Next line
     */
    s << endl;

    /* Piece of Matrix:
     * 2.       } Spaces
     *
     * Advance to the first column header
     */
    for(u_int i = 0; i <= m.getPrintCellSize(); ++i)
        s << " ";

    /* Piece of Matrix:
     * 2.        __
     *
     * Start with an underline
     */
    s << "__";

    /* Piece of Matrix:
     * 2.        ______________________________
     *
     * Print out an underline under the column headers
     */
    for(u_int i = 0; i < m.colSize(); ++i)
        for(u_int j = 0; j <= m.getPrintCellSize(); ++j)
            s << "_";

    for(size_type i = 0; i < m.rowSize(); ++i)
    {
        /* Piece of Matrix: 
         * 3.
         * 4.
         * 5.
         * 6.
         * 7.
         *
         * Start next line
         */
        s << std::endl;

        /* Piece of Matrix: 
         * 3.    one
         * 4.    two
         * 5.  three
         * 6.   four
         * 7.   five
         *
         * Print out the row header
         */
        s << cell(m.getRowList()[i], m.getPrintCellSize(), 0, "right") << " ";
        
        /* Piece of Matrix: 
         * 3.    one |
         * 4.    two |
         * 5.  three |
         * 6.   four |
         * 7.   five |
         *
         * Drop in the left matrix edge
         */
        s << "|";

        /* Piece of Matrix: 
         * 3.    one |  4    5    0    7    3 
         * 4.    two |  5    6    3    2    1
         * 5.  three |  0    2    1    5    7  
         * 6.   four |  1    2    3    4    5
         * 7.   five | 10   11    2    2    3
         *
         * Print the row values out
         */
        for(size_type j = 0; j < m.colSize(); ++j)
            s << cell(m[i][j], m.getPrintCellSize()) << " ";
    }
    
    /* Piece of Matrix: 
     * 7.   five | 10   11    2    2    3
     *
     * New line and return the ostream
     */
    s << std::endl;
    return s;

} // operator<<

} // namespace brd
#endif
