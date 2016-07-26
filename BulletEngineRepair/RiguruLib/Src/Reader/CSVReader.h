#ifndef _CSV_READER_H_
#define _CSV_READER_H_

#include <string>
#include <vector>
#include <map>
#include "FileID.h"

enum CONFIG_DATA{
	MUSIC_VOL,
	SE_VOL,
};

class CSVReader
{
public :
	CSVReader();
	~CSVReader();

	static CSVReader &GetInstance(){
		static CSVReader c;
		return c;
	}

	void FileSet(FILE_ID id, const std::string& filename);
	/**********
	*	@brief �ǂݍ���
	*	@param[in] filename [std::string]
	*	@note -
	*
	*	@return	�ǂݍ��݂ɐ���������^
	**********/
	bool load(FILE_ID id);
	/**********
	*	@brief ���݂̓ǂݍ��܂�Ă���l�̕ۑ�
	*	@param[in] filename [std::string]
	*	@note -
	*
	*	@return	�ۑ��ɐ���������^
	**********/
	bool save(FILE_ID id);
	/**********
	*	@brief �s���擾
	*	@note �\�Ō����c
	*
	*	@return	�s����Ԃ�
	**********/
	int rows(FILE_ID id) const;
	/**********
	*	@brief �񐔎擾
	*	@param[in] row [unsigned int] default = 0
	*	@note �\�Ō�����, �s���Ȃ�������O���Ԃ�
	*
	*	@return	�񐔂�Ԃ�
	**********/
	int colums(FILE_ID id, unsigned int row = 0) const;
	/**********
	*	@brief ������擾
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�ǂݍ��܂�Ă��镶�����Ԃ�
	**********/
	const std::string& get(FILE_ID id, unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾int
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������int�^�ɕϊ��������̂�Ԃ�
	**********/
	int geti(FILE_ID id, unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾float
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������float�^�ɕϊ��������̂�Ԃ�
	**********/
	float getf(FILE_ID id, unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾double
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������double�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	double getd(FILE_ID id, unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾long double
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������long double�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	long double getld(FILE_ID id, unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾long
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������long�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	long getl(FILE_ID id, unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾long long
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������long long�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	long long getll(FILE_ID id, unsigned int row, unsigned int col) const;

	void WriteData(FILE_ID id, std::map<int, std::vector<std::string>> str);

private :	/* Copy Guard */
	CSVReader(const CSVReader& other);
	CSVReader& operator = (const CSVReader& other);

private :
	typedef std::vector<std::string> Row;
	typedef std::vector<Row> Rows;
	std::map<FILE_ID, Rows> datas;
	std::map<FILE_ID, std::string> files;
};

#endif