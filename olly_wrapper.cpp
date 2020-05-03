#include "stdafx.h"
#include "Plugin.h"


// Fix for missing Isprefix inside Plugin.h, but exported by olly inside the Ollydbg.def file
extc void cdecl Isprefix(void) {}


extc void    cdecl Addtolist(long addr, int highlight, char* format, ...) {}
extc void    cdecl Updatelist(void) {}
extc HWND    cdecl Createlistwindow(void) { return 0; }

/*
Displays message box with information about error. To continue, user must click OK button, press Enter or Esc. Use this call for critical errors only; if error is not very important, Flash, Message or Infoline are better alternatives.

void Error(char *format,...);

Parameters:

format - format string (as in call to printf), followed by optional arguments.
*/
extc void    cdecl Error(char* format, ...) {
	va_list va;
	va_start(va, format);
	verror(format, va);
}

/*
Displays message on the bottom of main OllyDbg window and adds it to the log window. If format is NULL, message will be removed from the bottom line but not added to the log. Formatted message may contain dollar sign '$'. This symbol is replaced by dash '-' on the bottom line and terminates line added to the log. For example, if you call Message(0,"Critical error $ press SPACE to continue"), bottom line will display "Critical error - press SPACE to continue" and log window "Critical error". Call to this function removes flash and progress bar from the bottom line.

void Message(ulong addr,char *format,...);

Parameters:

addr - memory address associated with log line. By doubleclicking the line in log window, one can instantly jump to the corresponding code or data in CPU. addr is not displayed in the bottom line;

format - format string (as in call to printf), followed by optional arguments.
*/
extc void    cdecl Message(ulong addr, char* format, ...) {
	va_list va;
	va_start(va, format);
	vmsg(format, va);
}
/*
Displays message on the bottom of main OllyDbg window. If format is NULL, currently displayed message will be removed. Call to Infoline removes flash and progress bar from the bottom line.

void Infoline(char *format,...);

Parameters:

format - format string (as in call to printf), followed by optional arguments.

*/
extc void    cdecl Infoline(char* format, ...) {
	va_list va;
	va_start(va, format);
	vmsg(format, va);
}
/*
Displays progress bar on the bottom of main OllyDbg window. Bar will contain formatted text with attached percent of execution. Formatted text may contain dollar sign '$', in this case persent of execution, enclosed in dashes, is inserted instead of dollra sign. If promille is 0, function closes progress bar restores previously displayed message. Calls to Message, Infoline and Flash also will close progress bar.

void Progress(int promille,char *format,...);

Parameters:

promille - progress, in 1/1000th;

format - format string (as in call to printf), followed by optional arguments.

*/
extc void    cdecl Progress(int promille, char* format, ...) {}
/*
Displays highlighted message on the bottom of main OllyDbg window. This message automatically disappears in 500 milliseconds.

void Flash(char *format,...);

Parameters:

format - format string (as in call to printf), followed by optional arguments.

*/
extc void    cdecl Flash(char* format, ...) {}


extc int     cdecl Decodeaddress(ulong addr, ulong base, int addrmode,
	char* symb, int nsymb, char* comment) {
	return 0;
}
extc int     cdecl Decoderelativeoffset(ulong addr, int addrmode,
	char* symb, int nsymb) {
	return 0;
}
extc int     cdecl Decodecharacter(char* s, uint c) { return 0; }
extc int     cdecl Printfloat4(char* s, float f) { return 0; }
extc int     cdecl Printfloat8(char* s, double d) { return 0; }
extc int     cdecl Printfloat10(char* s, long double ext) { return 0; }
extc int     cdecl Print3dnow(char* s, uchar* f) { return 0; }
extc int     cdecl Printsse(char* s, char* f) { return 0; }
extc ulong   cdecl Followcall(ulong addr) { return 0; }
extc int     cdecl IstextA(char c) { return 0; }
extc int     cdecl IstextW(wchar_t w) { return 0; }
extc int     cdecl Stringtotext(char* data, int ndata, char* text, int ntext) { return 0; }


