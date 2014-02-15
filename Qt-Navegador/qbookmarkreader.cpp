#include "qbookmarkreader.h"

QBookmarkReader::QBookmarkReader(QList<BookmarkVector>* bookmarkStore)
    : QXmlStreamReader ()
{
    bookmarkFile_.setFileName("/Users/kevinrobayna/Workstation/tmp/bookmark.xml");
    bookmarkFile_.open(QFile::ReadOnly);


    BookmarkVector dummyBookmark();
    setDevice(bookmarkFile_);
    while (!atEnd())
    {
        readNext();
        if (isStartElement() && name() == "Bookmarks")
        {
            while (!atEnd())
            {
                readNext();
                if (isEndElement())
                    break;
                if (isStartElement())
                {
                    if (name() == "name")
                    {
                        dummyBookmark.setName(readElementText());
                    }
                    else if (name() == "url")
                    {
                        dummyBookmark.setUrl(readElementText());
                    }
                }
                bookmarkStore -> push_back(dummyBookmark);
            }
        }
    }
}

QBookmarkReader::~QBookmarkReader()
{

}
