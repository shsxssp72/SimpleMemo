//
// Created by 星落_月残 on 2018/12/27.
//

#ifndef SIMPLEMEMO_CRYPTO_H
#define SIMPLEMEMO_CRYPTO_H


#include <mutex>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include <cryptopp/sha3.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/aes.h>
#include <cryptopp/rc6.h>
#include <cryptopp/twofish.h>
#include <cryptopp/serpent.h>
#include <cryptopp/rsa.h>
#include <cryptopp/randpool.h>
#include <cryptopp/osrng.h>
#include "AbstractSingleton.h"
#include "Commons.h"


//TODO 改为map<string,内部类>的方式，使用时get内部实体，并使用bind传出函数，要求内部实体无状态,需要在构造函数中添加初始化语句
//TODO 统一内部类接口
//TODO 可能的params:toEncode,result,可选的key,iv等






struct CryptoParameters
{
	CryptoParameters(std::string_view input="",std::string_view key="",std::string_view iv="")
	:input(input),key(key),iv(iv)
	{}
	std::string input;
	std::string key;
	std::string iv;
};

class AbstractCryptoProcess
{
public:
	virtual std::string operator()(const CryptoParameters &parameters) const = 0;
};

template<class E>
class EncodeTemplate:public AbstractCryptoProcess
{
public:
	std::string operator()(const CryptoParameters &parameters) const override
	{
		if(isAnyStringEmpty(&parameters.input))
			throw std::invalid_argument("Crypto: Input should not be empty when encoding/decoding.");
		static_assert(std::is_base_of<CryptoPP::BufferedTransformation,E>::value);
		std::string output;
		CryptoPP::StringSource(parameters.input,true,new E(new CryptoPP::StringSink(output)));
		return output;
	}
};

template<class H>
class HashTemplate:public AbstractCryptoProcess
{
public:
	std::string operator()(const CryptoParameters &parameters) const override
	{
		if(isAnyStringEmpty(parameters.input))
			throw std::invalid_argument("Crypto: Input should not be empty when hashing.");
		static_assert(std::is_base_of<CryptoPP::HashTransformation,H>::value);
		H hashGenerator;
		std::string output;
		CryptoPP::StringSource(parameters.input,true,new CryptoPP::HashFilter(hashGenerator,new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));
		return output;
	}
};

template<class S>
class SymmetricTemplate:public AbstractCryptoProcess
{
public:
	std::string operator()(const CryptoParameters &parameters) const override
	{
		if(isAnyStringEmpty(parameters.input,parameters.key,parameters.iv))
			throw std::invalid_argument("Crypto: Input, key and iv should not be empty when encrypting/decrypting.");
		static_assert(std::is_base_of<CryptoPP::StreamTransformation,S>::value);
		std::string bKey,bIV;
		CryptoPP::StringSource(parameters.key,true,new CryptoPP::Base64Decoder(new CryptoPP::StringSink(bKey)));
		CryptoPP::StringSource(parameters.iv,true,new CryptoPP::Base64Decoder(new CryptoPP::StringSink(bIV)));
		CryptoPP::SecByteBlock key(reinterpret_cast<const CryptoPP::byte *>(bKey.data()),bKey.size());
		CryptoPP::SecByteBlock iv(reinterpret_cast<const CryptoPP::byte *>(bIV.data()),bIV.size());

		S s(key,key.size(),iv);
		std::string output;
		CryptoPP::StringSource(parameters.input,true,new CryptoPP::StreamTransformationFilter(s,new CryptoPP::StringSink(output)));
		return output;
	}
};

template<class A>
class AsymmetricEncryptTemplate:public AbstractCryptoProcess
{
public:
	std::string operator()(const CryptoParameters &parameters) const override
	{
		if(isAnyStringEmpty(parameters.input,parameters.key))
			throw std::invalid_argument("Crypto: Input and key should not be empty when encrypting.");
		CryptoPP::StringSource publString(parameters.key,true,new CryptoPP::HexDecoder);
		CryptoPP::AutoSeededRandomPool rnd;
		A publ(publString);
		std::string output;
		CryptoPP::StringSource(parameters.input,true,new CryptoPP::PK_EncryptorFilter(rnd,publ,new CryptoPP::HexEncoder(new CryptoPP::StringSink(output))));
		return output;
	}
};

