#include "NotepadXWindow.h"

NotepadXWindow::NotepadXWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 内容同步
    connect(ui.markdownEdit, &QPlainTextEdit::textChanged, [this] { ui.markdownPreview->setMarkdown(ui.markdownEdit->toPlainText()); });

	// 查找
	connect(ui.actionFind, &QAction::triggered, [this] {
		if (ui.markdownEdit->textCursor().hasSelection())
		{
			findDialog.ui.lineEdit->setText(ui.markdownEdit->textCursor().selectedText());
		}
		findDialog.show();
		});

	// 查找下一个
	connect(findDialog.ui.pushButton, &QPushButton::clicked, [this] {
		QString findText = findDialog.ui.lineEdit->text();
		if (ui.markdownEdit->find(findText))
		{
			QPalette palette = ui.markdownEdit->palette();
			palette.setColor(QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
			ui.markdownEdit->setPalette(palette);
		}
		else
		{
			QMessageBox::information(this, "NotepadX", "没有查找到内容", QMessageBox::Ok);
		}
		;
		});

	// 加粗
	connect(ui.actionBold, &QAction::triggered, [this]
		{
			if (ui.markdownEdit->textCursor().hasSelection())
			{
				auto selectedText = ui.markdownEdit->textCursor().selectedText();
				ui.markdownEdit->textCursor().insertText("**" + selectedText + "**");
			}
			
		});

	// 斜体
	connect(ui.actionItalic, &QAction::triggered, [this]
		{
			if (ui.markdownEdit->textCursor().hasSelection())
			{
				auto selectedText = ui.markdownEdit->textCursor().selectedText();
				ui.markdownEdit->textCursor().insertText("*" + selectedText + "*");
			}
		});

	// 下划线
	connect(ui.actionUnderline, &QAction::triggered, [this]
		{
			if (ui.markdownEdit->textCursor().hasSelection())
			{
				auto selectedText = ui.markdownEdit->textCursor().selectedText();
				ui.markdownEdit->textCursor().insertText("<u>" + selectedText + "</u>");
			}
		});

	// 删除线
	connect(ui.actionStrikeout, &QAction::triggered, [this]
		{
			if (ui.markdownEdit->textCursor().hasSelection())
			{
				auto selectedText = ui.markdownEdit->textCursor().selectedText();
				ui.markdownEdit->textCursor().insertText("~~" + selectedText + "~~");
			}
		});

	// 颜色
	connect(ui.actionColor, &QAction::triggered, [this]
		{
			if (ui.markdownEdit->textCursor().hasSelection())
			{
				auto selectedText = ui.markdownEdit->textCursor().selectedText();

				auto color = QColorDialog::getColor(Qt::black, this);
				if (color.isValid())
				{
					;
					selectedText = "<font color=" + color.name() + ">" + selectedText + "</font>";
					ui.markdownEdit->textCursor().insertText(selectedText);
				}
			}
		});

	// 字体
	connect(ui.actionFont, &QAction::triggered, [this]
		{
			if (ui.markdownEdit->textCursor().hasSelection())
			{
				auto selectedText = ui.markdownEdit->textCursor().selectedText();

				bool ok;
				auto font = QFontDialog::getFont(&ok, this);
				if (ok)
				{
					selectedText = "<font face=\"" + font.family() + "\" size=" + QString::number(font.pointSize()) + ">" + selectedText + "</font>";
					ui.markdownEdit->textCursor().insertText(selectedText);
				}
			}
		});

	// 打开
	connect(ui.actionOpen, &QAction::triggered, [this]
		{
			auto fileName = QFileDialog::getOpenFileName(this, "打开文件", "/", "Markdown文档(*.md)");
			QFile file(fileName);
			if (file.exists())
			{
				file.open(QIODevice::ReadOnly | QIODevice::Text);
				if (file.isReadable())
				{
					workingFileName = fileName;
					ui.markdownEdit->setPlainText(QString(file.readAll()));
				}
				file.close();
			}
		});

	// 保存
	connect(ui.actionSave, &QAction::triggered, [this]
		{
			if (workingFileName.isEmpty())
				workingFileName = QFileDialog::getSaveFileName(this, "保存文件", "/", "Markdown文档(*.md)");
			QFile file(workingFileName);
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			if (file.isWritable())
				file.write(ui.markdownEdit->toPlainText().toUtf8());
			file.close();
		});

	// 保存为
	connect(ui.actionSaveAs, &QAction::triggered, [this]
		{
			workingFileName = QFileDialog::getSaveFileName(this, "保存为", "/", "Markdown文档(*.md)");
			QFile file(workingFileName);
			file.open(QIODevice::WriteOnly | QIODevice::Text);
			if (file.isWritable())
				file.write(ui.markdownEdit->toPlainText().toUtf8());
			file.close();
		});

	// 关于
	connect(ui.actionAbout, &QAction::triggered, &about, &About::exec);

	// 打印 TODO: 未完成
	connect(ui.actionPrint, &QAction::triggered, [this]
		{
			QPrinter printer;
			QPrintDialog* dialog = new QPrintDialog(&printer, this);
			dialog->setWindowTitle("打印");
			if (ui.markdownPreview->textCursor().hasSelection())
				dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
			if (dialog->exec() != QDialog::Accepted)
				return;
		});

	// TODO: 左右滚动条同步


	// 填充初始内容
	ui.markdownEdit->setPlainText(R"MARKDOWN(# 标题1
## 标题2
### 标题3
#### 标题4
##### 标题5
###### 标题6
---

# 2. 列表
* 圆圈
- 实心圆
+ 方块
---

# 3. 嵌套列表
1. 第一项：
    - 第一项嵌套的第一个元素
    - 第一项嵌套的第二个元素
1. 第二项：
    - 第二项嵌套的第一个元素
    - 第二项嵌套的第二个元素
---

# 4. 任务列表
- [ ] task1
- [x] task2
- [x] task3
---

# 5. 文字格式
**粗体文本**
_斜体文本_
_**粗斜体文本**_
~~删除线文本~~
<u>带下划线文本</u>
<font face="微软雅黑" >微软雅黑字体</font>
<font size=1 >1号字</font>
<font size=2 >2号字</font>
<font color=#FF0000 >红色</font>
<font color=#008000 >绿色</font>
<font color=#0000FF >蓝色</font>
`code`
```cpp
#include <QApplication>
#include "NotepadXWindow.h"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	NotepadXWindow mainWindow;

	mainWindow.show();
	return a.exec();
}
```

---

# 6. 分隔线
---

# 7. 表格
|  表头1   | 表头2  |这里是右对齐|这里是左对齐|
|  ----  | :----:  |---:|:---|
| 单元格1  | 单元格2 |3|-3|
| 单元格4  | 单元格5 |6|-6|


)MARKDOWN");
}