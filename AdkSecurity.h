/***************************************************************************
 * Module:											(BuildNum:0007-20080626)
 *       AdkSecurity.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Time:
 *		2007-12-28,Nanjing
 *
 * Notes:
 *		����Windows Security��һЩ�������� ( ���ļ����ر�˵������ȫʹ��UNICODE�ַ��� )
 *
 * Functions:
 *
 *		AdkGetTextualSid					-- ���ں���(���Ƽ�ʹ��)
 *		AdkGetTextualSidEx					-- Wrapper ConvertSidToStringSid
 *		AdkGetBinarySid						-- ���ں���(���Ƽ�ʹ��)
 *		AdkGetBinarySidEx					-- Wrapper ConvertStringSidToSid
 *
 *		AdkGetSIDByAccountName				-- ��㺯��
 *		AdkGetAccountNameBySID				-- ��㺯��
 *		AdkLookupAccountSidW				-- Wrapper LookupAccountSid
 *		AdkLookupAccountNameW				-- Wrapper LookupAccountName
 *
 *		AdkGetTextualSidByAccountName		-- ֱ�����ʻ����õ��ı�SID
 *		AdkGetAccountNameByTextualSid		-- ֱ�����ı�SID�õ��ʻ���
 *
 *		AdkGetFileSecurityW(A)				-- Wrapper GetFileSecurity
 *		AdkGetFileSDOwnerSID
 *		AdkGetFileSDDacl
 *
 *		AdkEnablePrivileges
 *
 *		AdkGetACECountInACL
 *		AdkAddAccessAllowedACEToFile		-- Add an Access-Allowed ACE to a File
 *
 * TODO:
 *		AdkGetUserNameFromToKen
 *		AdkAddDenyRightsToFile
 *		AdkDelAccessRightsToFile
 *		AdkDelAccessAllowedRightsToFile		-- Del an Access-Allowed ACE to a File
 *
 */
#pragma once

#ifndef _ADK_19780810_SECURITY_H_
#define _ADK_19780810_SECURITY_H_

