#include "widget.h"
#include "ui_widget.h"
#include "speechrecognizemanager.h"

#if defined (Q_OS_ANDROID)
#include <QtAndroid>
#endif


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    languages.push_back("en-US");
    languages.push_back("ka-GE");
    languages.push_back("uk-UA");
    languages.push_back("da-DK");
    languages.push_back("de-DE");
    languages.push_back("cy-GB");
    languages.push_back("en-GB");
    languages.push_back("en-AU");
    languages.push_back("en-CA");
    SpeechRecognizeManager::getInstance()->setWidget(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setText(QString str)
{
    QTextCursor text_cursor = QTextCursor(ui->textEdit->document());
    text_cursor.movePosition(QTextCursor::End);
    text_cursor.insertText(str);
}

void Widget::on_pushButton_clicked()
{
    int index = ui->comboBox->currentIndex();
    if (index >=0 && index < languages.size())
    {
        QAndroidJniObject languageStr = QAndroidJniObject::fromString(languages[index]);
        QtAndroid::androidActivity().callMethod<void>("startSpeechRecogniztion",
                                                      "(Ljava/lang/String;)V",
                                                      languageStr.object<jstring>());
    }
}
