#include "stdafx.h"

#if IDA610

void print_insn_mnem(qstring* out, ea_t ea) {
	char ob[128] = {0};
	
	auto pea = prev_visea(ea);
	auto nea = next_visea(ea);
	auto adjea = ea;

	// try to see if 'ea' is actually in the middle of a command
	if (nea > ea && pea < ea && prev_visea(nea) == pea) {
		adjea = pea;
	}

	out->clear();
	if (generate_disasm_line(adjea, ob, ARRAYSIZE(ob))) {
		// Remove color coding
		tag_remove(ob, ob, ARRAYSIZE(ob));
		out->append(ob);
	}
	else {
		out->append("(unable to disasm)");
	}
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

