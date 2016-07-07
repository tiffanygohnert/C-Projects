/***********************************************************************
* Program:
*    Project 1, Prodedural Chess  
*    Brother McCracken, CS165
* Author:
*    Tiffany Gohnert
* Summary: 
*    This program is a user friendly game of procedural chess. This game
* will be based on the Smith Notation of chess algebra and will be able to
* save and load a game. 
*
*    Estimated:  10.0 hrs   
*    Actual:     15.0 hrs
*      I couldn't figure out how to get my read file to run properly.
************************************************************************/

#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include<cstring>
#include <cassert>
using namespace std;

// Define 
#define WHITE_WHITE "\E[31;47m"
#define WHITE_BLACK "\E[30;47m"
#define BLACK_WHITE "\E[37;41m"
#define BLACK_BLACK "\E[30;41m"
#define NO_PIECE ' '
#define INVALID 127

//Struct to hold row and column
struct Coord
{
   char r;   // row, from 0..7
   char c;   // col, from 0..7
};

//Struct to hold moves
struct Move
{
   string text;
   char piece;
   bool capture;
   bool castleK;
   bool castleQ;
   bool enpassant;
   bool promote;
   Coord  source;        
   Coord  dest;          
};

void initialize(char board[][8]);
void display(char board[][8], bool simple);
void read(vector<string> & moves, char board[][8], bool simple);
void interact(vector<string> & moves, char board[][8]);
inline bool parse(Move & move, char board[][8], string & errorMessage);
void executeMove(Move & move, char board[][8]);
void write(vector<string> & moves);
inline void displayOptions();
void  resetBoard(char board[][8]);
 

/**********************************************************************
 * MAIN
 *    This is the driver function that allows the rest of the program
 * to run properly. 
 ***********************************************************************/
int main()
{
   // string for holding moves
   vector<string> moves;
   // define the board
   char board[8][8];
   // initialize the board
   initialize(board);
   // display the board
   display(board, false);
   // allows the uers to interact with the board
   interact(moves, board);
   return 0;
}

/**********************************************************************
 * INITIALIZE
 *    This function initalizes the board.
 ***********************************************************************/
void initialize(char board[][8])
{
   // white pieces
   board[0][0] = 'r';
   board[0][1] = 'n';
   board[0][2] = 'b';
   board[0][3] = 'q';
   board[0][4] = 'k';
   board[0][5] = 'b';
   board[0][6] = 'n';
   board[0][7] = 'r';

   for(int c = 0; c <= 7; c++)
      board[1][c] = 'p';

   // empty spaces
   for(int r = 2; r <= 5; r++)
      for(int c = 0; c <= 7; c++)
         board[r][c] = ' ';

   // black pieces
   for(int c = 0; c <= 7; c++)
      board[6][c] = 'P';

   board[7][0] = 'R';
   board[7][1] = 'N';
   board[7][2] = 'B';
   board[7][3] = 'Q';
   board[7][4] = 'K';
   board[7][5] = 'B';
   board[7][6] = 'N';
   board[7][7] = 'R';
   
   //clear board
   cout << "\E[H\E[2J";
}

/**********************************************************************
 * DISPLAY
 *    This funtion displays the board as it the user inputs moves. 
 ***********************************************************************/
void display(char board[][8], bool simple)
{


   // declaration of variables
   bool blackSquare;
   bool blackPiece;
   char tempPiece;

   // the simple version of the board
   if (simple)
   {
      cout << "  ";
      for (char c ='a'; c <= 'h'; c++)
         cout << c;

      cout << endl;
      
      // cycles through and shows the board
      for (int r = 7; r >= 0; r--)
      {
         cout << r + 1 << " ";
         for (int c = 0; c <= 7; c++)
            cout << board[r][c];
         cout << endl;
      }
   }
   else
   {
      cout << "  ";

      for (char c ='a'; c <= 'h'; c++)
         cout << ' ' << c << ' ';

      cout << endl;



      // color board rows 7-8
      for (int r = 7; r >= 6; r--)
      {
         cout << r + 1 << " ";
         for (int c = 0; c <= 7; c++)

         {
            //check color of pieces and square
            blackSquare = (r + c) % 2;
            tempPiece = board[r][c];
            blackPiece = isupper(tempPiece);
            tempPiece = toupper(tempPiece);
            if (tempPiece == 'P')
               tempPiece = tolower(tempPiece);
            if (!blackSquare && !blackPiece)
               cout << BLACK_WHITE << " " << tempPiece << " \E[0m";
            else if (!blackSquare && blackPiece)
               cout << BLACK_BLACK << " " << tempPiece << " \E[0m";
            else if (blackSquare && !blackPiece)
               cout << WHITE_WHITE << " " << tempPiece << " \E[0m";
            else if (blackSquare && blackPiece)
               cout << WHITE_BLACK << " " << tempPiece << " \E[0m";
         }
         cout << endl;
      }


      // color board rows 2 through 5
      for (int r = 5; r >= 2; r--)
      {
         cout << r + 1 << " ";
         for (int c = 0; c <= 7; c++)
         {
            // check color of pieces and square
            blackSquare = (r + c) % 2;
            tempPiece = board[r][c];
            blackPiece = isupper(tempPiece);
            tempPiece = toupper(tempPiece);
            if (tempPiece == 'P')
               tempPiece = tolower(tempPiece);
            if (!blackSquare && !blackPiece)
               cout << BLACK_BLACK << " " << tempPiece << " \E[0m";
            else if (!blackSquare && blackPiece)
               cout << BLACK_BLACK << " " << tempPiece << " \E[0m";
            else if (blackSquare && !blackPiece)
               cout << WHITE_BLACK << " " << tempPiece << " \E[0m";
            else if (blackSquare && blackPiece)
               cout << WHITE_BLACK << " " << tempPiece << " \E[0m";
         }
         cout << endl;
      }




      // color board for rows 0-1
      for (int r = 1; r >= 0; r--)
      {
         cout << r + 1 << " ";
         for (int c = 0; c <= 7; c++)
         {
            // check color of pieces and square
            blackSquare = (r + c) % 2;
            tempPiece = board[r][c];
            blackPiece = isupper(tempPiece);
            tempPiece = toupper(tempPiece);
            if (tempPiece == 'P')
               tempPiece = tolower(tempPiece);
            if (!blackSquare && !blackPiece)
               cout << BLACK_WHITE << " " << tempPiece << " \E[0m";
            else if (!blackSquare && blackPiece)
               cout << BLACK_BLACK << " " << tempPiece << " \E[0m";
            else if (blackSquare && !blackPiece)
               cout << WHITE_WHITE << " " << tempPiece << " \E[0m";
            else if (blackSquare && blackPiece)
               cout << WHITE_BLACK << " " << tempPiece << " \E[0m";
         }
         cout << endl;
      }
   }







}

