#include "pch.h"
#include "Bank.h"


constexpr LPCTSTR bankDBHost = TEXT("localhost");
constexpr LPCTSTR bankDBUser = TEXT("root");
constexpr LPCTSTR bankDBPassword = TEXT("root");
constexpr LPCTSTR bankDBName = TEXT("Bank");


bool thatboy::Bank::createAccount(std::string cardAccount, std::string cardPassword, float cardBalance, std::string userName, bool userGender, std::string userPhoneNumber, std::string userID)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select CreateAccount")
		+ R"(( ')" + cardAccount
		+ R"(', ')" + md5(cardPassword)
		+ R"(', )" + std::to_string(cardBalance)
		+ R"(, ')" + userName
		+ R"(', ')" + (userGender ? "Male" : "Female")
		+ R"(', ')" + userPhoneNumber
		+ R"(', ')" + userID
		+ R"(' );)"
		).c_str());
	return connector.getResult().front() == "1";
}

std::string thatboy::Bank::applyAccountNumber()
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query(R"(select GenerateAccountNumber();)");
	return connector.getResult().front();
}

bool thatboy::Bank::verifyPassword(std::string cardAccount, std::string cardPassword)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select VerifyPassword(")
		+ R"(')" + cardAccount
		+ R"(', ')" + thatboy::md5(cardPassword) + R"(');)"
		).c_str());
	return connector.getResult().front() == "1";
}

bool thatboy::Bank::depositAndWithdraw(std::string cardAccount, float changeBalance)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select DepositAndWithdraw(")
		+ R"(')" + cardAccount
		+ R"(', )" + std::to_string(changeBalance) + R"();)"
		).c_str());
	return connector.getResult().front() == "1";
}

bool thatboy::Bank::transfer(std::string thisAccount, std::string thatAccount, float changeBalance)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select Transfer(")
		+ R"(')" + thisAccount
		+ R"(', ')" + thatAccount
		+ R"(', )" + std::to_string(changeBalance) + R"();)"
		).c_str());
	return connector.getResult().front() == "1";
}

bool thatboy::Bank::cancelAccount(std::string cardAccount)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select CancelAccount(")
		+ R"(')" + cardAccount + R"(');)"
		).c_str());
	return connector.getResult().front() == "1";
}

thatboy::MySQLResult thatboy::Bank::queryHistoryEvent(std::string thisAccount, std::string beginTime,std::string endTime)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	
	if (beginTime.empty() && endTime.empty())
		connector.query((std::string("select ac.changeTime,ac.changeType,ac.transferAccount, ac.changeBalance,ac.serviceCharge from accountchangeevent ac,usercard uc where uc.cardAccount=\'") + thisAccount + "\' and ac.cardAccount=uc.cardAccount ORDER BY ac.changeID;").c_str());
	else if (!beginTime.empty() && !endTime.empty())
		connector.query((std::string("select ac.changeTime,ac.changeType,ac.transferAccount, ac.changeBalance,ac.serviceCharge from accountchangeevent ac,usercard uc where uc.cardAccount=\'") + thisAccount + "\' and ac.cardAccount=uc.cardAccount and ac.changeTime BETWEEN \'" + beginTime + "\' and \'" + endTime + "\' ORDER BY ac.changeID;").c_str());
	else if(!beginTime.empty())
		connector.query((std::string("select ac.changeTime,ac.changeType,ac.transferAccount, ac.changeBalance,ac.serviceCharge from accountchangeevent ac,usercard uc where uc.cardAccount=\'") + thisAccount + "\' and ac.cardAccount=uc.cardAccount and ac.changeTime > \'" + beginTime + "\' ORDER BY ac.changeID;").c_str());
	else if (!endTime.empty())
		connector.query((std::string("select ac.changeTime,ac.changeType,ac.transferAccount, ac.changeBalance,ac.serviceCharge from accountchangeevent ac,usercard uc where uc.cardAccount=\'") + thisAccount + "\' and ac.cardAccount=uc.cardAccount and ac.changeTime < \'" + endTime + "\' ORDER BY ac.changeID;").c_str());

	return connector.getResult();
}

