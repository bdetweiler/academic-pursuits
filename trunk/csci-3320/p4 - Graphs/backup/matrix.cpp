/****************************************************************************
 * File:    matrix.cpp                                                      *
 * Author:  Brian Detweiler                                                 *
 * Use:     This is a matrix class. A matrix is a vector of vectors. Use    *
 *          this like you would a 2-D array.                                *
 ***************************************************************************/

template<class X>
Matrix<X>::Matrix(void)
{
    setSize();

    for(u_int i = 0; i < rows; ++i)
        matrix.push_back(new vector<X*>());
}

template<class X>
Matrix<X>::Matrix(const u_int r, const u_int c)
{
    setSize(c, r);

    for(u_int i = 0; i < rows; ++i)
    {
        matrix.push_back(new vector<X*>());

        /* The user is at least expecting to be able to access
         * the matrix at whatever size they allocated it for.
         * For right now, that location is NULL, but it is 
         * accessable.
         */
        for(u_int j = 0; j < cols; ++j)
        {
            // examples: string, int, bool
            (*matrix[i]).push_back(NULL);
        }
    }
}

template<class X>
Matrix<X>::Matrix(const Matrix &m)
{
    // Copy sizes
    setSize(m.colSize(), m.rowSize());

    for(u_int i = 0; i < rows; ++i)
    {
        matrix.push_back(new vector<X*>());

        // Copy the matrix over
        for(u_int j = 0; j < cols; ++j)
            (*matrix[i]).push_back((*m[i])[j]);
    }
}

template<class X>
void Matrix<X>::setSize(const u_int c, const u_int r)
{
    cols = c;
    rows = r;
}

template<class X>
const u_int Matrix<X>::rowSize(void)
{
    return rows;
}

template<class X>
const u_int Matrix<X>::colSize(void)
{
    return cols;
}
#endif
