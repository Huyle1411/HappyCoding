#include "ui/userinterface.h"

int main()
{
    UserInterface ui;
    while(1) {
        ui.run();
        if(ui.isRunning() == false)
            break;
    }

    return 0;
}
