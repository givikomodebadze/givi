#pragma once

#include "widget.h"

#include <QObject>

class SpeechRecognizeManager : public QObject
{
    //Q_OBJECT
public:
    SpeechRecognizeManager();
    ~SpeechRecognizeManager();

    static SpeechRecognizeManager* getInstance();

    void onError(QString &str);
    void onResult(QStringList &str);
    void setWidget(Widget* pWidget);
protected:
    Widget* m_pMainWidgt;
    static SpeechRecognizeManager* m_pUniqueObj;
};
