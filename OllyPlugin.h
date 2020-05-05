#include "stdafx.h"

#pragma once
#include <unordered_map>
#include <stack>

struct patch_t {
	ea_t ea;
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

	std::string menu_name;

	bool add_menu_item(
		const char* name,
		const char* hotkey,
		int flags,
		menu_item_callback_t* callback,
		void* ud) {

		// TODO: Normalize name so it doesn't try to create submenus

		std::string fullname{ menu_name };
		fullname.append(" -> ");
		fullname.append(name);

		if (::add_menu_item(
			"Edit",
			fullname.c_str(),
			hotkey, flags, callback, ud
		)) {
			menu_items.push_back(std::string("Edit/").append(fullname));
			return true;
		}
		return false;
	}


	void del_menu_items() {
		for (auto& mi : menu_items) {
			::del_menu_item(mi.c_str());
		}
	}

	static void unload_all() {
		for (auto& kvp : g_s_plugins) {
			auto plugin = kvp.second;
			plugin->del_menu_items();
			msg("unloading %s\n", plugin->get_name().c_str());
			plugin->destroy_cb();
		}
	}

	void push_undo_action(patch_t x) {
		undo_stack.push(x);
		// Clear redo actions so we overwrote the previous action
		clear_redo_actions();
	}
	void push_redo_action(patch_t x) {
		redo_stack.push(x);
	}
	
	void clear_redo_actions() { clear_stack(redo_stack); }
	void clear_undo_actions() { clear_stack(undo_stack); }

	patch_t* get_undo_action() {
		if (undo_stack.empty()) return nullptr;
		patch_t ret = undo_stack.top();
		undo_stack.pop();
		return &ret;
	}

	patch_t* get_redo_action() {
		if (redo_stack.empty()) return nullptr;
		patch_t ret = redo_stack.top();
		redo_stack.pop();
		return &ret;
	}
private:
	static std::unordered_map<HMODULE, OllyPlugin*> g_s_plugins;
	std::string name;
	std::list<std::string> menu_items;

	std::stack<patch_t> undo_stack;
	std::stack<patch_t> redo_stack;

	void clear_stack(std::stack<patch_t>& stack) {
		while (!stack.empty()) {
			patch_t patch = stack.top();
			stack.pop();

			qfree(patch.data);
		}
	}

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
