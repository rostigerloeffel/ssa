#define NDEBUG 1

#include <iostream>
#include "util/commandline.hpp"
#include "util/signal.hpp"
#include "util/rand.hpp"
#include "frontend/solver_factory.hpp"


int main(int argc, char** argv)
{
    std::signal(SIGTERM, sls::util::termination_handler);
    std::signal(SIGINT,  sls::util::termination_handler);
    std::signal(SIGXCPU, sls::util::termination_handler);
    std::signal(SIGABRT, sls::util::termination_handler);
    std::signal(SIGTSTP, sls::util::termination_handler);
    std::signal(SIGUSR2, sls::util::termination_handler);

    sls::util::commandline cl(argv, argc);
    std::srand(cl.get("-seed", sls::util::read_seed()));

    auto solver = sls::frontend::create_solver(cl);

    auto model = solver->solve();

    if(!sls::util::is_interrupted())
    {
        std::cout << "s SATISFIABLE\n";
/*
        std::cout << "v ";
        for(auto variable : model)
            std::cout << variable << " ";
        std::cout << "0" << std::endl;
*/
        return 10;
    }
    else
    {
        std::cout << "s UNKNOWN" << std::endl;
        return 0;
    }
}
