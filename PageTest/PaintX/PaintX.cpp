#include "PaintX.h"

PaintX::PaintX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    auto sketchpadWidget = new PaintWidget(ui.sketchpad);

    // 导出
    connect(ui.actionExport, &QAction::triggered, [sketchpadWidget] 
        { 
            QFile file(QFileDialog::getSaveFileName(sketchpadWidget, "Export", "/", "SVG Files(*.svg);"), sketchpadWidget);        
            file.open(QIODevice::WriteOnly| QIODevice::Text);
            if (file.isOpen())
            {
                file.write(sketchpadWidget->exportSvg().toStdString().c_str());
                file.close();
            }
        });

    // 颜色按钮
    ui.foreColorBtn->setAutoFillBackground(true);
    ui.backColorBtn->setAutoFillBackground(true);
    ui.foreColorBtn->setFlat(true);
    ui.backColorBtn->setFlat(true);
    ui.foreColorBtn->setPalette(sketchpadWidget->getForeColor());
    ui.backColorBtn->setPalette(sketchpadWidget->getBackColor());

    // 颜色选择
    connect(ui.foreColorBtn, &QPushButton::clicked, [=]
        {
            auto c = QColorDialog::getColor(ui.foreColorBtn->palette().color(QPalette::Button));
            if (c.isValid())
            {
                ui.foreColorBtn->setPalette(c);
                sketchpadWidget->setForeColor(c);
            }
        });
    connect(ui.backColorBtn, &QPushButton::clicked, [=]
        {
            auto c = QColorDialog::getColor(ui.backColorBtn->palette().color(QPalette::Button));
            if (c.isValid())
            {
                ui.backColorBtn->setPalette(c);
                sketchpadWidget->setBackColor(c);
            }
        });

    // 图层创建回调
    sketchpadWidget->setPaintObjectCreateCallBack([=](PaintWidget::PaintMode mode, const thatboy::qt::PaintObject*)
        {
            switch (mode)
            {
            case PaintWidget::PAINT_NULL:
                break;
            case PaintWidget::PAINT_PENCIL:
                ui.paintObjectList->addItem("Penceil");
                break;
            case PaintWidget::PAINT_LINE:
                ui.paintObjectList->addItem("Line");
                break;
            case PaintWidget::PAINT_CIRCLE:
                ui.paintObjectList->addItem("Circle");
                break;
            case PaintWidget::PAINT_ELLIPSE:
                ui.paintObjectList->addItem("Ellipse");
                break;
            case PaintWidget::PAINT_RECTANGLE:
                ui.paintObjectList->addItem("Rectangle");
                break;
            case PaintWidget::PAINT_ROUNDEDRECTANGLE:
                ui.paintObjectList->addItem("RoundRectangle");
                break;
            case PaintWidget::PAINT_POLYGON:
                ui.paintObjectList->addItem("Polygon");
                break;
            default:
                break;
            }
        });

    // 画笔粗细
    ui.penWidthSlider->setMinimum(1);
    ui.penWidthSlider->setMaximum(50);
    ui.penWidthSpinBox->setMinimum(1);
    ui.penWidthSpinBox->setMaximum(50);
    ui.penWidthSlider->setSingleStep(1);
    ui.penWidthSpinBox->setSingleStep(1);
    // 同步SpinBox和Slider
    connect(ui.penWidthSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui.penWidthSlider, &QSlider::setValue);
    connect(ui.penWidthSlider, &QSlider::valueChanged, ui.penWidthSpinBox, &QSpinBox::setValue);
    connect(ui.penWidthSlider, &QSlider::valueChanged, sketchpadWidget, &PaintWidget::setPenWidth);

    // 取消其他按钮选中
    auto unCheckOtherActions = [=](QAction* showAction) {
        ui.actionPenceil->setChecked(false);
        ui.actionLine->setChecked(false);
        ui.actionRectangle->setChecked(false);
        ui.actionRoundRectangle->setChecked(false);
        ui.actionCircle->setChecked(false);
        ui.actionEllipse->setChecked(false);
        ui.actionPolgon->setChecked(false);
        if (showAction)
            showAction->setChecked(true);
    };

    // 按钮
    connect(ui.actionClear, &QAction::triggered, sketchpadWidget, &PaintWidget::clearPaint);
    connect(ui.actionClear, &QAction::triggered, ui.paintObjectList, &QListWidget::clear);
    connect(ui.actionArrow, &QAction::triggered, [=]
        {
            unCheckOtherActions(nullptr);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_NULL);
        });
    connect(ui.actionPenceil, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionPenceil);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_PENCIL);
        });
    connect(ui.actionLine, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionLine);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_LINE);
        });
    connect(ui.actionRectangle, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionRectangle);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_RECTANGLE);
        });
    connect(ui.actionRoundRectangle, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionRoundRectangle);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_ROUNDEDRECTANGLE);
        });
    connect(ui.actionCircle, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionCircle);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_CIRCLE);
        });
    connect(ui.actionEllipse, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionEllipse);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_ELLIPSE);
        });
    connect(ui.actionPolgon, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionPolgon);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_POLYGON);
        });
 
}
