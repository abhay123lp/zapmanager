#include "Database.h"
using namespace shaman::model;

#include "DelimParser.h"

#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/filefn.h>

#include <set>
using namespace std;

Database::Database( wxString csv_path )
    : my_file_name( csv_path ), MAX_COL( 3 )
{
    my_col_labels = new wxString[ MAX_COL ];
    my_col_labels[0] = "File Name";
    my_col_labels[1] = "File Size (Bytes)";
    my_col_labels[2] = "File Hash (SHA-256)";
}

Database::~Database() {
    delete []my_col_labels;
}

int Database::GetNumberRows() {
    return my_files_attributes.size();
}

int Database::GetNumberCols() {
    return MAX_COL;
}

bool Database::IsEmptyCell( int row, int col ) {
    if( GetValue( row, col ) == "" ) return true;
    else return false;
}

wxString Database::GetValue( int row, int col ) {
    if( row > my_files_attributes.size() )
        throw "Row argument out of bounds in Database::GetValue.";
    if( col == 0 ) return my_files_attributes[ row ].name;
    else if( col == 1 ) return my_files_attributes[ row ].size.ToString();
    else if( col == 2 ) return my_files_attributes[ row ].hash;
    else throw "Col argument out of bounds in Database::GetValue.";
}

void Database::SetValue( int row, int col, const wxString& value ) {
    throw "Cannot set individual cell value. Values must be set completely.";
}

wxString Database::GetColLabelValue( int col ) {
    if( col < MAX_COL && col >= 0 ) return my_col_labels[ col ];
    else throw "Col argument out of bounds in Database::GetColLabelValue.";
}

bool Database::open() {
    try {
        if( !my_file_name.FileExists() ) throw wxString( "File does not exist." );
        wxString csv_path = my_file_name.GetFullPath();

        wxFileInputStream csv_input( csv_path );
        wxTextInputStream csv_text( csv_input );
        wxString line;

        int row = 0;
        int col;
        wxString value[ MAX_COL ];
        unsigned long file_size;
        bool is_unique = true;

        while( csv_input.IsOk() ) {
            line = csv_text.ReadLine();
            DelimParser csv_parser( line );

            if( !line.IsEmpty() ) {
                for( col = 0; col < MAX_COL; ++col ) {
                    value[ col ] = csv_parser.get_value();
                }
                value[ SIZE ].ToULong( &file_size );
                is_unique = my_files_attributes.push_back(
                                FileAttributes( value[ NAME ],
                                                file_size,
                                                value[ HASH ] ) ).second;
                if( !is_unique )
                    throw wxString( "Could not open "
                        + my_file_name.GetFullName()
                        + ". Duplicate file name or hash found at line "
                        << row + 1 << "." );
                ++row;
            }
        }
        return true;
    }
    catch( wxString &error ) {
        wxMessageBox( error );
        close();
    }
    return false;
}

bool Database::open( const wxString &csv_path ) {
    my_file_name.Assign( csv_path );
    return open();
}

bool Database::is_open() const{
    return !my_files_attributes.empty();
}

void Database::close() {
    my_files_attributes.clear();
}


