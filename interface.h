/**
 * @file interface.h
 * @author Ruslan Zhigalenko (r.zhigalenko@mail.ru)
 * @brief Файл интер
 * @version 0.1
 * @date 2022-03-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <memory>

/**
 * @brief Интерфейс для работы с компанентами графического редактора
 * 
 */
struct IVisitor
{
    virtual void visit(class Dot*) = 0;
    virtual void visit(class Line*) = 0;
    virtual void visit(class File*) = 0;
    ~IVisitor() = default;
};

/**
 * @brief Абстрактный класс компонентов графичейского редактора
 * 
 */
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
    virtual void reIndex(std::size_t&) = 0;
    virtual void draw()  = 0;
    virtual void accept(IVisitor*) = 0;
};
///@brief статический член задающий id объекта
std::size_t Component::id = 0; 

/**
 * @brief Интерфейс контроллера
 * 
 */
struct IController
{
    virtual ~IController() = default;
    virtual void createDoc(const std::string& file) = 0;
    virtual void importDoc(class std::unique_ptr<File>) = 0;
    virtual void exportDoc() = 0;
    virtual std::size_t createShape(std::unique_ptr<Component>) = 0;
    virtual void deleteShape(std::size_t id) = 0;
};

/**
 * @brief Интерфейс модели
 * 
 */
struct IView
{
    virtual ~IView() = default;
    virtual void setController(const std::shared_ptr<IController>&) = 0;
    virtual void update() = 0;
};

/**
 * @brief Интерфейс модели
 * 
 * Интерфейс модели использует петерн Наблюдатель через методы:
 * connect, disconnect, notification
 */
struct IModel
{
    virtual ~IModel() = default;
    virtual void connect(const std::shared_ptr<IView>& view) = 0;
    virtual void disconnect(const std::shared_ptr<IView>& view) = 0;
    virtual void notification() = 0;
    virtual void createDoc(const std::string& file) = 0;
    virtual void importDoc(class std::unique_ptr<File>) = 0;
    virtual void exportDoc() = 0;
    virtual std::size_t createShape(std::unique_ptr<Component>) = 0;
    virtual void deleteShape(std::size_t id) = 0;
    virtual void draw() const = 0;
};





