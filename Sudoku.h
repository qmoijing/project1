#include <iostream>
#include <cstdlib>
class Sudoku
{
    public:
        void GiveQuestion();
        void ReadIn();
        void Check();
        void Run(int n);
        void Solve();
    private:
        int ans[144];
        int sudoku[144];
        int catergory;
};

