#include "ft_ssl_crypt.h"
static char *extract_salt(t_des_flags *f, unsigned char **ciphertext, uint32_t *cipher_len)
{
    char *salt;

    if (strncmp((const char*)ciphertext,"Salted__",8) == 0)
        memcpy(salt,&ciphertext[8],8);
    ciphertext += 16;
    (*cipher_len) -= 16;
    f->salt = salt;
}

unsigned char    *decrypt(unsigned char *ciphertext, int ciphertext_len, t_des_flags f)
{
    unsigned char   *plaintext;
    uint32_t        plaintext_len;

    if (!(plaintext = (unsigned char*)malloc(ciphertext_len + 1)))
        return (NULL);
    ft_bzero(plaintext, ciphertext_len);
    /* Create and initialise the context */
   
    /* Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     */

    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    
    /* Finalize the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    
    /* Add the null terminator */
    plaintext[plaintext_len] = 0;
    /* Clean up */
    return (plaintext);
}