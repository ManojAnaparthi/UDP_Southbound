/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Autovalidator for actions is a default implementation. */
/* #undef ACTIONS_AUTOVALIDATOR_DEFAULT */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* If the C compiler is GCC 4.7 or later, define to the return value of
   __atomic_always_lock_free(1, 0). If the C compiler is not GCC or is an
   older version of GCC, the value does not matter. */
#define ATOMIC_ALWAYS_LOCK_FREE_1B 1

/* If the C compiler is GCC 4.7 or later, define to the return value of
   __atomic_always_lock_free(2, 0). If the C compiler is not GCC or is an
   older version of GCC, the value does not matter. */
#define ATOMIC_ALWAYS_LOCK_FREE_2B 1

/* If the C compiler is GCC 4.7 or later, define to the return value of
   __atomic_always_lock_free(4, 0). If the C compiler is not GCC or is an
   older version of GCC, the value does not matter. */
#define ATOMIC_ALWAYS_LOCK_FREE_4B 1

/* If the C compiler is GCC 4.7 or later, define to the return value of
   __atomic_always_lock_free(8, 0). If the C compiler is not GCC or is an
   older version of GCC, the value does not matter. */
#define ATOMIC_ALWAYS_LOCK_FREE_8B 1

/* Autovalidator for the userspace datapath classifier is a default
   implementation. */
/* #undef DPCLS_AUTOVALIDATOR_DEFAULT */

/* If MAP_HUGE_SHIFT is defined, anonymous memory mapping is supported by the
   kernel, and --in-memory can be used. */
/* #undef DPDK_IN_MEMORY_SUPPORTED */

/* System uses the DPDK module. */
/* #undef DPDK_NETDEV */

/* DPIF AVX512 is a default implementation of the userspace datapath
   interface. */
/* #undef DPIF_AVX512_DEFAULT */

/* Define to 1 if AF_XDP support is available and enabled. */
/* #undef HAVE_AF_XDP */

/* Define to 1 if you have the <atomic> header file. */
/* #undef HAVE_ATOMIC */

/* Define to 1 if compiler supports the '-mavx512bw' option. */
#define HAVE_AVX512BW 1

/* Define to 1 if compiler supports the '-mavx512f' option. */
#define HAVE_AVX512F 1

/* Define to 1 if compiler supports the '-mavx512vbmi' option. */
#define HAVE_AVX512VBMI 1

/* Define to 1 if compiler supports the '-mavx512vl' option. */
#define HAVE_AVX512VL 1

/* Define to 1 if the build system implements the vpopcntdq instruction. */
#define HAVE_AVX512VPOPCNTDQ 1

/* Define to 1 if you have backtrace(3). */
#define HAVE_BACKTRACE 1

/* Define to 1 if you have the <bits/floatn-common.h> header file. */
#define HAVE_BITS_FLOATN_COMMON_H 1

/* Define to 1 if you have the `bpf_xdp_detach' function. */
/* #undef HAVE_BPF_XDP_DETACH */

/* Define to 1 if you have the `bpf_xdp_query_id' function. */
/* #undef HAVE_BPF_XDP_QUERY_ID */

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* define if the compiler supports basic C++11 syntax */
#define HAVE_CXX11 1

/* Define to 1 if you have the declaration of `malloc_trim', and to 0 if you
   don't. */
#define HAVE_DECL_MALLOC_TRIM 1

/* Define to 1 if you have the declaration of `RTE_EAL_NUMA_AWARE_HUGEPAGES',
   and to 0 if you don't. */
/* #undef HAVE_DECL_RTE_EAL_NUMA_AWARE_HUGEPAGES */

/* Define to 1 if you have the declaration of `RTE_LIBRTE_VHOST_NUMA', and to
   0 if you don't. */
/* #undef HAVE_DECL_RTE_LIBRTE_VHOST_NUMA */

/* Define to 1 if you have the declaration of `strerror_r', and to 0 if you
   don't. */
#define HAVE_DECL_STRERROR_R 1

/* Define to 1 if you have the declaration of `sys_siglist', and to 0 if you
   don't. */
#define HAVE_DECL_SYS_SIGLIST 0

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if the C compiler and linker supports the GCC 4.0+ atomic
   built-ins. */
#define HAVE_GCC4_ATOMICS 1

/* Define to 1 if gcc implements the vpermd instruction. */
#define HAVE_GCC_AVX512VL_GOOD 1

/* Define to 1 if you have the `getloadavg' function. */
#define HAVE_GETLOADAVG 1

/* Define to 1 if you have the `getmntent_r' function. */
#define HAVE_GETMNTENT_R 1

/* Define to 1 if pthread_setname_np() is available and takes 2 parameters
   (like glibc). */
#define HAVE_GLIBC_PTHREAD_SETNAME_NP 1

/* Define to 1 if net/if_dl.h is available. */
/* #undef HAVE_IF_DL */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if binutils correctly supports AVX512. */
#define HAVE_LD_AVX512_GOOD 1

