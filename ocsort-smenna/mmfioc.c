/*
 *  Copyright (C) 2014 Geoff McLane 
 *  Copyright (C) 2015 Sauro Menna
 *
 *	This file is part of OCSort.
 *
 *  OCSort is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OCSort is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with OCSort.  If not, see <http://www.gnu.org/licenses/>.

*/
// MMFIO.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <stdio.h>
#include "ocsort.h"
#include "mmfioc.h"
#include "job.h"


//~~~ CWinMMFIO implementation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct mmfio_t* mmfio_constructor( void )
{
	SYSTEM_INFO sinf;
	struct mmfio_t* mmf=(struct mmfio_t *)malloc(sizeof(struct mmfio_t));
	GetSystemInfo(&sinf);
	mmf->m_dwAllocGranularity = sinf.dwAllocationGranularity;
	mmf->m_lExtendOnWriteLength = mmf->m_dwAllocGranularity;		
	mmf->m_dwBytesInView = mmf->m_dwAllocGranularity*globalJob->nMlt;
	mmf->m_nCurPos = 0;
	mmf->m_nViewBegin = 0;
	mmf->m_nSeekPos = 0;
	mmf->m_pbFile = 0;
	mmf->m_hFileMapping = INVALID_HANDLE_VALUE;
	mmf->m_cRefCount = 0;
	mmf->m_lHowManyUnmap=0;
	return mmf;
}

void mmfio_close(struct mmfio_t* mmf)
{

	if(mmf->m_pbFile)
	{
		FlushViewOfFile(mmf->m_pbFile, 0);
		UnmapViewOfFile(mmf->m_pbFile);
		mmf->m_pbFile = NULL;
	}

	if(mmf->m_hFileMapping)
	{
		//close mapping object handle
		CloseHandle(mmf->m_hFileMapping);
		mmf->m_hFileMapping = NULL;
	}

	if(mmf->m_hFile)
	{
		CloseHandle(mmf->m_hFile);
		mmf->m_hFile = NULL;
	}
}

void mmfio_destructor(struct mmfio_t* mmf)
{
	mmfio_close(mmf);
}