extc int     cdecl Getlong(char* title, ulong* data, int datasize,
	char letter, int mode) {
	return 0;
}
extc int     cdecl Getlongxy(char* title, ulong* data, int datasize,
	char letter, int mode, int x, int y) {
	return 0;
}
extc int     cdecl Getregxy(char* title, ulong* data, char letter, int x, int y) { return 0; }
extc int     cdecl Getline(char* title, ulong* data) { return 0; }
extc int     cdecl Getlinexy(char* title, ulong* data, int x, int y) { return 0; }
extc int     cdecl Getfloat10(char* title, long double* fdata,
	uchar* tag, char letter, int mode) {
	return 0;
}
extc int     cdecl Getfloat10xy(char* title, long double* fdata,
	char* tag, char letter, int mode, int x, int y) {
	return 0;
}
extc int     cdecl Getfloat(char* title, void* fdata, int size,
	char letter, int mode) {
	return 0;
}
extc int     cdecl Getfloatxy(char* title, void* fdata, int size,
	char letter, int mode, int x, int y) {
	return 0;
}
extc void    cdecl Getasmfindmodel(t_asmmodel model[NMODELS],
	char letter, int searchall) {}
extc void    cdecl Getasmfindmodelxy(t_asmmodel model[NMODELS],
	char letter, int searchall, int x, int y) {}
extc int     cdecl Gettext(char* title, char* text,
	char letter, int type, int fontindex) {
	return 0;
}
extc int     cdecl Gettextxy(char* title, char* text, char letter,
	int type, int fontindex, int x, int y) {
	return 0;
}
extc int     cdecl Gethexstring(char* title, t_hexstr* hs,
	int mode, int fontindex, char letter) {
	return 0;
}
extc int     cdecl Gethexstringxy(char* title, t_hexstr* hs, int mode,
	int fontindex, char letter, int x, int y) {
	return 0;
}
extc int     cdecl Getmmx(char* title, uchar* data, int mode) { return 0; }
extc int     cdecl Getmmxxy(char* title, char* data, int mode, int x, int y) { return 0; }
extc int     cdecl Get3dnow(char* title, uchar* data, int mode) { return 0; }
extc int     cdecl Get3dnowxy(char* title, char* data, int mode, int x, int y) { return 0; }
extc int     cdecl Browsefilename(char* title, char* name, char* defext,
	int getarguments) {
	return 0;
}
extc int     cdecl OpenEXEfile(char* path, int dropped) { return 0; }
extc int     cdecl Attachtoactiveprocess(int newprocessid) { return 0; }
extc void    cdecl Animate(int animation) {}

extc int     cdecl Createsorteddata(t_sorted* sd, char* name, int itemsize,
	int nmax, SORTFUNC* sortfunc, DESTFUNC* destfunc) {
	return 0;
}
extc void    cdecl Destroysorteddata(t_sorted* sd) {}
extc void    cdecl* Addsorteddata(t_sorted* sd, void* item) { return 0; }
extc void    cdecl Deletesorteddata(t_sorted* sd, ulong addr) {}
extc void    cdecl Deletesorteddatarange(t_sorted* sd, ulong addr0, ulong addr1) {}
extc int     cdecl Deletenonconfirmedsorteddata(t_sorted* sd) { return 0; }
extc void* cdecl Findsorteddata(t_sorted* sd, ulong addr) { return 0; }
extc void* cdecl Findsorteddatarange(t_sorted* sd, ulong addr0, ulong addr1) { return 0; }
extc int     cdecl Findsorteddataindex(t_sorted* sd, ulong addr0, ulong addr1) { return 0; }
extc int     cdecl Sortsorteddata(t_sorted* sd, int sort) { return 0; }
extc void* cdecl Getsortedbyselection(t_sorted* sd, int index) { return 0; }
extc void    cdecl Defaultbar(t_bar* pb) {}
extc int     cdecl Tablefunction(t_table* pt,
	HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	return 0;
}
extc void    cdecl Painttable(HWND hw, t_table* pt, DRAWFUNC getline) {}
extc int     cdecl Gettableselectionxy(t_table* pt, int column, int* px, int* py) { return 0; }
extc void    cdecl Selectandscroll(t_table* pt, int index, int mode) {}


