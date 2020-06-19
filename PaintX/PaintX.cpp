#include "PaintX.h"

PaintX::PaintX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.paintObjectList, &QListWidget::itemDoubleClicked, [this](QListWidgetItem* item)
        {
            ui.sketchpad->removePaintObject(ui.paintObjectList->currentRow());
            ui.paintObjectList->removeItemWidget(item);
            delete item;
            update();
        });
    connect(ui.paintObjectList, &QListWidget::itemClicked, [this](QListWidgetItem* item)
        {
            ui.sketchpad->selectPaintObject(ui.paintObjectList->currentRow());
            update();
        });

    // 导出
    connect(ui.actionExport, &QAction::triggered, [this] 
        { 
            QFile file(QFileDialog::getSaveFileName(ui.sketchpad, "Export", "/", "SVG Files(*.svg);"), ui.sketchpad);        
            file.open(QIODevice::WriteOnly| QIODevice::Text);
            if (file.isOpen())
            {
                file.write(ui.sketchpad->exportSvg().toStdString().c_str());
                file.close();
            }
        });

    // 颜色按钮
    ui.foreColorBtn->setAutoFillBackground(true);
    ui.backColorBtn->setAutoFillBackground(true);
    ui.foreColorBtn->setFlat(true);
    ui.backColorBtn->setFlat(true);
    ui.foreColorBtn->setPalette(ui.sketchpad->getForeColor());
    ui.backColorBtn->setPalette(ui.sketchpad->getBackColor());

    // 颜色选择
    connect(ui.foreColorBtn, &QPushButton::clicked, [=]
        {
            auto c = QColorDialog::getColor(ui.foreColorBtn->palette().color(QPalette::Button));
            if (c.isValid())
            {
                ui.foreColorBtn->setPalette(c);
                ui.sketchpad->setForeColor(c);
            }
        });
    connect(ui.backColorBtn, &QPushButton::clicked, [=]
        {
            auto c = QColorDialog::getColor(ui.backColorBtn->palette().color(QPalette::Button));
            if (c.isValid())
            {
                ui.backColorBtn->setPalette(c);
                ui.sketchpad->setBackColor(c);
            }
        });

    // 图层创建回调
    ui.sketchpad->setPaintObjectCreateCallBack([=](PaintWidget::PaintMode mode, const thatboy::qt::PaintObject*)
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
    connect(ui.penWidthSlider, &QSlider::valueChanged, ui.sketchpad, &PaintWidget::setPenWidth);

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
    connect(ui.actionClear, &QAction::triggered, ui.sketchpad, &PaintWidget::clearPaint);
    connect(ui.actionClear, &QAction::triggered, ui.paintObjectList, &QListWidget::clear);
    connect(ui.actionArrow, &QAction::triggered, [=]
        {
            unCheckOtherActions(nullptr);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_NULL);
        });
    connect(ui.actionPenceil, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionPenceil);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_PENCIL);
        });
    connect(ui.actionLine, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionLine);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_LINE);
        });
    connect(ui.actionRectangle, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionRectangle);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_RECTANGLE);
        });
    connect(ui.actionRoundRectangle, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionRoundRectangle);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_ROUNDEDRECTANGLE);
        });
    connect(ui.actionCircle, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionCircle);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_CIRCLE);
        });
    connect(ui.actionEllipse, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionEllipse);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_ELLIPSE);
        });
    connect(ui.actionPolgon, &QAction::triggered, [=]
        {
            unCheckOtherActions(ui.actionPolgon);
            ui.sketchpad->switchPaintMode(PaintWidget::PAINT_POLYGON);
        });
 
}