#ifdef __cplusplus
extern "C"{
#endif//__cplusplus

#include "Sddl.h"

/**************************************************************
 * AdkGetTextualSid
 *	
 *	NOTE: you need to Call AdkFree to free SID returned by this function
 *
 */
__inline
PWSTR AdkGetTextualSid(PSID		pSid)
{
    PSID_IDENTIFIER_AUTHORITY psia;
    DWORD					dwSubAuthorities;
    DWORD					dwSidRev = SID_REVISION;
    DWORD					dwCounter;
    DWORD					dwSidSize;
	LPWSTR					TextualSid = NULL;

	AdkASSERT((pSid));

    if (!IsValidSid(pSid)) 
	{
		return NULL;
	}

    // Get the identifier authority value from the SID.
	//
    psia = GetSidIdentifierAuthority(pSid);

    // Get the number of subauthorities in the SID.
	//
    dwSubAuthorities = *GetSidSubAuthorityCount(pSid);

    // Compute the buffer length.
    // S-SID_REVISION- + IdentifierAuthority- + subauthorities- + NULL
	//
    dwSidSize=(15 + 12 + (12 * dwSubAuthorities) + 1) * sizeof(WCHAR);

	TextualSid = (LPWSTR)AdkMalloc(dwSidSize + 2);
	if (TextualSid == NULL)
	{
		return NULL;
	}

    // Add 'S' prefix and revision number to the string.
	//
    dwSidSize = swprintf(TextualSid, L"S-%lu-", dwSidRev );

    // Add SID identifier authority to the string.
	//
    if ( (psia->Value[0] != 0) || (psia->Value[1] != 0) )
    {
        dwSidSize += swprintf(TextualSid + wcslen(TextualSid),
								L"0x%02hx%02hx%02hx%02hx%02hx%02hx",
								(USHORT)psia->Value[0],
								(USHORT)psia->Value[1],
								(USHORT)psia->Value[2],
								(USHORT)psia->Value[3],
								(USHORT)psia->Value[4],
								(USHORT)psia->Value[5]);
    }
    else
    {
        dwSidSize += swprintf(TextualSid + wcslen(TextualSid),
							 L"%lu",
							(ULONG)(psia->Value[5]      )   +
							(ULONG)(psia->Value[4] <<  8)   +
							(ULONG)(psia->Value[3] << 16)   +
							(ULONG)(psia->Value[2] << 24)   );
    }

    // Add SID subauthorities to the string.
    //
    for (dwCounter=0 ; dwCounter < dwSubAuthorities ; dwCounter++)
    {
        dwSidSize += swprintf(TextualSid + dwSidSize, L"-%lu", *GetSidSubAuthority(pSid, dwCounter) );
    }

    return TextualSid;
}

/**************************************************************
 * AdkGetBinarySid
 *	
 *	NOTE: you need to Call AdkFree to free SID returned by this function
 *
 */
__inline
PSID AdkGetBinarySid(PCWSTR lpwzTextualSid)
{
    SID_IDENTIFIER_AUTHORITY identAuthority;
    PSID		pSid = 0;
    WCHAR		buffer[1024];
    int			i;
    LPWSTR		ptr;
	LPWSTR		ptr1;
    BYTE		nByteAuthorityCount = 0;
    DWORD		dwSubAuthority[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	AdkASSERT((lpwzTextualSid));

    ZeroMemory(&identAuthority, sizeof(identAuthority));

    lstrcpyW(buffer, lpwzTextualSid);

    // S-SID_REVISION- + identifierauthority- + subauthorities- + NULL
	//

    // Skip S
	//
    if (!(ptr = wcschr(buffer, L'-')))
    {
        return pSid;
    }

    // Skip -
	//
    ptr++;

    // Skip SID_REVISION
	//
    if (!(ptr = wcschr(ptr, L'-')))
    {
        return pSid;
    }

    // Skip -
    ptr++;

    // Skip identifierauthority
	//
    if (!(ptr1 = wcschr(ptr, L'-')))
    {
        return pSid;
    }
    *ptr1= 0;

    if ((*ptr == '0') && (*(ptr+1) == 'x'))
    {
        swscanf(ptr, L"0x%02hx%02hx%02hx%02hx%02hx%02hx",
            &identAuthority.Value[0],
            &identAuthority.Value[1],
            &identAuthority.Value[2],
            &identAuthority.Value[3],
            &identAuthority.Value[4],
            &identAuthority.Value[5]);
    }
    else
    {
        DWORD value;

        swscanf(ptr, L"%lu", &value);

        identAuthority.Value[5] = (BYTE)(value & 0x000000FF);
        identAuthority.Value[4] = (BYTE)(value & 0x0000FF00) >> 8;
        identAuthority.Value[3] = (BYTE)(value & 0x00FF0000) >> 16;
        identAuthority.Value[2] = (BYTE)(value & 0xFF000000) >> 24;
    }

    // Skip -
    *ptr1 = '-';
    ptr = ptr1;
    ptr1++;

    for (i = 0; i < 8; i++)
    {
        // get subauthority
		//
        if (!(ptr = wcschr(ptr, L'-')))
        {
            break;
        }
        *ptr=0;
        ptr++;
        nByteAuthorityCount++;
    }

    for (i = 0; i < nByteAuthorityCount; i++)
    {
        // Get subauthority.
		//
		swscanf(ptr1, L"%lu", &dwSubAuthority[i]);
        ptr1 += lstrlenW(ptr1) + 1;
    }

    if (!AllocateAndInitializeSid(&identAuthority,
								  nByteAuthorityCount,
								  dwSubAuthority[0],
								  dwSubAuthority[1],
								  dwSubAuthority[2],
								  dwSubAuthority[3],
								  dwSubAuthority[4],
								  dwSubAuthority[5],
								  dwSubAuthority[6],
								  dwSubAuthority[7],
								  &pSid))
    {
        pSid = 0;
    }

    return pSid;
}

/**************************************************************
 * AdkGetTextualSidEx
 *	
 *	NOTE: you need to Call LocalFree to free StringSid
 *
 */
__inline
BOOL AdkGetTextualSidEx(PSID Sid, LPTSTR* StringSid)
{
	return ConvertSidToStringSid(Sid, StringSid);
}

/**************************************************************
 * AdkGetBinarySidEx
 *	
 *	NOTE: you need to Call LocalFree to free StringSid
 *
 */
__inline
BOOL AdkGetBinarySidEx(LPCTSTR StringSid,PSID* Sid)
{
	return ConvertStringSidToSid(StringSid, Sid);
}

/**************************************************************
 * AdkGetAccountNameBySID
 *	
 *	NOTE: you need to Call AdkFree to free AccountName returned by this function
 *
 */
__inline
LPWSTR AdkGetAccountNameBySID(LPVOID pUserSID)
{
    BOOL            bRet;
    PWCHAR          szDomain    = NULL;
    DWORD           cbDomain    = 0;
    PWCHAR          UserName    = NULL;
    DWORD           cbUserName  = 0;
    SID_NAME_USE    snuType;
	LPWSTR			TextualSid = NULL;

	AdkASSERT((pUserSID));

    do
    {
        bRet = LookupAccountSidW(NULL,
                                 pUserSID,
                                 UserName,
                                 &cbUserName,
                                 szDomain,
                                 &cbDomain,
                                 &snuType);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
			TextualSid = AdkGetTextualSid(pUserSID);
			if (TextualSid)
			{
				UserName = TextualSid;
				bRet = TRUE;
			}
			break;
        }

        UserName = (PWCHAR)AdkMalloc(cbUserName * sizeof(PWCHAR));
        if (UserName == NULL)
        {
            bRet = FALSE;
            break;
        }

        szDomain = (PWCHAR) AdkMalloc(cbDomain * sizeof(PWCHAR));
        if (!szDomain)
        {
            bRet = FALSE;        
            break;
        }

        bRet = LookupAccountSidW(NULL,
                                pUserSID,
                               UserName,
                               &cbUserName,
                               szDomain,
                               &cbDomain,
                               &snuType );

    } while (FALSE);

    if (szDomain)
    {
        AdkFree(szDomain);
    }

    if (!bRet && UserName)
    {
        AdkFree(UserName);
        UserName = NULL;
    }
    
    return UserName;
}

/**************************************************************
 * AdkGetSIDByAccountName
 *	
 *	NOTE: you need to Call AdkFree to free SID returned by this s
 *
 */
__inline
LPVOID AdkGetSIDByAccountName(LPCWSTR lpszAccountName)
{
    BOOL            bRet         = FALSE;
    PWCHAR          szDomain     = NULL;
    DWORD           cbDomain     = 0;
    DWORD           cbUserSID    = 0;
    LPVOID          pUserSID     = NULL;
    SID_NAME_USE    snuType;
    
	AdkASSERT((lpszAccountName));

    do
    {
        bRet = LookupAccountNameW(NULL,
                                lpszAccountName,
                                pUserSID,
                                &cbUserSID,
                                szDomain,
                                &cbDomain,
                                &snuType);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
           break;
        }

        pUserSID = AdkMalloc(cbUserSID);
        if (pUserSID == NULL)
        {
            bRet = FALSE;
            break;
        }

        szDomain = (PWCHAR) AdkMalloc(cbDomain * sizeof(PWCHAR));
        if (!szDomain)
        {
            bRet = FALSE;        
            break;
        }

        bRet = LookupAccountNameW(NULL,
                                 lpszAccountName,
                                 pUserSID,
                                 &cbUserSID,
                                 szDomain,
                                 &cbDomain,
                                 &snuType);

    } while(FALSE);

    if (szDomain)
    {
        AdkFree(szDomain);
    }

    if (!bRet && pUserSID)
    {
        AdkFree(pUserSID);
        pUserSID = NULL;
    }
    
    return pUserSID;
}

