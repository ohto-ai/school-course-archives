#include "RSA.h"

RSA::RSA() {
	produceKeys();
}


void RSA::encrypt(LONG_CPTR dataIn, size_t dataInSize, LONG_PTR dataOut, LONG public_key, LONG share_key)
{
	for (size_t i = 0; i < dataInSize; i++)
		dataOut[i] = encrypt(dataIn[i], public_key, share_key);
}

void RSA::decrypt(LONG_CPTR dataIn, size_t dataInSize, LONG_PTR dataOut, LONG private_key, LONG share_key)
{
	for (size_t i = 0; i < dataInSize; i++)
		dataOut[i] = encrypt(dataIn[i], private_key, share_key);
}

//加密单个信息，模幂运算
RSA::LONG  RSA::encrypt(LONG msg, LONG key, LONG share_key) {
	LONG msg_out = 1;
	LONG a = msg;
	LONG b = key;
	LONG c = share_key;
	while (b) {
		if (b & 1) {
			//msg_out = (A0*A1...Ai...An) % c
			msg_out = (msg_out * a) % c;
		}
		b >>= 1;
		a = (a * a) % c;
	}
	return msg_out;
}

//产生素数，随机产生两个素数
RSA::LONG RSA::producePrime()
{
	srand(time(nullptr));
	LONG prime = 0;
	while (1) {
		prime = rand() % 50 + 2;
		if (isPrime(prime))
			break;
	}
	return prime;
}

//判断一个数是否是素数
bool RSA::isPrime(LONG prime) {
	if (prime < 2)
		return false;
	LONG sqrt_prime = static_cast<LONG>(sqrt(prime));
	for (LONG i = 3; i < sqrt_prime; i += 2)
		if (prime % i == 0)
			return false;
	return true;
}

//产生所有的key值
void RSA::produceKeys() {
	//选择两个不相等的素数
	LONG prime1 = producePrime();
	LONG prime2 = producePrime();
	while (prime1 == prime2)
		prime2 = producePrime();
	_key.share_key = produceShareKey(prime1, prime2);
	LONG orla = produceOrla(prime1, prime2);
	_key.public_key = producePublicKey(orla);
	_key.private_key = producePrivateKey(_key.public_key, orla);
}

//求share_kay
RSA::LONG RSA::produceShareKey(LONG prime1, LONG prime2) {
	return prime1 * prime2;
}

//根据欧拉函数求乘积
RSA::LONG RSA::produceOrla(LONG prime1, LONG prime2) {
	return (prime1 - 1) * (prime2 - 1);
}

//求public_key，随机选择一个数， 1 < public_key < orla，public_key,oala互质
RSA::LONG RSA::producePublicKey(LONG orla) {
	LONG public_key;
	srand(time(nullptr));
	while (1) {
		public_key = rand() % orla;
		if (public_key > 1 && gcd(public_key, orla) == 1)
			break;
	}
	return public_key;
}

RSA::LONG RSA::gcd(LONG public_key, LONG orla) {
	LONG residual;
	while (residual = public_key % orla) {
		public_key = orla;
		orla = residual;
	}
	return orla;
}

RSA::LONG RSA::producePrivateKey(LONG public_key, LONG orla) {
	//(public_key * private_key) % orla == 1
	LONG private_key = orla / public_key;
	while (1) {
		if ((public_key * private_key) % orla == 1)
			break;
		++private_key;
	}
	return private_key;
}