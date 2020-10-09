#include <openssl/md5.h>
#include <stdio.h>
#include <time.h>

unsigned char md5sumresult[MD5_DIGEST_LENGTH];
char md5sumresulthex[MD5_DIGEST_LENGTH * 2 + 1];
FILE *logfile;
time_t timer;
char outputbuffer[0x100];
struct tm *tm_info;

unsigned char *md5sum(const unsigned char *data, size_t len);
char *md5sumhex(const unsigned char *data, size_t len);
void printhexdump(const unsigned char *data, size_t len);
void loginit();
void logtime();
void logclose();

unsigned char *md5sum(const unsigned char *data, size_t len) {
  MD5(data, len, md5sumresult);
  return md5sumresult;
}
char *md5sumhex(const unsigned char *data, size_t len) {
  int i;

  MD5(data, len, md5sumresult);
  memset(md5sumresulthex, 0, sizeof(md5sumresulthex));
  for (i = 0; i < 16; i++) {
    sprintf(md5sumresulthex + strlen(md5sumresulthex), "%02x", md5sumresult[i]);
  }
  return md5sumresulthex;
}
void hexdump(const unsigned char *data, size_t len) {
  int i;
  for (i = 0; i < len; i++) {
    if (i % 16 == 0 && i != 0) {
      puts("");
    }
    printf("%02x ", data[i]);
  }
}
void loginit() {
  logfile = fopen("/tmp/aflfuzzlog.txt", "wb");
  if (logfile == NULL) {
    fprintf(stderr, "open /tmp/aflfuzzlog.txt error");
    exit(-1);
  }
  atexit(logclose);
}
void logtime() {
  time(&timer);
  tm_info = localtime(&timer);
  strftime(outputbuffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
  fprintf(logfile, "[%s] ", outputbuffer);
}

#define loginfo(msg...) ;

#define loginfotest(msg...)                                                        \
  logtime();                                                                   \
  fprintf(logfile, msg);                                                       \
  fprintf(logfile, "\n");                                                      \
  fflush(logfile);

#define logdebug(msg...)                                                        \
  logtime();                                                                   \
  fprintf(logfile, msg);                                                       \
  fprintf(logfile, "\n");                                                      \
  fflush(logfile);

void logclose() { fclose(logfile); }