/* Define to 1 if libcap-ng is available. */
#define HAVE_LIBCAPNG 1

/* Define to 1 if you have the `socket' library (-lsocket). */
/* #undef HAVE_LIBSOCKET */

/* Define to 1 if you have the <libunwind.h> header file. */
/* #undef HAVE_LIBUNWIND_H */

/* xsk.h is supplied with libxdp */
/* #undef HAVE_LIBXDP */

/* Define to 1 if you have the <linux/if_ether.h> header file. */
#define HAVE_LINUX_IF_ETHER_H 1

/* Define to 1 if you have the <linux/net_namespace.h> header file. */
#define HAVE_LINUX_NET_NAMESPACE_H 1

/* Define to 1 if you have the <linux/perf_event.h> header file. */
#define HAVE_LINUX_PERF_EVENT_H 1

/* Define to 1 if you have the <linux/types.h> header file. */
#define HAVE_LINUX_TYPES_H 1

/* Define to 1 if you have the <minix/config.h> header file. */
/* #undef HAVE_MINIX_CONFIG_H */

/* Define to 1 if you have the `mlockall' function. */
#define HAVE_MLOCKALL 1

/* Define to 1 if you have the <mntent.h> header file. */
#define HAVE_MNTENT_H 1

/* Define to 1 if pthread_setname_np() is available and takes 3 parameters
   (like NetBSD). */
/* #undef HAVE_NETBSD_PTHREAD_SETNAME_NP */

/* Define to 1 if Netlink protocol is available. */
#define HAVE_NETLINK 1

/* Define to 1 if you have the <net/if_mib.h> header file. */
/* #undef HAVE_NET_IF_MIB_H */

/* Define to 1 if struct nla_bitfield32 is available. */
#define HAVE_NLA_BITFIELD32 1

/* Define to 1 if OpenSSL is installed. */
#define HAVE_OPENSSL 1

/* Define to 1 if `posix_memalign' works. */
#define HAVE_POSIX_MEMALIGN 1

/* Define if compiler supports #pragma message directive */
#define HAVE_PRAGMA_MESSAGE 1

/* Define to 1 if you have the `pthread_set_name_np' function. */
/* #undef HAVE_PTHREAD_SET_NAME_NP */

/* Define to 1 if you have the `pthread_spin_lock' function. */
#define HAVE_PTHREAD_SPIN_LOCK 1

/* Define to 1 if you have the <rte_config.h> header file. */
/* #undef HAVE_RTE_CONFIG_H */

/* Define to 1 if SCTP_CONNTRACK_HEARTBEAT_SENT is available. */
#define HAVE_SCTP_CONNTRACK_HEARTBEATS 1

/* Define to 1 if you have the `sendmmsg' function. */
#define HAVE_SENDMMSG 1

/* Define to 1 if you have the `sigdescr_np' function. */
#define HAVE_SIGDESCR_NP 1

/* Define to 1 if you have the `statvfs' function. */
#define HAVE_STATVFS 1

/* Define to 1 if you have the <stdatomic.h> header file. */
#define HAVE_STDATOMIC_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if you have `strerror_r'. */
#define HAVE_STRERROR_R 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define if strtok_r macro segfaults on some inputs */
/* #undef HAVE_STRTOK_R_BUG */

/* Define to 1 if `ifr_flagshigh' is a member of `struct ifreq'. */
/* #undef HAVE_STRUCT_IFREQ_IFR_FLAGSHIGH */

/* Define to 1 if `msg_len' is a member of `struct mmsghdr'. */
#define HAVE_STRUCT_MMSGHDR_MSG_LEN 1

/* Define to 1 if `sin6_scope_id' is a member of `struct sockaddr_in6'. */
#define HAVE_STRUCT_SOCKADDR_IN6_SIN6_SCOPE_ID 1

/* Define to 1 if `st_mtimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIMENSEC */

/* Define to 1 if `st_mtim.tv_nsec' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC 1

/* Define to 1 if `firstuse' is a member of `struct tcf_t'. */
#define HAVE_STRUCT_TCF_T_FIRSTUSE 1

/* Define to 1 if the system has the type `struct timespec'. */
/* #undef HAVE_STRUCT_TIMESPEC */

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#define HAVE_SYS_STATVFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if TCA_ACT_FLAGS_SKIP_HW is available. */
#define HAVE_TCA_ACT_FLAGS_SKIP_HW 1

/* Define to 1 if HAVE_TCA_MPLS_TTL is available. */
#define HAVE_TCA_MPLS_TTL 1

/* Define to 1 if TCA_PEDIT_KEY_EX_HDR_TYPE_UDP is available. */
#define HAVE_TCA_PEDIT_KEY_EX_HDR_TYPE_UDP 1

/* Define to 1 if TCA_SKBEDIT_FLAGS is available. */
#define HAVE_TCA_SKBEDIT_FLAGS 1

/* Define to 1 if TCA_STATS_PKT64 is available. */
#define HAVE_TCA_STATS_PKT64 1