extc int     cdecl Insertname(ulong addr, int type, char* name) { return 0; }
extc int     cdecl Quickinsertname(ulong addr, int type, char* name) { return 0; }
extc void    cdecl Mergequicknames(void) {}
extc void    cdecl Discardquicknames(void) {}
extc int     cdecl Findname(ulong addr, int type, char* name) { return 0; }
extc int     cdecl Decodename(ulong addr, int type, char* name) { return 0; }
extc ulong   cdecl Findnextname(char* name) { return 0; }
extc int     cdecl Findlabel(ulong addr, char* name) { return 0; }
extc void    cdecl Deletenamerange(ulong addr0, ulong addr1, int type) {}
extc int     cdecl Findlabelbyname(char* name, ulong* addr,
	ulong addr0, ulong addr1) {
	return 0;
}
extc ulong   cdecl Findimportbyname(char* name, ulong addr0, ulong addr1) { return 0; }
extc int     cdecl Demanglename(char* name, int type, char* undecorated) { return 0; }
extc int     cdecl Findsymbolicname(ulong addr, char* fname) { return 0; }

/*
Disassembles command, determines its size and decodes operands. Returns size of the command. Disasm functionality depends on the selected mode and global disassembling/analysis options. See description of t_disasm for more details:

Mode	Actions
DISASM_SIZE	Fastest mode, only calculates command size
DISASM_DATA	Extracts most important data, no textual information
DISASM_TRACE	Extracts most important data and traces contents of integer registers, no textual information
DISASM_FILE	Disassembles command in assumption that registers are undefined and symbolic names are invalid. Usually used to disassemble contents of file
DISASM_CODE	Disassembles command assuming that registers are undefined
DISASM_ALL	Complete and relatively slow disassembly

ulong Disasm(char *src,ulong srcsize,ulong srcip,char *srcdec,t_disasm *disasm,int disasmmode,ulong threadid);

Parameters:

src - pointer to binary command that must be disassembled;

srcsize - size of src. Length of 80x86 commands is limited to MAXCMDSIZE bytes;

srcip - address of the command;

srcdec - pointer to decoding data produced by Analyzer or NULL if decoding data is absent. You must supply srcdec if you want to decode switch tables, constants and strings;

disasm - pointer to t_disasm structure that receives results of disassembling;

disasmmode - disassembly mode, one of DISASM_xxx. See desctiption of t_disasm and table above;

threadid - identifier of thread containing registers, or NULL if registers are undefined.


Example:
- https://github.com/x64dbg/OllyDbg/blob/f369a4cd9c5d631082db31d07fea0bd5d8c565e8/OllyDbg/disasm/main.c

*/
extc ulong   cdecl Disasm(uchar* src, ulong srcsize, ulong srcip, uchar* srcdec,
	t_disasm* disasm, int disasmmode, ulong threadid) {

	// Pretty much disassemble the given src[0:srcsize], that is based on addr srcip.
	// Do not use decoding data srcdec

	if (disasm == NULL) {
		warning("disasm == null");
		return 0;
	}

	if (disasmmode != DISASM_CODE) {
		warning("Unable to disasm mode %d", disasmmode);
		return 0;
	}

	// IDA is unable to just generate assembly based on some data, so we need to write the assembly,
	// then disasm, and then revert it

	void* backup = qalloc_or_throw(srcsize);
	get_bytes(backup, srcsize, srcip);

	put_bytes(srcip, src, srcsize);
	{
		qstring out{};
		print_insn_mnem(&out, srcip);

		strncpy_s(disasm->result, out.c_str(), out.length());
	}
	put_bytes(srcip, backup, srcsize);
	qfree(backup);

	return 0;
}
extc ulong   cdecl Disassembleback(uchar* block, ulong base, ulong size,
	ulong ip, int n, int usedec) {
	return 0;
}
extc ulong   cdecl Disassembleforward(uchar* block, ulong base, ulong size,
	ulong ip, int n, int usedec) {
	return 0;
}
extc int     cdecl Issuspicious(char* cmd, ulong size, ulong ip,
	ulong threadid, t_reg* preg, char* s) {
	return 0;
}
extc int     cdecl Isfilling(ulong offset, char* data, ulong size, ulong align) { return 0; }


