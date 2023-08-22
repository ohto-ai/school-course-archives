#include "pch.h"
#include "MySQLConnector.h"

#ifdef _DEBUG
MYSQL* DEBUG_CHECK_VALUE(MYSQL* handleConnector, MYSQL* handleMySQL)
{
	if (handleMySQL == nullptr)
	{
		OutputDebugString(mysql_error(handleConnector));
		throw mysql_error(handleConnector);
	}
	return handleMySQL;
}
int DEBUG_CHECK_VALUE(MYSQL* handleConnector, int errorNum)
{
	if (errorNum != 0)
	{
		OutputDebugString(mysql_error(handleConnector));
		throw mysql_error(handleConnector);
	}
	return errorNum;
}

#define MYSQLCONNECTOR_ASSERT(exp) DEBUG_CHECK_VALUE(this, exp)
#else
#define MYSQLCONNECTOR_ASSERT(exp) exp
#endif


thatboy::MySQLConnector::MySQLConnector()
	: lastResult()
{
	MYSQLCONNECTOR_ASSERT(mysql_init(this));
}

thatboy::MySQLConnector::MySQLConnector(const char* host, const char* user, const char* passwd, const char* db, unsigned int port, const char* unix_socket, unsigned long clientflag)
	: lastResult()
{
	MYSQLCONNECTOR_ASSERT(mysql_init(this));
	realConnect(host, user, passwd, db, port, unix_socket, clientflag);
}

thatboy::MySQLConnector::~MySQLConnector()
{
	mysql_close(this);
}

void thatboy::MySQLConnector::selectDatabase(const char* db)
{
	MYSQLCONNECTOR_ASSERT(mysql_select_db(this, db));
}

void thatboy::MySQLConnector::realConnect(const char* host, const char* user, const char* passwd, const char* db, unsigned int port, const char* unix_socket, unsigned long clientflag)
{
	MYSQLCONNECTOR_ASSERT(mysql_real_connect(this, host, user, passwd, db, port, unix_socket, clientflag));
}

void thatboy::MySQLConnector::query(const char* queryCmd)
{
#ifdef _DEBUG
	OutputDebugString("\nMySQL:"); OutputDebugString(queryCmd); OutputDebugString("\n");
#endif
	MYSQLCONNECTOR_ASSERT(mysql_query(this, thatboy::Tool::Unicode2UTF8(queryCmd).GetString()));
	lastResult = mysql_store_result(this);
}

thatboy::MySQLResult& thatboy::MySQLResult::operator=(MYSQL_RES*res)
{
	result = res;
	return *this;
}

bool thatboy::MySQLResult::empty() const
{
	return result == nullptr || result->row_count == 0;
}

std::string thatboy::MySQLResult::front() const
{
	return empty() ? "" : thatboy::Tool::UTF82Unicode(result->data->data->data[0]);
}

size_t thatboy::MySQLResult::getRowsNum() const
{
	return result == nullptr ? 0 : result->row_count;
}

size_t thatboy::MySQLResult::getFieldsNum() const
{
	return result == nullptr ? 0 : result->field_count;
}

thatboy::MySQLField thatboy::MySQLResult::fetchField()
{
	return mysql_fetch_field(result);
}

thatboy::MySQLField thatboy::MySQLResult::fetchFieldDirect(size_t ptr)
{
	return mysql_fetch_field_direct(result, ptr);
}

thatboy::MySQLRow thatboy::MySQLResult::fetchRow()
{
	return mysql_fetch_row(result);
}

thatboy::MySQLResult::MySQLRowIterator thatboy::MySQLResult::begin()
{
	return result == nullptr ? nullptr : result->data == nullptr ? nullptr : result->data->data;
}

thatboy::MySQLResult::MySQLRowIterator thatboy::MySQLResult::end()
{
	return nullptr;
}

thatboy::MySQLField::MySQLField(MYSQL_FIELD* fld)
{
	field = fld;
}

thatboy::MySQLField& thatboy::MySQLField::operator=(MYSQL_FIELD*fld)
{
	field = fld;
	return *this;
}

char* thatboy::MySQLField::getName()
{
	return field == nullptr ? nullptr : field->name;
}

char* thatboy::MySQLField::getOrgName()
{
	return field == nullptr ? nullptr : field->org_name;
}

char* thatboy::MySQLField::getTable()
{
	return field == nullptr ? nullptr : field->table;
}

char* thatboy::MySQLField::getOrgTable()
{
	return field == nullptr ? nullptr : field->org_table;
}
