/*
 *   Copyright (C) 2010
 *   by Ariel Constenla-Haile <ariel.constenla.haile@gmail.com>
 *
 * This file is part of OpenDocument Thumbnail Creator.
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * This is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenDocument Thumbnail Creator.  If not, see
 * <http://www.gnu.org/licenses/> for a copy of the LGPLv3 License.
 */

#include "fcstdcreator.h"

#include <kzip.h>

#include <QImage>
#include <QPainter>

extern "C"
{
    KDE_EXPORT ThumbCreator *new_creator()
    {
        return new FcstdCreator;
    }
}


FcstdCreator::FcstdCreator()
{

}

FcstdCreator::~FcstdCreator()
{

}

bool FcstdCreator::create ( const QString &path, int w, int h, QImage &img )
{
    Q_UNUSED(w)
    Q_UNUSED(h)

    bool bRet = false;
    KZip zip ( path );
    if ( zip.open ( QIODevice::ReadOnly ) )
    {
        const KArchiveDirectory* dir = zip.directory();
        const KArchiveEntry* entry = dir->entry ( "thumbnails/Thumbnail.png" );

        if ( ( entry != NULL ) && ( entry->isFile() ) )
        {
            const KArchiveFile* file = ( KArchiveFile* ) entry;
            QByteArray data ( file->data() );

            if ( data.size() > 0 )
            {
                img.loadFromData ( data,"PNG" );
#ifndef KEEP_ALPHA_CHANNEL
                if ( !img.isNull() && img.hasAlphaChannel() )
                    img = img.convertToFormat ( QImage::Format_RGB32 );
#endif
                if ( !img.isNull() )
                    bRet = true;
            }
        }
    }
    zip.close();
    return bRet;
}

ThumbCreator::Flags FcstdCreator::flags() const
{
    return (Flags)(DrawFrame | BlendIcon);
}


// kate: indent-mode cstyle; space-indent on; indent-width 4;
