#include "PopupContainer.h"

PopupContainer::PopupContainer(QWidget *parent)
    : QWidget{parent}
    , _shadowAnimation(nullptr)
    , _shadowOFFSET(0)
    , _needBackground(true)
{
    SetMemory();
    SetupModules();
}

void PopupContainer::SetMemory()
{
    if (this->_shadowAnimation == nullptr)
        this->_shadowAnimation = new QPropertyAnimation(this);
}

void PopupContainer::SetupModules()
{
    this->_shadowAnimation->setTargetObject(this);
    this->_shadowAnimation->setDuration(180);
    this->_shadowAnimation->setPropertyName("_shadowOFFSET");
    connect(this->_shadowAnimation, &QPropertyAnimation::finished, this, &PopupContainer::shadowAnimationFinished);
}

void PopupContainer::PushPopup(PopupType value)
{
    Popup* popup = nullptr;
    switch (value)
    {
    case PopupContainer::PopupType::SETTINGS:

        popup = new SettingsPopup(this);
        popup->setGeometry(width() / 2 - popup->width() / 2,
                           height() / 2 - popup->height() / 2,
                           popup->width(),
                           popup->height());
        popup->raise();
        popup->show();
        this->_popupStack.push(popup);

        break;
    case PopupContainer::PopupType::NONE:
        break;
    }
}

void PopupContainer::PopPopup()
{
    this->_popupStack.top()->hide();
    this->_popupStack.pop();
}

void PopupContainer::Update()
{
    for (auto it = this->_popupStack.begin(); it != this->_popupStack.end(); it++)
    {
        (*it)->setGeometry(width() / 2 - (*it)->width() / 2,
                           height() / 2 - (*it)->height() / 2,
                           (*it)->width(),
                           (*it)->height());
    }
}

void PopupContainer::SetShadowOFFSET(int value)
{
    this->_shadowOFFSET = value;
    update();
}

int PopupContainer::GetShadowOFFSET()
{
    return this->_shadowOFFSET;
}

void PopupContainer::shadowAnimationFinished()
{
    if (this->_shadowOFFSET == 0)
    {
        hide();
    }
}

void PopupContainer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Popup* popup = this->_popupStack.top();
        if (!(event->pos().x() >= width() / 2 - popup->width() / 2 &&
              event->pos().x() <= width() / 2 - popup->width() / 2 + popup->width() &&
              event->pos().y() >= height() / 2 - popup->height() / 2 &&
              event->pos().y() <= height() / 2 - popup->height() / 2 + popup->height()))
        {
            popup->hide();
            this->_popupStack.pop();

            if (this->_popupStack.empty())
            {
                this->StartHideAnimation();
            }
        }
    }
}

void PopupContainer::showEvent(QShowEvent *event)
{
    (void)event;

    if (this->_shadowAnimation->state() == QPropertyAnimation::Running)
    {
        this->_shadowAnimation->stop();
    }
    this->_shadowAnimation->setStartValue(0);
    this->_shadowAnimation->setEndValue(130);
    this->_shadowAnimation->start();
}

void PopupContainer::StartHideAnimation()
{
    if (this->_shadowAnimation->state() == QPropertyAnimation::Running)
    {
        this->_shadowAnimation->stop();
    }
    this->_shadowAnimation->setStartValue(130);
    this->_shadowAnimation->setEndValue(0);
    this->_shadowAnimation->start();
}

void PopupContainer::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    if (this->_needBackground)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(10, 12, 16, this->_shadowOFFSET));
        painter.drawRect(QRect(0, 0, width(), height()));
    }
}
