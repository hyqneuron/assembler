//
// Symbol utility implementation.
//
//  Copyright (C) 2001-2008  Michael Urman, Peter Johnson
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND OTHER CONTRIBUTORS ``AS IS''
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR OTHER CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
#include "symbol_util.h"

#include "assoc_data.h"
#include "expr.h"
#include "marg_ostream.h"
#include "name_value.h"
#include "symbol.h"


namespace
{

using namespace yasm;

class ObjextNamevals : public AssocData
{
public:
    static const char* key;

    ObjextNamevals(std::auto_ptr<NameValues> nvs) : m_nvs(nvs.release()) {}
    ~ObjextNamevals();

    void put(marg_ostream& os) const;

    const NameValues* get() const { return m_nvs.get(); }

private:
    boost::scoped_ptr<NameValues> m_nvs;
};

const char* ObjextNamevals::key = "ObjextNamevals";

ObjextNamevals::~ObjextNamevals()
{
}

void
ObjextNamevals::put(marg_ostream& os) const
{
    os << "Objext Namevals: " << *m_nvs << '\n';
}


class CommonSize : public AssocData
{
public:
    static const char* key;

    CommonSize(std::auto_ptr<Expr> e) : m_expr(e.release()) {}
    ~CommonSize();

    void put(marg_ostream& os) const;

    Expr* get() { return m_expr.get(); }

private:
    boost::scoped_ptr<Expr> m_expr;
};

const char* CommonSize::key = "CommonSize";

CommonSize::~CommonSize()
{
}

void
CommonSize::put(marg_ostream& os) const
{
    os << "Common Size=" << *m_expr << '\n';
}

} // anonymous namespace

namespace yasm
{

void
set_objext_namevals(Symbol& sym, std::auto_ptr<NameValues> objext_namevals)
{
    std::auto_ptr<AssocData> ad(new ObjextNamevals(objext_namevals));
    sym.add_assoc_data(ObjextNamevals::key, ad);
}

const NameValues*
get_objext_namevals(const Symbol& sym)
{
    const AssocData* ad = sym.get_assoc_data(ObjextNamevals::key);
    if (!ad)
        return 0;
    const ObjextNamevals* x = static_cast<const ObjextNamevals*>(ad);
    return x->get();
}

void
set_common_size(Symbol& sym, std::auto_ptr<Expr> common_size)
{
    std::auto_ptr<AssocData> ad(new CommonSize(common_size));
    sym.add_assoc_data(CommonSize::key, ad);
}

Expr*
get_common_size(Symbol& sym)
{
    AssocData* ad = sym.get_assoc_data(CommonSize::key);
    if (!ad)
        return 0;
    CommonSize* x = static_cast<CommonSize*>(ad);
    return x->get();
}

} // namespace yasm