#ifndef ZAPMANAGERDATA_H_INCLUDED
#define ZAPMANAGERDATA_H_INCLUDED

//wx
#include <wx/string.h>

//CryptoPP
#include "sha.h"
#include "hex.h"
#include "files.h"
using namespace CryptoPP;

class FileProperties
{
    public:
        FileProperties( wxString, wxString, wxString );
        FileProperties();
        //FileProperties(const FileProperties &);
        ~FileProperties(){};
        FileProperties &operator=( const FileProperties & );
        bool operator==( const FileProperties & ) const;
        bool operator<( const FileProperties & ) const;

        wxString get_property( const int ) const;
        void set_property( const int, const wxString );
        char get_status() const;
        void compare_with( const FileProperties & );
        void load_from_dir( wxString, wxString, HashTransformation & );
        //void SaveAsCSV(string);

    protected:
        wxString my_properties[3];//Filename, Size, Hash
        char my_status;//'u' = unrecognized, 'n' = different filename, 'm' = complete match

};

#endif // FileProperties_H_INCLUDED