extc int     cdecl Assemble(char* cmd, ulong ip, t_asmmodel* model, int attempt,
	int constsize, char* errtext) {
	return 0;
}
extc int     cdecl Checkcondition(int code, ulong flags) { return 0; }



extc int     cdecl Expression(t_result* result, char* expression, int a, int b,
	uchar* data, ulong database, ulong datasize, ulong threadid) {
	return 0;
}



extc HWND    cdecl Createthreadwindow(void) { return 0; }
extc t_thread* cdecl Findthread(ulong threadid) { return 0; }
extc int     cdecl Decodethreadname(char* s, ulong threadid, int mode) { return 0; }
extc ulong   cdecl Getcputhreadid(void) { return 0; }
extc ulong   cdecl Runsinglethread(ulong threadid) { return 0; }
extc void    cdecl Restoreallthreads(void) {}



extc int     cdecl Listmemory(void) { return 0; }
/*
Given address of memory, returns pointer to descriptor of memory block that this address belongs to, or NULL if there is no allocated memory.

t_memory* Findmemory(ulong addr);

Parameters:

addr - address of memory in the memory space of debugged application.

*/
extc t_memory* cdecl Findmemory(ulong addr) {
	sel_t selector = find_selector(addr);
	const segment_t* segment = get_segm_by_sel(selector);

	if (segment == nullptr) {
		return 0;
	}

	qstring str{};
	if (get_segm_class(&str, segment) == -1) {
		warning("get_segm_class failed on segment");
		return 0;
	}
	qstring name{};
	if (get_segm_name(&name, segment) == -1) {
		warning("Unable to fetch segment name!");
		return 0;
	}


	t_memory* ret = new t_memory();
	strncpy_s(ret->sect, name.c_str(), name.length());
	ret->owner = 0;
	ret->threadid = 0;
	ret->copy = NULL;

#if IDA610
	ret->base = segment->startEA;
	ret->size = segment->endEA - segment->startEA;
#else
	ret->base = segment->start_ea;
	ret->size = segment->end_ea - segment->start_ea;
#endif
	ret->type = 0;
	if (str == "DATA") ret->type |= TY_DATA;
	if (str == "CODE") ret->type |= TY_CODE;
	if (str == "STACK") ret->type |= TY_STACK;
	// Unable to map this correctly
	if (str == "BSS") ret->type |= TY_DATA;
	if (str == "XTRN") ret->type |= TY_IMPDATA;

	// TODO: 
	// - mark TY_EXPDATA if segment has exports (see: entry.hpp)
	// - mark TY_RESRC

	// map segment permission to PAGE_*

	bool perm_r = segment->perm & SEGPERM_READ;
	bool perm_w = segment->perm & SEGPERM_WRITE;
	bool perm_x = segment->perm & SEGPERM_EXEC;

	if (false) {}
	else if (perm_r && perm_w && perm_x) ret->access = PAGE_EXECUTE_READWRITE;

	else if (perm_r && perm_w && !perm_x) ret->access = PAGE_READWRITE;

	else if (perm_r && !perm_w && perm_x) ret->access = PAGE_EXECUTE_READ;

	else if (!perm_r && !perm_w && perm_x) ret->access = PAGE_EXECUTE;

	else if (perm_r && !perm_w && !perm_x) ret->access = PAGE_READONLY;

	else {
		warning("Unknown permissions on segment %s, r %d w %d x %d", name.c_str(), perm_r, perm_w, perm_x);
	}

	return ret;
}

