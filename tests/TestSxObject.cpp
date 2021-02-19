#include <scixtracercpp>


int main(void)
{ 
    SxObject object;
    object.set_object_name("object name");

    if (object.get_object_name() != "object name")
    {
        return 1;
    }
    return 0;
}
