#include "ZapManagerData.h"

//std
#include <string>
using namespace std;

//wxWidgets
#include <wx/filename.h>

FileProperties::FileProperties( wxString name, wxString size, wxString hash ) {
    my_properties[0] = name;
    my_properties[1] = size;
    my_properties[2] = hash;
}

FileProperties::FileProperties() {
    my_properties[0] = "New File";
    my_properties[1] = "0";
    my_properties[2] = "";
}

FileProperties& FileProperties::operator=( const FileProperties &RhData ) {
   this->my_properties[0] = RhData.my_properties[0];
   this->my_properties[1] = RhData.my_properties[1];
   this->my_properties[2] = RhData.my_properties[2];

   return *this;
}

bool FileProperties::operator==(const FileProperties &RhData) const {
    if( this->my_properties[0] != RhData.my_properties[0]
        || this->my_properties[1] != RhData.my_properties[1]
        || this->my_properties[2] != RhData.my_properties[2] )
    {
        return false;
    }
    else return true;
}

//Compare strings for limited alphabetizing and speeding up comparisons
bool FileProperties::operator<(const FileProperties &RhData) const {
    if( this->my_properties[0] < RhData.my_properties[0] ) return true;

    else return false;
}

void FileProperties::compare_with( const FileProperties &RhData ) {
    if( this->operator==( RhData ) )
        my_status = 'm';

    if( this->my_properties[0] != RhData.my_properties[0]
        && this->my_properties[1] == RhData.my_properties[1]
        && this->my_properties[2] == RhData.my_properties[2] )
    {
        my_status = 'n';
    }

    else
        my_status = 'u';
}

wxString FileProperties::get_property(const int i) const {
    if (i >= 0 && i < 3) return my_properties[i];

    else {
        throw "Data request out of bounds";
        //wxMessageBox( _("Data request out of bounds") );
        //return "Data request out of bounds";
    }
}

void FileProperties::set_property( const int i, const wxString str ) {
    my_properties[i] = str;
}

char FileProperties::get_status() const {
    return my_status;
}

void FileProperties::load_from_dir( wxString file_name, wxString dir_name, HashTransformation &hash_type ) {
        set_property( 0, file_name );

        wxFileName file_attributes( dir_name, file_name );
        wxULongLong file_size = file_attributes.GetSize();
        set_property( 1, _( file_size.ToString() ) );

        string file_hash;
        FileSource convert_to_hash( file_attributes.GetFullPath(), true,
             new HashFilter( hash_type,
                 new HexEncoder(
                    new StringSink( file_hash ) ) ) );
        set_property( 2, file_hash );
}



