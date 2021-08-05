# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    05/03 2021 10:38
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        05/03 2021      create the file
# 
#     last modified: 05/03 2021 10:38
# ===============================================================

# ------------------
# defining variables
# ------------------
_no_error_com   =
_include_com    =
_sources_com    =
_cppflags_com   =
_cflags_com     =
_cxxflags_com   =
_ldflags_com    =
_ldadd_com      =
bin_PROGRAMS    =
BUILT_SOURCES   =
CLEANFILES      =

_at32f4xx_lib   = src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries

# ---------------------
# add necessary content
# ---------------------
_no_error_com       += -Wno-error=address

_include_com    += -I$(top_srcdir)/include

_sources_com    +=

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_no_error_com) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(BIN_LDFLAGS_COM)

if COMPILE_LIBHY_UTILS
_ldadd_com      += $(HY_UTILS_LIBS)
endif

_ldadd_com      += $(top_builddir)/src/lib@project_name@.la

if COMPILE_LIBPROTOBUF_C
_ldadd_com      += $(LIBPROTOBUF_C_LIBS)
endif

if COMPILE_MCU_AT32F407VGT7
_ldflags_com    += -T$(top_srcdir)/$(_at32f4xx_lib)/CMSIS/CM4/DeviceSupport/startup/gcc/linker/AT32F407xG_FLASH.ld
endif

bin_PROGRAMS        += main.elf
main_elf_SOURCES    = $(_sources_com) main.c
main_elf_CPPFLAGS   = $(_cppflags_com)
main_elf_CFLAGS     = $(_cflags_com)
main_elf_CXXFLAGS   = $(_cxxflags_com)
main_elf_LDFLAGS    = $(_ldflags_com) -Wl,--gc-sections,-Map=main.map,-cref,-u,Reset_Handler
main_elf_LDADD      = $(_ldadd_com)

address_book.pb.c address_book.pb.h: @PROTOC_C@ address_book.proto
	$(AM_V_GEN)@PROTOC_C@ --c_out=. address_book.proto

BUILT_SOURCES += \
                 address_book.pb.c \
                 address_book.pb.h

bin_PROGRAMS                    += protobuf-c-demo.elf
protobuf_c_demo_elf_SOURCES     = $(_sources_com) protobuf-c-demo.c address_book.pb-c.c
protobuf_c_demo_elf_CPPFLAGS    = $(_cppflags_com)
protobuf_c_demo_elf_CFLAGS      = $(_cflags_com)
protobuf_c_demo_elf_CXXFLAGS    = $(_cxxflags_com)
protobuf_c_demo_elf_LDFLAGS     = $(_ldflags_com) -Wl,--gc-sections,-Map=protobuf-c-demo.map,-cref,-u,Reset_Handler
protobuf_c_demo_elf_LDADD       = $(_ldadd_com)

CLEANFILES += $(BUILT_SOURCES)

install-exec-hook:
	@gcc_prefix@objcopy -O binary main.elf main.bin
	@gcc_prefix@objcopy -O binary protobuf-c-demo.elf protobuf-c-demo.bin
	$(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) *.bin "$(DESTDIR)$(bindir)$$dir"

