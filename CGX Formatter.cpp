#include <iostream>

/**This program takes an input of a number of lines of text
 * and outputs a modifide version of that text.
 */

std::string raw_string( std::string input_string )
{ // This method takes a string and returns the same string with the
    // escape characters '\n' and '\t' replaced with '\\n' and '\\t'
    for( size_t index = 0; index < input_string.size(); ++index)
    { // check every index
        if( input_string[ index ] == '\n' )
        {
            input_string.replace( index, 1, "\\n" );
            ++index;
        }
        
        if( input_string[ index ] == '\t' )
        {
            input_string.replace( index, 1, "\\t" );
            ++index;
        }
    }

    return input_string;
}

int main()
{
    std::string CGXLine;
    size_t input_count;
    
    std::cin >> input_count; std::cin.ignore();
    
    for( size_t count = input_count; count; --count )
    { // input of text
        std::string input_string;
        getline( std::cin, input_string );
        
        CGXLine += "\n" + input_string; // \n is incase a line break is within quotes
    }
    
    std::cerr << "#####\n" << raw_string( CGXLine ) << "\n#####" << std::endl; // input text before modification
    
    for( size_t indention = 0, index = 0; index < CGXLine.size(); )
    {
        if( CGXLine[ index ] == '(' ) //# all lines after "(" are indented 4 spaces
        {
            if( CGXLine[ index - 1 ] == '=' )
            { // block assigned to key, add new line
                CGXLine.insert( index, "\n" + std::string( indention * 4, ' ' ) ); // new line with indentation before index
                index += 1 + indention * 4; // skip over new characters
            }
                
            ++indention;
        }
        
        switch( CGXLine[ index ] )
        {
            case '\'': //# always keep text in quotes unmodified
                index = CGXLine.find( '\'', index + 1 ) + 1; // skip over characters in quotes
            
                if( index == std::string::npos ) // error check
                {
                    std::cerr << "Open string error" << std::endl;
                }
                
                break;

            case '(': //# ";" and "(" create a new line
            case ';':
                CGXLine.insert( index + 1, "\n" + std::string( indention * 4, ' ' ) ); // new line with indentation after index
                index += 2 + indention * 4; // skip over new characters
                break;

            case ')': //# ")" removes the 4 space indention for itself and all lines after it
                --indention;
            
                if( CGXLine[ index - 6 - indention * 4 ] == '(' )
                { // empty block
                    CGXLine.erase( index - 4, 4 ); // remove indent
                    index -= 3; // next character minus the removed characters
                }
                else
                {
                    CGXLine.insert( index, "\n" + std::string( indention * 4, ' ' ) ); // new line with indentation before index
                    index += 2 + indention * 4; // skip over new characters
                }
                
                break;

            case ' ': //# strip all spaces, tabs, and new lines outside of quotes
            case '\t':
            case '\n':
                CGXLine.erase( index, 1 ); // remove index
                break;

            default: //# no operation, error characters will fall though here
                ++index; // next character
        }
    }
    
    std::cout << CGXLine << std::endl;
}