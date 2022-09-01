#pragma once

// these are custom interfaces, created just for understanding purposes

class ISum:public IUnknown
{
    public:
        virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract:public IUnknown
{
    public:
        virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {F13D54E4-75CF-4638-9A25-71058C07EF48}
const CLSID CLSID_SumSubtract = {0xf13d54e4, 0x75cf, 0x4638, 0x9a, 0x25, 0x71, 0x5, 0x8c, 0x7, 0xef, 0x48};

// {5D4ECED0-7432-4AFC-86B2-ABAD52D091DA}
const IID IID_ISum = {0x5d4eced0, 0x7432, 0x4afc, 0x86, 0xb2, 0xab, 0xad, 0x52, 0xd0, 0x91, 0xda};

// {A763D5B5-1422-4751-B2DE-8B13FE28E79C}
const IID IID_ISubtract = {0xa763d5b5, 0x1422, 0x4751, 0xb2, 0xde, 0x8b, 0x13, 0xfe, 0x28, 0xe7, 0x9c};




