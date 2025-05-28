// very small Windows-only stub – good enough for the Engine tools
extern "C" {

    // index of next argument to process
    int   optind = 1;
    // pointer to option argument, if any
    char *optarg = nullptr;

    /*  Minimal getopt: recognises no options, always returns -1.
        Good enough because the Esenthel helper code only *checks*
        whether getopt() failed – it doesn't need real parsing here. */
    int getopt(int /*argc*/, char * const /*argv*/[], const char* /*optstring*/)
    {
        return -1;          // "no more options"
    }
}
