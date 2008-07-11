#ifndef YASM_SYMBOL_UTIL_H
#define YASM_SYMBOL_UTIL_H
///
/// @file
/// @brief Symbol utility interface.
///
/// @license
///  Copyright (C) 2001-2008  Michael Urman, Peter Johnson
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
///  - Redistributions of source code must retain the above copyright
///    notice, this list of conditions and the following disclaimer.
///  - Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
///
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND OTHER CONTRIBUTORS ``AS IS''
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR OTHER CONTRIBUTORS BE
/// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
/// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
///  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
/// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
/// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
/// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
/// POSSIBILITY OF SUCH DAMAGE.
/// @endlicense
///
#include "export.h"

#include <memory>


namespace yasm
{

class Expr;
class NameValues;
class Symbol;

/// Set object-extended name/values.
/// @param sym              symbol
/// @param objext_namevals  object-extended name/values
YASM_LIB_EXPORT
void set_objext_namevals(Symbol& sym,
                         std::auto_ptr<NameValues> objext_namevals);

/// Get object-extended name/values, if any, associated with symbol's
/// declaration.
/// @param sym          symbol
/// @return Object-extended name/values (NULL if none).
YASM_LIB_EXPORT
/*@null@*/ const NameValues* get_objext_namevals(const Symbol& sym);

/// Set common size of symbol.
/// @param sym          symbol
/// @param common_size  common size expression
/// @return Symbol (this).
YASM_LIB_EXPORT
void set_common_size(Symbol& sym, std::auto_ptr<Expr> common_size);

/// Get common size of symbol, if symbol is declared #COMMON and a
/// size was set for it.
/// @param sym          symbol
/// @return Common size (NULL if none).
YASM_LIB_EXPORT
/*@null@*/ Expr* get_common_size(Symbol& sym);

} // namespace yasm

#endif