extc int     cdecl Guardmemory(ulong base, ulong size, int guard) { return 0; }
extc void    cdecl Havecopyofmemory(uchar* copy, ulong base, ulong size) {}
/*
Reads memory of debugged process optionally removing INT3 breakpoints. You can read memory "on the fly": if necessary, Readmemory temporaily pauses debugged application and enables read access. Returns size of memory actually read. Currently, this is either size or 0 if memory cannot be read at once.

Important note: Any access to the memory of debugged application is time-consuming. To optimize access, consider use of Havecopyofmemory.

ulong Readmemory(void *buf,ulong addr,ulong size,int mode);

Parameters:

buf - pointer to buffer of size at least size that receives copy of memory;

addr - address of memory in the memory space of debugged application;

size - size of requested memory block;

mode - mode of operation, combination of following bits:


MM_RESTORE	Restore INT3 breakpoints
MM_SILENT	On error, don't display error message box
*/
extc ulong   cdecl Readmemory(void* buf, ulong addr, ulong size, int mode) {

	ssize_t ret = get_bytes(buf, size, addr);
	if (ret == -1) {
		warning("User cancelled get_bytes call.");
		// User cancelled, return 0 instead
		return 0;
	}

	return ret;
}
/*
Modifies memory of debugged process, optionally removing INT3 breakpoints, broadcasting memory changes and removing analysis data. Returns size of actually modified memory. Currently, this is either size or 0 if memory cannot be written at once.


ulong Writememory(void *buf,ulong addr,ulong size,int mode);

Parameters:

buf - pointer to buffer with new contents of memory;

addr - address of memory in the memory space of debugged application;

size - size of new contents;

mode - mode of operation, combination of following bits:
MM_RESTORE  Remove INT3 breakpoints in the modified area and broadcast memory changes
MM_DELANAL	Wipe off analysis in the modified area
MM_SILENT	On error, don't display error message box
*/
extc ulong   cdecl Writememory(void* buf, ulong addr, ulong size, int mode) {
	patch_bytes(addr, buf, size);
	if (mode & MM_DELANAL) {
		// Re-analyze region
		reanalyze_function(NULL, addr, addr + size);
	}
	return size;
}
extc ulong   cdecl Readcommand(ulong ip, char* cmd) { return 0; }



extc t_module* cdecl Findmodule(ulong addr) { return 0; }
extc t_fixup* cdecl Findfixup(t_module* pmod, ulong addr) { return 0; }

/*
Searches for decoding data that starts on specified address. On success, sets *psize to size of located data
and returns pointer to decoding information. If there is no decoding information, sets *psize to 0 and returns NULL.
For each byte of analysed code, corresponding byte of decoding data contains combination of type, procedure
and analysis fields:
		 Type field, use DEC_TYPEMASK to extract it from decoding data:

DEC_UNKNOWN	Unknown type
DEC_BYTE	Byte
DEC_WORD	First byte of 16-bit integer
DEC_NEXTDATA	Subsequent byte of data
DEC_DWORD	First byte of 32-bit integer
DEC_FLOAT4	First byte of 32-bit float
DEC_FWORD	First byte of descriptor or long pointer
DEC_FLOAT8	First byte of 64-bit double
DEC_QWORD	First byte of 64-bit integer
DEC_FLOAT10	First byte of 80-bit long double
DEC_TBYTE	First byte of 10-byte BCD integer
DEC_STRING	First byte of ASCII string
DEC_UNICODE	First byte of UNICODE string
DEC_3DNOW	First byte of 3DNow! operand
DEC_SSE	First byte of SSE operand
DEC_BYTESW	Byte which is a second-level switch index
DEC_NEXTCODE	Subsequent byte of command
DEC_COMMAND	First byte of command
DEC_JMPDEST	First byte of command that is jump destination
DEC_CALLDEST	First byte of command that is call (and maybe jump) destination
		Procedure field, use DEC_PROCMASK to extract it from decoding data:
DEC_PROC	Start of procedure
DEC_PBODY	Body of procedure
DEC_PEND	End of procedure
Bit DEC_CHECKED, if set, reports that byte was analyzed.

char *Finddecode(ulong addr,ulong *psize);

Parameters:

addr - address of the first byte in the memory space of debugged process for which decoding information is requested;

psize - pointer to variable that will receive size of found decoding data or NULL.

*/
extc uchar* cdecl Finddecode(ulong addr, ulong* psize) {
	// TODO: Figure out what kind of operator this address is.
	return 0;
}
extc ulong   cdecl Findfileoffset(t_module* pmod, ulong addr) { return 0; }
extc int     cdecl Decoderange(ulong addr, ulong size, char* s) { return 0; }
extc int     cdecl Analysecode(t_module* pm) { return 0; }



