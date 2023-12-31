/* SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License */

/* Parts of this are taken from glibc's syslog.h which is distributed under the license
 * specified above.
 *
 * ESP implementation Copyright 2023 Fritz Elfert
 */

#pragma once

/*
 * priorities/facilities are encoded into a single 32-bit quantity, where the
 * bottom 3 bits are the priority (0-7) and the top 28 bits are the facility
 * (0-big number).  Both the priorities and the facilities map roughly
 * one-to-one to strings in the syslogd(8) source code.  This mapping is
 * included in this file.
 *
 * priorities (these are ordered)
 */
#define LOG_EMERG   0 /* system is unusable */
#define LOG_ALERT   1 /* action must be taken immediately */
#define LOG_CRIT    2 /* critical conditions */
#define LOG_ERR     3 /* error conditions */
#define LOG_WARNING 4 /* warning conditions */
#define LOG_NOTICE  5 /* normal but significant condition */
#define LOG_INFO    6 /* informational */
#define LOG_DEBUG   7 /* debug-level messages */

#define LOG_PRIMASK 0x07  /* mask to extract priority part (internal) */

/* extract priority */
#define LOG_PRI(p)  ((p) & LOG_PRIMASK)
#define LOG_MAKEPRI(fac, pri) (((fac) << 3) | (pri))

/* facility codes */
#define LOG_KERN        (0<<3)  /* kernel messages */
#define LOG_USER        (1<<3)  /* random user-level messages */
#define LOG_MAIL        (2<<3)  /* mail system */
#define LOG_DAEMON      (3<<3)  /* system daemons */
#define LOG_AUTH        (4<<3)  /* security/authorization messages */
#define LOG_SYSLOG      (5<<3)  /* messages generated internally by syslogd */
#define LOG_LPR         (6<<3)  /* line printer subsystem */
#define LOG_NEWS        (7<<3)  /* network news subsystem */
#define LOG_UUCP        (8<<3)  /* UUCP subsystem */
#define LOG_CRON        (9<<3)  /* clock daemon */
#define LOG_AUTHPRIV    (10<<3) /* security/authorization messages (private) */
#define LOG_FTP         (11<<3) /* ftp daemon */

/* other codes through 15 reserved for system use */
#define LOG_LOCAL0      (16<<3) /* reserved for local use */
#define LOG_LOCAL1      (17<<3) /* reserved for local use */
#define LOG_LOCAL2      (18<<3) /* reserved for local use */
#define LOG_LOCAL3      (19<<3) /* reserved for local use */
#define LOG_LOCAL4      (20<<3) /* reserved for local use */
#define LOG_LOCAL5      (21<<3) /* reserved for local use */
#define LOG_LOCAL6      (22<<3) /* reserved for local use */
#define LOG_LOCAL7      (23<<3) /* reserved for local use */

#define LOG_NFACILITIES 24  /* current number of facilities */
#define LOG_FACMASK 0x03f8  /* mask to extract facility part */

/* facility of pri */
#define LOG_FAC(p)  (((p) & LOG_FACMASK) >> 3)

#define LOG_MASK(pri)  (1 << (pri))             /* mask for one priority */
#define LOG_UPTO(pri)  ((1 << ((pri)+1)) - 1)	/* all priorities through pri */

#ifdef CONFIG_USE_SYSLOG

# ifdef __cplusplus
extern "C" {
# endif

/** See syslog(3) */
extern void syslog(int __pri, const char* __fmt, ...)
__attribute__ ((__format__ (__printf__, 2, 3)));

/** See vsyslog(3) */
extern void vsyslog(int __pri, const char* __fmt, va_list alist);

/** See syslog(3), except app overrides the ident, specified in openlog for this one message */
extern void syslogx(int __pri, const char* app, const char* __fmt, ...)
__attribute__ ((__format__ (__printf__, 3, 4)));

/** See vsyslog(3), except app overrides the ident, specified in openlog for this one message */
extern void vsyslogx(int __pri, const char* app, const char* __fmt, va_list alist);

/** See openlog(3) except option has no effect */
extern void openlog(const char* ident, int option, int facility);

/** Blocks, until syslog message-queue is empty */
extern void syslog_flush(void);

extern void closelog(void);

/** See setlogmask(3) */
extern int setlogmask(int mask);

/** Sets the local hostname, used when sending */
extern void set_syslog_hostname(const char* hostname);

# ifdef __cplusplus
}
# endif

#else /* CONFIG_USE_SYSLOG */

# define closelog(...) while(0)
# define openlog(...) while(0)
# define setlogmask(...) while(0)
# define set_syslog_hostname(...) while(0)
# define syslog(...) while(0)
# define syslogx(...) while(0)
# define syslog_flush(...) while(0)
# define vsyslog(...) while(0)
# define vsyslogx(...) while(0)

#endif
