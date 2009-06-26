#include "DelimParser.h"
using namespace shaman;

 //   my_quote_location = 0;
//    my_delimiter_location = 0;


DelimParser::DelimParser( wxString const &line, wxString delim)
    : my_delimiter( delim ), my_delimiter_location( 0 ), my_line( &line )
{
    my_quote_location = my_line->find( "\"" );
}

DelimParser::DelimParser( wxString const &line )
    : my_delimiter( "," ), my_delimiter_location( 0 ), my_line( &line )
{
    my_quote_location = my_line->find( _T("\"") );
}

DelimParser::DelimParser()
    : my_delimiter( "," ), my_delimiter_location( 0 ), my_quote_location( 0 )
{
}

wxString DelimParser::get_value() {
    wxString value;

    my_next_quote_location = my_line->find( _T("\""), my_quote_location + 1 );
    my_next_delimiter_location = my_line->find( my_delimiter, my_delimiter_location );

    if( ((my_delimiter_location < my_quote_location
              && my_next_delimiter_location < my_quote_location)
          || my_quote_location == wxString::npos) )
    {
        value = my_line->Mid( my_delimiter_location,
            my_next_delimiter_location - my_delimiter_location );
        my_next_quote_location = my_next_delimiter_location;
    }
    else {
        value = my_line->Mid( my_quote_location + 1,
            my_next_quote_location - my_quote_location - 1 );
        my_next_delimiter_location = my_next_quote_location + 1;
    }

    my_quote_location = my_line->find( _T("\""), my_next_quote_location + 1 );
    my_delimiter_location = my_next_delimiter_location + 1;

    return value;
}

