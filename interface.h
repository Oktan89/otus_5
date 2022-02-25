#pragma once
#include <memory>


struct Component
{
    struct coordinates
    {
        double _x;
        double _y;
        coordinates(double x = 0, double y = 0) : _x(x), _y(y) {}
    };
    virtual ~Component() = default;
    virtual void draw() = 0;
    virtual void createShape(std::shared_ptr<Component>){};
    virtual void deleteShape(std::shared_ptr<Component>){};
};

struct IView
{
    virtual ~IView() = default;
    //virtual void setController(std::shared_ptr<IModel>) = 0;
    virtual void update() = 0;
};

struct IModel
{
    virtual ~IModel() = default;
    virtual void connect(IView*) = 0;
    virtual void disconnect(IView*) = 0;
    virtual void notification() const = 0;
    virtual void createDoc(const std::string& file) = 0;
    virtual void importDoc() = 0;
    virtual void exportDoc() = 0;
    virtual void createShape(std::shared_ptr<Component>) = 0;
    virtual void deleteShape(std::shared_ptr<Component>) = 0;
    virtual void draw() = 0;
};

struct IController
{
    virtual ~IController() = default;
    virtual void createDoc(const std::string& file) = 0;
    virtual void importDoc() = 0;
    virtual void exportDoc() = 0;
    virtual void createShape(std::shared_ptr<Component>) = 0;
    virtual void deleteShape(std::shared_ptr<Component>) = 0;
};



