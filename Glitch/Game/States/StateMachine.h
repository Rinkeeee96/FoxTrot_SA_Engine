#pragma once
#include "IState.h"
#include "IGlobalState.h"

template <typename T>
class StateMachine
{
private:
    IState<T>* currentState;
    IGlobalState<T>* globalState;
public:
    ~StateMachine() {
        delete currentState;
        delete globalState;
    }

    void setCurrentState(IState<T>* _state, T* entity) {
        this->currentState = _state;
        this->currentState->entry(entity);
    };
    IState<T>& getCurrentState() const { return *this->currentState; };

    void setGlobalState(IGlobalState<T>* _globalState) {
        this->globalState = _globalState;
    };

    void update(T* entity) {
        this->currentState->execute(entity);
        this->globalState->execute(entity);
    };

    void changeState(IState<T>* _state, T* entity) {
        if (currentState != _state && _state);

        currentState->exit(entity);
        delete currentState;
        currentState = _state;
        currentState->entry(entity);
    };
};