/**************************************************************
 * AdkLookupAccountSid
 *
 * ppwzName:
 *	if *ppName isn't null, you need call AdkFree to free buffer
 * ppwzReferencedDomainName:
 *	if *ppReferencedDomainName isn't null, you need call AdkFree to free buffer
 *
 */
__inline
BOOL AdkLookupAccountSidW(LPCWSTR		lpcwzSystemName,
						  PSID			lpSid,
						  LPWSTR*		ppwzName,
						  LPWSTR*		ppwzReferencedDomainName,
						  PSID_NAME_USE	pSnuType)
{
    BOOL            bRet;
    PWCHAR          szDomain    = NULL;
    PWCHAR          UserName    = NULL;
    DWORD           cbDomain    = 0;
    DWORD           cbUserName  = 0;

	AdkASSERT((lpSid));
	AdkASSERT((ppwzName));
	AdkASSERT((ppwzReferencedDomainName));
	AdkASSERT((pSnuType));

    do
    {
        bRet = LookupAccountSidW(lpcwzSystemName,
                                 lpSid,
                                 UserName,
                                 &cbUserName,
                                 szDomain,
                                 &cbDomain,
                                 pSnuType);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
			bRet = FALSE;
			break;
        }

        UserName = (PWCHAR)AdkMalloc(cbUserName * sizeof(PWCHAR));
        if (UserName == NULL)
        {
            bRet = FALSE;
            break;
        }

        szDomain = (PWCHAR) AdkMalloc(cbDomain * sizeof(PWCHAR));
        if (!szDomain)
        {
            bRet = FALSE;        
            break;
        }

        bRet = LookupAccountSidW(lpcwzSystemName,
                                 lpSid,
                                 UserName,
                                 &cbUserName,
                                 szDomain,
                                 &cbDomain,
                                 pSnuType);

    } while (FALSE);

	if ( ! bRet)
	{
		if (UserName)
		{
			AdkFree(UserName);
		}

		if (szDomain)
		{
			AdkFree(szDomain);
		}
	}

	*ppwzName = UserName;
	*ppwzReferencedDomainName = szDomain;

	return bRet;
}

/**************************************************************
 * AdkLookupAccountName
 *
 * ppSid:
 *	if *ppSid isn't null, you need call AdkFree to free buffer
 * ppwzReferencedDomainName
 *	if *ppwzReferencedDomainName isn't null, you need call AdkFree to free buffer
 *
 */
__inline
BOOL AdkLookupAccountNameW(LPCWSTR			lpcwzSystemName,
						   LPCWSTR			lpcwzAccountName,
						   PSID*			ppSid,
						   LPWSTR*			ppwzReferencedDomainName,
						   PSID_NAME_USE	pSnuType)
{
    BOOL            bRet         = FALSE;
    PWCHAR          szDomain     = NULL;
    LPVOID          pUserSID     = NULL;
    DWORD           cbDomain     = 0;
    DWORD           cbUserSID    = 0;

	AdkASSERT((lpcwzAccountName));
	AdkASSERT((ppSid));
	AdkASSERT((ppwzReferencedDomainName));
	AdkASSERT((pSnuType));

    do
    {
        bRet = LookupAccountNameW(lpcwzSystemName,
                                lpcwzAccountName,
                                pUserSID,
                                &cbUserSID,
                                szDomain,
                                &cbDomain,
                                pSnuType);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
			bRet = FALSE;
			break;
        }

        pUserSID = AdkMalloc(cbUserSID);
        if (pUserSID == NULL)
        {
            bRet = FALSE;
            break;
        }

        szDomain = (PWCHAR) AdkMalloc(cbDomain * sizeof(PWCHAR));
        if (!szDomain)
        {
            bRet = FALSE;        
            break;
        }

        bRet = LookupAccountNameW(lpcwzSystemName,
                                  lpcwzAccountName,
                                  pUserSID,
                                  &cbUserSID,
                                  szDomain,
                                  &cbDomain,
                                  pSnuType);

    } while(FALSE);

	if (! bRet)
	{
		if (pUserSID)
		{
			AdkFree(pUserSID);
			pUserSID = NULL;
		}

		if (szDomain)
		{
			AdkFree(szDomain);
			szDomain = NULL;
		}
	}

	*ppSid = pUserSID;
	*ppwzReferencedDomainName = szDomain;

	return bRet;
}

