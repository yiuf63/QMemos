#include "IniConfig.h"

#include <qdebug.h>

IniConfig::IniConfig() :QSettings(path, QSettings::IniFormat) {
}

IniConfig::~IniConfig() {
}

QString IniConfig::path;//������   cnm  https://blog.csdn.net/sexiao0100/article/details/80254935

//��ʼ��ini�ļ��ĵ�ַ����������ڵļ�
//ini��ֵֻ�������� �ַ��� ����ֵ�������ֵ�����ڣ����Ĭ��ֵ�������Ǳ�������δ������⣬��������ĵ���
//QVariant �ܹ�ʵ�ֽ�����ֵ����ini������ʧȥ�ɶ���
void IniConfig::initialPath() {//����setPath ��������
	if (path.size() > 1) {//������Ҳû�����壬����public ��
		qDebug() << "path.size() > 1, won\'t reset.";
		return;
	}
	path = QCoreApplication::applicationDirPath() + "/data/config.ini";
	qDebug() << "set ini path:" << path;
	IniConfig s;
	auto keys = s.allKeys();
};
