/****************************************************************************
** libebml : parse EBML files, see http://embl.sourceforge.net/
**
** <file/class description>
**
** Copyright (C) 2002-2010 Steve Lhomme.  All rights reserved.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** See http://www.gnu.org/licenses/lgpl-2.1.html for LGPL licensing information.
**
** Contact license@matroska.org if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

/*!
  \file
  \version \$Id$
  \author Steve Lhomme     <robux4 @ users.sf.net>
*/
#ifndef LIBEBML_DATE_H
#define LIBEBML_DATE_H

#include "EbmlTypes.h"
#include "EbmlElement.h"

START_LIBEBML_NAMESPACE

/*!
    \class EbmlDate
    \brief Handle all operations related to an EBML date
*/
class EBML_DLL_API EbmlDate : public EbmlElement {
  public:
    EbmlDate() :EbmlElement(8, false), myDate(0) {}
    EbmlDate(const EbmlDate & ElementToClone);

    /*!
      \brief set the date with a UNIX/C/EPOCH form
      \param NewDate UNIX/C date in UTC (no timezone)
    */
    void SetEpochDate(std::int64_t NewDate) {myDate = (NewDate - UnixEpochDelay) * 1000000000; SetValueIsSet();}
    EbmlDate &SetValue(std::int64_t NewValue) {SetEpochDate(NewValue); return *this;}

    /*!
      \brief get the date with a UNIX/C/EPOCH form
      \note the date is in UTC (no timezone)
    */
    std::int64_t GetEpochDate() const {return std::int64_t(myDate/1000000000 + UnixEpochDelay);}
    std::int64_t GetValue() const {return GetEpochDate();}

    virtual bool ValidateSize() const {return IsFiniteSize() && ((GetSize() == 8) || (GetSize() == 0));}

    /*!
      \note no Default date handled
    */
    filepos_t UpdateSize(bool /* bWithDefault = false */, bool /* bForceRender = false */) {
      if(!ValueIsSet())
        SetSize_(0);
      else
        SetSize_(8);
      return GetSize();
    }

    virtual bool IsSmallerThan(const EbmlElement *Cmp) const;

    filepos_t ReadData(IOCallback & input, ScopeMode ReadFully = SCOPE_ALL_DATA);

    bool IsDefaultValue() const {
      return false;
    }

#if defined(EBML_STRICT_API)
    private:
#else
    protected:
#endif
    filepos_t RenderData(IOCallback & output, bool bForceRender, bool bWithDefault = false);

    std::int64_t myDate; ///< internal format of the date

    static const std::uint64_t UnixEpochDelay;
};

END_LIBEBML_NAMESPACE

#endif // LIBEBML_DATE_H
