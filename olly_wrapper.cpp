#include "stdafx.h"
#include "OllyPlugin.h"
#include <list>

struct table_info {
	// Name of the window, required for refresh_chooser
	std::string name;

	// Name that is used w/ pluginclass
	std::string winclass;
};

std::unordered_map<t_table*, table_info> t_table_instances{};
std::unordered_map<std::string, WNDPROC> pluginclass_map{};

static bool progress_bar_open = false;

static void close_progress_bar() {
	if (!progress_bar_open) return;
	hide_wait_box();
	progress_bar_open = false;
}


// Fix for missing Isprefix inside Plugin.h, but exported by olly inside the Ollydbg.def file
extc void cdecl Isprefix(void) {}

/*
The Addtolist function adds single line of ASCII text, up to TEXTLEN characters long, to the log window.

void Addtolist(long addr,int highlight,char *format,...);

Parameters:

addr - memory address associated with log line. By doubleclicking the line in log window, one can instantly jump to the corresponding code or data in CPU;

highlight - color of text:

0	standard color (black in black on white color scheme);
1	highlighted (red);
-1	grayed (gray);
format - format string (as in call to printf), followed by optional arguments.
*/
extc void    cdecl Addtolist(long addr, int highlight, char* format, ...) {
	msg("[%08X] ", addr);

	va_list va;
	va_start(va, format);
	vmsg(format, va);
	msg("\n");
}
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
	vinfo(format, va);
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
	msg("\n");
	close_progress_bar();
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
	msg("\n");
	close_progress_bar();
}
/*
Displays progress bar on the bottom of main OllyDbg window. Bar will contain formatted text with attached percent of execution. Formatted text may contain dollar sign '$', in this case persent of execution, enclosed in dashes, is inserted instead of dollra sign. If promille is 0, function closes progress bar restores previously displayed message. Calls to Message, Infoline and Flash also will close progress bar.

void Progress(int promille,char *format,...);

Parameters:

promille - progress, in 1/1000th;

format - format string (as in call to printf), followed by optional arguments.

*/
extc void    cdecl Progress(int promille, char* format, ...) {
	va_list va;
	va_start(va, format);

	char stars[101] = {};
	for (int i = 0; i < 100; i++) {
		if (promille >= (i * 10)) {
			stars[i] = 'x';
		}
		else {
			stars[i] = ' ';
		}
	}

	msg("[%s] ", stars);
	vmsg(format, va);
	msg("\n");

	if (promille == 0) {
		close_progress_bar();
	}
	else {
		if (!progress_bar_open) {
			show_wait_box_v(format, va);
			progress_bar_open = true;
		}
		else {
			replace_wait_box_v(format, va);
		}

	}
}
/*
Displays highlighted message on the bottom of main OllyDbg window. This message automatically disappears in 500 milliseconds.

void Flash(char *format,...);

Parameters:

format - format string (as in call to printf), followed by optional arguments.

*/
extc void    cdecl Flash(char* format, ...) {
	va_list va;
	va_start(va, format);
	msg("[flash] ");
	vmsg(format, va);
	msg("\n");
	close_progress_bar();
}


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

