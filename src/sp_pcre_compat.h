#ifndef SP_PCRE_COMPAT_H
#define SP_PCRE_COMPAT_H

#if HAVE_BUNDLED_PCRE
  #ifdef PCRE2_MAJOR
    #include "ext/pcre/pcre2lib/pcre2.h"
  #else
    #include "ext/pcre/pcrelib/pcre.h"
  #endif
 #undef pcre_exec
 #undef pcre_compile
 //#define sp_pcre_exec pcre_exec
 //#define sp_pcre_compile pcre_compile
#else
 #include "pcre.h"
 //#define sp_pcre_exec pcre_exec
 //#define sp_pcre_compile pcre_compile
#endif


#include "php_snuffleupagus.h"

#ifdef PCRE2_MAJOR
#define sp_pcre pcre2_code
#else
#define sp_pcre pcre
#endif

sp_pcre* sp_pcre_compile(const char* str);
#define sp_is_regexp_matching(regexp, str) \
	sp_is_regexp_matching_len(regexp, str, strlen(str))
bool sp_is_regexp_matching_len(const sp_pcre* regexp, const char* str, size_t len);

#endif // SP_PCRE_COMPAT_H