/* Define to 1 if TCA_TUNNEL_KEY_ENC_TTL is available. */
#define HAVE_TCA_TUNNEL_KEY_ENC_TTL 1

/* Define to 1 if TCA_VLAN_PUSH_VLAN_PRIORITY is available. */
#define HAVE_TCA_VLAN_PUSH_VLAN_PRIORITY 1

/* Define to 1 if the C compiler and linker supports the C11 thread_local
   matcro defined in <threads.h>. */
#define HAVE_THREAD_LOCAL 1

/* Define to 1 if unbound is detected. */
/* #undef HAVE_UNBOUND */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if unwind is detected. */
/* #undef HAVE_UNWIND */

/* Define to 1 if USDT probes are enabled. */
/* #undef HAVE_USDT_PROBES */

/* Define to 1 if you have the <valgrind/valgrind.h> header file. */
#define HAVE_VALGRIND_VALGRIND_H 1

/* Define to 1 if __virtio16 is available. */
#define HAVE_VIRTIO_TYPES 1

/* Define to 1 if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Define to 1 if the C compiler and linker supports the GCC __thread
   extenions. */
/* #undef HAVE___THREAD */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Autovalidator for miniflow_extract is a default implementation. */
/* #undef MFEX_AUTOVALIDATOR_DEFAULT */

/* Define to 1 if OpenSSL supports Server Name Indication (SNI). */
#define OPENSSL_SUPPORTS_SNI 1

/* Name of package */
#define PACKAGE "openvswitch"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "bugs@openvswitch.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "openvswitch"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "openvswitch 3.1.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "openvswitch"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.1.0"

/* Define to 1 if all of the C90 standard headers exist (not just the ones
   required in a freestanding environment). This macro is provided for
   backward compatibility; new code need not use it. */
#define STDC_HEADERS 1

/* Define to 1 if strerror_r returns char *. */
#define STRERROR_R_CHAR_P 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable general extensions on macOS.  */
#ifndef _DARWIN_C_SOURCE
# define _DARWIN_C_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable X/Open compliant socket functions that do not require linking
   with -lxnet on HP-UX 11.11.  */
#ifndef _HPUX_ALT_XOPEN_SOCKET_API
# define _HPUX_ALT_XOPEN_SOCKET_API 1
#endif
/* Identify the host operating system as Minix.
   This macro does not affect the system headers' behavior.
   A future release of Autoconf may stop defining this macro.  */
#ifndef _MINIX
/* # undef _MINIX */
#endif
/* Enable general extensions on NetBSD.
   Enable NetBSD compatibility extensions on Minix.  */
#ifndef _NETBSD_SOURCE
# define _NETBSD_SOURCE 1
#endif
/* Enable OpenBSD compatibility extensions on NetBSD.
   Oddly enough, this does nothing on OpenBSD.  */
#ifndef _OPENBSD_SOURCE
# define _OPENBSD_SOURCE 1
#endif
/* Define to 1 if needed for POSIX-compatible behavior.  */
#ifndef _POSIX_SOURCE
/* # undef _POSIX_SOURCE */
#endif
/* Define to 2 if needed for POSIX-compatible behavior.  */
#ifndef _POSIX_1_SOURCE
/* # undef _POSIX_1_SOURCE */
#endif
/* Enable POSIX-compatible threading on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-5:2014.  */
#ifndef __STDC_WANT_IEC_60559_ATTRIBS_EXT__
# define __STDC_WANT_IEC_60559_ATTRIBS_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-1:2014.  */
#ifndef __STDC_WANT_IEC_60559_BFP_EXT__
# define __STDC_WANT_IEC_60559_BFP_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-2:2015.  */
#ifndef __STDC_WANT_IEC_60559_DFP_EXT__
# define __STDC_WANT_IEC_60559_DFP_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-4:2015.  */
#ifndef __STDC_WANT_IEC_60559_FUNCS_EXT__
# define __STDC_WANT_IEC_60559_FUNCS_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-3:2015.  */
#ifndef __STDC_WANT_IEC_60559_TYPES_EXT__
# define __STDC_WANT_IEC_60559_TYPES_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TR 24731-2:2010.  */
#ifndef __STDC_WANT_LIB_EXT2__
# define __STDC_WANT_LIB_EXT2__ 1
#endif
/* Enable extensions specified by ISO/IEC 24747:2009.  */
#ifndef __STDC_WANT_MATH_SPEC_FUNCS__
# define __STDC_WANT_MATH_SPEC_FUNCS__ 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable X/Open extensions.  Define to 500 only if necessary
   to make mbstate_t available.  */
#ifndef _XOPEN_SOURCE
/* # undef _XOPEN_SOURCE */
#endif


/* Version number of package */
#define VERSION "3.1.0"

/* NUMA Aware vHost support detected in DPDK. */
/* #undef VHOST_NUMA */

/* System uses the Visual Studio build target. */
/* #undef VSTUDIO_DDK */

/* Define to 1 if building on WIN32. */
/* #undef WIN32 */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

#ifdef WIN32
#include "include/windows/windefs.h"
#endif
