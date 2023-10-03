# QMemos

用于在桌面端使用快捷键快速呼出输入框，以添加内容到[memos](https://github.com/usememos/memos)的工具。

使用[QHotkeys](https://github.com/mrousavy/QHotkeys)项目创建全局快捷键。

使用时需要填写"./data/config.ini"文件，示例如下，需要填写的内容包括memos服务器地址、access token，暂时没有通过账号密码 openID使用的方式。

```ini
[memos]
url=***:5230
access_token=***

[General]
hotkey=Ctrl+Alt+Q
```

默认的快捷键是“Ctrl+Alt+Q”，也可在ini文件中修改。

我暂时对github使用还不熟悉，请大家多提意见。
