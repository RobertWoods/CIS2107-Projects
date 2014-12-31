#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "blowfish.h"

int main(void)
{
  uint32_t stuff[] = {
    0x72657645,0x69687479,0x6920676e,0x77612073,
    0x6d6f7365,0x45200a65,0x79726576,0x6e696874,
    0x73692067,0x6f6f6320,0x6877206c,0x79206e65,
    0x7227756f,0x61702065,0x6f207472,0x20612066,
    0x6d616574,0x7645200a,0x74797265,0x676e6968,
    0x20736920,0x73657761,0xa656d6f,0x65685720,
    0x6577206e,0x20657227,0x6976696c,0x6f20676e,
    0x64207275,0x6d616572,0x200a200a,0x72657645,
    0x69687479,0x6920676e,0x65622073,0x72657474,
    0x65687720,0x6577206e,0x69747320,0x74206b63,
    0x7465676f,0xa726568,0x64695320,0x79622065,
    0x64697320,0x59200a65,0x6120756f,0x4920646e,
    0x6f47200a,0x20616e6e,0x206e6977,0x65726f66,
    0xa726576,0x74654c20,0x70207327,0x79747261,
    0x726f6620,0x72657665,0x200a200a,0x72276557,
    0x68742065,0x61732065,0x200a656d,0x206d2749,
    0x656b696c,0x756f7920,0x6f59200a,0x65722775,
    0x6b696c20,0x656d2065,0x6557200a,0x20657227,
    0x206c6c61,0x6b726f77,0x20676e69,0x68206e69,
    0x6f6d7261,0x200a796e,0x7645200a,0x74797265,
    0x676e6968,0x20736920,0x73657761,0xa656d6f,
    0x65764520,0x68747972,0x20676e69,0x63207369,
    0x206c6f6f,0x6e656877,0x756f7920,0x20657227,
    0x74726170,0x20666f20,0x65742061,0x200a6d61,
    0x72657645,0x69687479,0x6920676e,0x77612073,
    0x6d6f7365,0x57200a65,0x206e6568,0x72276577,
    0x696c2065,0x676e6976,0x72756f20,0x65726420,
    0x200a6d61,0x6854200a,0x2c656572,0x6f777420,
    0x6e6f202c,0x200a2e65,0x6148200a,0x79206576,
    0x6820756f,0x64726165,0x65687420,0x77656e20,
    0x76652073,0x6f797265,0x7327656e,0x6c617420,
    0x676e696b,0x694c200a,0x69206566,0x6f672073,
    0x2720646f,0x73756163,0x76652065,0x74797265,
    0x676e6968,0x61207327,0x6f736577,0x200a656d,
    0x74736f4c,0x20796d20,0x2c626f6a,0x65687420,
    0x73276572,0x6e206120,0x6f207765,0x69727070,
    0x696e7574,0x200a7974,0x65726f4d,0x65726620,
    0x69742065,0x6620656d,0x6d20726f,0x77612079,
    0x6d6f7365,0x6f632065,0x6e756d6d,0xa797469,
    0x49200a20,0x65656620,0x6f6d206c,0x61206572,
    0x6f736577,0x7420656d,0x206e6168,0x61206e61,
    0x6f736577,0x7020656d,0x7573736f,0x44200a6d,
    0x6d207069,0x6f622079,0x69207964,0x6863206e,
    0x6c6f636f,0x20657461,0x736f7266,0x676e6974,
    0x6854200a,0x20656572,0x72616579,0x616c2073,
    0x20726574,0x68736177,0x66666f20,0x65687420,
    0x6f726620,0x6e697473,0x53200a67,0x6c6c656d,
    0x20676e69,0x656b696c,0x62206120,0x73736f6c,
    0x202c6d6f,0x72657645,0x69687479,0x6920676e,
    0x77612073,0x6d6f7365,0x53200a65,0x70706574,
    0x69206465,0x756d206e,0x67202c64,0x6e20746f,
    0x62207765,0x6e776f72,0x6f687320,0x200a7365,
    0x73277449,0x65776120,0x656d6f73,0x206f7420,
    0x206e6977,0x20646e61,0x73277469,0x65776120,
    0x656d6f73,0x206f7420,0x65736f6c,0x200a200a,
    0x72657645,0x69687479,0x6920676e,0x65622073,
    0x72657474,0x65687720,0x6577206e,0x69747320,
    0x74206b63,0x7465676f,0xa726568,0x64695320,
    0x79622065,0x64697320,0x59200a65,0x6120756f,
    0x4920646e,0x6f47200a,0x20616e6e,0x206e6977,
    0x65726f66,0xa726576,0x74654c20,0x70207327,
    0x79747261,0x726f6620,0x72657665,0x200a200a,
    0x72276557,0x68742065,0x61732065,0x200a656d,
    0x206d2749,0x656b696c,0x756f7920,0x6f59200a,
    0x65722775,0x6b696c20,0x656d2065,0x6557200a,
    0x20657227,0x206c6c61,0x6b726f77,0x20676e69,
    0x68206e69,0x6f6d7261,0x200a796e,0x7645200a,
    0x74797265,0x676e6968,0x20736920,0x73657761,
    0xa656d6f,0x65764520,0x68747972,0x20676e69,
    0x63207369,0x206c6f6f,0x6e656877,0x756f7920,
    0x20657227,0x74726170,0x20666f20,0x65742061,
    0x200a6d61,0x72657645,0x69687479,0x6920676e,
    0x77612073,0x6d6f7365,0x57200a65,0x206e6568,
    0x72276577,0x696c2065,0x676e6976,0x72756f20,
    0x65726420,0x200a6d61,0x6c42200a,0x73206575,
    0x7365696b,0x6f62202c,0x79636e75,0x72707320,
    0x73676e69,0x6557200a,0x73756a20,0x616e2074,
    0x2064656d,0x206f7774,0x73657761,0x20656d6f,
    0x6e696874,0x200a7367,0x6f4e2041,0x206c6562,
    0x7a697270,0x61202c65,0x65697020,0x6f206563,
    0x74732066,0x676e6972,0x6f59200a,0x6e6b2075,
    0x7720776f,0x27746168,0x77612073,0x6d6f7365,
    0x76652d65,0x74797265,0x676e6968,0x7254200a,
    0x2c736565,0x6f726620,0x202c7367,0x676f6c63,
    0x68742073,0x72277965,0x77612065,0x6d6f7365,
    0x52200a65,0x736b636f,0x6c63202c,0x736b636f,
    0x646e6120,0x636f7320,0x7420736b,0x27796568,
    0x61206572,0x6f736577,0x200a656d,0x73676946,
    0x646e6120,0x67696a20,0x6e612073,0x77742064,
    0x20736769,0x74616874,0x61207327,0x6f736577,
    0x200a656d,0x72657645,0x69687479,0x7920676e,
    0x7320756f,0x6f206565,0x68742072,0x206b6e69,
    0x7320726f,0x69207961,0x77612073,0x6d6f7365,
    0xa200a65,0x65764520,0x68747972,0x20676e69,
    0x61207369,0x6f736577,0x200a656d,0x72657645,
    0x69687479,0x6920676e,0x6f632073,0x77206c6f,
    0x206e6568,0x27756f79,0x70206572,0x20747261,
    0x6120666f,0x61657420,0x45200a6d,0x79726576,
    0x6e696874,0x73692067,0x65776120,0x656d6f73,
    0x6857200a,0x77206e65,0x65722765,0x76696c20,
    0x20676e69,0x2072756f,0x61657264,0x00000000
  };

  uint32_t more_stuff[] = {
    0x72657645,0x69687479,0x6920676e,0x77612073,
    0x6d6f7365,0x45200a65,0x79726576,0x6e696874,
    0x73692067,0x6f6f6320,0x6877206c,0x79206e65,
    0x7227756f,0x61702065,0x6f207472,0x20612066,
    0x6d616574,0x7645200a,0x74797265,0x676e6968,
    0x20736920,0x73657761,0xa656d6f,0x65685720,
    0x6577206e,0x20657227,0x6976696c,0x6f20676e,
    0x64207275,0x6d616572,0x200a200a,0x72657645,
    0x69687479,0x6920676e,0x65622073,0x72657474,
    0x65687720,0x6577206e,0x69747320,0x74206b63,
    0x7465676f,0xa726568,0x64695320,0x79622065,
    0x64697320,0x59200a65,0x6120756f,0x4920646e,
    0x6f47200a,0x20616e6e,0x206e6977,0x65726f66,
    0xa726576,0x74654c20,0x70207327,0x79747261,
    0x726f6620,0x72657665,0x200a200a,0x72276557,
    0x68742065,0x61732065,0x200a656d,0x206d2749,
    0x656b696c,0x756f7920,0x6f59200a,0x65722775,
    0x6b696c20,0x656d2065,0x6557200a,0x20657227,
    0x206c6c61,0x6b726f77,0x20676e69,0x68206e69,
    0x6f6d7261,0x200a796e,0x7645200a,0x74797265,
    0x676e6968,0x20736920,0x73657761,0xa656d6f,
    0x65764520,0x68747972,0x20676e69,0x63207369,
    0x206c6f6f,0x6e656877,0x756f7920,0x20657227,
    0x74726170,0x20666f20,0x65742061,0x200a6d61,
    0x72657645,0x69687479,0x6920676e,0x77612073,
    0x6d6f7365,0x57200a65,0x206e6568,0x72276577,
    0x696c2065,0x676e6976,0x72756f20,0x65726420,
    0x200a6d61,0x6854200a,0x2c656572,0x6f777420,
    0x6e6f202c,0x200a2e65,0x6148200a,0x79206576,
    0x6820756f,0x64726165,0x65687420,0x77656e20,
    0x76652073,0x6f797265,0x7327656e,0x6c617420,
    0x676e696b,0x694c200a,0x69206566,0x6f672073,
    0x2720646f,0x73756163,0x76652065,0x74797265,
    0x676e6968,0x61207327,0x6f736577,0x200a656d,
    0x74736f4c,0x20796d20,0x2c626f6a,0x65687420,
    0x73276572,0x6e206120,0x6f207765,0x69727070,
    0x696e7574,0x200a7974,0x65726f4d,0x65726620,
    0x69742065,0x6620656d,0x6d20726f,0x77612079,
    0x6d6f7365,0x6f632065,0x6e756d6d,0xa797469,
    0x49200a20,0x65656620,0x6f6d206c,0x61206572,
    0x6f736577,0x7420656d,0x206e6168,0x61206e61,
    0x6f736577,0x7020656d,0x7573736f,0x44200a6d,
    0x6d207069,0x6f622079,0x69207964,0x6863206e,
    0x6c6f636f,0x20657461,0x736f7266,0x676e6974,
    0x6854200a,0x20656572,0x72616579,0x616c2073,
    0x20726574,0x68736177,0x66666f20,0x65687420,
    0x6f726620,0x6e697473,0x53200a67,0x6c6c656d,
    0x20676e69,0x656b696c,0x62206120,0x73736f6c,
    0x202c6d6f,0x72657645,0x69687479,0x6920676e,
    0x77612073,0x6d6f7365,0x53200a65,0x70706574,
    0x69206465,0x756d206e,0x67202c64,0x6e20746f,
    0x62207765,0x6e776f72,0x6f687320,0x200a7365,
    0x73277449,0x65776120,0x656d6f73,0x206f7420,
    0x206e6977,0x20646e61,0x73277469,0x65776120,
    0x656d6f73,0x206f7420,0x65736f6c,0x200a200a,
    0x72657645,0x69687479,0x6920676e,0x65622073,
    0x72657474,0x65687720,0x6577206e,0x69747320,
    0x74206b63,0x7465676f,0xa726568,0x64695320,
    0x79622065,0x64697320,0x59200a65,0x6120756f,
    0x4920646e,0x6f47200a,0x20616e6e,0x206e6977,
    0x65726f66,0xa726576,0x74654c20,0x70207327,
    0x79747261,0x726f6620,0x72657665,0x200a200a,
    0x72276557,0x68742065,0x61732065,0x200a656d,
    0x206d2749,0x656b696c,0x756f7920,0x6f59200a,
    0x65722775,0x6b696c20,0x656d2065,0x6557200a,
    0x20657227,0x206c6c61,0x6b726f77,0x20676e69,
    0x68206e69,0x6f6d7261,0x200a796e,0x7645200a,
    0x74797265,0x676e6968,0x20736920,0x73657761,
    0xa656d6f,0x65764520,0x68747972,0x20676e69,
    0x63207369,0x206c6f6f,0x6e656877,0x756f7920,
    0x20657227,0x74726170,0x20666f20,0x65742061,
    0x200a6d61,0x72657645,0x69687479,0x6920676e,
    0x77612073,0x6d6f7365,0x57200a65,0x206e6568,
    0x72276577,0x696c2065,0x676e6976,0x72756f20,
    0x65726420,0x200a6d61,0x6c42200a,0x73206575,
    0x7365696b,0x6f62202c,0x79636e75,0x72707320,
    0x73676e69,0x6557200a,0x73756a20,0x616e2074,
    0x2064656d,0x206f7774,0x73657761,0x20656d6f,
    0x6e696874,0x200a7367,0x6f4e2041,0x206c6562,
    0x7a697270,0x61202c65,0x65697020,0x6f206563,
    0x74732066,0x676e6972,0x6f59200a,0x6e6b2075,
    0x7720776f,0x27746168,0x77612073,0x6d6f7365,
    0x76652d65,0x74797265,0x676e6968,0x7254200a,
    0x2c736565,0x6f726620,0x202c7367,0x676f6c63,
    0x68742073,0x72277965,0x77612065,0x6d6f7365,
    0x52200a65,0x736b636f,0x6c63202c,0x736b636f,
    0x646e6120,0x636f7320,0x7420736b,0x27796568,
    0x61206572,0x6f736577,0x200a656d,0x73676946,
    0x646e6120,0x67696a20,0x6e612073,0x77742064,
    0x20736769,0x74616874,0x61207327,0x6f736577,
    0x200a656d,0x72657645,0x69687479,0x7920676e,
    0x7320756f,0x6f206565,0x68742072,0x206b6e69,
    0x7320726f,0x69207961,0x77612073,0x6d6f7365,
    0xa200a65,0x65764520,0x68747972,0x20676e69,
    0x61207369,0x6f736577,0x200a656d,0x72657645,
    0x69687479,0x6920676e,0x6f632073,0x77206c6f,
    0x206e6568,0x27756f79,0x70206572,0x20747261,
    0x6120666f,0x61657420,0x45200a6d,0x79726576,
    0x6e696874,0x73692067,0x65776120,0x656d6f73,
    0x6857200a,0x77206e65,0x65722765,0x76696c20,
    0x20676e69,0x2072756f,0x61657264,0x00000000
  };


  char *key = "LAME_KEY";
  BLOWFISH_CTX ctx;
  int i,
    stufflen,			/* length of the stuff array */
    keylen;			/* length of the key */
  char *p;
  
  /* remember that we have to be careful with such
     uses of sizeof */
  stufflen=sizeof(stuff)/4;
  keylen=strlen(key);
  Blowfish_Init(&ctx, (unsigned char*)key, keylen);

  printf("Encrypting buffer ...\n");
  for (i=0; i<stufflen; i++) {
    Blowfish_Encrypt(&ctx, &stuff[i], &more_stuff[i]);
  }

  printf("Decrypting buffer ...\n");
  for (i=0; i<stufflen; i++) {
    Blowfish_Decrypt(&ctx, &stuff[i], &more_stuff[i]);
  }

  printf("Done.\n");
  return 0;
}
