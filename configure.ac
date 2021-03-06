#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

m4_include([m4/check_project_info.m4])
m4_include([m4/get_cross_gcc_info.m4])

AC_INIT([PROJECT_NAME], [VERSION_NUM], [EMAIL_INFO], [PROJECT_NAME], [PROJECT_URL])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_SILENT_RULES([yes])
AM_PROG_AR

LT_INIT

PKG_PROG_PKG_CONFIG([0.24])

# check m4 macro
CHECK_PROJECT_INFO
GCC_PREFIX_INFO
CHECK_VERSION_INFO
CHECK_DOXYGEN
CHECK_JAVA

SELECT_MCU_CORTEX
ENABLE_MCU

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
# AC_PROG_RANLIB

AM_PROG_AS
AC_PROG_MKDIR_P

# Checks for libraries.

# Checks for header files.
AC_HEADER_MAJOR
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h limits.h netdb.h netinet/in.h shadow.h stddef.h stdint.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h syslog.h unistd.h utmp.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UID_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([gethostbyname gettimeofday inet_ntoa memmove memset select strchr strdup strerror strncasecmp strrchr strstr strtol strtoul])

AC_CONFIG_FILES([Makefile
                 $project_name.pc
                 doc/Makefile
                 doc/at32f4xx/Makefile
                 include/Makefile
                 res/Makefile
                 src/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/AT32F4xx_StdPeriph_Driver/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/AT32F4xx_StdPeriph_Driver/inc/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/AT32F4xx_StdPeriph_Driver/src/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/CM4/CoreSupport/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/CM4/DeviceSupport/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/CM4/DeviceSupport/startup/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/CM4/DeviceSupport/startup/gcc/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/CM4/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/CMSIS/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries/Makefile
                 src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Makefile
                 src/at32f4xx/Makefile
                 src/at32f4xx/lwip-2.1.2/Makefile
                 src/at32f4xx/lwip-2.1.2/port/Makefile
                 src/at32f4xx/lwip-2.1.2/src/Makefile
                 src/at32f4xx/lwip-2.1.2/src/api/Makefile
                 src/at32f4xx/lwip-2.1.2/src/core/Makefile
                 src/at32f4xx/lwip-2.1.2/src/core/ipv4/Makefile
                 src/at32f4xx/lwip-2.1.2/src/netif/Makefile
                 src/hc32l13x/CMSIS/Include/Makefile
                 src/hc32l13x/CMSIS/Makefile
                 src/hc32l13x/Makefile
                 src/hc32l13x/driver/Makefile
                 src/hc32l13x/driver/inc/Makefile
                 src/hc32l13x/driver/src/Makefile
                 src/hc32l13x/mcu/Makefile
                 src/hc32l13x/mcu/common/Makefile])
AC_OUTPUT