/**************************************************************
 * AdkGetTextualSidByAccountName
 *	
 *	NOTE: you need to Call AdkFree to free RETURN_VALUE returned by this function
 *
 */
__inline
PWSTR AdkGetTextualSidByAccountName(LPCWSTR lpwzAccountName)
{
	PVOID	pSID = AdkGetSIDByAccountName(lpwzAccountName);
	PWSTR	pTextualSid = NULL;

	if (pSID)
	{
		pTextualSid = AdkGetTextualSid(pSID);

		AdkFree(pSID);
	}

	return pTextualSid;
}

/**************************************************************
 * AdkGetAccountNameByTextualSid
 *
 *	NOTE: you need to Call AdkFree to free RETURN_VALUE returned by this function
 *
 */
__inline
PWSTR AdkGetAccountNameByTextualSid(PCWSTR	lpcwzTextualSid)
{
	BOOL	bRet;
	PSID	pSid;
	PWSTR	pAccountName;
	
	AdkASSERT((lpcwzTextualSid));

	bRet = ConvertStringSidToSidW(lpcwzTextualSid, &pSid);
	if (bRet)
	{
		pAccountName = AdkGetAccountNameBySID(pSid);
		LocalFree(pSid);
	}

	return pAccountName;
}

/**************************************************************
 * AdkGetFileSecurityA
 *	
 *	NOTE: you need to Call AdkFree to free RETURN_VALUE returned by this function
 *
 */
__inline
PSECURITY_DESCRIPTOR AdkGetFileSecurityA(IN LPCSTR				 lpcszFileName, 
										 IN SECURITY_INFORMATION RequestedInformation)
{
    BOOL                 bResult  = FALSE;
    PSECURITY_DESCRIPTOR pFileSD  = NULL;
    DWORD                cbFileSD = 0;

	AdkASSERT((lpcszFileName));

    do
    {
        GetFileSecurityA(lpcszFileName,
                         RequestedInformation,
						 pFileSD,
						 0,
						 &cbFileSD);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
            break;
        }

        pFileSD = AdkMalloc(cbFileSD);
        if (!pFileSD)
        {
            break;
        }

        bResult = GetFileSecurityA(lpcszFileName,
								  RequestedInformation,
								  pFileSD,
								  cbFileSD,
								  &cbFileSD);

    } while(FALSE);

    if (!bResult && pFileSD)
    {
        AdkFree(pFileSD);
        pFileSD = NULL;
    }

    return pFileSD;
}

/**************************************************************
 * AdkGetFileSecurityW
 *	
 *	NOTE: you need to Call AdkFree to free RETURN_VALUE returned by this function
 *
 */
__inline
PSECURITY_DESCRIPTOR AdkGetFileSecurityW(IN LPCWSTR				 lpcwzFileName, 
										 IN SECURITY_INFORMATION RequestedInformation)
{
    BOOL                 bResult  = FALSE;
    PSECURITY_DESCRIPTOR pFileSD  = NULL;
    DWORD                cbFileSD = 0;

	AdkASSERT((lpcwzFileName));

    do
    {
        GetFileSecurityW(lpcwzFileName,
                         RequestedInformation,
						 pFileSD,
						 0,
						 &cbFileSD);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
            break;
        }

        pFileSD = AdkMalloc(cbFileSD);
        if (!pFileSD)
        {
            break;
        }

        bResult = GetFileSecurityW(lpcwzFileName,
								   RequestedInformation,
								   pFileSD,
								   cbFileSD,
								   &cbFileSD);

    } while(FALSE);

    if (!bResult && pFileSD)
    {
        AdkFree(pFileSD);
        pFileSD = NULL;
    }

    return pFileSD;
}

/**************************************************************
 * AdkGetFileSDOwnerSID
 *
 * ppFileSD:
 *		After lpOwner is used, you should AdkFree *ppFileSD.
 *
 */
