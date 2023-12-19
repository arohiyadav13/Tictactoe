// NxN tic-tac-toes
#include <iostream>
#include <cstdlib>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);


/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);


/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * @brief Get the Ai Choice for the current player and update grid object
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If an error occurred or a choice was unable to be made
 * @return false If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**
 * @brief Picks a random location for the current player and update grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If no viable location to be played
 * @return false If a play was successfully made
 */
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player);


/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
    return grid[ (dim*r) + c ];
}

int idxToRow(int idx, int dim)
{
    return idx/dim;/* Add Expression here to convert idx to appropriate row */ ;
}

int idxToCol(int idx, int dim)
{
    return idx%dim;/* Add Expression here to convert idx to appropriate column */;
}

void printTTT(char grid[], int dim)
{
  //print out row and columns
  for(int r = 0; r<dim; r++)
  {
    for(int c = 0; c<dim; c++)
    {
      cout << grid[(dim*r) + c];
      if(c < dim-1)
      {
        cout << " | ";
      }
    }
    cout << endl;
    int dashes = (dim*4)-1; // grid times 4 -1
    if(r < dim -1)
    {
      for(int i = 1; i<= dashes; i++)
      {
        cout<< "-";
      }
      cout << endl;
    }

  }
}

int checkForWinner(char grid[], int dim)
{
  //row wins
  for(int i = 0; i<dim; i++)
  {
    char rowSymbol = getEntryAtRC(grid, dim, i, 0);
    bool rwin = true; 
    for(int j = 0; j<dim; j++)
    {
      if(rowSymbol != getEntryAtRC(grid, dim, i, j))
      {
        rwin = false;
        break;
      }
    }
    if(rwin == true)
    {
      if (rowSymbol == 'X')
      {
        return 1;
      } 
      if (rowSymbol == 'O')
      {
        return 2;
      } 
    }
  }


  // column wins
  for(int i = 0; i<dim; i++)
  {
    char colSymbol = getEntryAtRC(grid, dim, 0, i);
    bool cwin = true; 
    for(int j = 0; j<dim; j++)
    {
      //cout << colSymbol << "expected" << endl;
      //cout << getEntryAtRC(grid, dim, i, j) << "location" << i << j << endl; 
      if(colSymbol != getEntryAtRC(grid, dim, j, i))
      {
        cwin = false;
        break;
      }
    }
    if(cwin == true)
    {
      if (colSymbol == 'X')
      {
        return 1;
      } 
      if (colSymbol == 'O')
      {
        return 2;
      } 
    }
  }

  //diagonal wins 
  char diag1 = getEntryAtRC(grid, dim, 0, 0);
  bool diagWin1 = true;
  for(int i = 0; i<dim; i++) 
  {
    if(diag1 != getEntryAtRC(grid, dim, i, i))
    {
      diagWin1 = false;
      break;
    }
  }
  if (diagWin1 == true)
  {
    if (diag1 == 'X')
    {
      return 1;
    }
    if (diag1 == 'O')
    {
      return 2;
    }
  }

  //diagonal 2 wins
  char diag2 = getEntryAtRC(grid, dim, 0, dim-1);
  bool diagWin2 = true;
  for(int i = 0; i<dim; i++) 
  {
    if(diag2 != getEntryAtRC(grid, dim, i, dim-1-i))
    {
      diagWin2 = false;
      break;
    }
  }
  if (diagWin2 == true)
  {
    if (diag2 == 'X')
    {
      return 1;
    }
    if (diag2 == 'O')
    {
      return 2;
    }
  }

  return 0; 
}