extc int     cdecl Registerotclass(char* classname,
	char* iconname, WNDPROC classproc) {
	return 0;
}
extc HWND    cdecl Newtablewindow(t_table* pt, int nlines, int maxcolumns,
	char* winclass, char* wintitle) {
	return 0;
}
extc HWND    cdecl Quicktablewindow(t_table* pt, int nlines, int maxcolumns,
	char* winclass, char* wintitle) {
	return 0;
}
extc HWND    cdecl Createdumpwindow(char* name, ulong base, ulong size,
	ulong addr, int type, SPECFUNC* specdump) {
	return 0;
}
extc void    cdecl Setdumptype(t_dump* pd, int dumptype) {}
extc void    cdecl Dumpbackup(t_dump* pd, int action) {}
extc int     cdecl Broadcast(UINT msg, WPARAM wp, LPARAM lp) { return 0; }



extc ulong   cdecl Compress(uchar* bufin, ulong nbufin,
	uchar* bufout, ulong nbufout) {
	return 0;
}
extc ulong   cdecl Getoriginaldatasize(char* bufin, ulong nbufin) { return 0; }
extc ulong   cdecl Decompress(uchar* bufin, ulong nbufin,
	uchar* bufout, ulong nbufout) {
	return 0;
}
extc ulong   cdecl Calculatecrc(uchar* copy, ulong base, ulong size,
	t_module* pmod, ulong fixupoffset) {
	return 0;
}



extc int     cdecl Findreferences(ulong base, ulong size, ulong addr0, ulong addr1,
	ulong origin, int recurseonjump, char* title) {
	return 0;
}
extc int     cdecl Findstrings(ulong base, ulong size, ulong origin, char* title) { return 0; }
extc int     cdecl Findalldllcalls(t_dump* pd, ulong origin, char* title) { return 0; }
extc int     cdecl Findallcommands(t_dump* pd, t_asmmodel* model,
	ulong origin, char* title) {
	return 0;
}
extc int     cdecl Findallsequences(t_dump* pd, t_extmodel model[NSEQ][NMODELS],
	ulong origin, char* title) {
	return 0;
}
extc ulong   cdecl Walkreference(int dir) { return 0; }
extc ulong   cdecl Walkreferenceex(int dir, ulong* size) { return 0; }



