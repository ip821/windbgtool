#pragma once

#ifndef __PLDBGMCMDS__
DEFINE_GUID(CLSID_ManagedDebugSessionService, 0xB2B96417, 0x20CC, 0x4677, 0x80, 0x58, 0x9D, 0x3C, 0xC1, 0xD0, 0xD2, 0xF5);
#endif

#define VAR_OSID L"VAR_OSID"
#define VAR_THREADOBJ L"VAR_THREADOBJ"
#define VAR_STATE L"VAR_STATE"
#define VAR_GC L"VAR_GC"
#define VAR_ALLOC L"VAR_ALLOC"
#define VAR_DOMAIN L"VAR_DOMAIN"
#define VAR_LOCKCOUNT L"VAR_LOCKCOUNT "
#define VAR_APT L"VAR_APT"
#define VAR_EXCEPTION L"VAR_EXCEPTION"

// {4D31C80C-AFA7-4B14-B76E-41BE692EAC70}
DEFINE_GUID(DBGCOMMAND_DOTNETINFO, 0x4d31c80c, 0xafa7, 0x4b14, 0xb7, 0x6e, 0x41, 0xbe, 0x69, 0x2e, 0xac, 0x70);
// {2BC03630-AF81-4D1B-ACB9-EA4EEB34A19F}
DEFINE_GUID(DBGCOMMAND_HEAPSTAT, 0x2bc03630, 0xaf81, 0x4d1b, 0xac, 0xb9, 0xea, 0x4e, 0xeb, 0x34, 0xa1, 0x9f);
// {423B0D90-85DB-446C-A3BD-BCE66F5AE394}
DEFINE_GUID(DBGCOMMAND_CORDLL, 0x423b0d90, 0x85db, 0x446c, 0xa3, 0xbd, 0xbc, 0xe6, 0x6f, 0x5a, 0xe3, 0x94);
// {CA11E576-DCDE-479E-9707-DADAC260B0D0}
DEFINE_GUID(DBGCOMMAND_LOADCLR, 0xca11e576, 0xdcde, 0x479e, 0x97, 0x7, 0xda, 0xda, 0xc2, 0x60, 0xb0, 0xd0);
// {E6B395E0-630D-4A50-8D34-50029B9F5223}
DEFINE_GUID(DBGCOMMAND_OBJECTS, 0xe6b395e0, 0x630d, 0x4a50, 0x8d, 0x34, 0x50, 0x2, 0x9b, 0x9f, 0x52, 0x23);
// {FD781547-F954-45F6-9B99-A7B912F292E7}
DEFINE_GUID(DBGCOMMAND_OBJECT_PROPS, 0xfd781547, 0xf954, 0x45f6, 0x9b, 0x99, 0xa7, 0xb9, 0x12, 0xf2, 0x92, 0xe7);
// {68C4BA5B-E1FE-42F3-A809-80DB382A38FB}
DEFINE_GUID(DBGCOMMAND_OBJECT_VALUES, 0x68c4ba5b, 0xe1fe, 0x42f3, 0xa8, 0x9, 0x80, 0xdb, 0x38, 0x2a, 0x38, 0xfb);
// {DB460A3E-B11E-4087-BCFC-C9C6C2E084D3}
DEFINE_GUID(DBGCOMMAND_THREADSINFO, 0xdb460a3e, 0xb11e, 0x4087, 0xbc, 0xfc, 0xc9, 0xc6, 0xc2, 0xe0, 0x84, 0xd3);
// {E1A9B072-4FEA-406B-9261-B9D70CC71A10}
DEFINE_GUID(DBGCOMMAND_GCROOT, 0xe1a9b072, 0x4fea, 0x406b, 0x92, 0x61, 0xb9, 0xd7, 0xc, 0xc7, 0x1a, 0x10);
// {D408323F-4A64-4FEC-A7C9-32D20FA8E575}
DEFINE_GUID(DBGCOMMAND_GCMROOT, 0xd408323f, 0x4a64, 0x4fec, 0xa7, 0xc9, 0x32, 0xd2, 0xf, 0xa8, 0xe5, 0x75);
// {96B22051-4149-4F47-9029-8C26D766E621}
DEFINE_GUID(DBGCOMMAND_BUILD_INDEX, 0x96b22051, 0x4149, 0x4f47, 0x90, 0x29, 0x8c, 0x26, 0xd7, 0x66, 0xe6, 0x21);


// {14F9AB8F-A8D6-42AA-8FBE-9D0853240D68}
DEFINE_GUID(DBGCOMMAND_LOADBY,0x14f9ab8f, 0xa8d6, 0x42aa, 0x8f, 0xbe, 0x9d, 0x8, 0x53, 0x24, 0xd, 0x68);


