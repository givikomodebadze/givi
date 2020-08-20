//#include "speechrecognizemanager.h"
#include "speechrecognizemanager.h"
#include "widget.h"


#include <jni.h>
#include <QDebug>
#include <QAndroidJniObject>
#include <QMessageBox>
//ამ ფუნქციის გამოძახება მოხდება Java-დან


static void onError(JNIEnv *env , jobject, jstring msg)
{
    QString qstr(env->GetStringUTFChars(msg, 0));
    //SpeechRecognizeManager::getInstance()->onError(qstr);
}

static void onResult(JNIEnv *env , jobject, jstring array)
{
    QStringList list;
    QString qstr(env->GetStringUTFChars(array, 0));
    //list = qstr.split(QLatin1Char('\n'), Qt::SkipEmptyParts);

    //for (auto i=0; i<list.size(); i++)
    //    list.push_back(list[i]);

    list.push_back(qstr);
    SpeechRecognizeManager::getInstance()->onResult(list);
}

static JNINativeMethod methods[] =
{
    {"onResult",   "(Ljava/lang/String;)V", (void*)onResult},
    {"onError",    "(Ljava/lang/String;)V", (void*)onError},
};

//გამოიძახება ავტომატურად Java-ს ჩატვირთვის მერე
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void*)
{
    JNIEnv* env;
    // დავაბრუნოთ JNIEnv მიმთითებელი.
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    jclass javaClass = env->FindClass("com/mbruel/test/NativeFunctions");
    if (!javaClass)
        return JNI_ERR;

    // დავარეგისტრიროთ ჩვენი native მეთოდები
    if (env->RegisterNatives(javaClass, methods, sizeof(methods) / sizeof(methods[0])) < 0)
    {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}

