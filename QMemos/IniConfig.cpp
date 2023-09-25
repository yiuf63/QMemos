#include "IniConfig.h"

#include <qdebug.h>

IniConfig::IniConfig() :QSettings(path, QSettings::IniFormat) {
}

IniConfig::~IniConfig() {
}

QString IniConfig::path;//不能少   cnm  https://blog.csdn.net/sexiao0100/article/details/80254935

//初始化ini文件的地址，检查必须存在的键
//ini的值只能是整数 字符串 布尔值，如果键值不存在，会给默认值，而不是报错，但是未免出问题，还是在这改掉吧
//QVariant 能够实现将其他值放入ini，但会失去可读性
void IniConfig::initialPath() {//不用setPath 避免重名
	if (path.size() > 1) {//这个检查也没有意义，都是public 了
		qDebug() << "path.size() > 1, won\'t reset.";
		return;
	}
	path = QCoreApplication::applicationDirPath() + "/data/config.ini";
	qDebug() << "set ini path:" << path;
	IniConfig s;
	auto keys = s.allKeys();
};
