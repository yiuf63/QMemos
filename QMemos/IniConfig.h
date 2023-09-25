#pragma once

#include <qsettings>
#include <qcoreapplication.h>

/*ini�ļ���ʽ
[General]  Ĭ�Ϸ���
lastOpen=2023-09-13T14:33:49  key����пո��չʾ��%20 ��ò�Ҫ�ÿո�  windows��ini�ƺ���Сд�����У���ò�Ҫ��keyͨ����Сд����

*/

class IniConfig : public QSettings {
	Q_OBJECT
public:
	IniConfig();
	~IniConfig();

	//main�����һ�������ɡ�����
	static void initialPath();
private:
	static QString path;
};

//const QString IniConfig::path = QCoreApplication::applicationDirPath() + "/data";//������ôд��QCoreApplication�ڱ���ʱ��������

/*֪ʶ�� Hint
cpp�ļ���û�����������
static Qt����ܻ���ʹ�����⣬Ҫ��cpp������һ��
����಻ʹ��Q_OBJECT��Ҳ���ã������»���ʲô����
C++ ����̫��̫�����ˣ��ụ�����
QSettings ���һ��groupû��key�Ļ����ǲ�����ֵ�
*/
