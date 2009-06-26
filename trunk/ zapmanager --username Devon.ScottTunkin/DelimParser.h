#ifndef DELIMPARSER_H_INCLUDED
#define DELIMPARSER_H_INCLUDED

#include <wx/string.h>

namespace shaman {

class DelimParser {
    public:
        DelimParser( wxString const &, wxString );
        DelimParser( wxString const & );
        DelimParser();

        wxString get_value();

    protected:
        wxString my_delimiter;
        size_t my_delimiter_length;
        size_t my_delimiter_location;
        size_t my_next_delimiter_location;

        size_t my_quote_location;
        size_t my_next_quote_location;

        wxString const *my_line;
};
} //shaman
#endif // DELIMPARSER_H_INCLUDED
