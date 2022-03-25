#include <cstdio>

class CSimulator;
extern int bx_begin_simulator(CSimulator* pSim, int argc, char* argv[]);
extern int bx_main_proc(int argc, char* argv[]);
//========================================================================
class CMyBochsApp
{
public:
    CMyBochsApp()
    {
        printf("  >> CMyBochsApp::CMyBochsApp() called.\n");
    }
    virtual ~CMyBochsApp()
    {
        printf("  >> CMyBochsApp::~CMyBochsApp() called.\n");
    }
public:
    virtual int MainProc(int argc, char* argv[])
    {
        printf("  >> CMyBochsApp::~MainProc(argc=%d, argv=%p) called.\n", argc, argv);
        return bx_main_proc(argc, argv);
    }
};
//========================================================================


//========================================================================
class CMyBochsCpu_t
{
public:
    CMyBochsCpu_t()
    {
        printf("  >> CMyBochsCpu_t::CMyBochsCpu_t() called.\n");
    }
    virtual ~CMyBochsCpu_t()
    {
        printf("  >> CMyBochsCpu_t::~CMyBochsCpu_t() called.\n");
    }
public:
    virtual void cpu_loop(void);
};

class CSimulator
{
public:
    class CMyBochsCpu_t* mp_cpu;
public:
    CSimulator()
        :mp_cpu(NULL)
    {
        printf("  >> CSimulator::CSimulator() called.\n");
    }
    
    CSimulator(CMyBochsCpu_t* cpu)
        :mp_cpu(cpu)
    {
        printf("  >> CSimulator::CSimulator() called.\n");
    }
    
    virtual ~CSimulator()
    {
        printf("  >> CSimulator::~CSimulator() called.\n");
        delete mp_cpu;
    }
    
public:
    virtual int begin_simulator(int argc, char* argv[])
    {
        printf("  >> CSimulator::begin_simulator(argc=%d, argv=%p) called.\n", argc, argv);
        int iret = 0;
        try
        {
            iret = bx_begin_simulator(this, argc, argv);
        }
        catch(...)
        {
            //
        }

        return iret;
    }
};

void CMyBochsCpu_t::cpu_loop(void)
{
    printf("  >> CMyBochsCpu_t::cpu_loop(tbc) called.\n");
    unsigned int iCnt = 0;
    while(1)
    {
        //???
        printf("  >> CMyBochsCpu_t::cpu_loop(tbc) step 1.\n");
        //???
        printf("  >> CMyBochsCpu_t::cpu_loop(tbc) step 2.\n");
        //???
        printf("  >> CMyBochsCpu_t::cpu_loop(tbc) step 3.\n");
        if(iCnt++>3) break;
    }
    
    return;
}

int bx_begin_simulator(CSimulator* pSim, int argc, char* argv[])
{
    printf("  >> bx_begin_simulator(argc=%d, argv=%p) called.\n", argc, argv);
    
    CMyBochsCpu_t* ptrCpu = pSim->mp_cpu;
    
    ptrCpu->cpu_loop();
    
    //exit??
    return 0;
}

int bx_main_proc(int argc, char* argv[])
{
    printf("  >> bx_main_proc(argc=%d, argv=%p) called.\n", argc, argv);
    
    CSimulator* ptrSim = new CSimulator(new CMyBochsCpu_t);
    ptrSim->begin_simulator(argc, argv);
    delete ptrSim;
    return 0;
}
//========================================================================
CMyBochsApp theApp;
int main(int argc, char* argv[])
{
    printf("  >> the mybochs app starting ... ...\n");
    int iret = 0;
    do
    {
        printf("   >> the mybochs app do_work().\n");
        CMyBochsApp* ptrApp = &theApp;
        iret = ptrApp->MainProc(argc, argv);
        
    }while(0);
    
    printf("  >> the mybochs app exit(%d).\n", iret);
    
    return 0;
}

#if 0
g++ -std=c++11 -g -Wall -O0 mybochs-la-0.1.00.cpp -o myapp_exe_0
g++ -std=c++11 -g -Wall -O0 mybochs-la-0.1.01.cpp -o myapp_exe_1
g++ -std=c++11 -g -Wall -O0 mybochs-la-0.1.02.cpp -o myapp_exe_2
#endif