/**********************************************************************
 * READ
 *    This function reads an inputed file and displays the moves
 * from the file to a new board. 
 ***********************************************************************/
void read(vector<string> & moves, char board[][8], bool simple)
{
// declaration of variables
   bool good = true;
   string errorMessage;

   // gets filename
   string fileName;
   cout << "Filename: ";
   cin  >> fileName;

   // opens file
   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Unable to read file: " << fileName << endl;
      return;
   }

   // execues file moves
   string fileMove;
   while(fin >> fileMove)
   {
      moves.push_back(fileMove);
   }

   // checks files moves
   vector<string>::iterator p;
   for(p = moves.begin(); p < moves.end(); p++)
   {
      resetBoard(board); 
      display(board, true);
      interact(moves, board);

      Move tmpMove;
      tmpMove.castleK = false;
      tmpMove.castleQ = false;
      tmpMove.text = *p;
      if(!parse(tmpMove, board, errorMessage))
      {
         cout << "Error parsing file "
              << fileName
              << " with move \'"
              << errorMessage;
         good = false;
      }
      else
      {
         // execute moves if they pass
         executeMove(tmpMove, board);
         display(board, true);
         interact (moves, board); 
      }
   }

   // put in vector is not ok
   if (good)
   {
      vector<string>::iterator p;
      for(p = moves.begin(); p < moves.end(); p++)
      {
         *p = "";
      }
      initialize(board);
      
   }

   // close file
   fin.close();
}

/**********************************************************************
 * DISPLAY OPTIONS
 *    This function displays the users options.
 ***********************************************************************/
inline void displayOptions()
{
   // displays options
   cout << "Options:\n"
        << " ?      Display these options\n"
        << " b2b4   Specify a move using the Smith Notation\n"
        << " read   Read a saved game from a file\n"
        << " test   Simple display for test purposes\n"
        << " quit   Leave the game. You will be prompted to save\n";
}

/**********************************************************************
 * INTERACT
 *    This function allows the uers to interact with the board.
 ***********************************************************************/
void interact(vector<string> & moves, char board[][8])
{
   // declaration of variables
   string errorMessage;
   string input;
   bool simple = true;
   bool quit = false;

   // loop
   do
   {
      //black or white turn
      switch (moves.size() % 2)
      {
         case 0:
            cout << "(White): ";
            break;
         case 1:
            cout << "(Black): ";
            break;
         default:
            cout << "Oops";
      }

      
      cin >> input;

      // displays users options
      if (input == "?")
         displayOptions();
      
      else if (input == "read")
      {
        read(moves, board, simple);       
      }
     
      else if (input == "test")
      {
         simple = true;
         display(board, simple);
      }
     
      else if (input == "quit")
         quit = true;
// if not input option then move
      else
      {
         Move move;
         move.castleK = false;
         move.castleQ = false;
         move.piece = NO_PIECE;
         move.capture = false;
         move.enpassant = false;
         move.promote = false; 
         move.text = input;
         
         // parse users input
         if (parse(move, board, errorMessage))
         {
            executeMove(move, board);
            display(board, simple);
             moves.push_back(move.text);
         }
         else
         {
            cout << "Error in move \'"
                 << errorMessage
                 << "        Type ? for more options\n";
         }

      }
   } while (quit == false);

   // quit and save
   write(moves);
   return;
}

