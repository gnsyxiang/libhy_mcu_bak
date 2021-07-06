dnl ===============================================================
dnl 
dnl Release under GPLv-3.0.
dnl 
dnl @file    select_mcu_platform.m4
dnl @brief   
dnl @author  gnsyxiang <gnsyxiang@163.com>
dnl @date    19/03 2021 08:16
dnl @version v0.0.1
dnl 
dnl @since    note
dnl @note     note
dnl 
dnl     change log:
dnl     NO.     Author              Date            Modified
dnl     00      zhenquan.qiu        19/03 2021      create the file
dnl 
dnl     last modified: 19/03 2021 08:16
dnl ===============================================================

# SELECT_MCU_PLATFORM()
# --------------------------------------------------------------
# select mcu platform

AC_DEFUN([SELECT_MCU_PLATFORM],
    [
        AC_ARG_WITH([mcu_platform],
            [AS_HELP_STRING([--with-mcu-platform=@<:@at32f4xx|xxx@:>@], [mcu platform about @<:@at32f4xx|xxx@:>@ @<:@default=at32f4xx@:>@])],
            [],
            [with_mcu_platform=at32f4xx])

        case "$with_mcu_platform" in
            at32f4xx)   AC_DEFINE(HAVE_MCU_PLATFORM_AT32F4XX, 1, [select at32f4xx mcu platform]) ;;
            xxx)        AC_DEFINE(HAVE_MCU_PLATFORM_XXX, 1, [select xxx mcu platform]) ;;
            *)          AC_MSG_ERROR([bad value ${with_mcu_platform} for --with-mcu-platform=@<:@at32f4xx|xxx@:>@]) ;;
        esac

        AM_CONDITIONAL([COMPILE_MCU_PLATFORM_AT32F4XX], [test "x$with_mcu_platform" = "xat32f4xx"])
        AM_CONDITIONAL([COMPILE_MCU_PLATFORM_XXX], [test "x$with_mcu_platform" = "xxxx"])
    ])

