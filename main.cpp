#include <iostream>
#include <memory>
#include "lib.h"
#include "model.h"
#include "view.h"
#include "controller.h"

int main(int, char**)
{   

    std::shared_ptr<Doc> doc = std::make_shared<Doc>();
    std::shared_ptr<Controller> cont = std::make_shared<Controller>(doc);
    std::unique_ptr<View> view = std::make_unique<View>(doc, cont);


    view->createDoc();

    return 0;
}