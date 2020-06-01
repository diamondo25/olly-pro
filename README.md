# olly-pro
IDA Pro (6.1) plugin for running OllyDBG 1.1 plugins

## Why

OllyDBG 1.1 has a lot of plugins, and some are very useful on their own, not requiring a running executable. 

## How

OllyDBG plugins are really just a dll that has a lot of exports (olly-to-plugin interop) and imports (plugin-to-olly interop).
This plugin builds on top of Olly's Plugin.h and its Def (export definition) file, to allow the plugins to interop with IDA, and IDA (this plugin) to interop with the plugin.
However, as the olly plugins are built using ollydbg.exe as import module, this has to be edited to ollypro.plw in order to allow interop (for now).

## Where's my IDA Pro 7.x support, Summer?

Olly plugins are built for x86, and due to this plugin literally loading in the olly plugin, it won't work as you cannot load 32-bit dlls into a 64-bit executable. The idea is to create a bridge executable that loads in the dll (maybe even called ollydbg.exe) and then using something like sockets to bridge data back and forth. Or maybe something like a memory map of some kind hmm.

## Support
Currently, only Deathway's Oreans UnVirtualizer is supported. It's kinda hardcoded, but it is able to un-vm chunks just fine.

## TODO
- Use bridge executable for loading 32-bit plugins (= all olly plugins) and interop with a 64-bit IDA.
- Parse output from Pluginmenu to build the menus, instead of hardcoded.
- Add support for external configuration for each plugin to allow customizations and additions to IDA.
- Write test suite using the olly plugin lib to test functionality.
