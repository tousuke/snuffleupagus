#include "sp_pcre_compat.h"

sp_pcre* sp_pcre_compile(const char *const pattern) {
	sp_pcre* ret = NULL;
	const char *pcre_error;
#ifdef PCRE2_MAJOR
	int errornumber, erroroffset;
	ret = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_CASELESS, &errornumber, &erroroffset, NULL);
#else
	int erroroffset;
	ret = pcre_compile(pattern, PCRE_CASELESS, &pcre_error, &erroroffset, NULL);
#endif
	
	if (NULL == ret) {
		sp_log_err("config", "Failed to compile '%s': %s on line %zu.", pattern,
				pcre_error, sp_line_no);
	}
	return ret;
}

zend_always_inline bool sp_is_regexp_matching_len(const sp_pcre* regexp, const char* str, size_t len) {
  int vec[30];
  int ret = 0;

  assert(NULL != regexp);
  assert(NULL != str);

#ifdef PCRE2_MAJOR
	pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(regexp, NULL);
	ret = pcre2_match(regexp, str, len, 0, 0, match_data, NULL);
#else
  ret = pcre_exec(regexp, NULL, str, len, 0, 0, vec,
                     sizeof(vec) / sizeof(int));
#endif

  if (ret < 0) {
#ifdef PCRE2_MAJOR
    if (ret != PCRE2_ERROR_NOMATCH) {
#else
    if (ret != PCRE_ERROR_NOMATCH) {
#endif
      sp_log_err("regexp", "Something went wrong with a regexp (%d).", ret);
    }
    return false;
  }
  return true;
}
