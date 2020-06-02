#include "PaintX.h"

PaintX::PaintX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    auto sketchpadWidget = new PaintWidget(ui.sketchpad);

    ui.foreColorBtn->setAutoFillBackground(true);
    ui.backColorBtn->setAutoFillBackground(true);

    ui.foreColorBtn->setFlat(true);
    ui.backColorBtn->setFlat(true);

    ui.foreColorBtn->setPalette(sketchpadWidget->getForeColor());
    ui.backColorBtn->setPalette(sketchpadWidget->getBackColor());

    auto unCheckActions = [=] {
        ui.actionPenceil->setChecked(false);
        ui.actionLine->setChecked(false);
        ui.actionRectangle->setChecked(false);
        ui.actionRoundRectangle->setChecked(false);
        ui.actionCircle->setChecked(false);
        ui.actionEllipse->setChecked(false);
        ui.actionPolgon->setChecked(false);
    };

    // 改变颜色
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

    // 画笔粗细
    ui.penWidthSlider->setMinimum(1);
    ui.penWidthSlider->setMaximum(50);
    ui.penWidthSpinBox->setMinimum(1);
    ui.penWidthSpinBox->setMaximum(50);
    ui.penWidthSlider->setSingleStep(1);
    ui.penWidthSpinBox->setSingleStep(1);
    connect(ui.penWidthSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui.penWidthSlider, &QSlider::setValue);
    connect(ui.penWidthSlider, &QSlider::valueChanged, ui.penWidthSpinBox, &QSpinBox::setValue);
    connect(ui.penWidthSlider, &QSlider::valueChanged, sketchpadWidget, &PaintWidget::setPenWidth);

    // 按钮

    connect(ui.actionClear, &QAction::triggered, sketchpadWidget, &PaintWidget::clearPaint);
    connect(ui.actionArrow, &QAction::triggered, [=]
        {
            unCheckActions();
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_NULL);
        });
    connect(ui.actionPenceil, &QAction::triggered, [=]
        {
            unCheckActions();
            ui.actionPenceil->setChecked(true);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_PENCIL);
        });
    connect(ui.actionLine, &QAction::triggered, [=]
        {
            unCheckActions();
            ui.actionLine->setChecked(true);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_LINE);
        });
    connect(ui.actionRectangle, &QAction::triggered, [=]
        {
            unCheckActions();
            ui.actionRectangle->setChecked(true);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_RECTANGLE);
        });
    connect(ui.actionRoundRectangle, &QAction::triggered, [=]
        {
            unCheckActions();
            ui.actionRoundRectangle->setChecked(true);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_ROUNDEDRECTANGLE);
        });
    connect(ui.actionCircle, &QAction::triggered, [=]
        {
            unCheckActions();
            ui.actionCircle->setChecked(true);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_CIRCLE);
        });
    connect(ui.actionEllipse, &QAction::triggered, [=]
        {
            unCheckActions();
            ui.actionEllipse->setChecked(true);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_ELLIPSE);
        });
    connect(ui.actionPolgon, &QAction::triggered, [=]
        {
            unCheckActions();
            ui.actionPolgon->setChecked(true);
            sketchpadWidget->switchPaintMode(PaintWidget::PAINT_POLYGON);
        });
 
}
