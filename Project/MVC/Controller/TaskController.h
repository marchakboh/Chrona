#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include "../Model/Task.h"
#include "../View/Button/TaskButton.h"

#include <QObject>
#include <QDomDocument>
#include <QDomElement>

class TaskController : public QObject
{
    Q_OBJECT
public:
    static TaskController& Instance();

    std::pair<Task*, TaskButton*> LoadTask(QDomElement&);
    TaskButton* AddTask(Task*);
    TaskButton* GetActiveTaskButton();
    void AddPipelineToActiveTask(Pipeline*);

private:
    explicit TaskController(QObject *parent = nullptr);
    TaskController(const TaskController&) = delete;
    TaskController& operator=(const TaskController&) = delete;

private slots:
    void TaskButtonClicked(TaskButton*);

private:
    QList<std::pair<Task*, TaskButton*>> _tasks;
};

#endif // TASKCONTROLLER_H
