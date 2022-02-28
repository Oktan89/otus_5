#pragma once
#include <memory>

struct IVisitor
{
    virtual void visit(class Dot*) = 0;
    virtual void visit(class Line*) = 0;
    virtual void visit(class File*) = 0;
    ~IVisitor() = default;
};

struct Component
{
    static std::size_t id;

    struct coordinates
    {
        double _x;
        double _y;
        coordinates(double x = 0, double y = 0) : _x(x), _y(y) {}
    };
    Component()
    {
        ++id;
    }
    virtual ~Component() = default;
    virtual std::size_t getId() const = 0;
    virtual void draw()  = 0;
    virtual void accept(IVisitor*) = 0;
};


std::size_t Component::id = 0;

struct IView
{
    virtual ~IView() = default;
    virtual void update() = 0;
};

struct IModel
{
    virtual ~IModel() = default;
    virtual void connect(IView*) = 0;
    virtual void disconnect(IView*) = 0;
    virtual void notification() const = 0;
    virtual void createDoc(const std::string& file) = 0;
    virtual void importDoc(const class File& file) = 0;
    virtual void exportDoc() = 0;
    virtual void createShape(std::shared_ptr<Component>) = 0;
    virtual void deleteShape(std::shared_ptr<Component>) = 0;
    virtual void draw() const = 0;
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



