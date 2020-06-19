#define HAVE_DECL_BASENAME 1
#include "demangle.h"

#include <cstring>
#include <regex>

#include <llvm/Demangle/Demangle.h>

extern "C"
char* msvc_demangle(const char* sym, int options)
{
  auto mangled = sym;
  auto suffix = std::strchr(sym, '!');
  if (suffix != 0) {
    mangled = suffix + 1;
  }

  auto flags = llvm::MSDemangleFlags(llvm::MSDF_NoAccessSpecifier | llvm::MSDF_NoCallingConvention);
  if (!(options & DMGL_ANSI)) {
    /* TODO: Wait for LLVM's demangler to get a flag for this */;
  }
  if (!(options & DMGL_PARAMS)) {
    /* TODO: Wait for LLVM's demangler to get a flag for this */;
  }

  //HACK: We should probably not do this on DMGL_AUTO, but the GNU C++
  //      demangler also omits the return type even without
  //      DMGL_RET_DROP...
  if ((options & (DMGL_RET_DROP | DMGL_AUTO))) {
    flags = llvm::MSDemangleFlags(flags | llvm::MSDF_NoReturnType);
  }

  auto demangled = llvm::microsoftDemangle(mangled, nullptr, nullptr, nullptr, flags);
  if (demangled == nullptr) {
    return nullptr;
  }

  auto result = std::string(demangled);

  //do we want this?
  if (mangled != sym) {
    result = std::string(sym, suffix - sym + 1) + result;
  }

  //TODO: Use OF_NoTagSpecifier (not currently available as a MSDF_* flag)
  result = std::regex_replace(result, std::regex("(class|struct|union|enum) "), "");

  result = std::regex_replace(result, std::regex(" (\\*|&)"), "$1");

  return strdup(result.c_str());
}
