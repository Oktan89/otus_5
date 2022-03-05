/**
 * @file view.h
 * @author Ruslan Zhigalenko (r.zhigalenko@mail.ru)
 * @brief Файл представления (MVC)
 * @version 0.1
 * @date 2022-03-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <iostream>
#include <memory>
#include "interface.h"

/**
 * @brief Класс Представления
 * 
 */
class View : public IView, public std::enable_shared_from_this<View>
{
    using model_type = std::shared_ptr<IModel>;
    using cont_type = std::shared_ptr<IController>;

    model_type _model;
    cont_type _cont;
public:
    /**
     * @brief Статический метод создания представления (Паттерн "Фабричный метод")
     * 
     * @param model Объект модели 
     * @param cont  Объект контроллера по умолчанию nullptr
     * @return std::shared_ptr<View> Объект представления
     */
    static std::shared_ptr<View> create(const model_type& model, const cont_type& cont = nullptr)
    {
        auto ptr = std::shared_ptr<View>(new View());
        ptr->setModel(model);
        ptr->setController(cont);
        return ptr;
    }

    /**
     * @brief Метод установки контроллера (Паттерн "Стратегия")
     * 
     * @param cont Объект контроллера
     */
    void setController(const cont_type& cont) override
    {
        _cont = cont;
    }

    /**
     * @brief Метод установки модели (Паттерн "Стратегия")
     * 
     * @param model Объект модели
     */
    void setModel(const model_type& model)
    {
        if(_model)
            _model->disconnect(shared_from_this());
        _model = model;
        _model->connect(shared_from_this());
    }

    /**
     * @brief Метод получения сообщения от модели (Паттерн "Наблюдатель")
     * 
     */
    void update() override
    {
        std::cout << "Update View" << std::endl;
        _model->draw();
    }
 
     ~View() = default;
private:

    View()
    {
        std::cout << "Create View" << std::endl;
    }
};