/*
Initializes descriptor of sorted data (structure t_sorted). If descriptor alseady contains data, this data is destroyed. Returns 0 on success and -1 on error.

int Createsorteddata(t_sorted *sd,char *name,int itemsize,int nmax,SORTFUNC *sortfunc,DESTFUNC *destfunc);

Parameters:

sd - pointer to descriptor of sorted data;

name - optional name of sorted data, can be NULL. OllyDbg uses this name only in some rare cases;

itemsize - size, in bytes, of the element of sorted data (including standard header);

nmax - initial number of data elements that allocated buffer can keep. If necessary, OllyDbg will automatically allocate additional memory;

sortfunc - pointer to function that compares two data elements according to sorting criterium, or NULL if data cannot be sorted. This criterium is usually the index of column in table window. If you specify AUTOARRANGE, data is autoarrangeable, that is, assumes that address of the element is simply its (0-based) ordinal number in the data and size of element is always 1. Even in this case, element must begin with valid header. Addsorteddata always inserts new items to autoarrangeable data and never replaces existing;

destfunc - pointer to function that is called for each element being removed from the table, or NULL if destructor is not necessary. You need destfunc, for example, if elements of sorted data allocate additional memory that must be freed before element is deleted.

*/
extc int     cdecl Createsorteddata(t_sorted* sd, char* name, int itemsize,
	int nmax, SORTFUNC* sortfunc, DESTFUNC* destfunc) {
	if (sd == nullptr) {
		msg("Createsorteddata sd == null\n");
		return 0;
	}

	if (name != nullptr) {
		strncpy_s(sd->name, name, strlen(name));
	}
	else {
		sd->name[0] = 0;
	}
	sd->nmax = nmax;
	sd->sortfunc = sortfunc;
	sd->destfunc = destfunc;
	sd->itemsize = itemsize;

	if (sd->data != nullptr) {
		qfree(sd->data);
	}

	sd->data = (uint8*)qalloc_or_throw(sd->nmax * sd->itemsize);

	return 0;
}
extc void    cdecl Destroysorteddata(t_sorted* sd) {
	if (sd == nullptr) {
		msg("Destroysorteddata sd == null\n");
		return;
	}
	if (sd->data != nullptr) {
		qfree(sd->data);
		sd->data = nullptr;
	}
}