bool checkForDraw(char grid[], int dim)
{
  int count = 0;
  bool rdraw = false;
  bool cdraw = false;
  bool d1draw = false;
  bool d2draw = false;
  // Check rows
  for (int i = 0; i < dim; i ++) 
  {
    bool hasX = false;
    bool hasO = false;
    for (int j = 0; j < dim; j ++) 
    {
      if (getEntryAtRC(grid, dim, i, j) == 'X') 
      {
        hasX = true;
      } 
      else if (getEntryAtRC(grid, dim, i, j) == 'O') 
      {
        hasO = true;
      }
      if (hasX && hasO && j == dim -1) 
      {
        //cout << i << " r draw" << endl;
        count++; 
      }
    }
  }
  if(count == dim)
  {
    //cout << "rows" << endl; 
    rdraw = true; 
  }


  // Check cols 
  count = 0; 
  for (int i = 0; i < dim; i ++) 
  {
    bool hasX = false;
    bool hasO = false;
    for (int j = 0; j < dim; j ++) 
    {
      if (getEntryAtRC(grid, dim, j, i) == 'X') 
      {
        hasX = true;
      } 
      else if (getEntryAtRC(grid, dim, j, i) == 'O') 
      {
        hasO = true;
      }
      if (hasX && hasO && j == dim -1) 
      {
        //cout << i << " c draw" << endl;
        count++; 
      }
    }
  }
  if(count == dim)
  {
    //cout << "columns" << endl;
    cdraw = true; 
  }

  //check diagonal 1
  int hasX = 0;
  int hasO = 0;
  for (int i = 0; i < dim; i ++) 
  { 
    if (getEntryAtRC(grid, dim, i, i) == 'X') 
    {
      hasX++;
    } 
    else if (getEntryAtRC(grid, dim, i, i) == 'O') 
    {
      hasO++;
    }
    if (hasX && hasO) 
    {
      //cout << "diag1" << endl;
      d1draw = true; 
    }
  }

  //check diagonal 2 
  hasX = 0;
  hasO = 0;
  for (int i = 0; i < dim; i ++) 
  { 
    if (getEntryAtRC(grid, dim, i, dim-1-i) == 'X') 
    {
      hasX++;
    } 
    else if (getEntryAtRC(grid, dim, i, dim-1-i) == 'O') 
    {
      hasO++;
    }
    if (hasX && hasO) 
    {
      //cout << "diag2" << endl;
      d2draw = true;
    }
    
  }
//cout << rdraw << cdraw << d1draw << d2draw << endl;
return (rdraw && cdraw && d1draw && d2draw); 

}

bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player)
{
  //x win
  if(player == 'X')
  {
    for(int i = 0; i<dim*dim; i++)
    {
      if(grid[i] == '?')
      {
        grid[i] = 'X';
        int x = checkForWinner(grid, dim);
        //cout << x << i << endl; 
        if(x == 1)
        {
          return false; 
        }
        else
        {
          grid[i] = '?';
        }
      }
    }
  }

  // o win
  if(player == 'O')
  {
    for(int i = 0; i<dim*dim; i++)
    {
      if(grid[i] == '?')
      {
        grid[i] = 'O';
        int x = checkForWinner(grid, dim);
        if(x == 2)
        {
          return false; 
        }
        else
        {
          grid[i] = '?';
        }
      }
    }
  }

  //x block
  if(player == 'X')
  {
    for(int i = 0; i<dim*dim; i++)
    {
      if(grid[i] == '?')
      {
        grid[i] = 'O';
        int x = checkForWinner(grid, dim);
        if( x == 2)
        {
          grid[i] = 'X';
          return false;
        }
        else
        {
          grid[i] = '?';
        }
      }
    }
  }

  // o block
  if(player == 'O')
  {
    for(int i = 0; i<dim*dim; i++)
    {
      if(grid[i] == '?')
      {
        grid[i] = 'X';
        int x = checkForWinner(grid, dim);
        if( x == 1)
        {
          grid[i] = 'O';
          return false; 
        }
        else
        {
          grid[i] = '?';
        }
        
      }
    }
  }


  return true; 

}


