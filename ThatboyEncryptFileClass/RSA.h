#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>


class RSA {
public:
	using LONG = int32_t;
	using LONGLONG = int64_t;
	using LONG_PTR = LONG*;
	using LONG_CPTR = const LONG*;

	struct Key {
		//公钥(public_key, share_key)
		LONGLONG share_key;
		LONGLONG public_key;
		//私钥(private_key, share_key)
		LONGLONG private_key;
	};

	RSA();
	Key GetKey() {
		return _key;
	}

	//对数据进行加密解密
	void encrypt(LONG_CPTR dataIn, size_t dataInSize, LONG_PTR dataOut, LONG public_key, LONG share_key);
	void decrypt(LONG_CPTR dataIn, size_t dataInSize, LONG_PTR dataOut, LONG private_key, LONG share_key);

private:
	//产生素数
	LONG producePrime();
	//判断一个数是否是素数
	bool isPrime(LONG prime);
	//产生所有的key值
	void produceKeys();
	//求share_kay
	LONG produceShareKey(LONG prime1, LONG prime2);
	//根据欧拉函数求乘积
	LONG produceOrla(LONG prime1, LONG prime2);
	//求public_key
	LONG producePublicKey(LONG orla);
	//判断两个数之间的最大公约是否为1
	LONG gcd(LONG public_key, LONG orla);
	//求private_key
	LONG producePrivateKey(LONG public_key, LONG orla);
	//加密单个信息
public:
	LONG encrypt(LONG msg, LONG key, LONG share_key);
private:
	Key _key;
};