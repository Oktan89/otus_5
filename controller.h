/**
 * @file controller.h

 * @author Ruslan Zhigalenko (r.zhigalenko@mail.ru)
 * @brief Файл контроллера (MVC)
 * @version 0.1
 * @date 2022-03-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "interface.h"
#include "component.h"

/**
 * @brief Класс Контроллер
 * 
 */
class Controller : public IController
{
    using Imodel_type = std::shared_ptr<IModel>;
    Imodel_type _model;
    
public:
    
    Controller(Imodel_type model) : _model(model){}

    void createDoc(const std::string& file) override
    {
        _model->createDoc(file);
    }
    void importDoc(std::unique_ptr<File> file) override 
    {
        _model->importDoc(std::move(file));
    }
    void exportDoc() override 
    {
        _model->exportDoc();
    }
    std::size_t createShape(std::unique_ptr<Component> shape) override 
    {
        return _model->createShape(std::move(shape));
    }    
    void deleteShape(std::size_t id) override 
    {
        _model->deleteShape(id);
    }
};

