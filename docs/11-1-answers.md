# 11.1 Describe terms and concepts associated with secure coding practices

### Objectives

- [ ] Common string-handling functions
- [ ] Which functions guarantee null terminated strings
- [ ] An off-by-one error
- [ ] An integer overflow
- [ ] A buffer overflow
- [ ] The concept of use-after-free
- [ ] Resource acquisition is initialization (RAII)
- [ ] The difference between input validation vs. input sanitization
- [ ] General low-level crypto basics (e.g. different encryption schemes and how you might implement them system wide, what crypto is better for different use cases)
- [ ] Penetration testing principles, tools, and techniques
- [ ] Obfuscation techniques
- [ ] The meaning of a pure function and if a function has a side-effect

### Answers

**Common string-handling functions**
> strcmp, strncmp, strcpy, strncpy, strlcpy, strcat, strlcat, strcat. In general to be secure the 'n' or 'l' versions of the functions should be used. These functions allow you to set the number of bytes to copy/cat/cmp or return the number of bytes in addition they have underlying mechanisms particulary in the case of the 'l' versions to prevent potential security problems.

**Which functions guarantee null terminated strings**
> stpcpy, strcpy, strcat as long as the source string(s) are null terminated and the provided buffer is large enough for the result plus the null terminator. strncat will be null terminated as long as the buffer is large enough (n + 1). snprintf will always null terminate as long as the buffer is large enough. strlcpy and strlcat will always null terminate.

**An off-by-one error**
> Can happen during loops where you iterate one past the length of an array or one less (when that was not the intent). This can cause buffer overflows, arbitrary code execution and boundary errors like improper input validation.

**An integer overflow**
> This occurs when a arithmetic operation causes a integer value to exceed its max or minimum possible value (based on the number of bytes used to store it). This generally leads to unexpected behavior and can result in buffer overflow, memory corruption, privilege escalation and crashing.

**A buffer overflow**
> Occurs when more data is written to a buffer than it was meant to hold. This can cause several issues including arbitrary code execution, crashes, data corruption, etc.

**The concept of use-after-free**
> Occurs when a pointer is used after it has been freed. Can cause undefined behavior, including the execution of arbitrary code, crashes, and data corruption.

**Resource acquisition is initialization (RAII)**
> Used in object-oriented languages to manage allocation and deallocation. The idea is to tie resource management(memory allocations, file handles, etc) to the lifetime of an object so that when it goes out of scope those resources can be reclaimed.

**The difference between input validation vs. input sanitization**
> Input validation is used to ensure whatever input received meets any specified criteria such as length, type, value ranges, and format. Input sanitization is modifying input to make it safe to use. This is generally done when input could be interpreted as code (e.g. sql injection, cross-site scripting or command injection).

**General low-level crypto basics (e.g. different encryption schemes and how you might implement them system wide, what crypto is better for different use cases)**
> Symmetric - use a single key for encryption/decryption of data; should use a strong encryption method like AES256. Good for use on files and database.
> Asymmetric - uses a public key for encryption and private key for decryption; use RSA or ECC encryption algorithm; useful for performing key exchange for TLS/SSL
> Hashing - useful for data integrity (i.e. checksums) and storing passwords (particularly with a salt); hash functions like SHA-256 should be used over MD5 as it has been broken
> Message Authentication Codes - uses a secrety key along with a hash to ensure data integrity and authenticity in messages/transmitted data; use crypto hash function like HMAC-SHA-256
> Digital Signatures - a sender signs the data with their private key and the receiver verifies with the sender's public key. 

**Penetration testing principles, tools, and techniques**
> The 5 stages of penetration testing:
> Planning and reconnaissance - Identify objectives and scope. Gather information about the network(layout, OSs, applications present)
> Vulnerability assessment - Find access points and weaknesses. Guessable passwords, coding errors, poor data protection, etc. Use of tools like vulnerability scanners are used (Nessuss, Trivy, etc)
> Security breaching - Use of cross-site scripting, sql injection, backdoors, and other strategies like privilege escalation to bypass security like firewalls. 
> Documentation - Compile a report containing vulnerabilities discovered and their potential impact, evaluation of incident response, and strategies for improving security.
> Remediation - Propose mitigation strategies suchs as patching, data encryption, and limiting permissions. Additional testing can be performed after mitigation steps are implemented.

**Obfuscation techniques**
> The process of replacing sensitive information with data that looks like real production information.
> Masking out where the type of data does not change only its values; maintaining a similar structure.
> Data encryption to make the data unusable until decrypted.
> Data tokenization replaces certain data with meaningless values.

**The meaning of a pure function and if a function has a side-effect**
> Pure functions when given the same input always return the same output, does not depend on or modify data outside of its scope, does not rely on side-causes (hidden inputs) and does not produce side-effects (hidden outputs)