/**********************************************************************
 * PARSE
 *    This function makes sure all the moves are valid.
 ***********************************************************************/
inline bool parse(Move & move, char board[][8], string & errorMessage)
{
   // initialize the move
   move.piece     = NO_PIECE;
   move.capture   = false;
   move.source.r  = INVALID;
   move.source.c  = INVALID;
   move.dest.r    = INVALID;
   move.dest.c    = INVALID;
   move.enpassant = false;
   move.castleK   = false;
   move.castleQ   = false;
   move.promote   = false;

   
   // column: a-h
   if (move.text[0] < 'a' || move.text[0] > 'h')
      throw string("Invalid format of source coordinates");
   move.source.c = move.text[0] - 'a';
   assert(move.source.c >= 0 && move.source.c <= 7);

   // row: 1-8
   if (move.text[1] < '1' || move.text[1] > '8')
      throw string("Invalid format of source coordinates");
   move.source.r = move.text[1] - '1';
   assert(move.source.r >= 0 && move.source.r <= 7);

   // if there is nothing to move, we have an error
   move.piece = tolower(board[move.source.r][move.source.c]);
   if (move.piece == NO_PIECE)
      throw string("No piece in the source coordinates position");

   //
   // to square
   //

   // column: a-h
   if (move.text[2] < 'a' || move.text[2] > 'h')
      throw string("Invalid format of destination coordinates");
   move.dest.c = move.text[2] - 'a';
   assert(move.dest.c >= 0 && move.dest.c <= 7);

   // row: 1-8
   if (move.text[3] < '1' || move.text[3] > '8')
      throw string("Invalid format of destination coordinates");
   move.dest.r = move.text[3] - '1';
   assert(move.dest.r >= 0 && move.dest.r <= 7);
   // capture if there is something there
   if (board[move.dest.r][move.dest.c] != NO_PIECE)
      move.capture = true;

   //
   // capture and promotion
   //
   for (int i = 4; i < move.text.size(); i++)
   {
      switch(move.text[i])
      {
         case 'p':   // capture a pawn
         case 'n':   // capture a knight
         case 'b':   // capture a bishop
         case 'r':   // capture a rook
         case 'q':   // capture a queen
         case 'k':   // !! you can't capture a king you silly!
            move.capture = true;
         break;

         case 'c':  // short castling or kings castle
            move.castleK = true;
            break;
         case 'C':  // long castling or queen castle
            move.castleQ = true;
            break;
         case 'E':  // En-passant
            move.enpassant = true;
            break;

         case 'N':  // Promote to knight
         case 'B':  // Promote to Bishop
         case 'R':  // Promote to Rook
         case 'Q':  // Promote to Queen
            move.piece = tolower(move.text[i]);
         move.promote = true;
         break;
         default:
            errorMessage = move.text + "\': Unknown promotion piece specification\n";
            return false;
      }
   }

   // once that is done, we can check if the square you're moving from is empty
   if (board[move.source.r][move.source.c] == ' ')
   {
      errorMessage = move.text
         + "\': No piece in the source coordinates position\n";
      return false;
   }
   return true;
}

/**********************************************************************
 * MOVE
 *    This functions takes the vector and changes the board according
 * to the move. 
 ***********************************************************************/
void executeMove(Move & move, char board[][8])
{
   // castling
   if (move.castleK)
   {
      board[move.dest.r][7] = ' ';
      board[move.dest.r][6] = 'K';
      board[move.dest.r][5] = 'R';
      board[move.dest.r][4] = ' ';
   }
   else if (move.castleQ)
   {
      board[move.dest.r][0] = ' ';
      board[move.dest.r][1] = ' ';
      board[move.dest.r][2] = 'K';
      board[move.dest.r][3] = 'R';
      board[move.dest.r][4] = ' ';
   }
   // normal moves
   else
   {
      board[move.dest.r][move.dest.c] = board[move.source.r][move.source.c];
      board[move.source.r][move.source.c] = ' ';
   }
}

/**********************************************************************
 * WRITE
 *    This function writes the board to a file. 
 ***********************************************************************/
void write(vector<string> & moves)
{
   // filename 
   string fileName;

   cout << "To save a game, please specify the filename.\n"
        << "    To quit without saving a file, just press <enter>\n";

    cin.ignore();
   getline(cin, fileName);

   
   if (fileName.empty())
      return;

   
   ofstream fout(fileName.c_str());

   // Error if failed
   if(fout.fail())
   {
      cout << "Could not write to file " << fileName << endl;
      return;
   }

   // write to file
   vector<string>::iterator p;
   for(p = moves.begin(); p < moves.end(); p++)
   {
      fout << *p << ' ';
   }

   // close file
   fout.close();
   return;
}

/**********************************************************************
 * RESETBOARD
 *    This function will reset the board when a new file is open.
 ***********************************************************************/
void resetBoard(char board[][8])
{
const char resetBoard[8][8] =
{
   { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
   { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
   { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
     NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
   { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
     NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
   { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
     NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
   { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
     NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
   { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
   { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
};
memcpy(board,resetBoard,sizeof(char)*64);
   


}

