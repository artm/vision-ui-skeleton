#pragma once

namespace QArtm {

class Throttle;

class LoggingHub : public QWidget {
    Q_OBJECT
public:
    static void setup( QMainWindow * window );

protected:
    LoggingHub( QMainWindow * mainWindow );
    virtual ~LoggingHub();
    void message(QtMsgType type, const char *msg);

    virtual bool event ( QEvent * e );
    virtual bool eventFilter ( QObject * watched, QEvent * event );

    static void dispatchMessage(QtMsgType type, const char *msg);

    QWeakPointer<QMainWindow> m_mainWindow;
    QtMsgHandler m_prevHandler;
    QString m_lastLine;
    QColor m_lastColor;
    QTextEdit * m_logView;
    QTextCursor m_logTailCursor;
    QTextCharFormat m_logFormat;
    QScopedPointer<Throttle> m_throttle;
    int m_maxLines;

    static QWeakPointer<LoggingHub> singleton;
};

}
