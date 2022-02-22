#pragma once
#include <memory>

struct IView
{
    virtual ~IView() = default;
    virtual void update() = 0;
};

struct IModelDoc
{
    virtual ~IModelDoc() = default;
    virtual void subscription(IView*) = 0;
    virtual void unsubscribe(IView*) = 0;
    virtual void notification() const = 0;
    virtual void createDoc() = 0;
    virtual void importDoc() = 0;
    virtual void exportDoc() = 0;
};

struct IController
{
    virtual ~IController() = default;
    virtual void setModel(std::shared_ptr<IModelDoc>) = 0;
    virtual void createDoc() = 0;
    virtual void importDoc() = 0;
    virtual void exportDoc() = 0;
    virtual void createShape() = 0;
    virtual void deleteShape() = 0;
};