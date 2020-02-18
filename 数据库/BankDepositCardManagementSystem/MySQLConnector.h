#pragma once
#include <mysql.h>

namespace thatboy
{
	class MySQLField
	{
	public:
		MySQLField() = default;
		MySQLField(const MySQLField&) = default;
		MySQLField(MySQLField&&) = default;
		MySQLField(MYSQL_FIELD*);
		MySQLField& operator =(const MySQLField&) = default;
		MySQLField& operator =(MYSQL_FIELD*);

		operator MYSQL_FIELD* ()
		{
			return field;
		}

		char* getName();       
		char* getOrgName();    
		char* getTable();      
		char* getOrgTable();   
	protected:
		MYSQL_FIELD* field;
	};

	using MySQLRow = MYSQL_ROW;

	class MySQLResult
	{
	public:
		MySQLResult() = default;
		MySQLResult(const MySQLResult&) = default;
		MySQLResult(MySQLResult&&) = default;
		MySQLResult& operator =(const MySQLResult&) = default;
		MySQLResult& operator =(MYSQL_RES*);


		bool empty()const;


		operator MYSQL_RES*()
		{
			return result;
		}

		std::string front()const;

		size_t getRowsNum()const;
		size_t getFieldsNum()const;

		MySQLField fetchField();
		MySQLField fetchFieldDirect(size_t);
		MySQLRow fetchRow();

		template<typename FuncType>
		void forEachField(FuncType);
		template<typename FuncType>
		void forEachRow(FuncType);

		struct MySQLRowIterator
		{
			MySQLRowIterator(MYSQL_ROWS* rows)
				: rows(rows) {}
			MYSQL_ROW& operator *()
			{
				return rows->data;
			}
			MySQLRowIterator& operator++()
			{
				if(rows!=nullptr)
					rows = rows->next;
				return *this;
			}
			MySQLRowIterator operator++(int)
			{
				MySQLRowIterator oldIt = *this;
				++* this;
				return oldIt;
			}
			bool operator !=(const MySQLRowIterator& it)const
			{
				return rows != it.rows;
			}
		protected:
			MYSQL_ROWS* rows;
		};

		MySQLRowIterator begin();
		MySQLRowIterator end();
	protected:
		MYSQL_RES* result;
	};

	class MySQLConnector :
		protected MYSQL
	{
	public:
		using MYSQL::MYSQL;
		MySQLConnector();
		MySQLConnector(const char* host
			, const char* user
			, const char* passwd
			, const char* db = nullptr
			, unsigned int port = 0
			, const char* unix_socket = nullptr
			, unsigned long clientflag = CLIENT_MULTI_STATEMENTS);
		~MySQLConnector();

		/* 选择数据库 */
		void selectDatabase(const char* db);

		/* 连接数据库 */
		void realConnect(
			const char* host
			, const char* user
			, const char* passwd
			, const char* db = nullptr
			, unsigned int port = 0
			, const char* unix_socket = nullptr
			, unsigned long clientflag = CLIENT_MULTI_STATEMENTS
		);

		/* 查询 */
		void query(const char* queryCmd);

		/* 结果 */
		inline MySQLResult getResult()
		{
			return lastResult;
		}
	protected:
		MySQLResult lastResult;
	};
	
	template<typename FuncType>
	inline void MySQLResult::forEachField(FuncType fun)
	{
		for (size_t i = 0; i < result->field_count; i++)
			fun(result->fields + i);
	}

	template<typename FuncType>
	inline void MySQLResult::forEachRow(FuncType fun)
	{
		for (auto row = result->data->data; row != nullptr; row = row->next)
			fun(row->data);
	}

}