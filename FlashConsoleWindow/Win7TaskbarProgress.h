#include <ShObjIdl.h>

// Source: http://stackoverflow.com/a/15002979/143684

class Win7TaskbarProgress  
{
public:
    Win7TaskbarProgress();
    virtual ~Win7TaskbarProgress();

    void SetProgressState(HWND hwnd, TBPFLAG flag);
    void SetProgressValue(HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ullTotal);

private:
    bool Init();
    ITaskbarList3* m_pITaskBarList3;
    bool m_bFailed;
};

Win7TaskbarProgress::Win7TaskbarProgress()
{
    m_pITaskBarList3 = NULL;
    m_bFailed = false;
}

Win7TaskbarProgress::~Win7TaskbarProgress()
{
    if (m_pITaskBarList3)   
    {
        m_pITaskBarList3->Release();
        CoUninitialize();
    }
}

void Win7TaskbarProgress::SetProgressState( HWND hwnd, TBPFLAG flag )
{
    if (Init())
        m_pITaskBarList3->SetProgressState(hwnd, flag);
}

void Win7TaskbarProgress::SetProgressValue( HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ullTotal )
{
    if (Init())
        m_pITaskBarList3->SetProgressValue(hwnd, ullCompleted, ullTotal);
}

bool Win7TaskbarProgress::Init()
{
    if (m_pITaskBarList3)
        return true;

    if (m_bFailed)
        return false;

    // Initialize COM for this thread...
    CoInitialize(NULL);

    CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void **)&m_pITaskBarList3);

    if (m_pITaskBarList3)
        return true;

    m_bFailed = true;
    CoUninitialize();
    return false;
}
