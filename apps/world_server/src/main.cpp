#include "WorldServer.h"
#include "stdafx.h"

int main(){
    InitPre();
    if(Init())
    {
        while(Update())
            Draw();
        Shut();
    }
    return 0;
}
