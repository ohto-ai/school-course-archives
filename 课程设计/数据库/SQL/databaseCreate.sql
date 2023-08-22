DROP database if exists Bank;
create database Bank;
use Bank;
create table UserCard
(
	cardID int primary key auto_increment not null
    , cardAccount char(18) unique not null
    , cardPassword char(32) not null
    , cardBalance float not null
    , cardState enum('Normal', 'Cancellation') not null											# 账户状态 正常、注销、冻结
    , userName char(20) not null
    , userGender enum('Male','Female') not null
		, userPhoneNumber char(11) not null
    , userID char(18) not null
);
create table AccountChangeEvent
(
	changeID int primary key auto_increment not null
		, changeType enum('Create', 'Cancel', 'Deposit', 'Withdraw', 'TransferIn', 'TransferOut')	not null# 变动类型
    , changeBalance float 																		# 金额变动
		, cardAccount char(18) not null																		# 本账户
    , transferAccount char(18)																			# 转账账户
    , changeTime datetime not null																# 事件时间
		, serviceCharge float DEFAULT 0
);

CREATE TABLE accountTable (
    `id` BIGINT(18) unsigned NOT NULL auto_increment,
    `replace_key` char(1) NOT NULL default '',
    PRIMARY KEY (`id`),
    UNIQUE KEY `replace_key` (`replace_key`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=622260026000107244;



