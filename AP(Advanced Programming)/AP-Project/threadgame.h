#ifndef THREADGAME_H
#define THREADGAME_H

#include <QThread>
class threadgame : public QThread
{
public:
    explicit threadgame(QObject *parent = nullptr);
    void run()
    {

    }
};

#endif // THREADGAME_H