thatboy::MySQLResult thatboy::Bank::enumNormalAccount()
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query(R"(select cardAccount from userCard where cardState='Normal';)");
	return connector.getResult();
}

thatboy::MySQLResult thatboy::Bank::queryUserReport(std::string thisAccount, float& sumBalance, int dateChoose, int typeChoose)
{
	auto querySum = std::string("select sum(changeBalance) from accountchangeevent")
		+ " where cardAccount=\'"
		+ thisAccount
		+ "\' and changeBalance"
		+ (typeChoose == 0 ? ">0 " : typeChoose == 1 ? "<0 " : "<>0 ")
		+ "and changeTime > DATE_SUB(LOCALTIME(), interval 1 "
		+ (dateChoose == 0 ? "DAY" : dateChoose == 1 ? "MONTH" : "YEAR")
		+ ") ORDER BY changeID;";
	auto queryList = std::string("select changeTime, changeType, transferAccount, changeBalance, serviceCharge from accountchangeevent")
		+ " where cardAccount=\'"
		+ thisAccount
		+ "\' and changeBalance"
		+ (typeChoose == 0 ? ">0 " : typeChoose == 1 ? "<0 " : "<>0 ")
		+ "and changeTime > DATE_SUB(LOCALTIME(), interval 1 "
		+ (dateChoose == 0 ? "DAY" : dateChoose == 1 ? "MONTH" : "YEAR")
		+ ") ORDER BY changeID;";

	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);

	connector.query(querySum.c_str());
	std::stringstream sstream(connector.getResult().front());
	sstream >> sumBalance;

	connector.query(queryList.c_str());
	return connector.getResult();
}

thatboy::MySQLResult thatboy::Bank::queryBankReport(float& sumBalance, int dateChoose, int typeChoose)
{
	auto querySum = std::string("select sum(changeBalance) from accountchangeevent")
		+ " where changeBalance"
		+ (typeChoose == 0 ? ">0 " : typeChoose == 1 ? "<0 " : "<>0 ")
		+ "and changeTime > DATE_SUB(LOCALTIME(), interval 1 "
		+ (dateChoose == 0 ? "DAY" : dateChoose == 1 ? "MONTH" : "YEAR")
		+ ") ORDER BY changeID;";
	auto queryList = std::string("select cardAccount, changeTime, changeType, transferAccount, changeBalance, serviceCharge from accountchangeevent")
		+ " where changeBalance"
		+ (typeChoose == 0 ? ">0 " : typeChoose == 1 ? "<0 " : "<>0 ")
		+ "and changeTime > DATE_SUB(LOCALTIME(), interval 1 "
		+ (dateChoose == 0 ? "DAY" : dateChoose == 1 ? "MONTH" : "YEAR")
		+ ") ORDER BY changeID;";

	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);

	connector.query(querySum.c_str());
	std::stringstream sstream(connector.getResult().front());
	sstream >> sumBalance;

	connector.query(queryList.c_str());
	return connector.getResult();
}

std::string thatboy::Bank::queryUserName(std::string cardAccount)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select userName from userCard where cardAccount = ")
		+ R"(')" + cardAccount+ R"(')").c_str());
	return connector.getResult().front();
}

std::string thatboy::Bank::queryUserGender(std::string cardAccount)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select userGender from userCard where cardAccount = ")
		+ R"(')" + cardAccount + R"(')").c_str());
	return connector.getResult().front();
}

std::string thatboy::Bank::queryUserPhoneNumber(std::string cardAccount)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select userPhoneNumber from userCard where cardAccount = ")
		+ R"(')" + cardAccount + R"(')").c_str());
	return connector.getResult().front();
}

std::string thatboy::Bank::queryCardBalance(std::string cardAccount)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select cardBalance from userCard where cardAccount = ")
		+ R"(')" + cardAccount + R"(')").c_str());
	return connector.getResult().front();
}

std::string thatboy::Bank::queryCardState(std::string cardAccount)
{
	MySQLConnector connector(bankDBHost, bankDBUser, bankDBPassword, bankDBName);
	connector.query((std::string("select cardState from userCard where cardAccount = ")
		+ R"(')" + cardAccount + R"(')").c_str());
	return connector.getResult().front();
}
