#include "speechrecognizemanager.h"

#include <QMessageBox>

SpeechRecognizeManager*SpeechRecognizeManager::m_pUniqueObj = nullptr;

SpeechRecognizeManager::SpeechRecognizeManager(): QObject()
{
    m_pUniqueObj = nullptr;
    m_pMainWidgt = nullptr;
}

SpeechRecognizeManager::~SpeechRecognizeManager()
{
    if(m_pUniqueObj)
    {
        delete m_pUniqueObj;
        m_pUniqueObj = nullptr;
    }
}

SpeechRecognizeManager *SpeechRecognizeManager::getInstance()
{
    if (!m_pUniqueObj)
        m_pUniqueObj = new SpeechRecognizeManager;
    return m_pUniqueObj;
}

void SpeechRecognizeManager::onError(QString &str)
{
    Q_UNUSED(str);
}

void SpeechRecognizeManager::onResult(QStringList &str)
{
    QString strText;
    for (auto i=0; i<str.size(); i++)
        strText += str[i];
    if (m_pMainWidgt)
    {
        m_pMainWidgt->setText(strText);
    }
    Q_UNUSED(str);
}

void SpeechRecognizeManager::setWidget(Widget *pWidget)
{
    m_pMainWidgt = pWidget;
}
