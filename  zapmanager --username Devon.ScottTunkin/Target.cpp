#include <wx/filefn.h>
#include <wx/arrstr.h>

#include "Target.h"
using namespace shaman::model;

Target::Target( wxString dir_path ) :
    DUPE_SUBDIR_NAME( "Duplicates" ), UNRECOG_SUBDIR_NAME( "Unrecognized" )
{
    set_dir( dir_path );
}

Target::~Target() {
}

void Target::set_dir( const wxString &dir_path ) {
    my_is_set = false;
    my_files_attributes.clear();
    my_dupe_file_names.clear();
    my_renames.clear();
    my_found_file_names.clear();

    if( my_dir.Open( dir_path ) ) {
        my_has_files_to_get = my_dir.GetFirst( &my_current_file_name,
                                               wxEmptyString, wxDIR_FILES );
        my_current_file.Assign( dir_path, my_current_file_name );
        my_dir_path = dir_path + my_current_file.GetPathSeparator();
        my_dupe_subdir_path = (my_current_file.GetPathWithSep()
            + DUPE_SUBDIR_NAME + my_current_file.GetPathSeparator());
        my_unrecog_subdir_path = (my_current_file.GetPathWithSep()
            + UNRECOG_SUBDIR_NAME + my_current_file.GetPathSeparator());
        my_is_set = true;
    }
}

void Target::reset_dir() {
    set_dir( my_dir_path );
}

bool Target::has_files_to_get() {
    return my_dir.GetNext( &my_current_file_name );
}

int Target::get_file_count() const {
    wxArrayString files;
    int file_count = my_dir.GetAllFiles( my_dir_path, &files, wxEmptyString,
                                         wxDIR_FILES );
    return file_count;
}

void Target::get_file( HashTransformation &hash_type ) {
    my_current_file.Assign( my_dir_path, my_current_file_name );

    string current_file_hash;
    FileSource convert_to_hash( my_current_file.GetFullPath(), true,
         new HashFilter( hash_type,
             new HexEncoder(
                new StringSink( current_file_hash ) ) ) );
    my_current_file_hash = current_file_hash;
    my_current_file_hash.MakeLower();

    check_for_dupes();
    my_dir.GetNext( &my_current_file_name );
}

void Target::check_for_dupes() {
    pair< FileAttributesSet::iterator, bool > dupe_check;
    dupe_check = my_files_attributes.push_back(
        FileAttributes( my_current_file_name, my_current_file.GetSize(),
                        my_current_file_hash ) );

    FileAttributesSet::iterator dupe_it = dupe_check.first;
    bool is_dupe = !dupe_check.second;

    if( is_dupe ) {
        my_dupe_file_names.insert( my_current_file_name );
        //my_dupe_file_names.insert( dupe_it->name );
        //my_files_attributes.erase( dupe_it );
    }
}

void Target::move_dupes() {
    if( my_dupe_file_names.empty() ) {
        return;
    }
    wxString dir_path = my_current_file.GetPathWithSep();
    set< wxString >::iterator it;

    for( it = my_dupe_file_names.begin(); it != my_dupe_file_names.end(); ++it ) {
        wxMessageBox( *it );
        //Check for unrecognized dupes.
        if( my_found_file_names.find( *it ) == my_found_file_names.end() ) {
            my_unrecog_dupes.insert( *it );
            my_dupe_file_names.erase( it );
        }
        else
            move_file( *it, my_dupe_subdir_path );
    }
    my_dupe_file_names.clear();
}

void Target::save_as( const wxString &file_path,
                      HashTransformation &hash_type )
{
    move_dupes();
    if( !my_dupe_file_names.empty() )
        throw wxString(
            "Duplicate files found in directory. Cannot create database." );

    ofstream csv_file( file_path );
    FileAttributesSet::iterator it;
    FileAttributesSet::iterator end = my_files_attributes.end();
    for( it = my_files_attributes.begin(); it != end; ++it ) {
        csv_file << "\"" << it->name <<
                 "\",\"" << it->size.ToString() <<
                 "\",\"" << it->hash << "\"\n";
    }
    my_files_attributes.clear();
    csv_file.close();
}

int Target::find_match( wxString file_name, wxString file_hash ) {
    FileAttributesSetByHash& hash_index = my_files_attributes.get< hash >();
    FileAttributesSetByHash::iterator it = hash_index.find( file_hash );
    int match_type;
    if( it == hash_index.end() ) {
        match_type = UNRECOGNIZED;
    }
    else {
        my_found_file_names.insert( it->name );
        if( it->name != file_name ) {
            my_renames.insert( make_pair( file_name, it->name ) );
            match_type = PARTIAL;
        }
        else
            match_type = COMPLETE;

        // Erase so my_files_attributes will only have remaining unrecognized
        hash_index.erase( it );
    }
    return match_type;
}

bool Target::rename_file( wxString file_name ) {
    map< wxString, wxString >::iterator it;
    bool is_renamed;
    if( (it = my_renames.find( file_name )) == my_renames.end() )
        return false;

    // Rename target name to database name
    if( (is_renamed = wxRenameFile( my_dir_path + it->second,
                                    my_dir_path + file_name )) )
        my_renames.erase( file_name );

    return is_renamed;
}

bool Target::rename_all() {
    map< wxString, wxString >::iterator it;
    for( it = my_renames.begin(); it != my_renames.end(); ++it ) {
        if( !rename_file( it->first ) ) return false;
    }
    return true;
}

void Target::move_unrecognized() {
    set< wxString >::iterator it;
    FileAttributesSet::iterator jt;

    move_dupes();
    for( it = my_unrecog_dupes.begin(); it != my_unrecog_dupes.end(); ++it )
        move_file( *it, my_unrecog_subdir_path );
    for( jt = my_files_attributes.begin(); jt != my_files_attributes.end(); ++jt )
        move_file( jt->name, my_unrecog_subdir_path );
    my_files_attributes.clear();
}

void Target::move_file( wxString file_name, wxString subdir_path ) {
    if( !wxDirExists( subdir_path ) )
        wxMkdir( subdir_path, 0777 );
    wxCopyFile( (my_dir_path + file_name), (subdir_path + file_name) );
    wxRemoveFile( (my_dir_path + file_name) );
}