// NOTE: Not compatible with std::qsort_s
// See https://github.com/MicrosoftDocs/cpp-docs/issues/2162
int compare_sorteddata(void* context, const void* a, const void* b) {
	auto sd = (t_sorted*)context;
	auto sha = (t_sortheader*)a;
	auto shb = (t_sortheader*)b;

	if (sd->sortfunc == AUTOARRANGE) {
		// Sort on address
		return sha->addr - shb->addr;
	}
	else {
		return sd->sortfunc(sha, shb, sd->sort);
	}
}
/*
Adds or replaces element in initialized sorted data. Returns pointer to item in the data if item is correctly added or replaced and NULL if either input parameters are invalid, data buffer is full and OllyDbg is unable to allocate more memory, new element cannot replace old because it is neither subset nor superset of the old item, or it overlaps with two or more existing elements. This pointer is valid till the next operation that adds or removes data. Do not change address or size of element after it is added to sorted data, this may lead to severe data integrity problems.

void *Addsorteddata(t_sorted *sd,void *item);

Parameters:

sd - pointer to initialized descriptor of sorted data;

item - pointer to new element.

*/
extc void    cdecl* Addsorteddata(t_sorted* sd, void* item) {
	if (sd == nullptr) {
		warning("Addsorteddata sd == null\n");
		return (void*)0;
	}
	if (item == nullptr) {
		warning("Addsorteddata item == null\n");
		return (void*)0;
	}

	t_sortheader* sh = (t_sortheader*)item;


	// Size up the array if needed
	if (sd->n == sd->nmax) {
		sd->nmax = qmax(sd->nmax * 2, 32);
		sd->data = (uint8*)qrealloc_or_throw(sd->data, sd->nmax * sd->itemsize);
	}

	msg("Addsorteddata %d addr %08X %d\n", sd->n, sh->addr, sh->size);

	memcpy_s(sd->get_entry_data(sd->n), sd->itemsize, sh, sd->itemsize);

	sd->n++;

	qsort_s(sd->data, sd->n, sd->itemsize, compare_sorteddata, sd);

	return sd->get_entry_data(sd->n);
}
/*
Deletes element which begins exactly at specified address from sorted data.

void Deletesorteddata(t_sorted *sd,ulong addr);

Parameters:

sd - pointer to initialized descriptor of sorted data;

addr - address of element.

*/
extc void    cdecl Deletesorteddata(t_sorted* sd, ulong addr) {
	if (sd == nullptr) {
		warning("Deletesorteddata sd == null\n");
		return;
	}

	int pos = -1;
	for (int i = 0; i < sd->n; i++) {
		auto sh = sd->get_entry_data(i);
		if (sh->addr == addr) {
			pos = i;
			break;
		}
	}

	if (pos == -1) {
		// Not found
		return;
	}

	if (pos == sd->n - 1) {
		// last element, just decrease count and return
		sd->n--;
		return;
	}
	msg("memmove of deletesorteddata pos %d\n", pos);
	// Already sorted, so just move it move it to the left
	memmove(sd->get_entry_data(pos), sd->get_entry_data(pos + 1), (sd->n - pos) * sd->itemsize);
}
/*Deletes all elements which contain at least 1 address within the specified range from the table of sorted data.

void Deletesorteddatarange(t_sorted *sd,ulong addr0,ulong addr1);

Parameters:

sd - pointer to initialized descriptor of sorted data;

addr0 - start of address range (included);

addr1 - end of address range (not included).

*/
extc void    cdecl Deletesorteddatarange(t_sorted* sd, ulong addr0, ulong addr1) {
	// Same as Deletesorteddata, but then delete a chunk
	if (sd == nullptr) {
		warning("Deletesorteddatarange sd == null\n");
		return;
	}

	int startpos = -1;
	int endpos = -1;
	for (int i = 0; i < sd->n; i++) {
		auto sh = sd->get_entry_data(i);
		if (addr0 >= sh->addr &&
			sh->addr + sh->size < addr1) {
			if (startpos == -1) {
				startpos = i;
			}
			endpos = i;
		}
	}

	if (startpos == -1) {
		// Not found
		return;
	}

	if (endpos == sd->n - 1) {
		// until last element, so get rid of everything since start
		sd->n = startpos - 1;
		return;
	}
	msg("memmove of Deletesorteddatarange pos %d - %d\n", startpos, endpos);
	// Already sorted, so just move it move it to the left
	memmove(sd->get_entry_data(startpos), sd->get_entry_data(endpos), (sd->n - endpos) * sd->itemsize);
}
extc int     cdecl Deletenonconfirmedsorteddata(t_sorted* sd) { return 0; }
extc void* cdecl Findsorteddata(t_sorted* sd, ulong addr) { return 0; }
extc void* cdecl Findsorteddatarange(t_sorted* sd, ulong addr0, ulong addr1) {
	return 0;
}
extc int     cdecl Findsorteddataindex(t_sorted* sd, ulong addr0, ulong addr1) { return 0; }
extc int     cdecl Sortsorteddata(t_sorted* sd, int sort) { return 0; }
/*Returns pointer to element with specified index in sorted data sorted by actual criterium, or NULL on error. If necessary, function actualizes associated index table, so preliminary call to Sortsorteddata is not necessary. Function is very useful for extraction of selected element in table windows.

void* Getsortedbyselection(t_sorted *sd,int selection);

Parameters:

sd - pointer to descriptor of sorted data;

selection - zero-based index in data sorted by selected sort criterium.

*/
extc void* cdecl Getsortedbyselection(t_sorted* sd, int index) {
	return (void*)sd->get_entry_data(index);
}
extc void    cdecl Defaultbar(t_bar* pb) {}
extc int     cdecl Tablefunction(t_table* pt,
	HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	return 0;
}
extc void    cdecl Painttable(HWND hw, t_table* pt, DRAWFUNC getline) {
	auto x = t_table_instances.find(pt);
	if (x == t_table_instances.end()) {
		msg("Painttable, table not found\n");
		return;
	}
	msg("Painttable %08X %08X\n", getline, pt->drawfunc);
	if (getline != nullptr) {
		pt->drawfunc = getline;
	}
	refresh_chooser(x->second.name.c_str());
}

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
	msg("Disasm %08x %d\n", srcip, srcsize);

	// Pretty much disassemble the given src[0:srcsize], that is based on addr srcip.
	// Do not use decoding data srcdec

	if (disasm == nullptr) {
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
	msg("Findmemory %08x\n", addr);

	const segment_t* segment = getseg(addr);

	if (segment == nullptr) {
		warning("Unable to find segment for addr %08x\n", addr);
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
	strncpy_s(ret->sect, name.c_str(), qmin(SHORTLEN - 1, name.length()));
	ret->owner = 0;
	ret->threadid = 0;
	ret->copy = nullptr;

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

	msg("? Name: %s, base %08x size %08x\n", name.c_str(), ret->base, ret->size);


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
	msg("Readmemory %08x len %d\n", addr, size);

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
	msg("Writememory %08x len %d mode %d\n", addr, size, mode);


	patch_t p{};
	p.data = (uint8*)qalloc_or_throw(size);
	p.data_len = size;
	p.ea = addr;
	p.mode = mode & ~MM_UNDOREDO_FLAG;
	get_bytes(p.data, p.data_len, addr);
	if ((mode & MM_REVERT_PATCH) == 0) {
		OllyPlugin::g_s_current_plugin->push_undo_action(p);
	}
	else if ((mode & MM_REDO_PATCH) == 0) {
		OllyPlugin::g_s_current_plugin->push_redo_action(p);
	}


	patch_bytes(addr, buf, size);

	if (mode & MM_DELANAL) {
		msg("Analyzing data\n");
		// Re-analyze region
		do_unknown_range(addr, size, DOUNK_SIMPLE);
		for (int i = 0; i < 20 && i < size; i++) {
			create_insn(addr + i);
		}
	}
	return size;
}
extc ulong   cdecl Readcommand(ulong ip, char* cmd) { return 0; }



extc t_module* cdecl Findmodule(ulong addr) {
	msg("Findmodule %08x\n", addr);

	t_module* ret = new t_module();
	if (is_debugger_on() && false) {
		// Load modules from debugger info
		module_info_t minfo;
		for (bool ok = get_first_module(&minfo); ok; ok = get_next_module(&minfo)) {

		}
	}

	ret->base = get_imagebase();
	ret->nsect = get_segm_qty();

	auto sh = (IMAGE_SECTION_HEADER*)qalloc_or_throw(ret->nsect * sizeof(IMAGE_SECTION_HEADER));

	for (int i = 0; i < ret->nsect; i++) {
		auto segm = getnseg(i);
		get_segm_name(segm, (char*)sh[i].Name, ARRAYSIZE(sh[i].Name));
		sh[i].VirtualAddress = segm->startEA - ret->base;
		sh[i].Misc.VirtualSize = segm->endEA - segm->startEA;
	}

	ret->sect = sh;

	return ret;
}



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
/*If window already exists, restores it and brings to the top. Otherwise, sets default appearance parameters and creates new window. If record with window's title already exists in ollydbg.ini, table has TABLE_SAVEPOS attribute and option "Restore windows position and appearance" is selected, restores old position, size and appearance. Returns pointer to window or NULL on error. Note that alternative function, Newtablewindow, neither restores window nor changes its appearance.

HWND Quicktablewindow(t_table *pt,int nlines,int maxcolumns,char *winclass,char *wintitle);

Parameters:

pt - pointer to descriptor of table window;

nlines - preferred number of visible lines;

maxcolumns - preferred number of visible columns;

winclass - name of registered window class (for example, obtained from call to Registerpluginclass);

wintitle - window's title. If table has TABLE_SAVEPOS attribute, OllyDbg uses title to save and restore window's position and appearance.

*/
extc HWND    cdecl Quicktablewindow(t_table* pt, int nlines, int maxcolumns,
	char* winclass, char* wintitle) {
	auto ti = table_info{};
	ti.name = std::string{wintitle};
	ti.winclass = std::string{winclass};
	t_table_instances[pt] = ti;
	msg("Quicktablewindow %d drawfunc %08X\n", pt, pt->drawfunc);

	const auto windowClass = TEXT("OllyPro Quicktablewindow helper");

	static bool classInitialized = false;

	if (!classInitialized) {
		classInitialized = true;

		WNDCLASSEX wc;
		// initialize wc
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.cbWndExtra = sizeof(char*) * 1; // Extra slots
		wc.cbClsExtra = 0;
		wc.hInstance = 0;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = windowClass;
		wc.lpszMenuName = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

		wc.lpfnWndProc = [](HWND hwnd, UINT wndMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
			switch (wndMsg) {
			case WM_CREATE:
			{
				// Store the class pointer in the window info
				// We get it from the create struct
				CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
				SetWindowLongPtr(hwnd, 0, (LONG_PTR)cs->lpCreateParams);
				break;
			}

			case WM_SETFOCUS:
			{
				// Plugin wants us to show up. I say: refresh
				auto table = (t_table*)GetWindowLongPtr(hwnd, 0);
				Painttable(hwnd, table, table->drawfunc);
				break;
			}

			default:
				return DefWindowProc(hwnd, wndMsg, wParam, lParam);
			}

			return 0;
		};

		if (!RegisterClassEx(&wc)) {
			error("Unable to register class! %d\n", GetLastError());
			return 0;
		}
	}


	HWND ret = CreateWindowEx(
		WS_EX_NOACTIVATE,
		windowClass,
		TEXT(wintitle),
		WS_DISABLED,
		0, 0,
		0, 0,
		NULL,
		NULL,
		NULL,
		pt // Passed to WM_CREATE under lParam's CREATESTRUCT object
	);

	if (ret == NULL) {
		msg("CreateWindowEx failed with error code %d\n", GetLastError());
	}

	pt->hw = ret;

	choose2(
		(int)0, // flags
		-1, -1,
		-1, -1,

		(void*)pt,
		maxcolumns,
		(const int*)&pt->bar.defdx,
		// get row count / sizer
		[](void* data) -> uint32 { return ((t_table*)data)->data.n; },
		// get row / getl
		[](void* data, uint32 row, char* const* arrptr) {

		auto t = (t_table*)data;
		int colcount = t->bar.nbar;
		if (row == 0) {
			// generate the column headers
			for (int i = 0; i < colcount; i++) {
				qstrncpy(arrptr[i], t->bar.name[i], MAXSTR);
			}
			return;
		}

		row -= 1;

		char mask[TEXTLEN];
		int select;
		for (int col = 0; col < colcount; col++) {
			auto rowdata = t->data.get_entry_data(row);
			auto len = t->drawfunc(
				arrptr[col],
				mask,
				&select,
				rowdata,
				col
			);
			msg("Trying to render %d %d %s len %d addr %08X\n", row, col, arrptr[col], len, rowdata->addr);
		}

	},
		// Title
		wintitle,
		// Icon
		-1,
		// Selected line (deflt)
		0,
		nullptr, // delete
		nullptr, // insert
		nullptr, // update 
		[](void* data, uint32 row) { msg("edit %d\n", row); }, // edit
		// enter
		[](void* data, uint32 row) {
		msg("enter %d\n", row);
		auto t = (t_table*)data;

		t->data.selected = row;
		
		auto ti = t_table_instances.find(t);
		if (ti == t_table_instances.end()) {
			msg("Unable to find table instance\n");
			return;
		}

		auto pc = pluginclass_map.find(ti->second.winclass);
		if (pc == pluginclass_map.end()) {
			msg("Unable to find plugin class\n");
			return;
		}

		pc->second(t->hw, WM_KEYDOWN, 13, 0);
	},
		nullptr,
		// popup_names
		nullptr,
		// get_icon
		nullptr
	);

	// TODO: 
	// maybe do some heuristics for a context menu
	// maybe hook CreatePopupMenu, AppendMenu, DestroyMenu for figuring out which items
	// to add with add_chooser_command()

	return ret;
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


/*
Generates unique class name and registers new class of plugin windows. If iconname is NULL, uses standard plugin icon (letter 'P'). On success, returns 0 and fills classname (at least 32 bytes long) with unique class name. If registration failed, returns -1. Windows belonging to registered class has 8 longwords of extra memory, plugin is free to use longwords 2..7 (offsets 8..28 in calls to GetWindowLong and SetWindowLong). ODBG_Plugininit is the best place to call this function.

int Registerpluginclass(char *classname,char *iconname,HINSTANCE dllinst,WNDPROC classproc);

Parameters:

classname - pointer to buffer of length at least 32 characters that will receive unique class name;

iconname - name of icon resource in plugin DLL;

dllinst - plugin's instance;

classproc - pointer to window procedure of new class.

*/
extc int     cdecl Registerpluginclass(char* classname, char* iconname,
	HINSTANCE dllinst, WNDPROC classproc) {
	// Yanked from Ollydbg

	if (classname == nullptr || classproc == nullptr) {
		return -1;
	}

	static int cnt = 0;
	sprintf(classname, "OT_PLUGIN_%04i", cnt);
	cnt++;

	WNDCLASSA wc{};
	wc.style = 11;
	wc.lpfnWndProc = classproc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 32;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = 0;
	// no icon?
	wc.hCursor = 0;
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = classname;

	if (RegisterClassA(&wc)) {

		pluginclass_map[std::string{classname}] = classproc;

		return 0;
	}

	// Clear classname
	classname[0] = 0;

	return -1;
}
extc void    cdecl Unregisterpluginclass(char* classname) {}
/*
Stores an integer associated with a key in the plugin's personal section of the ollydbg.ini. Returns 1 on success and 0 on error.

int Pluginwriteinttoini(HINSTANCE dllinst,char *key,int value);

Parameters:

dllinst - plugin's instance;

key - name of the key to be associated with an integer;

value - integer to be written to ollydbg.ini.

*/
extc int     cdecl Pluginwriteinttoini(HINSTANCE dllinst, char* key, int value) {
	CHAR text[30] = { 0 };
	sprintf_s(text, "%d", value);

	msg("writeinttoini %08x [%s] %s\n", dllinst, key, text);
	auto plugin = OllyPlugin::get(dllinst);
	if (plugin == nullptr) {
		return 0;
	}

	WritePrivateProfileStringA(plugin->get_name().c_str(), key, text, ini_filename);
	return 1;
}
extc int     cdecl Pluginwritestringtoini(HINSTANCE dllinst, char* key, char* s) {
	msg("writestringtoini %08x [%s] %s\n", dllinst, key, s);
	auto plugin = OllyPlugin::get(dllinst);
	if (plugin == nullptr) {
		msg("plugin == null\n");
		return 0;
	}

	WritePrivateProfileStringA(plugin->get_name().c_str(), key, s, ini_filename);
	return 1;
}
/*
Reads integer associated with a key from the plugin's personal section of the ollydbg.ini. On success, returns integer from the initializations file. On error, returns specified default value.

int Pluginreadintfromini(HINSTANCE dllinst,char *key,int def);

Parameters:

dllinst - plugin's instance;

key - name of the key associated with an integer;

def - default value.

*/
extc int     cdecl Pluginreadintfromini(HINSTANCE dllinst, char* key, int def) {
	msg("readintfromini %d [%s] %d\n", dllinst, key, def);
	auto plugin = OllyPlugin::get(dllinst);
	if (plugin == nullptr) {
		msg("plugin == null\n");
		return 0;
	}

	return GetPrivateProfileIntA(plugin->get_name().c_str(), key, def, ini_filename);
}
/*
Reads string associated with a key from the plugin's personal section of the ollydbg.ini. On success, returns string from the initializations file. On error, returns specified default string.

int Pluginreadstringfromini(HINSTANCE dllinst,char *key,char *s,char *def);

Parameters:

dllinst - plugin's instance;

key - name of the key associated with the string;

s - pointer to buffer that receives string;

def - pointer to a null-terminated default string.
*/
extc int     cdecl Pluginreadstringfromini(HINSTANCE dllinst, char* key,
	char* s, char* def) {
	msg("readstringfromini %d [%s] %s\n", dllinst, key, def);
	auto plugin = OllyPlugin::get(dllinst);
	if (plugin == nullptr) {
		msg("plugin == null\n");
		return 0;
	}

	char tmp[128] = { 0 };

	int count = GetPrivateProfileStringA(plugin->get_name().c_str(), key, def, tmp, ARRAYSIZE(tmp), ini_filename);
	if (count > 0) {
		strncpy(s, tmp, count);
	}
	else {
		// Default value
		strncpy(s, def, strlen(def));
	}
	return 0;
}
extc int     cdecl Pluginsaverecord(ulong tag, ulong size, void* data) { return 0; }
/*
Retrieves various OllyDbg settings and variables.

int Plugingetvalue(int type);

Parameters:

type - setting or variable to retrieve:

type	Cast to	Explanation
VAL_HINST	(HINST)	Current OllyDbg instance
VAL_HWMAIN	(HWND)	Handle of the main OllyDbg window
VAL_HWCLIENT	(HWND)	Handle of the MDI client window
VAL_NCOLORS		Number of common colors
VAL_COLORS	(COLORREF *)	RGB values of common colors
VAL_BRUSHES	(HBRUSH *)	Handles of common color brushes
VAL_PENS	(PEN *)	Handles of common color pens
VAL_NFONTS		Number of common fonts
VAL_FONTS	(HFONT *)	Handles of common fonts
VAL_FONTNAMES	(char **)	Internal font names
VAL_FONTWIDTHS	(int *)	Average widths of common fonts
VAL_FONTHEIGHTS	(int *)	Average heigths of common fonts
VAL_NFIXFONTS		Actual number of fixed-pitch fonts
VAL_DEFFONT		Index of default font
VAL_NSCHEMES		Number of color schemes
VAL_SCHEMES	(t_scheme *)	Colour schemes
VAL_DEFSCHEME		Index of default colour scheme
VAL_DEFHSCROLL		Default horizontal scroll
VAL_RESTOREWINDOWPOS	Restore window positions from .ini
VAL_HPROCESS	(HANDLE)	Handle of debugged process
VAL_PROCESSID		Process ID of debugged process
VAL_HMAINTHREAD	(HANDLE)	Handle of main thread of debugged process
VAL_MAINTHREADID		Thread ID of main thread of debugged process
VAL_MAINBASE		Base of main module in the debugged process
VAL_PROCESSNAME	(char *)	Name of the debugged process
VAL_EXEFILENAME	(char *)	Name of the main debugged file
VAL_CURRENTDIR	(char *)	Current directory for debugged process
VAL_SYSTEMDIR	(char *)	Windows system directory
VAL_DECODEANYIP		Decode registers dependless on EIP
VAL_PASCALSTRINGS		Decode Pascal-style string constants
VAL_ONLYASCII		Only printable ASCII chars in dump
VAL_DIACRITICALS		Allow diacritical symbols in strings
VAL_GLOBALSEARCH		Search from the beginning of block
VAL_ALIGNEDSEARCH		Search aligned to item's size
VAL_SEARCHMARGIN		Floating search allows error margin
VAL_KEEPSELSIZE		Keep size of hex edit selection
VAL_MMXDISPLAY		MMX display mode in dialog (0:hex, 1:signed, 2:unsigned MMX)
VAL_WINDOWFONT		Use calling window's font in dialog
VAL_TABSTOPS		Distance between tab stops
VAL_MODULES	(t_table *)	Table of modules (.EXE and .DLL)
VAL_MEMORY	(t_table *)	Table of allocated memory blocks
VAL_THREADS	(t_table *)	Table of active threads
VAL_BREAKPOINTS	(t_table *)	Table of active breakpoints
VAL_REFERENCES	(t_table *)	Table with found references
VAL_SOURCELIST	(t_table *)	Table of source files
VAL_WATCHES	(t_table *)	Table of watches
VAL_CPUFEATURES		CPU feature bits as returned by CPUID
VAL_TRACEFILE	(FILE *)	Handle of run trace log file
VAL_ALIGNDIALOGS		Align dialogs
VAL_CPUDASM	(t_dump *)	Dump descriptor of CPU Disassembler pane
VAL_CPUDDUMP	(t_dump *)	Dump descriptor of CPU Dump pane
VAL_CPUDSTACK	(t_dump *)	Dump descriptor of CPU Stack pane
VAL_APIHELP	(char *)	Name of selected API help file
VAL_HARDBP		Whether hardware breakpoints are enabled
VAL_PATCHES	(t_table *)	Table of patches
VAL_HINTS	(t_sorted *)	Sorted data with analysis hints

*/
extc int     cdecl Plugingetvalue(int type) {
	msg("Plugingetvalue %d\n", type);

	static HFONT hFont = CreateFont(11, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Lucida Console"));

	switch (type) {
	case VAL_HINST: return (int)GetModuleHandle(NULL);
	case VAL_FONTS: return (int)&hFont;
	case VAL_DEFFONT: return 0;
	default:
		msg("[unknown]Plugingetvalue %d\n", type);
		break;
	}
	return 0;
}