__inline
BOOL AdkGetFileSDOwnerSID(LPCWSTR	lpcwzFileName,
						  PSID*		ppOwner,
						  LPBOOL	lpbOwnerDefaulted,
						  PVOID*	ppFileSD)
{
    PSECURITY_DESCRIPTOR pFileSD	= NULL;
	BOOL bRet;

	AdkASSERT((lpcwzFileName));
	AdkASSERT((ppOwner));
	AdkASSERT((ppFileSD));

	pFileSD = AdkGetFileSecurityW(lpcwzFileName, OWNER_SECURITY_INFORMATION);
	if (pFileSD == NULL)
	{
		AdkPANIC(("[AdkGetFileOwner] AdkGetFileSecurityW FAILED\r\n"));
		return FALSE;
    }

	bRet = GetSecurityDescriptorOwner(pFileSD, ppOwner, lpbOwnerDefaulted); 
	if (!bRet)
	{
		AdkFree(pFileSD);
		pFileSD = NULL;
	}

	*ppFileSD = pFileSD;

	return bRet;
}

/**************************************************************
 * AdkGetFileSDDacl
 *
 * ppFileSD:
 *		After lpOwner is used, you should AdkFree *ppFileSD
 *
 */
__inline
BOOL AdkGetFileSDDacl(LPCWSTR	lpcwzFileName,
					  LPBOOL	lpbDaclPresent,
					  PACL*		ppDacl,
					  LPBOOL	lpbDaclDefaulted,
					  PVOID*	ppFileSD)

{
	BOOL				 bRet	 ;
    PSECURITY_DESCRIPTOR pFileSD = NULL;

	AdkASSERT((lpcwzFileName));
	AdkASSERT((lpbDaclPresent));
	AdkASSERT((ppDacl));
	AdkASSERT((ppFileSD));

	pFileSD = AdkGetFileSecurityW(lpcwzFileName, DACL_SECURITY_INFORMATION);
	if (pFileSD == NULL)
	{
		AdkPANIC(("[AdkGetFileOwner] AdkGetFileSecurityW FAILED\r\n"));
		return FALSE;
    }

	bRet = GetSecurityDescriptorDacl(pFileSD, lpbDaclPresent, ppDacl, lpbDaclDefaulted);

	if (!bRet)
	{
		AdkFree(pFileSD);
		pFileSD = NULL;
	}

	*ppFileSD = pFileSD;

	return bRet;
}

/**************************************************************
 * AdkGetACECountInACL
 *	
 */
__inline
BOOL AdkGetACECountInACL(PACL		pAcl,
						 PDWORD		pdwAceCount)
{
	BOOL	bRet;
    ACL_SIZE_INFORMATION AclInfo;

	AdkASSERT((pAcl));
	AdkASSERT((pdwAceCount));

    bRet = GetAclInformation(pAcl,
                            &AclInfo,
                            sizeof(ACL_SIZE_INFORMATION),
                            AclSizeInformation);

	if (bRet)
	{
		*pdwAceCount = AclInfo.AceCount;
	}

	return bRet;
}

/**************************************************************
 * AdkAddAccessAllowedACEToFile
 *
 * ����:
 *		���ļ�(��)����AccessAllowedACE
 *
 * �ѵ�: ACE��˳������
 *	  To ensure that non-inherited ACEs have precedence over inherited ACEs, place all non-inherited ACEs 
 * in a group before any inherited ACEs. This ordering ensures, for example, that a non-inherited access-denied 
 * ACE is enforced regardless of any inherited ACE that allows access. 
 *
 *	  Within the groups of non-inherited ACEs and inherited ACEs, order ACEs according to ACE type, as the following shows: 
 *		Access-denied ACEs that apply to the object itself
 *		Access-denied ACEs that apply to a subobject of the object, such as a property set or property
 *		Access-allowed ACEs that apply to the object itself
 *		Access-allowed ACEs that apply to a subobject of the object
 *
 * ����:
 * dwAceFlags:
 *	��������������־��ֵ��ע���
 *		1) INHERIT_ONLY_ACE �ñ�־˵��ACE apply to a suboject of the object
 *			��dwAceFlags����INHERIT_ONLY_ACE��־,���Ǳ����ACE�ӵ�non-inherited group�������
 *			��dwAceFlags��û��INHERIT_ONLY_ACE��־,���Ǳ����ACE�ӵ�Access-allowed ACEs���е���ǰ��
 *			
 *		2) INHERITED_ACE	�ñ�־˵�����һ��Inherited ACE, ���Ǹú�������֧�ֵ�	
 *
 */
