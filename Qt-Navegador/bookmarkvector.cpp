#include "bookmarkvector.h"

BookmarkVector::BookmarkVector()
{
}
QString BookmarkVector::name() const
{
    return name_;
}

void BookmarkVector::setName(const QString &name)
{
    name_ = name;
}

QString BookmarkVector::name() const
{
    return name_;
}

void BookmarkVector::setName(const QString &name)
{
    name_ = name;
}
QString BookmarkVector::url() const
{
    return url_;
}

void BookmarkVector::setUrl(const QString &url)
{
    url_ = url;
}


