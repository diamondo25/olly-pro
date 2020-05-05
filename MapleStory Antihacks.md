# MapleStory Anti-Hack Measures

## Trash stack on cheat detection
This method is very effective, because there's no way to recover from this event.
If this happens inside Themida VM, the game will just close and you'll have no way to figure out where it happened.

Note: stack goes from bottom to top. This function starts erasing from the current stack pointer to the 'first'.
```
	xor     ebx, ebx			; Start clearing most registers
	xor     edx, edx
	xor     esi, esi
	xor     edi, edi
	xor     ebp, ebp
	mov     eax, large fs:18h	; Get the current task stack info
	mov     ecx, [eax+8]		; Load stack end position
	mov     eax, [eax+4]		; Load current stack position (ESP), will be counted down

trash_loop:
	cmp     eax, ecx			; Compare current position to the 'end' position.
	jbe     short exit_loop		; exit loop when we are done (we reached the end)
	sub     eax, 4				; go to next index
	mov     [eax], ebx			; overwrite this stack entry with 0 (we cleared that register in the beginning)
	jmp     short trash_loop

exit_loop:
	xor     eax, eax
	xor     ecx, ecx
	retn						; As stack is zero, there's no way to go back and the game will fail/exit
```

This assembly is used _a lot_ by the game.

## Inlining string assignment
This makes searching for strings inside the binary much harder. Usually found around DLL API calls like GetProcAddress and LoadLibraryA.
```
	mov     [ebp+var_14], 6Bh
	mov     [ebp+var_13], 65h
	mov     [ebp+var_12], 72h
	mov     [ebp+var_11], 6Eh
	mov     [ebp+var_10], 65h
	mov     [ebp+var_F], 6Ch
	mov     [ebp+var_E], 33h
	mov     [ebp+var_D], 32h
	mov     [ebp+var_C], 2Eh
	mov     [ebp+var_B], 64h
	mov     [ebp+var_A], 6Ch
	mov     [ebp+var_9], 6Ch
	mov     [ebp+var_8], 0
```

## Checking whether function call has been modified

The following code is a snippet from the UnVirtualizer. Note the two dwords being loaded after the mov.
```

	00DCE4AF	PUSH DWORD PTR [ESP]
	00DCE4B1	MOV DWORD PTR [ESP],EAX
	00DCE500	POP EAX
	00DCE509	POP ESP
	00DCE50A	MOV DWORD PTR [EBP+0xffffff74],0x19dea1bd <<< REAL ADDR
	00DCE54E	MOV DWORD PTR [EBP+0xfffffff0],0xbe02ff0a
	00DCE592	PUSH 0x0
	00DCE59E	LEA EAX,DWORD PTR [EBP+0xfffffff0]
	00DCE659	PUSH EAX
	00DCE667	LEA ECX,DWORD PTR [EBP+0xffffff64]
	00DCE6F6	PUSH ECX
	00DCE705	CALL 0x4a7ee0
```

`sub_4a7ee0` will check the the following:
1. `0x19dea1bd` will be xorred with another const value, resulting in `0x2010`
2. `0xbe02ff0a` will be xorred with another const value, resulting in `0x1022`


These are usually found before a packets gets sent, most of the times it will be attack packets.