#include "IpFinder.h"

IpFinder::IpFinder()
{
}

IpFinder::IpFinder(const char *pszFileName)
{
	this->Open(pszFileName);
}

bool IpFinder::Open(const char *pszFileName)
{
	m_fpIpDataFile = fopen(pszFileName, "rb");
	if (!m_fpIpDataFile) {
		return false;
	}

	// IPͷ������ʮ������4�ֽ�ƫ�������ɣ��ֱ�Ϊ������ʼ������������
	m_indexStart = this->GetValue4(0);
	m_indexEnd = this->GetValue4(4);
	return true;
}

IpFinder::~IpFinder()
{
	fclose(m_fpIpDataFile);
}


unsigned long IpFinder::IpString2IpValue(const char *pszIp) const
{
	if (!this->IsRightIpString(pszIp)) {
		return 0;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int nNum = 0;			// ÿ������ֵ
	const char *pBeg = pszIp;
	const char *pPos = NULL;
	unsigned long ulIp = 0; // ����IP��ֵ
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	pPos = strchr(pszIp, '.');
	while (pPos != NULL) {
		nNum = atoi(pBeg);
		ulIp += nNum;
		ulIp *= 0x100;
		pBeg = pPos + 1;
		pPos = strchr(pBeg, '.');
	}

	nNum = atoi(pBeg);
	ulIp += nNum;
	return ulIp;
}

void IpFinder::IpValue2IpString(unsigned long ipValue,
								 char *pszIpAddress,
								 int nMaxCount) const
{
	if (!pszIpAddress) {
		return;
	}

	_snprintf(pszIpAddress, nMaxCount, "%d.%d.%d.%d", (ipValue & 0xFF000000) >> 24,
		(ipValue & 0x00FF0000) >> 16, (ipValue & 0x0000FF00) >> 8,ipValue & 0x000000FF);
	pszIpAddress[nMaxCount - 1] = 0;
}

unsigned long IpFinder::SearchIp(unsigned long ipValue,
								  unsigned long indexStart,
								  unsigned long indexEnd) const
{
	if (!m_fpIpDataFile) {
		return 0;
	}

	if (0 == indexStart) {
		indexStart = m_indexStart;
	}

	if (0 == indexEnd) {
		indexEnd = m_indexEnd;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	unsigned long indexLeft = indexStart;
	unsigned long indexRight = indexEnd;

	// �ȳ������Ϊ�˱�֤midָ��һ��������ȷ������
	unsigned long indexMid = (indexRight - indexLeft) / INDEX_LENGTH / 2 * INDEX_LENGTH + indexLeft;

	// ��ʼIp��ַ(��172.23.0.0),����Ip��¼�е�Ip��ַ(��172.23.255.255)����һ��Ip��Χ���������Χ�ڵ�Ip��������������������ȡ���ҡ�����
	unsigned long ulIpHeader = 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	do
	{
		ulIpHeader = this->GetValue4(indexMid);
		if (ipValue < ulIpHeader) {
			indexRight = indexMid;
			indexMid = (indexRight - indexLeft) /	INDEX_LENGTH / 2 * INDEX_LENGTH + indexLeft;
		} else {
			indexLeft = indexMid;
			indexMid = (indexRight - indexLeft) /	INDEX_LENGTH / 2 * INDEX_LENGTH + indexLeft;
		}
	} while (indexLeft < indexMid);			// ע���Ǹ���mid�������ж�

	// ֻҪ���Ϸ�Χ�Ϳ��ԣ�����Ҫ��ȫ���
	return indexMid;
}


unsigned long IpFinder::SearchIp(const char *pszIp,
								  unsigned long indexStart,
								  unsigned long indexEnd) const
{
	if (!this->IsRightIpString(pszIp)) {
		return 0;
	}
	return this->SearchIp(this->IpString2IpValue(pszIp), indexStart,
		indexEnd);
}

unsigned long IpFinder::GetValue3(unsigned long indexStart) const
{
	if (!m_fpIpDataFile) {
		return 0;
	}

	//~~~~~~~~~~~~~~~~~~~~
	int nVal[3];
	unsigned long ulValue = 0;
	//~~~~~~~~~~~~~~~~~~~~

	fseek(m_fpIpDataFile, indexStart, SEEK_SET);
	for (int i = 0; i < 3; i++) {

		// ���˸�λ��һ�ζ�ȡһ���ַ�
		nVal[i] = fgetc(m_fpIpDataFile) & 0x000000FF;
	}

	for (int j = 2; j >= 0; --j) {

		// ��Ϊ��ȡ���16�����ַ�������
		ulValue = ulValue * 0x100 + nVal[j];
	}
	return ulValue;
}


unsigned long IpFinder::GetValue4(unsigned long indexStart) const
{
	if (!m_fpIpDataFile) {
		return 0;
	}

	//~~~~~~~~~~~~~~~~~~~~
	int nVal[4];
	unsigned long ulValue = 0;
	//~~~~~~~~~~~~~~~~~~~~

	fseek(m_fpIpDataFile, indexStart, SEEK_SET);
	for (int i = 0; i < 4; i++) {

		// ���˸�λ��һ�ζ�ȡһ���ַ�
		nVal[i] = fgetc(m_fpIpDataFile) & 0x000000FF;
	}

	for (int j = 3; j >= 0; --j) {

		// ��Ϊ��ȡ���16�����ַ�������
		ulValue = ulValue * 0x100 + nVal[j];
	}
	return ulValue;
}


unsigned long IpFinder::GetString(std::string &str, unsigned long indexStart) const
{
	if (!m_fpIpDataFile) {
		return 0;
	}

	str.erase(0, str.size());

	fseek(m_fpIpDataFile, indexStart, SEEK_SET);
	//~~~~~~~~~~~~~~~~~~~~~~
	int nChar = fgetc(m_fpIpDataFile);
	unsigned long ulCount = 1;
	//~~~~~~~~~~~~~~~~~~~~~~



	// ��ȡ�ַ�����ֱ������0x00Ϊֹ
	while (nChar != 0x00) {

		// ���η��������洢���ַ����ռ���
		str += static_cast<char>(nChar);
		++ulCount;
		nChar = fgetc(m_fpIpDataFile);
	}

	// �����ַ�������
	return ulCount;
}


void IpFinder::GetAddressByOffset(unsigned long ulOffset,
								   std::string &strCountry,
								   std::string &strLocation) const
{
	if (!m_fpIpDataFile) {
		return;
	}

	// ��ȥ4�ֽ�Ip��ַ
	ulOffset += IP_LENGTH;
	fseek(m_fpIpDataFile, ulOffset, SEEK_SET);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ��ȡ�׵�ַ��ֵ
	int nVal = (fgetc(m_fpIpDataFile) & 0x000000FF);
	unsigned long ulCountryOffset = 0;	// ��ʵ������ƫ��
	unsigned long ulLocationOffset = 0; // ��ʵ������ƫ��
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Ϊ�˽�ʡ�ռ䣬��ͬ�ַ���ʹ���ض��򣬶����Ƕ�ݿ���
	if (REDIRECT_MODE_1 == nVal) {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �ض���1����
		unsigned long ulRedirect = this->GetValue3(ulOffset + 1); // �ض���ƫ��
		///
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		fseek(m_fpIpDataFile, ulRedirect, SEEK_SET);

		if ((fgetc(m_fpIpDataFile) & 0x000000FF) == REDIRECT_MODE_2) {

			// �������1���ض���1���ͽ���������ض���2���� 
			// 0x01 1�ֽ�
			// ƫ���� 3�ֽ� -----> 0x02 1�ֽ� 
			//                     ƫ���� 3�ֽ� -----> ������
			//                     ������
			ulCountryOffset = this->GetValue3(ulRedirect + 1);
			this->GetString(strCountry, ulCountryOffset);
			ulLocationOffset = ulRedirect + 4;
		} else {

			// �������ض���ģʽ1
			// 0x01 1�ֽ�
			// ƫ���� 3�ֽ� ------> ������
			//                      ������
			ulCountryOffset = ulRedirect;
			ulLocationOffset = ulRedirect + this->GetString(strCountry,
				ulCountryOffset);
		}
	} else if (REDIRECT_MODE_2 == nVal) {

		// �ض���2����
		// 0x02 1�ֽ�
		// ����ƫ�� 3�ֽ� -----> ������
		// ������
		ulCountryOffset = this->GetValue3(ulOffset + 1);
		this->GetString(strCountry, ulCountryOffset);

		ulLocationOffset = ulOffset + 4;
	} else {

		// ��򵥵���� û���ض���
		// ������
		// ������
		ulCountryOffset = ulOffset;
		ulLocationOffset = ulCountryOffset + this->GetString(strCountry,
			ulCountryOffset);
	}

	// ��ȡ����
	fseek(m_fpIpDataFile, ulLocationOffset, SEEK_SET);
	if ((fgetc(m_fpIpDataFile) & 0x000000FF) == REDIRECT_MODE_2
		|| (fgetc(m_fpIpDataFile) & 0x000000FF) == REDIRECT_MODE_1) {

			// �������2(��ӵ����Σ�����Ҳ�ض���)
			// 0x01 1�ֽ�
			// ƫ���� 3�ֽ� ------> 0x02 1�ֽ�
			//                      ƫ���� 3�ֽ� -----> ������
			//                      0x01 or 0x02 1�ֽ�
			//                      ƫ���� 3�ֽ� ----> ������ ƫ����Ϊ0��ʾδ֪����
			ulLocationOffset = this->GetValue3(ulLocationOffset + 1);
	}

	this->GetString(strLocation, ulLocationOffset);
}


void IpFinder::GetAddressByIp(unsigned long ipValue,
							   std::string &strCountry,
							   std::string &strLocation) const
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	unsigned long ulIndexOffset = this->SearchIp(ipValue);
	unsigned long ulRecordOffset = this->GetValue3(ulIndexOffset + IP_LENGTH);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	this->GetAddressByOffset(ulRecordOffset, strCountry, strLocation);
}


void IpFinder::GetAddressByIp(const char *pszIp,
							   std::string &strCountry,
							   std::string &strLocation) const
{
	if (!this->IsRightIpString(pszIp)) {
		return;
	}
	this->GetAddressByIp(this->IpString2IpValue(pszIp), strCountry, strLocation);
}


unsigned long IpFinder::OutputData(const char *pszFileName,
									unsigned long indexStart,
									unsigned long indexEnd) const
{
	if (!m_fpIpDataFile || !pszFileName) {
		return 0;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	FILE *fpOut = fopen(pszFileName, "wb");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (!fpOut) {
		return 0;
	}

	if (0 == indexStart) {
		indexStart = m_indexStart;
	}

	if (0 == indexEnd) {
		indexEnd = m_indexEnd;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~
	char szEndIp[255];
	char szStartIp[255];
	std::string strCountry;
	std::string strLocation;
	unsigned long ulCount = 0;
	unsigned long ipValueEnd = 0;
	unsigned long ipValueStart = 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~

	for (unsigned long i = indexStart; i < indexEnd; i += INDEX_LENGTH) {

		// ��ȡIP�ε���ʼIP�ͽ���IP�� ��ʼIPΪ�������ֵ�ǰ4λ16����
		// ����IP��IP��Ϣ���ֵ�ǰ4λ16�����У�����������ָ����ƫ������Ѱ
		ipValueStart = this->GetValue4(i);
		ipValueEnd = this->GetValue4(this->GetValue3(i + IP_LENGTH));

		// ����IP��Ϣ����ʽ�� ��ʼIP/t����IP/t����λ��/t����λ��/n
		this->IpValue2IpString(ipValueStart, szStartIp, sizeof(szStartIp));
		this->IpValue2IpString(ipValueEnd, szEndIp, sizeof(szEndIp));
		this->GetAddressByOffset(this->GetValue3(i + IP_LENGTH), strCountry,
			strLocation);
		fprintf(fpOut, "%s/t%s/t%s/t%s/n", szStartIp, szEndIp,
			strCountry.c_str(), strLocation.c_str());
		ulCount++;
	}

	fclose(fpOut);

	// ���ص���������
	return ulCount;
}


unsigned long IpFinder::OutputDataByIp(const char *pszFileName,
										unsigned long ipValueStart,
										unsigned long ipValueEnd) const
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	unsigned long indexStart = this->SearchIp(ipValueStart);
	unsigned long indexEnd = this->SearchIp(ipValueEnd);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	return this->OutputData(pszFileName, indexStart, indexEnd);
}


unsigned long IpFinder::OutputDataByIp(const char *pszFileName,
										const char *pszStartIp,
										const char *pszEndIp) const
{
	if (!this->IsRightIpString(pszStartIp) || !this->IsRightIpString(pszEndIp)) {
		return 0;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	unsigned long ipValueEnd = this->IpString2IpValue(pszEndIp);
	unsigned long ipValueStart = this->IpString2IpValue(pszStartIp);
	unsigned long indexEnd = this->SearchIp(ipValueEnd);
	unsigned long indexStart = this->SearchIp(ipValueStart);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	return this->OutputData(pszFileName, indexStart, indexEnd);
}


bool IpFinder::IsRightIpString(const char* pszIp) const
{
	if (!pszIp) {
		return false;
	}

	int nLen = strlen(pszIp);
	if (nLen < 7) {

		// ���ٰ���7���ַ�"0.0.0.0"
		return false;
	}

	for (int i = 0; i < nLen; ++i) {
		if (!isdigit(pszIp[i]) && pszIp[i] != '.') {
			return false;
		}

		if (pszIp[i] == '.') {
			if (0 == i) {
				if (!isdigit(pszIp[i + 1])) {
					return false;
				}
			} else if (nLen - 1 == i) {
				if (!isdigit(pszIp[i - 1])) {
					return false;
				}
			} else {
				if (!isdigit(pszIp[i - 1]) || !isdigit(pszIp[i + 1])) {
					return false;
				}
			}
		}
	}
	return true;
}