CryptoPP::RandomPool &GlobalRNG()
{
	static CryptoPP::RandomPool randomPool;
	return randomPool;
}

template<class A>
class AsymmetricDecryptTemplate:public AbstractCryptoProcess
{
public:
	std::string operator()(const CryptoParameters &parameters) const override
	{
		if(isAnyStringEmpty(parameters.input,parameters.key))
			throw std::invalid_argument("Crypto: Input and key should not be empty when decrypting.");
		CryptoPP::StringSource privString(parameters.key,true,new CryptoPP::HexDecoder);
		A priv(privString);
		std::string output;
		CryptoPP::StringSource(parameters.input,true,new CryptoPP::HexDecoder(new CryptoPP::PK_DecryptorFilter(GlobalRNG(),priv,new CryptoPP::StringSink(output))));
		return output;
	}
};

struct CryptoKeys
{
	std::string mainKey;
	std::string additionKey;
};

class AbstractKeyGeneration
{
public:
	virtual CryptoKeys operator()() const = 0;
};

template<class K>
class SymmetricKeyGeneratorTemplate:public AbstractKeyGeneration
{
public:
	CryptoKeys operator()() const override
	{
		static_assert(std::is_base_of<CryptoPP::BlockCipherDocumentation,K>::value);
		CryptoPP::SecByteBlock key(nullptr,(unsigned long long int)K::MAX_KEYLENGTH);
		CryptoPP::SecByteBlock iv(nullptr,(unsigned long long int)K::BLOCKSIZE);
		CryptoPP::AutoSeededRandomPool rnd;
		rnd.GenerateBlock(key,key.size());
		rnd.GenerateBlock(iv,iv.size());

		std::string KEY(reinterpret_cast<const char *>(key.data()),key.size());
		std::string IV(reinterpret_cast<const char *>(iv.data()),iv.size());
		std::string bKEY;
		std::string bIV;
		CryptoPP::StringSource(KEY,true,new CryptoPP::Base64Encoder(new CryptoPP::StringSink(bKEY)));
		CryptoPP::StringSource(IV,true,new CryptoPP::Base64Encoder(new CryptoPP::StringSink(bIV)));

		CryptoKeys cryptoKeys;
		cryptoKeys.mainKey=bKEY;
		cryptoKeys.additionKey=bIV;
		return cryptoKeys;
	}
};

class RSAKeyGeneration:public AbstractKeyGeneration
{
public:
	CryptoKeys operator()() const override
	{
		std::string privateKeyString,publicKeyString;

		CryptoPP::AutoSeededRandomPool rnd;
		CryptoPP::InvertibleRSAFunction params;
		params.GenerateRandomWithKeySize(rnd,4096);
		CryptoPP::RSA::PrivateKey privatekey(params);
		CryptoPP::RSA::PublicKey publickey(params);

		CryptoPP::RSAES_OAEP_SHA_Decryptor priv(privatekey);
		CryptoPP::HexEncoder privString(new CryptoPP::StringSink(privateKeyString));
		priv.GetMaterial().Save(privString);//DEREncode(privString);
		privString.MessageEnd();

		CryptoPP::RSAES_OAEP_SHA_Encryptor publ(publickey);
		CryptoPP::HexEncoder publString(new CryptoPP::StringSink(publicKeyString));
		publ.GetMaterial().Save(publString);//DEREncode(publString);
		publString.MessageEnd();

		CryptoKeys cryptoKeys;
		cryptoKeys.mainKey=privateKeyString;
		cryptoKeys.additionKey=publicKeyString;
		return cryptoKeys;
	}
};


using Base64Encode=EncodeTemplate<CryptoPP::Base64Encoder>;
using Base64Decode=EncodeTemplate<CryptoPP::Base64Decoder>;

using WhirlpoolHash=HashTemplate<CryptoPP::Whirlpool>;
using SHA3_512Hash=HashTemplate<CryptoPP::SHA3_512>;

using AES_CFBEncrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption>;
using AES_CFBDecrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption>;
using RC6_CFBEncrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::RC6>::Encryption>;
using RC6_CFBDecrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::RC6>::Decryption>;
using Twofish_CFBEncrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::Twofish>::Encryption>;
using Twofish_CFBDecrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::Twofish>::Decryption>;
using Serpent_CFBEncrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::Serpent>::Encryption>;
using Serpent_CFBDecrypt=SymmetricTemplate<CryptoPP::CFB_Mode<CryptoPP::Serpent>::Decryption>;


