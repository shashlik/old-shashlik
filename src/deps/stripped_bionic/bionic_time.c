#include <time.h>

/*
** In the current implementation, "tzset()" refuses to deal with files that
** exceed any of the limits below.
*/

#ifndef TZ_MAX_TIMES
#define TZ_MAX_TIMES    1200
#endif /* !defined TZ_MAX_TIMES */

#ifndef TZ_MAX_TYPES
#ifndef NOSOLAR
#define TZ_MAX_TYPES    256 /* Limited by what (unsigned char)'s can hold */
#endif /* !defined NOSOLAR */
#ifdef NOSOLAR
/*
** Must be at least 14 for Europe/Riga as of Jan 12 1995,
** as noted by Earl Chew.
*/
#define TZ_MAX_TYPES    20  /* Maximum number of local time types */
#endif /* !defined NOSOLAR */
#endif /* !defined TZ_MAX_TYPES */

#ifndef TZ_MAX_CHARS
#define TZ_MAX_CHARS    50  /* Maximum number of abbreviation characters */
                /* (limited by what unsigned chars can hold) */
#endif /* !defined TZ_MAX_CHARS */

#ifndef TZ_MAX_LEAPS
#define TZ_MAX_LEAPS    50  /* Maximum number of leap second corrections */
#endif /* !defined TZ_MAX_LEAPS */

struct ttinfo {             /* time type information */
    int tt_gmtoff;  /* UTC offset in seconds */
    int          tt_isdst;   /* used to set tm_isdst */
    int          tt_abbrind; /* abbreviation list index */
    int          tt_ttisstd; /* TRUE if transition is std time */
    int          tt_ttisgmt; /* TRUE if transition is UTC */
};

struct lsinfo {             /* leap second information */
    time_t       ls_trans;   /* transition time */
    int ls_corr;    /* correction to apply */
};

#ifdef TZNAME_MAX
#define MY_TZNAME_MAX   TZNAME_MAX
#endif /* defined TZNAME_MAX */
#ifndef TZNAME_MAX
#define MY_TZNAME_MAX   255
#endif /* !defined TZNAME_MAX */

struct state {
    int     leapcnt;
    int     timecnt;
    int     typecnt;
    int     charcnt;
    int     goback;
    int     goahead;
    time_t      ats[TZ_MAX_TIMES];
    unsigned char   types[TZ_MAX_TIMES];
    struct ttinfo   ttis[TZ_MAX_TYPES];
    char        chars[MY_TZNAME_MAX];
    struct lsinfo   lsis[TZ_MAX_LEAPS];
    int defaulttype; /* for early times or if no transitions */
};

// Non-standard API: mktime(3) but with an explicit timezone parameter.
time_t mktime_tz(struct tm* const tmp, const char* tz) {
  struct state st;
//   if (__bionic_tzload_cached(tz, &st, TRUE) != 0) {
//     // TODO: not sure what's best here, but for now, we fall back to gmt.
//     gmtload(&st);
//   }
//   return time1(tmp, localsub, 0L, &st);
}

// Non-standard API: localtime(3) but with an explicit timezone parameter.
void localtime_tz(const time_t* const timep, struct tm* tmp, const char* tz) {
  struct state st;
//   if (__bionic_tzload_cached(tz, &st, TRUE) != 0) {
//     // TODO: not sure what's best here, but for now, we fall back to gmt.
//     gmtload(&st);
//   }
//   localsub(timep, 0L, tmp, &st);
}
