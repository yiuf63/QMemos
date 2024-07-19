#include "IniConfig.h"

#include <QDebug>

IniConfig::IniConfig() :QSettings(path, QSettings::IniFormat) {
}

IniConfig::~IniConfig() {
}

QString IniConfig::path;

void IniConfig::initialPath() {
    if (path.size() > 1) {
		qDebug() << "path.size() > 1, won\'t reset.";
		return;
	}
    path = QCoreApplication::applicationDirPath() + "/data/config.ini";
	qDebug() << "set ini path:" << path;
};