__inline
BOOL AdkAddAccessAllowedACEToFile(LPCWSTR	lpcwzFileName, 
								  LPCWSTR	lpcwzAccountName, 
								  DWORD		dwAccessMask,
								  DWORD		dwAceFlags) 
{
	// UserSID and FileSD
	//
	LPVOID					pUserSID	= NULL;
	PSECURITY_DESCRIPTOR	pFileSD		= NULL;
	SECURITY_DESCRIPTOR		newSD		;			

	// ACL variables.
	//
	PACL					pACL	= NULL;
	BOOL					fDaclPresent;
	BOOL					fDaclDefaulted;
	ACL_SIZE_INFORMATION	AclInfo	;
	PACL					pNewACL  = NULL;
	DWORD					cbNewACL = 0;

	// Temporary ACE.
	//
	LPVOID         pTempAce			= NULL;
	UINT           CurrentAceIndex	= 0;
	UINT           newAceIndex		= 0;

	// SD_Control
	//
    SECURITY_DESCRIPTOR_CONTROL controlBitsOfInterest = 0;
    SECURITY_DESCRIPTOR_CONTROL controlBitsToSet = 0;
    SECURITY_DESCRIPTOR_CONTROL oldControlBits = 0;
	DWORD			dwRevision = 0;

	// Assume function will fail.
	//
	BOOL			fResult		 = FALSE;
	BOOL			fInheritOnly = FALSE;

	AdkASSERT((lpcwzFileName));
	AdkASSERT((lpcwzAccountName));

	// dwAceFlags ���ܺ���INHERITED_ACE
	//
	AdkASSERT(((dwAceFlags & INHERITED_ACE) == 0));

	if (dwAceFlags & INHERIT_ONLY_ACE)
	{
		fInheritOnly = TRUE;
	}

	do 
	{

		// 
		// STEP 1: Get SID of the account name specified.
		// 
		pUserSID = AdkGetSIDByAccountName(lpcwzAccountName);
		if (pUserSID == NULL)
		{
			break;
		}

		// 
		// STEP 2: Get security descriptor (SD) of the file specified.
		//
		pFileSD = AdkGetFileSecurityW(lpcwzFileName, DACL_SECURITY_INFORMATION);
		if (pFileSD == NULL)
		{
			break;
		}

		// 
		// STEP 3: Initialize new SD.
		// 
		if (!InitializeSecurityDescriptor(&newSD,SECURITY_DESCRIPTOR_REVISION)) 
		{
			AdkPANICW((L"InitializeSecurityDescriptor() failed Error %d\r\n", GetLastError()));
			break;
		}

		// 
		// STEP 4: Get DACL from the old SD.
		// 
		if (!GetSecurityDescriptorDacl(pFileSD, &fDaclPresent, &pACL, &fDaclDefaulted)) 
		{
			AdkPANICW((L"GetSecurityDescriptorDacl() failed. Error %d\n", GetLastError()));
			break;
		}

		// 
		// STEP 5: Get size information for DACL.
		// 
		AclInfo.AceCount = 0; // Assume NULL DACL.
		AclInfo.AclBytesFree = 0;
		AclInfo.AclBytesInUse = sizeof(ACL);

		if (pACL == NULL)
		{
			fDaclPresent = FALSE;
		}

		// If not NULL DACL, gather size information from DACL.
		//
		if (fDaclPresent) 
		{         
			if (!GetAclInformation(pACL, &AclInfo, sizeof(ACL_SIZE_INFORMATION), AclSizeInformation)) 
			{
				AdkPANICW((L"GetAclInformation() failed. Error %d\n", GetLastError()));
				break;
			}
		}

		// 
		// STEP 6: Compute size needed for the new ACL.
		// 
		cbNewACL = AclInfo.AclBytesInUse + sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(pUserSID) - sizeof(DWORD);

		//
		// STEP 7: Allocate memory for new ACL.
		//
		pNewACL = (PACL) AdkMalloc(cbNewACL);
		if (!pNewACL) 
		{
			AdkPANICW((L"HeapAlloc() failed. Error %d\n", GetLastError()));
			break;
		}

		// 
		// STEP 8: Initialize the new ACL.
		// 
		if (!InitializeAcl(pNewACL, cbNewACL, ACL_REVISION2)) 
		{
			AdkPANICW((L"InitializeAcl() failed. Error %d\n", GetLastError()));
			break;
		}

		// 
		// STEP 9 If DACL is present, copy all the ACEs from the old DACL
		// to the new DACL.
		// 
		// The following code assumes that the old DACL is
		// already in Windows 2000 preferred order.  To conform 
		// to the new Windows 2000 preferred order, first we will 
		// copy all non-inherited ACEs from the old DACL to the 
		// new DACL, irrespective of the ACE type.
		// 

		newAceIndex = 0;

		if (fDaclPresent && AclInfo.AceCount) 
		{
			BOOL	bError = FALSE;
			for (CurrentAceIndex = 0; CurrentAceIndex < AclInfo.AceCount; CurrentAceIndex++) 
			{
				// 
				// STEP 10: Get an ACE.
				// 
				if (!GetAce(pACL, CurrentAceIndex, &pTempAce)) 
				{
					AdkPANICW((L"GetAce() failed. Error %d\n", GetLastError()));
					bError = TRUE;
					break;
				}

				//
				// STEP 11': ���ACE���� apply to a suboject of the object,���ǳ��Խ���
				//	��ӵ�Access Allowed ACE����ǰ��
				//
				if (fInheritOnly == FALSE)
				{
					if (((ACE_HEADER *)pTempAce)->AceType & ACCESS_ALLOWED_ACE_TYPE)
					{
						break;
					}
				}

				// 
				// STEP 11: Check if it is a non-inherited ACE.
				// If it is an inherited ACE, break from the loop so
				// that the new access allowed non-inherited ACE can
				// be added in the correct position, immediately after
				// all non-inherited ACEs.
				// 
				if (((ACCESS_ALLOWED_ACE *)pTempAce)->Header.AceFlags & INHERITED_ACE)
				{
					break;
				}

				// 
				// STEP 12: Skip adding the ACE, if the SID matches
				// with the account specified, as we are going to 
				// add an access allowed ACE with a different access 
				// mask.
				// 
				if (EqualSid(pUserSID, &(((ACCESS_ALLOWED_ACE *)pTempAce)->SidStart)))
				{
					continue;
				}

				// 
				// STEP 13: Add the ACE to the new ACL.
				// 
				if (!AddAce(pNewACL, ACL_REVISION, MAXDWORD, pTempAce, ((PACE_HEADER) pTempAce)->AceSize)) 
				{
					AdkPANICW((L"AddAce() failed. Error %d\n", GetLastError()));
					bError = TRUE;
					break;
				}

				newAceIndex++;
			}

			if (bError)
			{
				break;
			}
		}

		// 
		// STEP 14: Add the access-allowed ACE to the new DACL.
		// The new ACE added here will be in the correct position,
		// immediately after all existing non-inherited ACEs.
		// 
		if (!AddAccessAllowedAceEx(pNewACL, ACL_REVISION2, dwAceFlags, dwAccessMask, pUserSID)) 
		{
			AdkPANICW((L"AddAccessAllowedAce() failed. Error %d\n", GetLastError()));
			break;
		}

		// 
		// STEP 15: To conform to the new Windows 2000 preferred order,
		// we will now copy the rest of inherited ACEs from the
		// old DACL to the new DACL.
		// 
		if (fDaclPresent && AclInfo.AceCount) 
		{
			BOOL	bError = FALSE;
			for (;  CurrentAceIndex < AclInfo.AceCount; CurrentAceIndex++) 
			{
				// 
				// STEP 16: Get an ACE.
				// 
				if (!GetAce(pACL, CurrentAceIndex, &pTempAce)) 
				{
					AdkPANICW((L"GetAce() failed. Error %d\n", GetLastError()));
					bError = TRUE;
					break;
				}

				// Step 11":�����11���ĺ���֢
				//
				if ((((ACCESS_ALLOWED_ACE *)pTempAce)->Header.AceFlags & INHERITED_ACE) == 0)
				{
					if (EqualSid(pUserSID, &(((ACCESS_ALLOWED_ACE *)pTempAce)->SidStart)))
					{
						continue;
					}
				}

				// 
				// STEP 17: Add the ACE to the new ACL.
				// 
				if (!AddAce(pNewACL, ACL_REVISION, MAXDWORD, pTempAce, ((PACE_HEADER) pTempAce)->AceSize)) 
				{
					AdkPANICW((L"AddAce() failed. Error %d\n", GetLastError()));
					bError = TRUE;
					break;
				}
			}

			if (bError)
			{
				break;
			}
		}

		// 
		// STEP 18: Set the new DACL to the new SD.
		// 
		if (!SetSecurityDescriptorDacl(&newSD, TRUE, pNewACL, FALSE)) 
		{
			AdkPANICW((L"SetSecurityDescriptorDacl() failed. Error %d\n", GetLastError()));
			break;
		}

		// 
		// STEP 19: Copy the old security descriptor control flags 
		// regarding DACL automatic inheritance for Windows 2000 
		// 

        if (!GetSecurityDescriptorControl(pFileSD, &oldControlBits, &dwRevision)) 
		{
            AdkPANICW((L"GetSecurityDescriptorControl() failed Error %d\n", GetLastError()));
            break;
		}

        if (oldControlBits & SE_DACL_AUTO_INHERITED) 
		{
			controlBitsOfInterest = SE_DACL_AUTO_INHERIT_REQ |SE_DACL_AUTO_INHERITED;
            controlBitsToSet = controlBitsOfInterest;
        }
        else if (oldControlBits & SE_DACL_PROTECTED)
		{
            controlBitsOfInterest = SE_DACL_PROTECTED;
            controlBitsToSet = controlBitsOfInterest;
        }
         
        if (controlBitsOfInterest) 
		{
            if (!SetSecurityDescriptorControl(&newSD, controlBitsOfInterest, controlBitsToSet)) \
			{
				AdkPANICW((L"SetSecurityDescriptorControl() failed Error %d\n", GetLastError()));
               break;
			}
		}

		// 
		// STEP 20: Set the new SD to the File.
		// 
		if (!SetFileSecurityW(lpcwzFileName, DACL_SECURITY_INFORMATION, &newSD)) 
		{
			AdkPANICW((L"SetFileSecurity() failed. Error %d\n", GetLastError()));
			break;
		}

		fResult = TRUE;

	}while(FALSE);

	// 
	// STEP 21: Free allocated memory
	// 
	if (pUserSID)
	{
		AdkFree(pUserSID);
	}

	if (pFileSD)
	{
		AdkFree(pFileSD);
	}

	if (pNewACL)
	{
		AdkFree(pNewACL);
	}


	return fResult;
}

