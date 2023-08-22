use Bank;

set global log_bin_trust_function_creators=1;
# todo 检测余额不足 无法转账\取款
# todo 检测创建账户时，存款小于0则无法创建

delimiter $$



# 查询账户数量
drop function if exists CountTotalAccount;
Create function CountTotalAccount() returns int
BEGIN
	DECLARE accountCount int;
	SELECT count(cardID) into accountCount from userCard;
	return accountCount;
end $$

# 查询有效账户数量
drop function if exists CountNormalAccount;
Create function CountNormalAccount() returns int
BEGIN
	DECLARE accountNormalCount int;
	SELECT count(cardID) into accountNormalCount from userCard where cardState='Normal';
	return accountNormalCount;
end $$

# 查询指定账户存在
drop function if exists QueryExist;
Create function QueryExist(thisCardAccount char(18)) returns bool
BEGIN
	return !ISNULL((SELECT cardID from userCard where cardAccount = thisCardAccount)>0);
end $$


# 生成一个账户
drop function if exists GenerateAccountNumber;
Create function GenerateAccountNumber() returns char(18)
BEGIN
	REPEAT
		REPLACE INTO accountTable (`replace_key`) VALUES (' ');
	UNTIL !QueryExist(LAST_INSERT_ID()) 
	END REPEAT;
	return (SELECT LAST_INSERT_ID()); 
end $$


# 查询指定账户有效
drop function if exists QueryNormal;
Create function QueryNormal(thisCardAccount char(18)) returns bool
BEGIN
	return !ISNULL((SELECT cardID from userCard where cardAccount = thisCardAccount and cardState='Normal')>0);
end $$


# 查询余额
drop function if exists QueryBalance;
Create function QueryBalance(thisCardAccount char(18))returns float
begin
	DECLARE balance float;
	select cardBalance into balance from UserCard where cardAccount = thisCardAccount;
	return balance;
end $$

# 校验密码
drop function if exists VerifyPassword;
Create function VerifyPassword(thisCardAccount char(18), thisCardPassword char(32))returns bool
begin
	return (select cardPassword from UserCard where cardAccount = thisCardAccount)=thisCardPassword;
end $$



# 存取款
drop function if exists DepositAndWithdraw;
Create function DepositAndWithdraw(thisCardAccount char(18), thisChangeBalance float) returns bool
begin
	SET SQL_SAFE_UPDATES = 0;
    # 更新余额
    if thisChangeBalance=0 or QueryBalance(thisCardAccount) + thisChangeBalance < 0  then
			return false;			
    end if;
    
	update UserCard set cardBalance = cardBalance+thisChangeBalance
    where cardAccount = thisCardAccount;
    # 写入事件
	insert into AccountChangeEvent(changeType,changeBalance ,cardAccount, changeTime)
	values(if(thisChangeBalance > 0,'Deposit','Withdraw'), thisChangeBalance
    , thisCardAccount
    , LOCALTIME());
    return true;
end $$

drop function if exists CreateAccount;
Create function CreateAccount(
	thisCardAccount char(18)
	, thisCardPassword char(32)
	, thisCardBalance float
	, thisUserName char(20)
	, thisUserGender enum('Male','Female')
	, thisUserPhoneNumber char(11)
	, thisUserID char(18)
	)
	returns bool
begin
	SET SQL_SAFE_UPDATES = 0;
	# 创建账户，存款为0
	if (QueryExist(thisCardAccount))<>0 then
		return false;
	end if;

	insert into UserCard(cardAccount, cardPassword, cardBalance, cardState, userName, userGender, userPhoneNumber, userID)
		values(thisCardAccount, thisCardPassword, 0, 'Normal', thisUserName, thisUserGender, thisUserPhoneNumber, thisUserID);
	# 插入创建事件
	insert into AccountChangeEvent(changeType, cardAccount, changeTime)
		values('Create', thisCardAccount, LOCALTIME());
	# 存款
	return DepositAndWithdraw(thisCardAccount,thisCardBalance);
end $$


# 转账
drop function if exists Transfer;
Create function Transfer(thisCardAccount char(18),thatCardAccount char(18), thisChangeBalance float)
	returns bool
begin
	SET SQL_SAFE_UPDATES = 0;
    # 更新余额
    if thisChangeBalance=0 or (if(thisChangeBalance<0,QueryBalance(thisCardAccount)+thisChangeBalance-if(thisChangeBalance<0,-thisChangeBalance*0.01,0),
						QueryBalance(thatCardAccount)-thisChangeBalance - if(thisChangeBalance>0,thisChangeBalance*0.01,0))< 0) then
        return false;
    end if;
    
    
	update UserCard set cardBalance = cardBalance+thisChangeBalance-if(thisChangeBalance<0,-thisChangeBalance*0.01,0)
    where cardAccount = thisCardAccount;    
	update UserCard set cardBalance = cardBalance-thisChangeBalance-if(thisChangeBalance>0,thisChangeBalance*0.01,0)
    where cardAccount = thatCardAccount;
    
    # 写入事件
	insert into AccountChangeEvent(changeType,changeBalance ,cardAccount ,transferAccount, serviceCharge, changeTime)
	values(if(thisChangeBalance > 0,'TransferIn','TransferOut'), thisChangeBalance, 
    thisCardAccount
		, thatCardAccount
		, if(thisChangeBalance<0,-thisChangeBalance*0.01,0)
    , LOCALTIME());
    insert into AccountChangeEvent(changeType,changeBalance ,cardAccount ,transferAccount,serviceCharge, changeTime)
	values(if(thisChangeBalance < 0,'TransferIn','TransferOut'), thisChangeBalance, 
    thatCardAccount
    , thisCardAccount
		, if(thisChangeBalance>0,thisChangeBalance*0.01,0)
    , LOCALTIME());
    return true;
end $$


# 注销账户
drop function if exists CancelAccount;
Create function CancelAccount(thisCardAccount char(18))
    returns bool
begin
	DECLARE ret bool;
	select DepositAndWithdraw(thisCardAccount, -QueryBalance(thisCardAccount)) into ret;
    # 设置账户状态
    update UserCard set cardState = 'Cancellation'
			where cardAccount = thisCardAccount and cardState = 'Normal';
	# 插入注销事件
    insert into AccountChangeEvent(changeType, cardAccount, changeTime)
			values('Cancel', thisCardAccount, LOCALTIME());
	return true;
end $$



delimiter ;



