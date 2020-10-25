/**
 * @author David Hines
 * @file edit.h
 *
 * Header file for the edit component that contains preprocessor constants as well as
 * any needed extern variables or function prototypes.
 */

/**
 * This function modifies the global representation of the text to remove lines in the given range
 *
 * @param start  the start of the range of lines to remove
 * @param end  the end of the range of lines to remove
 */
void removeLines( int start, int end);

/**
 * This function modifies the global representation of the text to remove text within the columns
 * between the given range.  The line number where the columns will be modified is provided by the
 * lno parameter
 *
 * @param lno  the line number where the text columns will be modified
 * @param start  the start of the columns to modify
 * @param end  the end of the columns to modify
 */
void editLines( int lno, int start, int end);
