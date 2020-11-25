#pragma once
#include "Commands\ICommand.h"
/**
 * The CommandInvoker is associated with one or several commands. It sends a request to
 * the command.
 */
class CommandInvoker {
    /**
     * @var Command
     */
private:
    ICommand* on_start_ = nullptr;
    /**
     * @var Command
     */
    ICommand* on_finish_ = nullptr;
    /**
     * Initialize commands.
     */
    function<bool(void)> finishCondition;

    EventCallbackFn onFinishLambda;

public:
    ~CommandInvoker() {
        delete on_start_;
        delete on_finish_;
    }

    void SetOnStart(ICommand* command, function<bool(void)> _finishCondition) {
        finishCondition = _finishCondition;
        this->on_start_ = command;
    }
    void SetOnFinish(ICommand* command) {
        this->on_finish_ = command;
    }
    /**
     * The CommandInvoker does not depend on concrete command or receiver classes. The
     * CommandInvoker passes a request to a receiver indirectly, by executing a command.
     */
    void execute() {
        if (this->on_start_) {
            this->on_start_->execute();
        }
        if (this->on_finish_ && finishCondition()) {
            this->on_finish_->execute();
        }
    }
};