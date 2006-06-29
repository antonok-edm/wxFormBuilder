///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "model/types.h"
#include <wx/tokenzr.h>
#include "utils/stringutils.h"
#include "utils/debug.h"
#include "utils/typeconv.h"

ObjectType::ObjectType(unistring name, int id, bool hidden, bool item)
{
  m_id = id;
  m_name = name;
  m_hidden = hidden;
  m_item = item;
}

void ObjectType::AddChildType(PObjectType type, int max)
{
  assert(max != 0);
  m_childTypes.insert(ChildTypeMap::value_type(type,max));
}

int ObjectType::FindChildType(int type_id)
{
  int max = 0;
  ChildTypeMap::iterator it;
  for (it = m_childTypes.begin(); it != m_childTypes.end() && max == 0; it++)
  {
    PObjectType type(it->first);
    if (type && type_id == type->GetId())
      max = it->second;
  }
  return max;
}

int ObjectType::FindChildType(PObjectType type)
{
  int type_id = type->GetId();
  return FindChildType(type_id);
}

unsigned int ObjectType::GetChildTypeCount()
{
  return (unsigned int)m_childTypes.size();
}

PObjectType ObjectType::GetChildType(unsigned int idx)
{
  PObjectType result;
  
  assert (idx < GetChildTypeCount());
  
  unsigned int i = 0;
  ChildTypeMap::iterator it = m_childTypes.begin();
  
  while (i < idx && it != m_childTypes.end())
  {
    i++;
    it++;
  }
  
  if (i == idx)
    result = PObjectType(it->first);
    
    
  return result;
}

///////////////////////////////////////////////////////////////////////////////

IntList::IntList(unistring value)
{
  SetList(value);
}

void IntList::DeleteList()
{
  m_ints.erase(m_ints.begin(), m_ints.end());
}

void IntList::SetList(unistring str)
{
  wxString wxstr( _WXSTR(str) );
  DeleteList();
  wxStringTokenizer tkz(wxstr, wxT(","));
  while (tkz.HasMoreTokens())
  {
    long value;
    wxString token;
    token = tkz.GetNextToken();
    token.Trim(true);
    token.Trim(false);
    
    if (token.ToLong(&value))
      Add((int)value);
  }
}

unistring IntList::ToString()
{
  unistring result;
  
  for (unsigned int i=0; i< m_ints.size() ; i++)
  {
    result = result + StringUtils::IntToStr(m_ints[i]);
  }
  
  return result;
}
