#pragma once
#include "interface.h"
// #include "view.h"
// #include "model.h"


class Controller : public IController
{
    using model_type = std::shared_ptr<IModelDoc>;
    model_type _model;
    
public:
    
    Controller(const model_type& model) : _model(model){}

    void setModel(model_type model) override
    {
        _model = model;
    }

    void createDoc() override
    {
        _model->createDoc();
    }
    void importDoc() override {}
    void exportDoc() override {}
    void createShape() override {}
    void deleteShape() override {}
};
