#include <QString>

#ifndef BOOKMARKVECTOR_H
#define BOOKMARKVECTOR_H

class BookmarkVector
{
public:
    BookmarkVector();

    QString name() const;
    void setName(const QString &name);

    QString url() const;
    void setUrl(const QString &url);

private:
    QString name_;
    QString url_;
};

#endif // BOOKMARKVECTOR_H
