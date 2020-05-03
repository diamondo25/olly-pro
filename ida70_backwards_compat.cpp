#include "stdafx.h"

#if IDA610

void print_insn_mnem(qstring* out, ea_t ea) {
	char ob[128] = {0};
	ua_mnem(ea, ob, ARRAYSIZE(ob));
	
	out->clear();
	out->append(ob);
}

ssize_t get_segm_class(qstring* out, const segment_t* seg) {
	char ob[128] = {0};
	ssize_t ret = get_segm_class(seg, ob, ARRAYSIZE(ob));
	
	out->clear();
	out->append(ob);
	return ret;
}

ssize_t idaapi get_segm_name(qstring* out, const segment_t* seg) {
	char ob[128] = {0};
	ssize_t ret = get_segm_name(seg, ob, ARRAYSIZE(ob));
	
	out->clear();
	out->append(ob);
	return ret;
}
#endif