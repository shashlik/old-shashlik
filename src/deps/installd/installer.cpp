#include <unistd.h>
#include <sys/types.h>

#include <QStringList>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QFile>

extern "C" {
int install(const char *pkgname, uid_t uid, gid_t gid, const char *seinfo);
}

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    app.setApplicationName("shashlik-installer");
    app.setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Android application installer tool");
    QCommandLineOption helpArgument =  parser.addHelpOption();
    QCommandLineOption versionArgument = parser.addVersionOption();
    parser.addPositionalArgument("apkfile", "Install the passed apk file.");
    parser.process(app);

    QStringList apkfile = parser.positionalArguments();
    if(apkfile.length() > 0 && QFile::exists(apkfile.at(0))) {
        install(apkfile.at(0).toLatin1(), getuid(), getuid(), "");
    }

    return app.exec();
}
