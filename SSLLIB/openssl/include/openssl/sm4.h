/*added by aisino gxg 201301
*/

#ifndef HEADER_SM4_H
#define HEADER_SM4_H

#include <openssl/opensslconf.h>

#include <stddef.h>

#ifdef OPENSSL_NO_SM4
#error SM4 is disabled.
#endif

#define SM4_ENCRYPT	1
#define SM4_DECRYPT	0

/* Because array size can't be a const in C, the following two are macros.
   Both sizes are in bytes. */
#define SM4_ROUNDS  32
#define SM4_MAXNR 36
#define SM4_BLOCK_SIZE 16
#define SM4_KEY_LENGTH 16

#ifdef OPENSSL_FIPS
#define FIPS_SM4_SIZE_T	int
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/* This should be a hidden type, but EVP requires that the size be known */
struct sm4_key_st {
#ifdef SM4_LONG
    unsigned long rd_key[SM4_MAXNR];
#else
    unsigned int rd_key[SM4_MAXNR];
#endif
    int rounds;
};
typedef struct sm4_key_st SM4_KEY;
 

int SM4_set_encrypt_key(const unsigned char *userKey, const int bits,
	SM4_KEY *key);
int SM4_set_decrypt_key(const unsigned char *userKey, const int bits,
	SM4_KEY *key);

void SM4_encrypt(const unsigned char *in, unsigned char *out,
	const SM4_KEY *key);
void SM4_decrypt(const unsigned char *in, unsigned char *out,
	const SM4_KEY *key);

void SM4_ecb_encrypt(const unsigned char *in, unsigned char *out,
	const SM4_KEY *key, const int enc);

void SM4_cbc_encrypt(const unsigned char *in, unsigned char *out,
		     size_t len, const SM4_KEY *key,
		     unsigned char *ivec, const int enc);
void AES_ofb128_encrypt(const unsigned char *in, unsigned char *out,
	size_t length, const SM4_KEY *key,
	unsigned char *ivec, int *num);
void SM4_cfb128_encrypt(const unsigned char *in, unsigned char *out,
	size_t length, const SM4_KEY *key,
	unsigned char *ivec, int *num, const int enc) ;


#ifdef  __cplusplus
}
#endif

#endif /* !HEADER_SM4_H */
