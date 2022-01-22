#include <cstdint>
#include <cstring>
#include <cstdio>

#include <iostream>
#include <iomanip>

// #include <linux/auxvec.h>
#include <elf.h>

#include "enum.hpp"

// typedef struct {
//   uint64_t a_type;
//   union {
//       uint64_t a_val;
//   } a_un;
// } Elf64_auxv_t;

// clang-format off
ENUM_HPP_CLASS_DECL(auxv_tag, uint64_t,
	(NUL = AT_NULL)
	(IGNORE = AT_IGNORE)
	(EXECFD = AT_EXECFD)
	(PHDR = AT_PHDR)
	(PHENT = AT_PHENT)
	(PHNUM = AT_PHNUM)
	(PAGESZ = AT_PAGESZ)
	(BASE = AT_BASE)
	(FLAGS = AT_FLAGS)
	(ENTRY = AT_ENTRY)
	(NOTELF = AT_NOTELF)
	(UID = AT_UID)
	(EUID = AT_EUID)
	(GID = AT_GID)
	(EGID = AT_EGID)
	(CLKTCK = AT_CLKTCK)
	(PLATFORM = AT_PLATFORM)
	(HWCAP = AT_HWCAP)
	(FPUCW = AT_FPUCW)
	(DCACHEBSIZE = AT_DCACHEBSIZE)
	(ICACHEBSIZE = AT_ICACHEBSIZE)
	(UCACHEBSIZE = AT_UCACHEBSIZE)
	(IGNOREPPC = AT_IGNOREPPC)
	(SECURE = AT_SECURE)
	(BASE_PLATFORM = AT_BASE_PLATFORM)
	(RANDOM = AT_RANDOM)
	(HWCAP2 = AT_HWCAP2)
	(EXECFN = AT_EXECFN)
	(SYSINFO = AT_SYSINFO)
	(SYSINFO_EHDR = AT_SYSINFO_EHDR)
	(L1I_CACHESHAPE = AT_L1I_CACHESHAPE)
	(L1D_CACHESHAPE = AT_L1D_CACHESHAPE)
	(L2_CACHESHAPE = AT_L2_CACHESHAPE)
	(L3_CACHESHAPE = AT_L3_CACHESHAPE)
	(L1I_CACHESIZE = AT_L1I_CACHESIZE)
	(L1I_CACHEGEOMETRY = AT_L1I_CACHEGEOMETRY)
	(L1D_CACHESIZE = AT_L1D_CACHESIZE)
	(L1D_CACHEGEOMETRY = AT_L1D_CACHEGEOMETRY)
	(L2_CACHESIZE = AT_L2_CACHESIZE)
	(L2_CACHEGEOMETRY = AT_L2_CACHEGEOMETRY)
	(L3_CACHESIZE = AT_L3_CACHESIZE)
	(L3_CACHEGEOMETRY = AT_L3_CACHEGEOMETRY)
	(MINSIGSTKSZ = AT_MINSIGSTKSZ)
)
// clang-format on

int main(int argc, const char **argv, const char **envp) {
	int envc = 0;
	for (const char **env = envp; *env; ++env, ++envc);
	auto auxv = (Elf64_auxv_t *)&envp[envc + 1];
	printf("argc: %d argv: %p envc: %d envp: %p auxv: %p\n",
		argc, argv, envc, envp, auxv);

	std::cout << std::setfill('0');

	for (int i = 0; auxv_tag{auxv[i].a_type} != auxv_tag::NUL; ++i) {
		std::cout << "auxv[" << std::setw(2) << i << "].a_type = " << auxv_tag_traits::to_string_or_empty(auxv_tag{auxv[i].a_type}) << "\n";
		std::cout << "auxv[" << std::setw(2) << i << "].a_val = 0x" << std::hex << std::setw(16) << auxv[i].a_un.a_val << std::dec << "\n";
	}

	return 0;
}
