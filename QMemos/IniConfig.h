#pragma once

#include <qsettings>
#include <qcoreapplication.h>

/*ini文件格式
[General]  默认分组
lastOpen=2023-09-13T14:33:49  key如果有空格会展示成%20 最好不要用空格  windows上ini似乎大小写不敏感，最好不要有key通过大小写区分

*/

class IniConfig : public QSettings {
	Q_OBJECT
public:
	IniConfig();
	~IniConfig();

	//main里调用一次拉倒吧。。。
	static void initialPath();
private:
	static QString path;
};

//const QString IniConfig::path = QCoreApplication::applicationDirPath() + "/data";//不能这么写，QCoreApplication在编译时还不存在

/*知识点 Hint
cpp文件有没有是有区别的
static Qt类可能会有使用问题，要在cpp再声明一下
这个类不使用Q_OBJECT宏也能用，但是怕会有什么问题
C++ 特性太多太离谱了，会互相干涉
QSettings 如果一个group没有key的话，是不会出现的
*/