/**************************************************************
 * AdkEnablePrivileges
 *
 */
INLINE
BOOL AdkEnablePrivileges(HANDLE hProcess, PCSTR pPriv)
{
	HANDLE				hToken;
	TOKEN_PRIVILEGES	tkp; 
	INT					iRet;
	BOOL				bRet = FALSE;

	xASSERT((pPriv));

	if (0 == OpenProcessToken( hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ))
	{
		xTRACEW((L"OpenProcessToken Error:%d\n", GetLastError())); 
		return FALSE;
	}

	tkp.PrivilegeCount              = 1;
	tkp.Privileges[0].Attributes    = SE_PRIVILEGE_ENABLED;
	tkp.Privileges[0].Luid.HighPart = 0;
	tkp.Privileges[0].Luid.LowPart  = 0;

	if (0 == LookupPrivilegeValue(NULL, pPriv, &tkp.Privileges[0].Luid))
	{
		xTRACEW((L"LookupPrivilegeValue Error:%d\r\n", GetLastError())); 
		return FALSE; 
	}

	do
	{
		if (0 == AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, NULL ) )
		{
			xTRACEW((L"AdjustTokenPrivileges Error:%d\r\n", GetLastError())); 
			break;
		}

		// To determine whether AdjustTokenPrivileges adjusted all of the specified privileges, call GetLastError
		//
		iRet = GetLastError();

		switch (iRet)
		{
		case ERROR_NOT_ALL_ASSIGNED: 
			xTRACEW((L"AdjustTokenPrivileges ERROR_NOT_ALL_ASSIGNED\r\n" ));
			break;

		case ERROR_SUCCESS:
			bRet = TRUE;
			break;
			
		default:    
			xTRACEW((L"AdjustTokenPrivileges Unknow Error:%d\r\n", iRet));
			break;
		}

	} while(FALSE);

	CloseHandle(hToken);

	return bRet;
}

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // _ADK_19780810_SECURITY_H_

