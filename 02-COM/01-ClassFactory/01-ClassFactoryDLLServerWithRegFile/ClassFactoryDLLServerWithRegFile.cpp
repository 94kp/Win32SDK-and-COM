#include <windows.h>
#include "ClassFactoryDLLServerWithRegFile.h"

// Co-class (COM class or concrete class -> a class that cannot be a base class, but this class can be derived from another class)

class CSumSubtract : public ISum, ISubtract
{
	private:
		long m_cRef;
	public:
		// constructor
		CSumSubtract(void);
		
		// destructor
		~CSumSubtract(void);
		
		// iUnkown Methods
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		
		// ISum Method
		HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

		// ISubtract Method
		HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

// ClassFactory Class

class CSumSubtractClassFactory : public IClassFactory
{
	private:
		LONG m_cRef;
	public:
		// constructor
		CSumSubtractClassFactory(void);

		// destructor
		~CSumSubtractClassFactory(void);

		// iUnkown Methods
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);

		// IClassFactory Methods
		HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

// isum - rajesh pradhan isub - vidhate csumsubtract - patil/kulkarni /// client only sees csum and csub - binary encapsulation

// global variables

LONG glNumberOfActiveComponents;
LONG glNumberOfServerLocks;

///////////////////////////////////////////////////////////////////////////////////

// DLLmain code to be pasted here as it is - including comments and all (From any DLL)

///////////////////////////////////////////////////////////////////////////////////

// DLL Main

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
{
	// code
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
return(TRUE);
}

// CSumSubtract implementation

// Constructor

CSumSubtract::CSumSubtract(void)
{
	// code
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);

}


// Destructor

CSumSubtract::~CSumSubtract(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// IUnknown Implementation

HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	// code
	// in COM nothing is as important as IUnknown's Queryinterface

	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return S_OK;
}

ULONG CSumSubtract::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);

	return m_cRef;
}

ULONG CSumSubtract::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		// delete this
		delete(this);
		return 0;
	}
	else
	{
		return m_cRef;
	}
}

// ISum Implementation

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	// code
	*pSum = num1 + num2;

	return S_OK;
}


HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	// code
	*pSubtract = num1 - num2;

	return S_OK;
}

// CSumSubtract ClassFactory Implementation

// constructor

CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	// code
	m_cRef = 1;
}

// destructor

CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// code
}

// IUnknown method implementation

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);

	}
	else if(riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return S_OK;

}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);

	return m_cRef;
}

ULONG CSumSubtractClassFactory::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		// delete this
		delete(this);
		return 0;
	}
	else
	{
		return m_cRef;
	}
}

// IClassFactory Method Implementation

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	// code
	if (pUnkOuter != NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}
	
	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);

	pCSumSubtract->Release();

	return hr;
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	// code
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}

	return S_OK;
}

// Exportable COM DLL Methods

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// variable declarations
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);

	pCSumSubtractClassFactory->Release();

	return hr;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return S_OK;
	else
		return S_FALSE;
}





