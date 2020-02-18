#pragma once
#include <string>
#include "MySQLConnector.h"

namespace thatboy
{

	namespace Bank
	{
		bool createAccount(
            std::string cardAccount
            , std::string cardPassword
            , float cardBalance
            , std::string userName
            , bool userGender
            , std::string userPhoneNumber
            , std::string userID 
        );

        std::string applyAccountNumber();

        bool verifyPassword(std::string cardAccount, std::string cardPassword);

        bool depositAndWithdraw(std::string cardAccount, float changeBalance);
        bool transfer(std::string thisAccount, std::string thatAccount, float changeBalance);
        bool cancelAccount(std::string cardAccount);

        MySQLResult queryHistoryEvent(std::string thisAccount, std::string beginTime, std::string endTime);
        MySQLResult enumNormalAccount();

        MySQLResult queryUserReport(std::string thisAccount, float& sumBalance, int dateChoose, int typeChoose);
        MySQLResult queryBankReport(float& sumBalance, int dateChoose, int typeChoose);

        std::string queryUserName(std::string cardAccount);
        std::string queryUserGender(std::string cardAccount);
        std::string queryUserPhoneNumber(std::string cardAccount);
        std::string queryCardBalance(std::string cardAccount);
        std::string queryCardState(std::string cardAccount);
	};
}