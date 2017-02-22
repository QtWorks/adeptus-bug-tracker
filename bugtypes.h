#ifndef BUG_TYPES_H
#define BUG_TYPES_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QVariant>

//-----------------------------------------------------------------------------------------------

template <typename TResult> class QueryResult
{
public:
    TResult result() const { return _result; }
    const QString& error() const { return _error; }
    bool ok() const { return _error.isEmpty(); }

    static QueryResult fail(const QString& error) { return QueryResult(error); }
    static QueryResult ok(TResult result) { return QueryResult(QString(), result); }

private:
    QueryResult(const QString& error): _error(error) {}
    QueryResult(const QString& error, TResult result): _error(error), _result(result) {}

    QString _error;
    TResult _result;
};

typedef QueryResult<int> IntResult;
typedef QueryResult<QList<int>> IntListResult;

//-----------------------------------------------------------------------------------------------

class BugInfo
{
public:
    BugInfo() {}
    int id;
    QString summary;
    QString extra;
    int category;
    int severity;
    int priority;
    int status;
    int solution;
    int repeat;
    QDateTime created;
    QDateTime updated;
//    bool opened() const;
//    QDateTime created() { return _created.toString(); }
//    QDateTime updated() { return _updated.toString(); }
//    QString displayCreated() { return _created.toDateTime().toString(Qt::SystemLocaleShortDate); }
//    QString displayUpdated() { return _updated.toDateTime().toString(Qt::SystemLocaleShortDate); }
//    QDateTime rawCreated() const { return _created.toDateTime(); }
//    QDateTime rawUpdated() const { return _updated.toDateTime(); }
//private:
//    QVariant _created;
//    QVariant _updated;
};

typedef QueryResult<BugInfo> BugResult;

//-----------------------------------------------------------------------------------------------

class BugHistoryItem
{
public:
    struct ChangedParam
    {
        int paramId;
        QVariant oldValue;
        QVariant newValue;
        ChangedParam(int id, QVariant v1, QVariant v2): paramId(id), oldValue(v1), newValue(v2) {}
        QString str() const { return QString("%1: %2 -> %3").arg(paramId).arg(oldValue.toString()).arg(newValue.toString()); }
    };

public:
    int number = 0;
    QString comment;
    QDateTime moment;
    QList<ChangedParam> changedParams;
    QString momentStr() const { return moment.toString(Qt::SystemLocaleShortDate); }
    bool isValid() const { return number > 0; }
    QString str() const;
};

typedef QList<BugHistoryItem> BugHistoryItems;
typedef QueryResult<BugHistoryItems> BugHistoryResult;

//-----------------------------------------------------------------------------------------------

class BugProvider
{
public:
    virtual ~BugProvider() {}
    virtual BugResult getBug(int id) = 0;
    virtual BugHistoryResult getHistory(int id) = 0;
    virtual IntListResult getRelations(int id) = 0;
    virtual QString bugParamName(int paramId) = 0;
    virtual bool isBugOpened(int status)= 0;
};

//-----------------------------------------------------------------------------------------------

#endif // BUG_TYPES_H