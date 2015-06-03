#pragma once;
#include <string>

const int INDEX_LENGTH = 7;		// һ����������4�ֽڵ���ʼIP��3�ֽڵ�IP��¼ƫ�ƣ���7�ֽ�
const int IP_LENGTH = 4;
const int OFFSET_LENGTH = 3;

enum {
	REDIRECT_MODE_1 = 0x01,	// �ض���ģʽ1 ƫ�������޵�����
	REDIRECT_MODE_2 = 0x02,	// �ض���ģʽ2 ƫ�������е�����
};

class IpFinder
{
public:
	IpFinder();
	IpFinder(const char* pszFileName);
	~IpFinder();

	// ��ȡip��������������
	void GetAddressByIp(unsigned long ipValue, std::string& strCountry, std::string& strLocation) const;
	void GetAddressByIp(const char* pszIp, std::string& strCountry, std::string& strLocation) const;
	void GetAddressByOffset(unsigned long ulOffset, std::string& strCountry, std::string& strLocation) const;

	unsigned long GetString(std::string& str, unsigned long indexStart) const;
	unsigned long GetValue3(unsigned long indexStart) const;
	unsigned long GetValue4(unsigned long indexStart) const;

	// ת��
	unsigned long IpString2IpValue(const char *pszIp) const;
	void IpValue2IpString(unsigned long ipValue, char* pszIpAddress, int nMaxCount) const;
	bool IsRightIpString(const char* pszIp) const;

	// �������
	unsigned long OutputData(const char* pszFileName, unsigned long ulIndexStart = 0, unsigned long ulIndexEnd = 0) const;
	unsigned long OutputDataByIp(const char* pszFileName, unsigned long ipValueStart, unsigned long ipValueEnd) const;
	unsigned long OutputDataByIp(const char* pszFileName, const char* pszStartIp, const char* pszEndIp) const;

	unsigned long SearchIp(unsigned long ipValue, unsigned long indexStart = 0, unsigned long indexEnd = 0) const;
	unsigned long SearchIp(const char* pszIp, unsigned long indexStart = 0, unsigned long indexEnd = 0) const;

	bool Open(const char* pszFileName);
private:
	FILE *m_fpIpDataFile;			// IP���ݿ��ļ�
	unsigned long m_indexStart;	// ��ʼ����ƫ��
	unsigned long m_indexEnd;		// ��������ƫ��
};
