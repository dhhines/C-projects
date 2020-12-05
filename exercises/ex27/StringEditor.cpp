#include <iostream>
#include <vector>
#include <string>

using namespace std;

/** Abstract base class for an edit operation.  It represents an
    und-oable change to a C++ string object.  It how to apply itself
    (perform the edit) and undo itself (restore the state of the
    string to what it looked like before the edit).  */
class Edit {
protected:
  /** String this edit operation is supposed to modify, protected,
      so derived classes can access it directly. */
  string &str;
public:
  /** Make a new edito operation that modifies the given string. */
  Edit( string &str ) : str( str ) {
  }

  /** Virtual destructor to clean up for this object.  The base class doesn't
      need to do anything. */
  virtual ~Edit() {
  }

  /** Make an edit to the string, str. */
  virtual void apply() = 0;
  
  /** Undo this edit in the given string.  Restore the state the string was in
      before the edit. */
  virtual void undo() = 0;
};

/** Edit operation that erases a character from a given position in
    the string, as if you had backspaced over that character. */
class Erase : public Edit {
  /** Position of the character to erase. */
  int pos;

  /** To be able to undo, we need to remember the character we erased. */
  char victim;
  
public:
  /** Make an edit that erases from str the character at the given
      position. */
  Erase( string &str, int pos ) : Edit( str ) {
    Erase::pos = pos;
  }
  
  virtual void apply() {
    // Remeber the character we're erasing.
    victim = str[ pos ];

    // Erase it.
    str.erase( pos, 1 );
  }
  
  virtual void undo() {
    // Put the character back where it came from.
    str.insert( pos, 1, victim );
  }
};

// Define your own derived classes of Edit.
// ...

/** Perform the given edit, and put it on the edit history. */
void performEdit( Edit *edit )
{
  // Apply the edit.
  edit->apply();

  // Put it on the history.
  // ...
}

/** Remove the most recen edit from the Undo the most recent edit,
    then free memory for it.  Return false if there's no edit to
    undo. */
bool undoEdit()
{
  // ...

  return true;
}

/** Clear the contents of the history.  This is so we can restore the
    state of the history between tests. */
void clearHistory()
{
  // ...
}

/** Print out the value of a string, and make sure it matches the
    expected value. Report the test number, so it's easy to tell which
    block of code this test comes from. */
void checkString( int tnum, string const &str, string const &target )
{
  // Print the test number and the string.
  cout << "Test-" << tnum << ": " << str;

  // Complain if it's not the expected strign.
  if ( str != target )
    cout << " (should be " << target << ")";
  
  cout << endl;
}

// Try out just the Erase edit, provided for you.
void editTest1()
{
  // String we're going to edit.
  string str = "abc123";
  checkString( 1, str, "abc123" );
  
  // Remove the first digit.
  performEdit( new Erase( str, 3 ) );
  checkString( 1, str, "abc23" );

  // Remove the rest of the digits.
  performEdit( new Erase( str, 3 ) );
  performEdit( new Erase( str, 3 ) );
  checkString( 1, str, "abc" );

  clearHistory();
}

// Try using the history, and undo-ing some edits. 
void editTest2()
{
  // String we're going to edit.
  string str = "abcdefgh";
  checkString( 2, str, "abcdefgh" );
  
  // Remove every other letter.
  performEdit( new Erase( str, 0 ) );
  performEdit( new Erase( str, 1 ) );
  performEdit( new Erase( str, 2 ) );
  performEdit( new Erase( str, 3 ) );
  checkString( 2, str, "bdfh" );

  // Undo the last two edits.
  undoEdit();
  undoEdit();
  checkString( 2, str, "bdefgh" );
  
  // Undo the rest.
  undoEdit();
  undoEdit();
  checkString( 2, str, "abcdefgh" );

  // Shouldn't need this here.
  clearHistory();
}

// Try the Replace edit, to change characters individually.
void editTest3()
{
  /* Un-comment this once you've implemented Replace.

  // String we're going to edit.
  string str = "cute";
  checkString( 3, str, "cute" );
  
  // Start changing characters one at a time.
  performEdit( new Replace( str, 2, 'r' ) );
  checkString( 3, str, "cure" );
  
  performEdit( new Replace( str, 0, 'p' ) );
  checkString( 3, str, "pure" );
  
  performEdit( new Replace( str, 2, 'c' ) );
  checkString( 3, str, "puce" );
  
  performEdit( new Replace( str, 1, 'a' ) );
  checkString( 3, str, "pace" );
  
  performEdit( new Replace( str, 3, 't' ) );
  checkString( 3, str, "pact" );
  
  // Undo the last couple of edits.
  undoEdit();
  undoEdit();
  checkString( 3, str, "puce" );

  */

  clearHistory();
}

// Try the Insert edit, insert individual characters int he string.
void editTest4()
{
  /* Un-comment this once you've implemented Insert.

  // String we're going to edit.
  string str = "5";
  checkString( 4, str, "5" );
  
  // Start inserting characters in this string.
  performEdit( new Insert( str, 0, '2' ) );
  checkString( 4, str, "25" );
  
  performEdit( new Insert( str, 1, '4' ) );
  checkString( 4, str, "245" );
  
  performEdit( new Insert( str, 3, '9' ) );
  checkString( 4, str, "2459" );
  
  performEdit( new Insert( str, 0, '1' ) );
  checkString( 4, str, "12459" );
  
  performEdit( new Insert( str, 4, '7' ) );
  checkString( 4, str, "124579" );
  
  // Undo the last couple of edits.
  undoEdit();
  undoEdit();
  checkString( 4, str, "2459" );

  */

  clearHistory();
}

// Prototype for test 5, defined below.
void editTest5();

int main()
{
  // Various tests of the code you get to write.
  editTest1();
  editTest2();
  editTest3();
  editTest4();
  editTest5();
  
  return 0;
}

// Don't change the preprocessor directives around this function.
// I put this code inside conditional compilation.  So, when I test your
// code, I can replace this test with a function from another file.
#ifndef EXTERNAL_TEST_5

// Try some of each type of edit.
void editTest5()
{
  /* Un-comment this once you've implemented everything.

  // String we're going to edit.
  string str = "north";
  checkString( 5, str, "north" );
  
  // Start making edits to the string.
  performEdit( new Replace( str, 0, 'f' ) );
  checkString( 5, str, "forth" );
  
  performEdit( new Erase( str, 4 ) );
  checkString( 5, str, "fort" );
  
  performEdit( new Replace( str, 2, 'o' ) );
  checkString( 5, str, "foot" );
  
  performEdit( new Replace( str, 0, 's' ) );
  checkString( 5, str, "soot" );
  
  performEdit( new Insert( str, 4, 'h' ) );
  checkString( 5, str, "sooth" );
  
  performEdit( new Replace( str, 2, 'u' ) );
  checkString( 5, str, "south" );

  // Undo the edits a little at a time.
  undoEdit();
  undoEdit();
  checkString( 5, str, "soot" );

  undoEdit();
  undoEdit();
  checkString( 5, str, "fort" );

  undoEdit();
  undoEdit();
  checkString( 5, str, "north" );
  
  */

  clearHistory();
}

#endif

