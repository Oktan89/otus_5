#include <iostream>
#include <memory>
#include "lib.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include "component.h"

int main(int, char**)
{   

    std::shared_ptr<Editor> model = std::make_shared<Editor>();
    std::shared_ptr<Controller> cont = std::make_shared<Controller>(model);
    std::unique_ptr<View> view = std::make_unique<View>(model, cont);

    Component::coordinates c = {3, 3};
    std::shared_ptr<Dot> sq = std::make_shared<Dot>(c);
    
    Component::coordinates d = {5, 13};
    std::shared_ptr<Line> sq2 = std::make_shared<Line>(c, d);

    std::string file = "Test.jpg";
    
    cont->createDoc(file);
    cont->createShape(sq);
    cont->createShape(sq2);
    cont->deleteShape(sq);
    
    return 0;
}