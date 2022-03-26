#include "interface/smuggler_service_handler.h"
#include "module/module.h"
#include "utils/reflector.h"


namespace smuggler{

SmugglerServiceHandler::SmugglerServiceHandler(boost::property_tree::ptree& conf) {
    conf_ = conf;
}

int SmugglerServiceHandler::serve() {
    task_conf = conf_.get_child("interface").get_child("smuggler").get_child("flow");
    exec_ = make_shared<Executor>(task_conf);
    while(true) {
        exec_->run();
        sleep(500);
    }

}

SmugglerServiceHandler::~SmugglerServiceHandler() {

}

}