/*
 * Revision:
 *
 *		8. ������AdkEnablePrivileges���������ӽ��̵�Ȩ��									(0008-20080808)
 *
 *		7. ������AdkGetBinarySidEx��AdkGetStringSidEx������Win2k�Ժ�ϵͳ��΢���ṩ�����ּ�㺯��ConvertStringSidToSid��ConvertSidToStringSid
 *		   AdkGetStringSid��AdkGetBinarySid�Ժ�Ͳ��Ƽ�ʹ����								(0007-20080626)
 *
 *		6. a) �޸���AdkLookupAccountNameW��AdkLookupAccountSidW����ֵ�ķ��---�����ɹ�,��ȡָ��Ĳ�����ֵ����Ϊ��ȷ��ֵ(����û�������)
 *			����ʧ��ʱ,��ȡָ��Ĳ�����ֵ����ΪNULL(ԭ������ʧ��ʱ,���޸Ĳ���ֵ),�����ĺô�����ǿ�����������幦��,�����û������,ͬʱҲ
 *			ͳһ�˷��
 *			b) ȥ����������AdkGetTextualSid��AdkGetBinarySid,��Ϊ��Win2000��ϵͳ�ṩ��ConvertSidToStringSid��ConvertStringSidToSid����
 *			�ɶ�Ӧ����
 *			c) ��MSDN�е�[Knowledge Base] HOWTO: Add an Access-Allowed ACE to a File�еĴ���������AdkAddAccessAllowedACEToFile,���޸�������
 *			�����Ĺ���
 *															(0006-20080314)
 *
 *		5. a) ����AdkGetFileSDDacl��������ȡ�ļ�(��)��DACL					
 *		   b) ��AdkGetFileSDDacl��AdkGetFileSDOwnerSID���ع�������һ��SD�ķ��ز��������ڵ�����ʹ��AdkFree�ͷ�SD
 *		������ΪOwnerSID��DACL����һ��ָ��SD��ĳһ���ָ�룬SD������֮ǰ���ͷ�
 *		   c) ����AdkGetACECountInACL����
 *		   d) ����AdkLookupAccountNameW��AdkLookupAccountSidW,��AdkGetFileSecurityWһ��������Ӧ��WinAPI������WINAPI�������ص�
 *		����Ҫ�������������յõ����ݣ���һ�����ڵõ����ȣ�,��AdkXXX�ĺ���ֱ��ʹ��һ�μȿ�
 *															(0005-20080311)
 *
 *		4. ����AdkGetFileSDOwnerSID��������ֱ��ȡ�ļ�(��)��ӵ����SID	
 *			��AdkGetFileSecurityW(A)�ĵ�һ����������Const����
 *															(0004-20080310)
 *
 *		3. ����AdkGetAccountNameByTextualSid ��㺯��		(0003-20080308)
 *		   ����AdkGetBinarySid����
 *
 *		2. ����AdkGetTextualSidByAccountName ��㺯��		(0002-20080227)
 *
 *		1. ���󲿷ֺ����ƶ���AdkUserGroup.h�ļ��У����ļ�Ŀǰ֧�ֺ�����	
 *			AdkGetTextualSid
 *			AdkGetSIDByAccountName
 *			AdkGetAccountNameBySID
 *			AdkGetFileSecurityW(A)
 *
 ****************************************************************************/