using RSA_OEAP_SHAEncrypt=AsymmetricEncryptTemplate<CryptoPP::RSAES_OAEP_SHA_Encryptor>;
using RSA_OEAP_SHADecrypt=AsymmetricDecryptTemplate<CryptoPP::RSAES_OAEP_SHA_Decryptor>;

using AESKeyGeneration=SymmetricKeyGeneratorTemplate<CryptoPP::AES>;
using RC6KeyGeneration=SymmetricKeyGeneratorTemplate<CryptoPP::RC6>;
using TwofishKeyGeneration=SymmetricKeyGeneratorTemplate<CryptoPP::Twofish>;
using SerpentKeyGeneration=SymmetricKeyGeneratorTemplate<CryptoPP::Serpent>;

class Crypto:public AbstractSingleton<Crypto>
{
	friend class std::shared_ptr<Crypto>;

	friend class AbstractSingleton<Crypto>;

public:
	const std::function<std::string(const CryptoParameters &)> getOperation(const std::string &name)
	{
		//注意处理out_of_range异常
		auto &toRetrieve=operations.at(name);
		return std::bind(&AbstractCryptoProcess::operator(),toRetrieve,std::placeholders::_1);
	}
	const std::function<CryptoKeys()> getKeyGenerator(const std::string &name)
	{
		//注意处理out_of_range异常
		auto &toRetrieve=keyGenerators.at(name);
		return std::bind(&AbstractKeyGeneration::operator(),toRetrieve);
	}

private:
	Crypto()
	{
		operations.insert(std::make_pair("Base64Encode",std::make_shared<Base64Encode>()));
		operations.insert(std::make_pair("Base64Decode",std::make_shared<Base64Decode>()));
		operations.insert(std::make_pair("WhirlpoolHash",std::make_shared<WhirlpoolHash>()));
		operations.insert(std::make_pair("SHA3_512Hash",std::make_shared<SHA3_512Hash>()));
		operations.insert(std::make_pair("AES_CFBEncrypt",std::make_shared<AES_CFBEncrypt>()));
		operations.insert(std::make_pair("AES_CFBDecrypt",std::make_shared<AES_CFBDecrypt>()));
		operations.insert(std::make_pair("RC6_CFBEncrypt",std::make_shared<RC6_CFBEncrypt>()));
		operations.insert(std::make_pair("RC6_CFBDecrypt",std::make_shared<RC6_CFBDecrypt>()));
		operations.insert(std::make_pair("Twofish_CFBEncrypt",std::make_shared<Twofish_CFBEncrypt>()));
		operations.insert(std::make_pair("Twofish_CFBDecrypt",std::make_shared<Twofish_CFBDecrypt>()));
		operations.insert(std::make_pair("Serpent_CFBEncrypt",std::make_shared<Serpent_CFBEncrypt>()));
		operations.insert(std::make_pair("Serpent_CFBDecrypt",std::make_shared<Serpent_CFBDecrypt>()));
		operations.insert(std::make_pair("RSA_OEAP_SHAEncrypt",std::make_shared<RSA_OEAP_SHAEncrypt>()));
		operations.insert(std::make_pair("RSA_OEAP_SHADecrypt",std::make_shared<RSA_OEAP_SHADecrypt>()));

		keyGenerators.insert(std::make_pair("AES",std::make_shared<AESKeyGeneration>()));
		keyGenerators.insert(std::make_pair("RC6",std::make_shared<RC6KeyGeneration>()));
		keyGenerators.insert(std::make_pair("Twofish",std::make_shared<TwofishKeyGeneration>()));
		keyGenerators.insert(std::make_pair("Serpent",std::make_shared<SerpentKeyGeneration>()));
		keyGenerators.insert(std::make_pair("RSA",std::make_shared<RSAKeyGeneration>()));
	}
	std::map<std::string,std::shared_ptr<AbstractCryptoProcess>> operations;
	std::map<std::string,std::shared_ptr<AbstractKeyGeneration>> keyGenerators;
};


#endif //SIMPLEMEMO_CRYPTO_H
