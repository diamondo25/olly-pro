#include "stdafx.h"

#pragma once
#include <unordered_map>
#include <stack>

struct patch_t {
	uint32 offset;
	uint8* data;
	size_t data_len;
	int mode;
};

class OllyPlugin
{
public:
	OllyPlugin(HMODULE module, const char* name) {
		data_cb = get_proc_addr_plugin_raw(module, ODBG_Plugindata);
		init_cb = get_proc_addr_plugin_raw(module, ODBG_Plugininit);
		mainloop_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginmainloop);
		saveudd_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginsaveudd);
		uddrecord_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginuddrecord);
		menu_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginmenu);
		action_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginaction);
		shortcut_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginshortcut);
		reset_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginreset);
		close_cb = get_proc_addr_plugin_raw(module, ODBG_Pluginclose);
		destroy_cb = get_proc_addr_plugin_raw(module, ODBG_Plugindestroy);
		paused_cb = get_proc_addr_plugin_raw(module, ODBG_Paused);
		pausedex_cb = get_proc_addr_plugin_raw(module, ODBG_Pausedex);
		cmd_ex = get_proc_addr_plugin_raw(module, ODBG_Plugincmd);

		g_s_plugins[module] = this;
		this->name = std::string(name);
	}


	static OllyPlugin* g_s_current_plugin;



	int data(char shortname[32]) { g_s_current_plugin = this; return data_cb(shortname); }
	int init(int ollydbgversion, HWND hw, ulong* features) { g_s_current_plugin = this; return init_cb(ollydbgversion, hw, features); }
	void mainloop(DEBUG_EVENT* debugevent) { g_s_current_plugin = this; mainloop_cb(debugevent); }
	void saveudd(t_module* pmod, int ismainmodule) { g_s_current_plugin = this; saveudd_cb(pmod, ismainmodule); }

	int menu(int origin, char data[4096], void* item) { g_s_current_plugin = this; return menu_cb(origin, data, item); }
	void action(int origin, int action, void* item) { g_s_current_plugin = this; action_cb(origin, action, item); }

	static OllyPlugin* get(HMODULE module) {
		auto v = g_s_plugins.find(module);
		if (v != g_s_plugins.end()) {
			return v->second;
		}
		else {
			// Not found
			return NULL;
		}
	}

	const std::string& get_name() const { return name; }

	std::stack<patch_t> patches;

private:
	static std::unordered_map<HMODULE, OllyPlugin*> g_s_plugins;
	std::string name;

	ODBG_Plugindata data_cb;
	ODBG_Plugininit init_cb;
	ODBG_Pluginmainloop mainloop_cb;
	ODBG_Pluginsaveudd saveudd_cb;
	ODBG_Pluginuddrecord uddrecord_cb;
	ODBG_Pluginmenu menu_cb;
	ODBG_Pluginaction action_cb;
	ODBG_Pluginshortcut shortcut_cb;
	ODBG_Pluginreset reset_cb;
	ODBG_Pluginclose close_cb;
	ODBG_Plugindestroy destroy_cb;
	ODBG_Paused paused_cb;
	ODBG_Pausedex pausedex_cb;
	ODBG_Plugincmd cmd_ex;
};
