#include "stdafx.h"

template <class T> void PrintMatrix(const T &m)
{
    for (auto p : m)
    {
        for (auto q : p)
        {
            std::cout << q << " ";
        }
        std::cout << "\n";
    }
}

class FindIslands
{
    struct Element
    {
        unsigned row;
        unsigned column;
    };

    std::vector<std::vector<int>> &matrix_;
    std::stack<Element> elementStack_;
    int count_ = 0;

    const unsigned int ROWS;
    const unsigned int COLS;

public:
    // constructor. PASSING THE MATRIX BY VALUE DELIBERATELY SO THAT WE DO NOT MODIFY ELEMENTS IN THE ORIGINAL WHEN MARKING THEM AS VISITED.
    // matrix_ should not be accessed after the constructor exits as it is a reference to a temporary copy made for the constructor.
    FindIslands(std::vector<std::vector<int>> m) : matrix_(m), ROWS(m.size()), COLS(m.size() == 0 ? 0 : matrix_[0].size())
    {
        GetIslands();
    }

    int Count() const
    {
        return count_;
    }

private:
    // for the given element, if its value is 1, push it onto the stack, mark it as "visited" by setting it to zero then return true.
    // Otherwise return false.
    bool VisitElement(unsigned row, unsigned column)
    {
        if (matrix_[row][column])
        {
            elementStack_.push(Element{ row, column });
            matrix_[row][column] = 0;
            return true;
        }
        return false;
    }

    void GetIslands() 
    {
        for (auto i = 0u; i < matrix_.size(); i++)
        {
            for (auto j = 0u; j < matrix_[i].size(); j++)
            {
                if (VisitElement(i, j))
                {
                    count_++;
                }

                // Now scan for neighbours - but for this example, DO NOT INCLUDE DIAGONAL NEIGHBOURS.
                while (!elementStack_.empty())
                {
                    auto& top = elementStack_.top();
                    auto neighbours = false;
                    if (top.row > 0)
                    {
                        neighbours |= VisitElement(top.row - 1, top.column);
                    }
                    if (top.column > 0)
                    {
                        neighbours |= VisitElement(top.row, top.column - 1);
                    }
                    if (top.row < ROWS - 1)
                    {
                        neighbours |= VisitElement(top.row + 1, top.column);
                    }
                    if (top.column < COLS - 1)
                    {
                        neighbours |= VisitElement(top.row, top.column + 1);
                    }
                    if (!neighbours)
                    {
                        elementStack_.pop();
                    }
                }
            }
        }
    }
};


#define TESTMATRIX(m) std::cout << "Matrix " #m " contains " << FindIslands(m).Count() << " islands.\n"

int main()
{
    std::vector<std::vector<int>> i0;
    std::vector<std::vector<int>> i1a = { {1} };
    std::vector<std::vector<int>> i1b = { {0} };

    std::vector<std::vector<int>> i2a = { {1, 1}, {1, 1} };
    std::vector<std::vector<int>> i2b = { {1, 0}, {0, 1} };

    std::vector<std::vector<int>> iA = {
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
    };

    std::vector<std::vector<int>> big(1000);
    for (auto i = 0u; i < 1000u; ++i)
    {
        for (auto j = 0u; j < 1000u; ++j)
        {
            big[i].push_back(1);
        }
    }

    big[500][500] = 0;
    big[500][502] = 0;
    big[499][501] = 0;
    big[501][501] = 0;

    TESTMATRIX(i0);
    TESTMATRIX(i1a);
    TESTMATRIX(i1b);
    TESTMATRIX(i2a);
    TESTMATRIX(i2b);
    TESTMATRIX(iA);
    TESTMATRIX(big);
    std::cout << "finished\n";
}
