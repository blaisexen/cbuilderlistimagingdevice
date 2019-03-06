#include <vcl.h>
#pragma hdrstop

#include <dshow.h>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall ListVideoDevices(TComboBox* xcombobox)
{
	HRESULT hr;
	unsigned long dev_count;
	ICreateDevEnum*		dev_enum;
	IEnumMoniker*		enum_moniker;
	IMoniker*			moniker;
	IPropertyBag*		pbag;
	VARIANT name;
	CoCreateInstance(CLSID_SystemDeviceEnum, NULL,CLSCTX_INPROC,IID_ICreateDevEnum,(void**)&dev_enum);
	dev_enum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&enum_moniker,NULL);
	dev_enum->Release();
	enum_moniker->Reset();
	VariantInit(&name);
	while (enum_moniker->Next(1, &moniker, &dev_count)==S_OK)
	{
			hr = moniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pbag);
			if(SUCCEEDED(hr)) {
			pbag->Read(L"FriendlyName", &name, 0);
			xcombobox->Style = csDropDownList;
			xcombobox->Items->Add(name.bstrVal);
			xcombobox->ItemIndex = 0;
			}
	}
	VariantClear(&name);
	pbag->Release();
	moniker->Release();
	enum_moniker->Release();
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
//
ListVideoDevices(ComboBox1);
}
//---------------------------------------------------------------------------