extc int     cdecl Setbreakpoint(ulong addr, ulong type, uchar cmd) { return 0; }
extc int     cdecl Setbreakpointext(ulong addr, ulong type, char cmd,
	ulong passcount) {
	return 0;
}
extc int     cdecl Manualbreakpoint(ulong addr,
	int key, int shiftkey, ulong nametype, int font) {
	return 0;
}
extc void    cdecl Deletebreakpoints(ulong addr0, ulong addr1, int silent) {}
extc ulong   cdecl Getbreakpointtype(ulong addr) { return 0; }
extc ulong   cdecl Getbreakpointtypecount(ulong addr, ulong* passcount) { return 0; }
extc ulong   cdecl Getnextbreakpoint(ulong addr, ulong* type, int* cmd) { return 0; }
extc void    cdecl Tempbreakpoint(ulong addr, int mode) {}
extc int     cdecl Hardbreakpoints(int closeondelete) { return 0; }
extc int     cdecl Sethardwarebreakpoint(ulong addr, int size, int type) { return 0; }
extc int     cdecl Deletehardwarebreakpoint(int index) { return 0; }
extc int     cdecl Deletehardwarebreakbyaddr(ulong addr) { return 0; }
extc int     cdecl Setmembreakpoint(int type, ulong addr, ulong size) { return 0; }
extc uchar* cdecl Findhittrace(ulong addr, uchar** ptracecopy, ulong* psize) { return 0; }
extc int     cdecl Modifyhittrace(ulong addr0, ulong addr1, int mode) { return 0; }
extc ulong   cdecl Isretaddr(ulong retaddr, ulong* procaddr) { return 0; }
extc HWND    cdecl Creatertracewindow(void) { return 0; }
extc void    cdecl Settracecondition(char* cond, int onsuspicious,
	ulong in0, ulong in1, ulong out0, ulong out1) {}
extc void    cdecl Settracecount(ulong count) {}
extc void    cdecl Settracepauseoncommands(char* cmdset) {}
extc int     cdecl Startruntrace(t_reg* preg) { return 0; }
extc void    cdecl Deleteruntrace(void) {}
extc int     cdecl Runtracesize(void) { return 0; }
extc int     cdecl Findprevruntraceip(ulong ip, int startback) { return 0; }
extc int     cdecl Findnextruntraceip(ulong ip, int startback) { return 0; }
extc int     cdecl Getruntraceregisters(int nback, t_reg* preg,
	t_reg* pold, char* cmd, char* comment) {
	return 0;
}
extc int     cdecl Getruntraceprofile(ulong addr, ulong size, ulong* profile) { return 0; }
extc void    cdecl Scrollruntracewindow(int back) {}
extc HWND    cdecl Createprofilewindow(ulong base, ulong size) { return 0; }




extc int     cdecl Injectcode(ulong threadid, t_inject* inject, char* data,
	ulong datasize, ulong parm1, ulong parm2,
	INJECTANSWER* answerfunc) {
	return 0;
}


/*
Updates state of panes in CPU window. If necessary, creates or restores CPU window and moves it to top.

void Setcpu(ulong threadid,ulong asmaddr,ulong dumpaddr,ulong stackaddr,int mode);

Parameters:

threadid - identified of thread to display in CPU, or 0 if thread remains unchanged. If threadid id non-zero, parameters asmaddr and stackaddr are ignored and set to contents of EIP and ESP of the specified thread. If threadid is 0 and actual thread is invalid, Setcpu automatically reswitches to main thread;

asmaddr - address to display in Disassembler, or 0 if this address remains unchanged. Ignored if threadid is not 0;

dumpaddr - address to display in CPU Dump, or 0 if this address remains unchanged;

stackaddr - address to display in Stack, or 0 if this address remains unchanged. Ignored if threadid is not 0;

mode - combination of CPU_xxx flags that select update mode:


CPU_ASMHIST	Add change to Disassembler history
CPU_ASMCENTER	Position address in the middle of Disassembler window
CPU_ASMFOCUS	Move focus to Disassembler
CPU_DUMPHIST	Add change to Dump history (currently not available)
CPU_DUMPFIRST	Make dumpaddr the first byte in CPU Dump
CPU_DUMPFOCUS	Move focus to CPU Dump
CPU_REGAUTO	Automatically change Registers mode to FPU/MMX/3DNow!
CPU_RUNTRACE	Show run trace data at offset asmaddr
CPU_NOCREATE	Don't create CPU window if absent
CPU_REDRAW	Redraw CPU window immediately
CPU_NOFOCUS	Don't force focus to main window
*/
extc void    cdecl Setcpu(ulong threadid, ulong asmaddr,
	ulong dumpaddr, ulong stackaddr, int mode) {
	if (asmaddr != 0 && threadid == 0) {
		// Jump to CPU/Assembly 
		jumpto(asmaddr);
	}
	// TODO: Add option to jump to stackview, hexview?
}
extc void    cdecl Setdisasm(ulong asmaddr, ulong selsize, int mode) {}
extc void    cdecl Redrawdisassembler(void) {}
extc void    cdecl Getdisassemblerrange(ulong* pbase, ulong* psize) {}
extc ulong   cdecl Findprocbegin(ulong addr) { return 0; }
extc ulong   cdecl Findprocend(ulong addr) { return 0; }
extc ulong   cdecl Findprevproc(ulong addr) { return 0; }
extc ulong   cdecl Findnextproc(ulong addr) { return 0; }
extc int     cdecl Getproclimits(ulong addr, ulong* start, ulong* end) { return 0; }
extc void    cdecl Sendshortcut(int where, ulong addr,
	int msg, int ctrl, int shift, int vkcode) {}



