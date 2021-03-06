#pragma once

#include <Windows.h>
#include <strsafe.h>
#include <tchar.h>

// IDA SDK
// For IDA 6.1:
// - comment pro.h:379 (vsscanf is defined)
// - comment pro.h:2552 (ulong defined by Plugin.h)
#include <ida.hpp>
#include <idp.hpp>
#include <expr.hpp>
#include <bytes.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <diskio.hpp>
#include <dbg.hpp>

#define IDA700 (IDA_SDK_VERSION == 700)
#define IDA610 (IDA_SDK_VERSION == 610)

#define MM_REDO_PATCH 0x40
#define MM_REVERT_PATCH 0x80

#define MM_UNDOREDO_FLAG (MM_REDO_PATCH|MM_REVERT_PATCH)

#if IDA610
#define get_bytes(buf, buf_size, ea) (get_many_bytes(ea, buf, buf_size) == 0 ? 0 : buf_size)
#define put_bytes put_many_bytes
#define patch_bytes patch_many_bytes

void print_insn_mnem(qstring * out, ea_t ea);
ssize_t get_segm_class(qstring* out, const segment_t* seg);
ssize_t idaapi get_segm_name(qstring* out, const segment_t* seg);
#endif


AS_PRINTF(1, 0) inline void replace_wait_box_v(const char *format, va_list va)
{
  callui(ui_mbox, mbox_replace, format, va);
}

#include "Plugin.h"


extern char ini_filename[];