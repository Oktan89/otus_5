#pragma once
#include <iostream>
#include <memory>
#include "interface.h"

class View : public IView, public std::enable_shared_from_this<View>
{
    using model_type = std::shared_ptr<IModel>;
    using cont_type = std::shared_ptr<IController>;

    model_type _model;
    cont_type _cont;
public:
    static std::shared_ptr<View> create(const model_type& model, const cont_type& cont = nullptr)
    {
        auto ptr = std::shared_ptr<View>(new View());
        ptr->setModel(model);
        ptr->setController(cont);
        return ptr;
    }

    
    void setController(const cont_type& cont) override
    {
        _cont = cont;
    }

    void setModel(const model_type& model)
    {
        if(_model)
            _model->disconnect(shared_from_this());
        _model = model;
        _model->connect(shared_from_this());
    }

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