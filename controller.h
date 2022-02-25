#pragma once
#include "interface.h"
#include "component.h"
// #include "view.h"
// #include "model.h"


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
    void importDoc() override {}
    void exportDoc() override {}
    void createShape(std::shared_ptr<Component> shape) override 
    {
        _model->createShape(shape);
    }
    void deleteShape(std::shared_ptr<Component> shape) override 
    {
        _model->deleteShape(shape);
    }
};
