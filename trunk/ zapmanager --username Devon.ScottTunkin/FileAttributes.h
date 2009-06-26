#ifndef FILEATTRIBUTES_H
#define FILEATTRIBUTES_H

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
using boost::multi_index_container;
using namespace boost::multi_index;

#include <wx/string.h>

namespace shaman {
namespace data {

struct FileAttributes {
    wxString name;
    wxULongLong size;
    wxString hash;

    FileAttributes() : name( wxString() ), size( 0 ), hash( wxString() ) {}
    FileAttributes( const wxString &a_name, const wxULongLong &a_size,
                    const wxString &a_hash )
        : name( a_name ), size( a_size ), hash( a_hash ) {}

    //bool operator< ( const FileAttributes & ) const;
    //bool operator== ( const FileAttributes & ) const;
};

struct name{};
struct hash{};
typedef multi_index_container<
    FileAttributes,
    indexed_by<
        random_access<>,
        ordered_unique< tag< name >,
            member< FileAttributes, wxString, &FileAttributes::name > >,
        hashed_unique< tag< hash >,
            member< FileAttributes, wxString, &FileAttributes::hash > >
    >
> FileAttributesSet;
typedef FileAttributesSet::index< hash >::type FileAttributesSetByHash;

} // data
} // shaman
#endif // FILEATTRIBUTES_H
