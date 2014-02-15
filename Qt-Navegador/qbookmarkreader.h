#ifndef QBOOKMARKREADER_H
#define QBOOKMARKREADER_H

#include <QXmlStreamReader>
#include <QString>
#include <QList>
#include <bookmarkvector.h>
#include <QFile>
#include <QIODevice>

class QBookmarkReader : public QXmlStreamReader
{
public:
    QBookmarkReader(QList<BookmarkVector>* bookmarkStore);
    virtual ~QBookmarkReader();
private:
    QFile bookmarkFile_();
};

#endif // QBOOKMARKREADER_H
