#include "MenuManager.h"
#include "src/Image.h"


int main(int argc, const char* argv[])
{
    MenuManager menuManager;
    
    menuManager.getInstance();
        
    menuManager.showMainMenu();

    return 0;
}