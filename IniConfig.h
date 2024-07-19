#ifndef INICONFIG_H
#define INICONFIG_H

#include <qsettings>
#include <qcoreapplication.h>



class IniConfig : public QSettings {
	Q_OBJECT
public:
	IniConfig();
	~IniConfig();

	static void initialPath();
    static QString path;
private:

};


#endif
