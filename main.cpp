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

    std::shared_ptr<Dot> dt = std::make_shared<Dot>(5, 6);
    std::shared_ptr<Line> ln = std::make_shared<Line>(Dot{10, 4}, Dot{2, 4});
    std::shared_ptr<Line> ln2 = std::make_shared<Line>(Dot{100, 44}, Dot{20, 64});

    std::string file = "Test.jpg";
    
    cont->createDoc(file);
    cont->createShape(dt);
    cont->createShape(ln);
    cont->createShape(ln2);
    cont->deleteShape(dt);
    cont->exportDoc();
    return 0;
}