// Complete...Do not alter
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player)
{
    int start = rand()%(dim*dim);
    // look for an open location to play based on random starting location.
    // If that location is occupied, move on sequentially until wrapping and
    // trying all locations
    for(int i=0; i < dim*dim; i++) {
        int loc = (start + i) % (dim*dim);
        if(grid[ loc ] == '?') {
            grid[ loc ] = player;
            return false;
        }
    }
    // No viable location
    return true;
}


/**********************************************************
 *  Complete the indicated parts of main(), below.
 **********************************************************/
int main()
{
    // This array holds the actual board/grid of X and Os. It is sized
    // for the biggest possible case (11x11), but you should only
    // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
    char tttdata[121];

    // dim stands for dimension and is the side length of the
    // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
    int dim;
    int seed;
    // Get the dimension from the user
    cin >> dim >> seed;
    srand(seed);

    int dim_sq = dim*dim;

    for(int i=0; i < dim_sq; i++) {
        tttdata[i] = '?';
    }

    // Print one of these messages when the game is over
    // and before you quit
    const char xwins_msg[] = "X player wins!";
    const char owins_msg[] = "O player wins!";
    const char draw_msg[] =  "Draw...game over!";

    bool done = false;
    char player = 'X';
    // Show the initial starting board
    printTTT(tttdata, dim);

    while(!done) {
      
      int choice;

        //**********************************************************
        // Get the current player's input (i.e. the location they want to
        // choose to place their mark [X or O]) or choice of AI or Random
        // location and update the tttdata array.
        // Be sure to follow the requirements defined in the guide/writeup
        // for quitting immediately if the user input is out-of-bounds
        // (i.e. not in the range 0 to dim_sq-1 nor -1 nor -2) as well as
        // continuing to prompt for an input if the user chooses locations
        // that have already been chosen (already marked with an X or O).
        //**********************************************************

        // Add your code here for getting input
        // Player X enter your square choice [0-8], -1 (AI), or -2 (Random):
        cout << "Player " << player << " enter your square choice [0-" << dim*dim-1 << "], -1 (AI), or -2 (Random):" << endl;
        cin >> choice; 

        if(choice == -1)
        {
          getAiChoiceAndUpdateGrid(tttdata, dim, player);
        }
        else if (choice == -2)
        {
          getRandChoiceAndUpdateGrid(tttdata, dim, player);
        }
        else if(choice >= 0 && choice < dim*dim)
        {
          while(tttdata[choice] != '?')
          {
            cout << "Player " << player << " enter your square choice [0-" << dim*dim-1 << "], -1 (AI), or -2 (Random):" << endl;
            cin >> choice;
           }
          tttdata[choice] = player;
        }  
        else
        {
          break;
        }
        



        // Show the updated board if the user eventually chose a valid location
        // (i.e. you should have quit the loop and program by now without any
        //  other output message if the user chosen an out-of-bounds input).
        printTTT(tttdata, dim);

        int win = checkForWinner(tttdata, dim);
        if(win == 1)
        {
          cout << xwins_msg << endl;
          break;
        }
        else if(win == 2)
        {
          cout << owins_msg << endl;
          break;
        }
        else if(checkForDraw(tttdata, dim))
        {
          cout << draw_msg << endl; 
          break; 
        }

        if(player == 'X')
        {
          player = 'O';
        }
        else if(player == 'O')
        {
          player = 'X';
        }



        //**********************************************************
        // Complete the body of the while loop to process the input that was just
        //  received to check for a winner or draw and update other status, as
        //  needed.
        //
        // To match our automated checkers' expected output, you must output
        // one of the messages defined above using *one* of the cout commands
        // (under the appropriate condition) below:
        //   cout << xwins_msg << endl;  OR
        //   cout << owins_msg << endl;  OR
        //   cout << draw_msg << endl;
        //
        // Note: Our automated checkers will examine a specific number of lines
        //  at the end of the program's output and expect to see the updated board
        //  and game status message.  You may certainly add some debug print
        //  statements during development but they will need to be removed to
        //  pass the automated checks.
        //**********************************************************

    } // end while
    return 0;
}