extc t_status cdecl Getstatus(void) { return STAT_NONE; }
extc int     cdecl Go(ulong threadid, ulong tilladdr, int stepmode,
	int givechance, int backupregs) {
	return 0;
}
extc int     cdecl Suspendprocess(int processevents) { return 0; }



extc uchar* cdecl Findknownfunction(ulong addr, int direct,
	int level, char* fname) {
	return 0;
}
extc int     cdecl Decodeknownargument(ulong addr, uchar* arg, ulong value,
	int valid, char* s, char* mask, uchar* pset[]) {
	return 0;
}
extc char    cdecl* Findunknownfunction(ulong ip, char* code, char* dec,
	ulong size, char* fname) {
	return 0;
}
extc int     cdecl Decodeascii(ulong value, char* s, int len, int mode) { return 0; }
extc int     cdecl Decodeunicode(ulong value, char* s, int len) { return 0; }



extc HWND    cdecl Showsourcefromaddress(ulong addr, int show) { return 0; }
extc int     cdecl Getresourcestring(t_module* pm, ulong id, char* s) { return 0; }
extc t_sourceline* cdecl Getlinefromaddress(ulong addr) { return 0; }
extc ulong   cdecl Getaddressfromline(ulong addr0, ulong addr1,
	char* path, ulong line) {
	return 0;
}
extc int     cdecl Getsourcefilelimits(ulong nameaddr,
	ulong* addr0, ulong* addr1) {
	return 0;
}
extc int     cdecl Decodefullvarname(t_module* pmod, t_symvar* psym,
	int offset, char* name) {
	return 0;
}
extc int     cdecl Getbprelname(t_module* pmod, ulong addr, long offset,
	char* s, int nsymb) {
	return 0;
}



extc HWND    cdecl Createwatchwindow(void) { return 0; }
extc int     cdecl Deletewatch(int indexone) { return 0; }
extc int     cdecl Insertwatch(int indexone, char* text) { return 0; }
extc int     cdecl Getwatch(int indexone, char* text) { return 0; }



extc HWND    cdecl Createwinwindow(void) { return 0; }




extc HWND    cdecl Createpatchwindow(void) { return 0; }



extc int     cdecl Registerpluginclass(char* classname, char* iconname,
	HINSTANCE dllinst, WNDPROC classproc) {
	return 0;
}
extc void    cdecl Unregisterpluginclass(char* classname) {}
extc int     cdecl Pluginwriteinttoini(HINSTANCE dllinst, char* key, int value) { return 0; }
extc int     cdecl Pluginwritestringtoini(HINSTANCE dllinst, char* key, char* s) { return 0; }
extc int     cdecl Pluginreadintfromini(HINSTANCE dllinst, char* key, int def) { return 0; }
extc int     cdecl Pluginreadstringfromini(HINSTANCE dllinst, char* key,
	char* s, char* def) {
	return 0;
}
extc int     cdecl Pluginsaverecord(ulong tag, ulong size, void* data) { return 0; }
extc int     cdecl Plugingetvalue(int type) { return 0; }


