#ifndef DATABASE_H
#define DATABASE_H

#include <map>
using namespace std;

#include <wx/grid.h>
#include <wx/filename.h>

#include "FileKeys.h"
using namespace shaman;
#include "FileAttributes.h"
using namespace shaman::data;

namespace shaman {
namespace model {

class Database : public wxGridTableBase
{
    public:
        enum AttributeIndex {
            NAME = 0,
            SIZE = 1,
            HASH = 2
        };

        explicit Database( wxString csv_path = wxString() );
        virtual ~Database();

        // Virtual wxGridTableBase overrides
        int GetNumberRows();
        int GetNumberCols();
        bool IsEmptyCell( int row, int col );
        wxString GetValue( int row, int col );
        void SetValue( int row, int col, const wxString &value );
        wxString GetColLabelValue ( int col );

        bool open();
        bool open( const wxString & );
        bool is_open() const;
        void close();

    protected:
        FileAttributesSet my_files_attributes;
        wxFileName my_file_name;
        wxString *my_col_labels;

        const int MAX_COL;
};

}
}
#endif // DATABASE_H
