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
    void exportDoc() override 
    {
        _model->exportDoc();
    }
    void createShape(std::unique_ptr<Component> shape) override 
    {
        _model->createShape(std::move(shape));
    }    
    void deleteShape(std::size_t id) override 
    {
        _model->deleteShape(id);
    }
};