int mmfio_Open(const unsigned char* strfile, enum OPENFLAGS oflags, int64_t maxsize, struct mmfio_t* mmf)
{
	DWORD dwflags;
	HANDLE hFile;
	DWORD dwFileSizeHigh;
	if(mmf->m_cRefCount!=0)
	{
		memcpy(mmf->m_strErrMsg, MMF_ERR_WRONG_OPEN, sizeof(MMF_ERR_WRONG_OPEN));
		return 0;
	}
	mmf->m_cRefCount++;
	dwflags = (OPN_READWRITE == oflags)? GENERIC_READ | GENERIC_WRITE: GENERIC_READ;
	mmf->m_hFile = CreateFile((LPCSTR) strfile, dwflags,
				FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS , FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
				 
	hFile=mmf->m_hFile;

	if(INVALID_HANDLE_VALUE == hFile)
	{
		memcpy(mmf->m_strErrMsg, MMF_ERR_OPEN_FILE, sizeof(MMF_ERR_OPEN_FILE));
		fprintf(stderr,"*OCSort*S501* Cannot Open MMF file input : %s, %s\n", strfile, strerror(errno));
		exit(OC_RTC_ERROR);
		return 0;
	}

	mmf->m_qwFileSize = GetFileSize(hFile, &dwFileSizeHigh);
	mmf->m_qwFileSize += (((int64_t) dwFileSizeHigh) << 32);

	if(mmf->m_qwFileSize == 0)
	{
		CloseHandle(hFile);
		//m_strErrMsg = MMF_ERR_ZERO_BYTE_FILE;
		memcpy(mmf->m_strErrMsg, MMF_ERR_ZERO_BYTE_FILE, sizeof(MMF_ERR_ZERO_BYTE_FILE));

		return 2;
	}

	// Create the file-mapping object.
	mmf->m_dwflagsFileMapping = (OPN_READWRITE == oflags)?PAGE_READWRITE:PAGE_READONLY;
	mmf->m_hFileMapping = CreateFileMapping(hFile, NULL, mmf->m_dwflagsFileMapping, 0, 0, 0);
	if(NULL == mmf->m_hFileMapping)
	{
		if(INVALID_HANDLE_VALUE == hFile)CloseHandle(hFile);
		memcpy(mmf->m_strErrMsg, MMF_ERR_CREATEFILEMAPPING, sizeof(MMF_ERR_CREATEFILEMAPPING));
		return 0;
	}

	if(mmf->m_qwFileSize <= mmf->m_dwBytesInView)
		mmf->m_dwBytesInView = (unsigned long) mmf->m_qwFileSize;
	mmf->m_dwflagsView = oflags || FILE_MAP_READ ; //gcc ||FILE_MAP_EXECUTE ; //|| FILE_FLAG_RANDOM_ACCESS || FILE_FLAG_NO_BUFFERING;
	mmf->m_pbFile = (PBYTE)MapViewOfFileEx(mmf->m_hFileMapping, mmf->m_dwflagsView, 0, 0, (DWORD) mmf->m_dwBytesInView, NULL);
	if(NULL == mmf->m_pbFile)  
	{
		DWORD dErr = GetLastError();
		CloseHandle(mmf->m_hFileMapping);
		memcpy(mmf->m_strErrMsg, MMF_ERR_MAPVIEWOFFILE, sizeof(MMF_ERR_MAPVIEWOFFILE));
		fprintf(stderr,"*OCSort*S515* Error Open File mmfio_Open %I64ld\n");
		exit(OC_RTC_ERROR);
		return 0;
	}

	mmf->m_nCurPos = 0;
	mmf->m_nViewBegin = 0;
	return 1;
}
int mmfio_Close(struct mmfio_t* mmf)
{
	mmf->m_cRefCount--;
	mmfio_close(mmf);
	return 1;
}

void mmfio_flush()
{
}

uint64_t mmfio_GetLength(struct mmfio_t* mmf)
{
	return mmf->m_qwFileSize;
}	
LONG mmfio_GetHowManyUnMap( struct mmfio_t* mmf )
{
	return mmf->m_lHowManyUnmap;
}
uint64_t mmfio_GetPosition(struct mmfio_t* mmf)
{
	return mmf->m_nCurPos;
}

int mmfio_SeekRead(void* pBuf, int64_t lOffset, int nCountIn, struct mmfio_t* mmf)
{
	if ((lOffset < mmf->m_nViewBegin) || ((lOffset + nCountIn) >= (mmf->m_nViewBegin+mmf->m_dwBytesInView))) {
		mmf->_N = lOffset/(mmf->m_dwAllocGranularity*globalJob->nMlt);
		mmf->m_nViewBegin =  mmf->_N*(mmf->m_dwAllocGranularity*globalJob->nMlt);
		mmf->m_dwBytesInView = mmf->m_dwAllocGranularity*globalJob->nMlt; 
	
		if(mmf->m_nViewBegin + mmf->m_dwBytesInView > mmf->m_qwFileSize)
		{
			mmf->m_dwBytesInView = mmf->m_qwFileSize - mmf->m_nViewBegin;
		}
		if (mmf->m_dwBytesInView != 0 && mmf->m_pbFile) 
		{
				//Unmap old view
				UnmapViewOfFile(mmf->m_pbFile);
				//Remap with new starting address
				mmf->m_pbFile = (PBYTE)MapViewOfFile(mmf->m_hFileMapping, mmf->m_dwflagsView, 
					(DWORD) (mmf->m_nViewBegin >> 32), (DWORD) (mmf->m_nViewBegin & 0xFFFFFFFF), 
					(DWORD)mmf->m_dwBytesInView);

				mmf->m_lHowManyUnmap++;
		}
	}
	mmf->nCount = nCountIn;//int is used to detect any bug
	memmove(pBuf, mmf->m_pbFile + (lOffset-mmf->m_nViewBegin), (int) mmf->nCount);
	mmf->m_nCurPos += mmf->nCount;
	return (int)mmf->nCount;
}


INLINE int mmfio_seek(int64_t lOffset, enum SEEKPOS eseekpos, struct mmfio_t** mmf)
{
	DWORD err ;
	if(SP_CUR == eseekpos)
	{
		lOffset = (*mmf)->m_nCurPos + lOffset;
	}
	else if(SP_END == eseekpos)
	{
		if(lOffset >= 0)
		{
			memcpy((*mmf)->m_strErrMsg, MMF_ERR_WRONGSEEK, sizeof(MMF_ERR_WRONGSEEK));
			return 0;
		}
		//lOffset in RHS is -ve
		lOffset = (*mmf)->m_qwFileSize + lOffset;
	}
	//lOffset must be less than the file size
	if(!(lOffset >= 0 && lOffset < (*mmf)->m_qwFileSize))
	{
		// m_strErrMsg = MMF_ERR_INVALIDSEEK;
		memcpy((*mmf)->m_strErrMsg, MMF_ERR_INVALIDSEEK, sizeof(MMF_ERR_INVALIDSEEK));
		return 0;
	}
	
	if(!(lOffset >= (*mmf)->m_nViewBegin && (lOffset < ((*mmf)->m_nViewBegin + (*mmf)->m_dwBytesInView))))
	{
		(*mmf)->_N = (int64_t)floor((double)lOffset/(((double)(*mmf)->m_dwAllocGranularity*globalJob->nMlt)));
		(*mmf)->m_nViewBegin = (int64_t )(*mmf)->_N*((*mmf)->m_dwAllocGranularity*globalJob->nMlt);
		// Moved into constructor
		(*mmf)->m_dwBytesInView = (int64_t )(*mmf)->m_dwAllocGranularity*globalJob->nMlt; 
				//check if m_nViewBegin+m_dwBytesInView crosses filesize
		if((*mmf)->m_nViewBegin + (*mmf)->m_dwBytesInView > (*mmf)->m_qwFileSize)
		{
			(*mmf)->m_dwBytesInView = (*mmf)->m_qwFileSize - (*mmf)->m_nViewBegin;
		}
		if((*mmf)->m_dwBytesInView != 0 && (*mmf)->m_pbFile)
		{
			//Unmap old view
			UnmapViewOfFile((*mmf)->m_pbFile);
			//Remap with new starting address
			(*mmf)->m_pbFile = (PBYTE)MapViewOfFileEx((*mmf)->m_hFileMapping, (*mmf)->m_dwflagsView, 
				(DWORD) ((*mmf)->m_nViewBegin >> 32), (DWORD) ((*mmf)->m_nViewBegin & 0xFFFFFFFF), 
				(DWORD)(*mmf)->m_dwBytesInView, NULL);

			if ((*mmf)->m_pbFile == NULL) {
				err = GetLastError();
				return -1;
			}
			//-->> only debug 
			(*mmf)->m_lHowManyUnmap++;
			
		}
	}
	else 
	{ // for problem in mmf->m_nViewBegin
		(*mmf)->_N = (int64_t)floor((double)lOffset/(((double)(*mmf)->m_dwAllocGranularity*globalJob->nMlt)));
		(*mmf)->m_nViewBegin = (int64_t )(*mmf)->_N*((*mmf)->m_dwAllocGranularity*globalJob->nMlt);
		
		// Moved into constructor
		(*mmf)->m_dwBytesInView = (int64_t )(*mmf)->m_dwAllocGranularity*globalJob->nMlt; 
	}

	(*mmf)->m_nCurPos = lOffset;
	return 1;
}
INLINE int mmfio_Seek(int64_t lOffset, enum SEEKPOS eseekpos, struct mmfio_t* mmf)
{
	return mmfio_seek(lOffset, eseekpos, &mmf);

}
INLINE int mmfio_Read(unsigned char* pBuf, int nCountIn, struct mmfio_t** mmf)
{

	if(nCountIn ==0)return 0;

	if((*mmf)->m_nCurPos >= (*mmf)->m_qwFileSize)
		return 0;

	(*mmf)->nCount = nCountIn;//int is used to detect any bug

	(*mmf)->m_dwBytesInView = (int64_t) (*mmf)->m_dwAllocGranularity*globalJob->nMlt;
	
	//check if m_nViewBegin+m_dwBytesInView crosses filesize
	if((*mmf)->m_nViewBegin + (*mmf)->m_dwBytesInView > (*mmf)->m_qwFileSize)
	{
		(*mmf)->m_dwBytesInView = (*mmf)->m_qwFileSize - (*mmf)->m_nViewBegin;
	}

	(*mmf)->nDataEndPos = (*mmf)->m_nCurPos + (*mmf)->nCount;
	if((*mmf)->nDataEndPos >= (*mmf)->m_qwFileSize)
	{
		(*mmf)->nDataEndPos = (*mmf)->m_qwFileSize;
		(*mmf)->nCount = (*mmf)->m_qwFileSize - (*mmf)->m_nCurPos;
	}

	(*mmf)->nViewEndPos = (*mmf)->m_nViewBegin + (*mmf)->m_dwBytesInView;

	if((*mmf)->nDataEndPos < (*mmf)->nViewEndPos)
	{
		memmove(pBuf, (*mmf)->m_pbFile + ((*mmf)->m_nCurPos-(*mmf)->m_nViewBegin), (int) (*mmf)->nCount);
		(*mmf)->m_nCurPos += (*mmf)->nCount;
	}
	else if((*mmf)->nDataEndPos == (*mmf)->nViewEndPos)
	{
		//Last exact bytes are read from the view
		memmove(pBuf, (*mmf)->m_pbFile + ((*mmf)->m_nCurPos-(*mmf)->m_nViewBegin), (int)(*mmf)->nCount);
		(*mmf)->m_nCurPos += (*mmf)->nCount;

		mmfio_seek((*mmf)->m_nCurPos, SP_BEGIN, &(*mmf));
		(*mmf)->nViewEndPos = (*mmf)->m_nViewBegin + (*mmf)->m_dwBytesInView;
	}
	else
	{
 		(*mmf)->pBufRead = (LPBYTE)pBuf;
 		if((*mmf)->nDataEndPos > (*mmf)->nViewEndPos)
 		{
 				(*mmf)->nReadBytes = (int) ((*mmf)->nViewEndPos - (*mmf)->m_nCurPos);
  
 				if((*mmf)->nViewEndPos > (*mmf)->nDataEndPos)
 					(*mmf)->nReadBytes = (int) ((*mmf)->nDataEndPos - (*mmf)->m_nCurPos);
				memmove((*mmf)->pBufRead, (*mmf)->m_pbFile + ((*mmf)->m_nCurPos-(*mmf)->m_nViewBegin), (*mmf)->nReadBytes);
 				(*mmf)->pBufRead += (*mmf)->nReadBytes;
				(*mmf)->m_nCurPos += (*mmf)->nReadBytes;
				//seeking does view remapping if m_nCurPos crosses view boundary
				(*mmf)->m_nSeekPos = (*mmf)->m_nCurPos - (*mmf)->nViewEndPos;
				mmfio_seek((*mmf)->m_nSeekPos, SP_CUR, &(*mmf));
 				(*mmf)->nViewEndPos = (*mmf)->m_nViewBegin + (*mmf)->m_dwBytesInView;
 				(*mmf)->nReadBytes = (int) ((*mmf)->nViewEndPos - (*mmf)->m_nCurPos);
 				if((*mmf)->nViewEndPos > (*mmf)->nDataEndPos)
 					(*mmf)->nReadBytes = (int) ((*mmf)->nDataEndPos - (*mmf)->m_nCurPos);
				memmove((*mmf)->pBufRead, (*mmf)->m_pbFile + ((*mmf)->m_nCurPos-(*mmf)->m_nViewBegin), (*mmf)->nReadBytes);
 				(*mmf)->pBufRead += (*mmf)->nReadBytes;
				(*mmf)->m_nCurPos += (*mmf)->nReadBytes;
 		}
	}

	return (int)(*mmf)->nCount;
}
