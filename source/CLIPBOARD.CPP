/*
 * Clipboard.CPP
 * 19 Nov 96 by Aldo Calpini
 *
 * XS interface to the Windows Clipboard 
 * based on Registry.CPP written by Jesse Dougherty
 *
 * Version: 0.03 23 Apr 97
 *
 */

#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
// Section for the constant definitions.
#define CROAK croak
#define MAX_LENGTH 2048
#define TMPBUFSZ 1024

#define SETIV(index,value) sv_setiv(ST(index), value)
#define SETPV(index,string) sv_setpv(ST(index), string)
#define SETPVN(index, buffer, length) sv_setpvn(ST(index), (char*)buffer, length)

#define NEW(x,v,n,t)  (v = (t*)safemalloc((MEM_SIZE)((n) * sizeof(t))))
#define PERLSvIV(sv) (SvIOK(sv) ? SvIVX(sv) : sv_2iv(sv))
#define PERLSvPV(sv, lp) (SvPOK(sv) ? ((lp = SvCUR(sv)), SvPVX(sv)) : sv_2pv(sv, &lp))

#define PERLPUSHMARK(p) if (++markstack_ptr == markstack_max)	\
			markstack_grow();			\
		    *markstack_ptr = (p) - stack_base

#define PERLXPUSHs(s)	do {\
 		if (stack_max - sp < 1) {\
			    sp = stack_grow(sp, sp, 1);\
			}\
  (*++sp = (s)); } while (0)


XS(XS_Win32__Clipboard_Get) {
	HANDLE myhandle;
	
	dXSARGS;

	if(OpenClipboard(NULL)) {
		if(myhandle = GetClipboardData(CF_TEXT)) {
		    ST(0) = sv_2mortal(newSVpv((char *) myhandle, 0));
			CloseClipboard();
			XSRETURN(1);
		} else {
		    CloseClipboard();
			XSRETURN_NO;
		}

	}
}


XS(XS_Win32__Clipboard_Set) {
	HANDLE myhandle;
	
	dXSARGS;

	int i = 0;
	if(sv_isa(ST(0), "Win32::Clipboard")) {
		i = 1;
	}
	
	int leng = SvCUR(ST(i));
	HGLOBAL hGlobal;
	LPTSTR szString;
	
	if (hGlobal = GlobalAlloc(GMEM_DDESHARE, (leng+1)*sizeof(char))) {

		szString = (char *) GlobalLock(hGlobal);
		memcpy(szString, (char *) PERLSvPV(ST(i), na), leng*sizeof(char));
		szString[leng] = (char) 0;
		GlobalUnlock(hGlobal);

		if(OpenClipboard(NULL)) {
			EmptyClipboard();
			myhandle = SetClipboardData(CF_TEXT, (HANDLE) hGlobal);
			CloseClipboard();

			if(myhandle) {				
				XSRETURN_YES;
			} else {
				//printf("SetClipboardData failed (%d)\n", GetLastError());
				XSRETURN_NO;
			}
		} else {
			//printf("OpenClipboard failed (%d)\n", GetLastError());
			GlobalFree(hGlobal);
			XSRETURN_NO;
		}
	} else {
		//printf("GlobalAlloc failed (%d)\n", GetLastError());
		XSRETURN_NO;
	}
}


XS(XS_Win32__Clipboard_Empty) {
	HANDLE myhandle;
	
	dXSARGS;

	if(OpenClipboard(NULL)) {
		if(EmptyClipboard()) {
			CloseClipboard();
			XSRETURN_YES;
		} else {
			CloseClipboard();
			XSRETURN_NO;
		}
	}
}


XS(boot_Win32__Clipboard)
{
    dXSARGS;
    char* file = __FILE__;

    newXS("Win32::Clipboard::Get", XS_Win32__Clipboard_Get, file);
    newXS("Win32::Clipboard::Set", XS_Win32__Clipboard_Set, file);
	newXS("Win32::Clipboard::Empty", XS_Win32__Clipboard_Empty, file);
    ST(0) = &sv_yes;
    XSRETURN(1);
}
