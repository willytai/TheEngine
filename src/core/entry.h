#ifndef __ENTRY_H__
#define __ENTRY_H__

#ifndef DEFAULT_CREATE
    #pragma message("compiling engine without a defulat appCreate function, make sure you've defined your own!")
#endif

int main(int argc, char *argv[])
{
    engine7414::App* app = engine7414::appCreate(argc, argv);
    app->run();
    delete app;
    return 0;
}

#endif /* __ENTRY_H__ */
