#include "LoggingHub.hpp"
#include "Pretty.hpp"
#include "Throttle.hpp"

using namespace QArtm;

LoggingHub * LoggingHub::singleton = 0;

LoggingHub::LoggingHub( QMainWindow * mainWindow )
    : m_mainWindow(mainWindow)
      , m_throttle(new Throttle(20))
      , m_maxLines(50)
{
    m_prevHandler = qInstallMsgHandler( &dispatchMessage );

    if (m_mainWindow) {
        QDockWidget * dockme = new QDockWidget("messages",m_mainWindow.data());
        dockme->setWidget(this);
        m_mainWindow.data()->statusBar()->installEventFilter(this);
        m_mainWindow.data()->addDockWidget(Qt::BottomDockWidgetArea, dockme);
        dockme->hide();

        QVBoxLayout * box = new QVBoxLayout(this);

        m_logView = new QTextEdit;
        m_logView->setReadOnly(true);
        m_logView->viewport()->installEventFilter(this);

        box->setContentsMargins(0,0,0,0);
        box->addWidget(m_logView);

        m_logTailCursor = QTextCursor(m_logView->document());
        m_logFormat.setFontFamily("Monaco");
        m_logFormat.setFontStyleHint(QFont::Monospace);
    }
}

LoggingHub::~LoggingHub()
{}

void LoggingHub::setup( QMainWindow * window )
{
    if (singleton) {
        std::cerr << "Trying to instantiate an additional LoggingHub!";
        abort();
    }
    singleton = new LoggingHub( window );
}

void LoggingHub::message(QtMsgType type, const char *raw)
{
    if (m_mainWindow) {
        QString tag;
        QColor color;
        switch(type) {
            case QtDebugMsg:
                tag = "I";
                color = Qt::black;
                break;
            case QtWarningMsg:
                tag = "W";
                color = Qt::darkYellow;
                break;
            case QtCriticalMsg:
                tag = "E";
                color = Qt::red;
                break;
            case QtFatalMsg:
                tag = "F";
                color = Qt::red;
                break;
        }

        QString message = QString("[") + Pretty::timestamp() + "] "
            + tag + ": " + raw;
        m_mainWindow.data()->statusBar()->showMessage(message);
        if (!m_lastLine.isNull()) {
            m_logFormat.setForeground( m_lastColor );
            m_logTailCursor.insertText( m_lastLine, m_logFormat );

            int tooMuch = m_logView->document()->lineCount() - m_maxLines;
            if (tooMuch > 0) {
                QTextCursor kill( m_logView->document() );
                kill.movePosition( QTextCursor::Down,
                                   QTextCursor::KeepAnchor,
                                   tooMuch );
                kill.removeSelectedText();
            }

            m_logView->ensureCursorVisible();
            m_lastLine = "\n";
        }
        m_lastLine += message;
        m_lastColor = color;
        if (m_prevHandler)
            m_prevHandler( type, qPrintable(message) );
        std::cerr << qPrintable(message) << "\n";
    }
}

void LoggingHub::dispatchMessage(QtMsgType type, const char *msg)
{
    if (singleton)
        singleton->message(type, msg);
}

bool LoggingHub::eventFilter ( QObject * watched, QEvent * event )
{
    if (m_mainWindow && watched == m_mainWindow.data()->statusBar()) {
        switch(event->type()) {
            case QEvent::MouseButtonPress:
                if (parentWidget()->isVisible())
                    parentWidget()->hide();
                else
                    parentWidget()->show();
                return true; // filter out
        }
    } else if (watched == m_logView->viewport()) {
        switch(event->type()) {
            case QEvent::Wheel:

                QWheelEvent * we = dynamic_cast<QWheelEvent*>(event);
                return
                    (we->modifiers() & Qt::ControlModifier) // ignore zoom
                    || !m_throttle->mayI();
        }
    }
    return QWidget::eventFilter(watched, event);
}
