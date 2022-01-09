
#include <string>
#include <fmt/format.h>

struct ResolverData
{
    std::string pattern;
    std::string mask;
};

ResolverData ResolvePattern( std::string pattern )
{
    ResolverData data = { };

    // make pattern
    for ( int i = 0; i < pattern.size( ) - 1; i++ ) {
        char c = pattern[i];

        if ( c != '?' && c != ' ' && !( pattern[i + 1] == ' ' ) )
        {
            data.pattern += fmt::format( "\\x{}{}" , c, pattern[i + 1] );//buf;
        }
        else if ( c == '?' )
            data.pattern += "\\x00";
    }

    // make mask
    for ( int i = 0; i < pattern.size( ) - 1; i++ ) {
        char c = pattern[i];

        if ( c != '?' && c != ' ' && !( pattern[i + 1] == ' ' ) )
            data.mask += "x";
        else if (c == '?' )
            data.mask += "?";
    }

    return data;
}

void main()
{
    const auto signature = "48 8B 05 ? ? ? ? 48 85 C0 74"; // Example signature, replace with your own!
    const auto result    = ResolvePattern( signature );        
    const auto& pattern  = result.pattern;
    const auto& mask     = result.mask;

    printf( "Pattern: %s\n\n" , pattern.c_str( ) );
    printf( "Mask: %s\n\n"    , mask.c_str( )    );
    
    system( "pause" );
}
