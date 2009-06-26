#ifndef TARGET_H
#define TARGET_H

#include "FileAttributes.h"
#include "Database.h"
using namespace shaman::data;

#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/string.h>

#include "sha.h"
#include "hex.h"
#include "files.h"
using namespace CryptoPP;

#include <set>
#include <list>
#include <algorithm>
using namespace std;

namespace shaman {
namespace model {

class Target {
    public:
        enum match {
            UNRECOGNIZED = 0,
            PARTIAL = 1,
            COMPLETE = 2
        };

        explicit Target( wxString dir_path = "" );
        ~Target();

        void set_dir( const wxString &dir_path );
        void reset_dir();
        bool has_files_to_get();
        int get_file_count() const;
        void get_file( HashTransformation &hash_type );
        void check_for_dupes();
        void move_unrecognized();
        void save_as( const wxString &file_path, HashTransformation &hash_type );
        bool is_set() const { return my_is_set; };
        int find_match( wxString name, wxString hash );
        bool rename_file( wxString file_name );
        bool rename_all();

    private:
        void move_dupes();
        void move_file( wxString file_name, wxString subdir );

        wxDir my_dir;
        wxString my_dir_path;
        bool my_has_files_to_get;
        bool my_is_set;

        wxFileName my_current_file;
        wxString my_current_file_name;
        wxString my_current_file_hash;

        FileAttributesSet my_files_attributes;

        set< wxString > my_found_file_names;
        map< wxString, wxString > my_renames;
        set< wxString > my_unrecog_dupes;
        set< wxString > my_dupe_file_names;
        const wxString DUPE_SUBDIR_NAME;
        const wxString UNRECOG_SUBDIR_NAME;
        wxString my_dupe_subdir_path;
        wxString my_unrecog_subdir_path;
};

}
}
#endif // TARGET_H
