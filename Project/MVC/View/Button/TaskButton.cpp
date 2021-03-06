#include "TaskButton.h"
#include "../../Controller/Manager/ColorManager.h"

TaskButton::TaskButton(QWidget *parent)
    : QWidget{parent}
    , _mainBackgroundColor(ColorManager::Instance().GetTaskButtonColors().idle)
    , _mainButtonColor(ColorManager::Instance().GetTaskButtonCloseButtonColors().idle)
    , _textColor(ColorManager::Instance().GetTaskButtonColors().color)
    , _buttonText("Button")
    , _buttonStatus(Task::TaskStatus::IDLE)
    , _isPress(false)
    , _isMouseInCloseButton(false)
    , _isFocused(false)
    , _task(nullptr)
    , _stackedIndex(-1)
{
    setFixedHeight(40);
    setMouseTracking(true);
}

TaskButton::~TaskButton()
{}

void TaskButton::SetStatus(Task::TaskStatus value)
{
    this->_buttonStatus = value;
}

Task::TaskStatus TaskButton::GetStatus()
{
    return this->_buttonStatus;
}

void TaskButton::SetText(QString &value)
{
    if (value.length() >= 24)
    {
        QString text = value.mid(0, 23);
        text.append("...");
        this->_buttonText = text;
    }
    else
        this->_buttonText = value;
}

QString& TaskButton::GetText()
{
    return this->_buttonText;
}

void TaskButton::SetFocused(bool value)
{
    this->_isFocused = value;
    if (value)
    {
        this->_mainBackgroundColor = ColorManager::Instance().GetTaskButtonColors().press;
        this->_textColor = "#FFFFFF";
    }
    else
    {
        this->_mainBackgroundColor = ColorManager::Instance().GetTaskButtonColors().idle;
        this->_textColor = ColorManager::Instance().GetTaskButtonColors().color;
    }
    update();
}

bool TaskButton::IsFocused()
{
    return this->_isFocused;
}

void TaskButton::SetTask(Task *task)
{
    this->_task = task;
}

Task* TaskButton::GetTask()
{
    return this->_task;
}

void TaskButton::SetStackedIndex(int value)
{
    this->_stackedIndex = value;
}

int TaskButton::GetStackedIndex()
{
    return this->_stackedIndex;
}

void TaskButton::enterEvent(QEvent* event)
{
    (void)event;

    if (!IsFocused())
        this->_mainBackgroundColor = ColorManager::Instance().GetTaskButtonColors().enter;
    update();
}

void TaskButton::leaveEvent(QEvent* event)
{
    (void)event;

    if (!IsFocused())
        this->_mainBackgroundColor = ColorManager::Instance().GetTaskButtonColors().idle;
    update();
}

void TaskButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (this->_isMouseInCloseButton)
        {
            emit this->closeClicked();
        }
        else
        {
            if (!IsFocused())
                this->_mainBackgroundColor = ColorManager::Instance().GetTaskButtonColors().press;
            this->_isPress = true;
            if (!IsFocused())
            {
                this->SetFocused(true);
                emit this->clicked(this);
            }
        }
        update();
    }
}

void TaskButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->_mainBackgroundColor = ColorManager::Instance().GetTaskButtonColors().enter;
        this->_isPress = false;
        update();
    }
}

void TaskButton::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    if (x >= width() - 24 && x <= width() - 10 &&
            y >= height() - 27 + static_cast<int>(this->_isPress) && y <= height() - 13 + static_cast<int>(this->_isPress))
    {
        this->_isMouseInCloseButton = true;
        this->_mainButtonColor = ColorManager::Instance().GetTaskButtonCloseButtonColors().enter;
    }
    else
    {
        this->_isMouseInCloseButton = false;
        this->_mainButtonColor = ColorManager::Instance().GetTaskButtonCloseButtonColors().idle;
    }
    update();
}

void TaskButton::paintEvent(QPaintEvent* event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(this->_mainBackgroundColor));
    painter.drawRoundedRect(QRectF(0,
                                   0 + static_cast<int>(this->_isPress),
                                   width(),
                                   height() - 1),
                            4, 4);

    // draw status idicator
    switch (this->GetStatus())
    {
    case Task::TaskStatus::IDLE:
        painter.setBrush(QColor("#7C7C7C"));
        break;
    case Task::TaskStatus::RUNNING:
        painter.setBrush(QColor("#FBBE20"));
        break;
    case Task::TaskStatus::SUCCESS:
        painter.setBrush(QColor("#189C3D"));
        break;
    case Task::TaskStatus::FAILED:
        painter.setBrush(QColor("#E11E1E"));
        break;
    case Task::TaskStatus::STARTWAIT:
        painter.setBrush(QColor("#00B2FF"));
        break;
    }
    painter.drawEllipse(QRect(10,
                              16 + static_cast<int>(this->_isPress),
                              8,
                              8));

    // draw text
    painter.setPen(QPen(QColor(this->_textColor), 1));
    painter.drawText(QPoint(32,
                            height() / 2 + 5 + static_cast<int>(this->_isPress)),
                     this->GetText());

    // draw close button
    painter.setPen(QPen(QColor(QColor(this->_mainButtonColor)), 2));
    painter.drawLine(QPointF(static_cast<qreal>(width()) - 21.5, static_cast<qreal>(height()) - 24.5 + static_cast<int>(this->_isPress)),
                     QPointF(static_cast<qreal>(width()) - 12.5, static_cast<qreal>(height()) - 15.5 + static_cast<int>(this->_isPress)));
    painter.drawLine(QPointF(static_cast<qreal>(width()) - 12.5, static_cast<qreal>(height()) - 24.5 + static_cast<int>(this->_isPress)),
                     QPointF(static_cast<qreal>(width()) - 21.5, static_cast<qreal>(height()) - 15.5 + static_cast<int>(this->_isPress)));
}
