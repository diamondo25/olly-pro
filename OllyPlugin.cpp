#include "stdafx.h"
#include "OllyPlugin.h"

OllyPlugin* OllyPlugin::g_s_current_plugin = nullptr;
std::unordered_map<HMODULE, OllyPlugin*> OllyPlugin::g_s_plugins = {};