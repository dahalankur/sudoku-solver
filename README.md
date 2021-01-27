# sudoku-solver
## A C++ sudoku solver
### By Ankur Dahal 

This is a sudoku solver written in C++. To compile and run the program, type `make sudoku` followed by `./sudoku`
If you want to provide the board input to the program through a text file, use `./sudoku filename`, 
where `filename` is a text file that contains the board state, in a format shown below: <br />
<br />
<h5>inputBoard.txt</h5>

<code>      9 0 0 0 0 0 0 0 1  </code> <br />
<code>      0 0 0 0 5 0 0 0 0  </code> <br />
<code>      8 0 0 0 4 0 0 0 0  </code> <br />
<code>      0 0 0 0 3 0 0 0 0  </code> <br />
<code>      0 0 0 9 1 0 0 0 0  </code> <br />
<code>      0 2 0 0 0 0 0 0 0  </code> <br />
<code>      0 0 0 0 0 0 0 0 8  </code> <br />
<code>      0 9 0 0 6 0 0 0 0  </code> <br />
<code>      5 0 0 0 0 1 0 0 9  </code> <br />
<br />
where 0 indicates an empty spot in the sudoku grid.
