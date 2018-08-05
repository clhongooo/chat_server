#include "buffer.h"
#include <map>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#include "tcp_socket.h" // for OnRead()

struct buffer {
  char *reader;
  uint32_t readed;
  uint32_t read_max;
  uint32_t read_total;
  TcpSocket *ts;

  char *writer;
  int writen;
  int write_max;
  uint32_t write_total;

  // for big file > 64KB
  char *extra; // reader

  // file <= 64KB
  char data[0];
};

static std::map<int, struct buffer*> buf_map;

void sock_onread(int sockfd, char *data, int len)
{
  data[len-1] = '\0';
  printf("client %d: len=%d, data=%s\n", sockfd, len, data);
  fflush(stdout);

  data[0] = 'S';
  send_data(sockfd, data, len);
}

int buf_alloc(int sockfd, unsigned int size)
{
  assert(buf_map.find(sockfd) == buf_map.end());
  if (buf_map.find(sockfd) != buf_map.end())
    return 0;

  struct buffer *pbuf = (struct buffer *)
    malloc(sizeof(struct buffer) + 2 * size * sizeof(char));

  if (!pbuf) {
    perror("malloc");
    return -1;
  }

  pbuf->reader = pbuf->data;
  pbuf->readed = 0;
  pbuf->read_max = size;
  pbuf->read_total = 0;
  pbuf->extra = 0;

  pbuf->writer = pbuf->data + size;
  pbuf->writen = 0;
  pbuf->write_max = size;
  pbuf->write_total = 0;

  buf_map[sockfd] = pbuf;
  return 0;
}

void buf_free(int sockfd)
{
  std::map<int, struct buffer*>::iterator it;
  it = buf_map.find(sockfd);
  if (it != buf_map.end())  {
    struct buffer *pbuf = it->second;
    if (pbuf) {
      if (pbuf->extra)
        free(pbuf->extra);

      free(pbuf);
    }
    buf_map.erase(sockfd);
  }
}

void settcpsocket(int sockfd, TcpSocket *ts)
{
  if (buf_map.find(sockfd) == buf_map.end()) {
    printf("no such sockfd %d:\n", sockfd);
    return;
  }

  struct buffer *pbuf = buf_map[sockfd];
  if (!pbuf)
    return;

  pbuf->ts = ts;
}

int handle_read(int sockfd)
{
  if (buf_map.find(sockfd) == buf_map.end()) {
    printf("no such sockfd %d:\n", sockfd);
    return -1;
  }

  struct buffer *pbuf = buf_map[sockfd];
  if (!pbuf)
    return -1;

  int n;
  while (1) {
    // read length
    if (pbuf->read_total == 0) {
      uint32_t len;
      n = read(sockfd, &len, sizeof(pbuf->read_total));
      if (n <= 0)
        goto fail;

      if (n != sizeof(pbuf->read_total)) {
        printf("client %d: read length failed\n", sockfd);
        len = 0;
      }

      pbuf->read_total = ntohl(len);
      pbuf->readed = n;
      pbuf->reader = pbuf->data;
      if (pbuf->read_total > pbuf->read_max) {
        pbuf->extra = (char*)malloc(pbuf->read_total);
        if (!pbuf->extra) {
          perror("malloc()");
          return -1;
        }
        pbuf->reader = pbuf->extra;
      }
    }

    // read real data
    if (pbuf->read_total == 0)
      continue;

    int left = pbuf->read_total - pbuf->readed;
    while (left > 0) {
      n = read(sockfd, pbuf->reader, left);
      if (n <= 0)
        goto fail;

      pbuf->reader += n;
      pbuf->readed += n;
      left -= n;
      // printf("readed: %.2f/100\n", 1.0*pbuf->readed/pbuf->read_total*100);
    }

    // finish read
    if (pbuf->readed == pbuf->read_total) {
      char *data = pbuf->data;
      if (pbuf->extra)
        data = pbuf->extra;
      int len = pbuf->read_total - sizeof(pbuf->read_total);

      // call back on data
#if 1
      sock_onread(sockfd, data, len);      // test
#endif
      if (pbuf->ts)
        pbuf->ts->OnRead(data, len);

      // recover for next round
      pbuf->read_total = 0;
      pbuf->reader = pbuf->data;
      if (pbuf->extra) {
        free(pbuf->extra);
        pbuf->extra = 0;
      }
    }
  }

 fail:
  if ((n < 0) && (errno == EAGAIN || errno == EWOULDBLOCK))
      return 0;

  printf("client %d: closed, n = %d\n, %s", sockfd, n, strerror(errno));
  close(sockfd);
  buf_free(sockfd);
  return -1;
}

static int handle_write_internal(int sockfd, struct buffer *pbuf)
{
  int n;
  int left = pbuf->write_total - pbuf->writen;
  while (left > 0) {
    n = write(sockfd, pbuf->writer, left);
    if (n <= 0)
      goto fail;
    pbuf->writen += n;
    pbuf->writer += n;
    left -= n;
  }
  // left == 0, send succeed
  pbuf->writen = 0;
  pbuf->writer = pbuf->data + pbuf->read_max;
  pbuf->write_total = 0;
  return 0;

 fail:
  if ((n < 0) && (errno == EAGAIN || errno == EWOULDBLOCK))
    return 0;

  perror("handle_write");
  printf("write error %d, n=%d\n", sockfd, n);
  close(sockfd);
  buf_free(sockfd);
  return -1;
}

void send_data(int sockfd, char *data, int len)
{
  if (buf_map.find(sockfd) == buf_map.end()) {
    printf("no such sockfd %d:\n", sockfd);
    return;
  }

  struct buffer *pbuf = buf_map[sockfd];
  if (!pbuf)
    return;

  if (pbuf->write_total != 0) {
    printf("in sending, please send later\n");
    return;
  }

  if (len > pbuf->write_max) {
    printf("send data cannot exceed size %d\n", pbuf->write_max);
    return;
  }

  pbuf->write_total = len;
  pbuf->writen = 0;
  pbuf->writer = pbuf->data + pbuf->read_max;
  memcpy(pbuf->writer, data, len);

  handle_write_internal(sockfd, pbuf);
}

int handle_write(int sockfd)
{
  if (buf_map.find(sockfd) == buf_map.end()) {
    printf("no such sockfd %d:\n", sockfd);
    return -1;
  }

  struct buffer *pbuf = buf_map[sockfd];
  // no buffer
  if (!pbuf)
    return 0;

  // nothing to write
  if (pbuf->write_total == 0)
    return 0;

  int rtn = handle_write_internal(sockfd, pbuf);
  return rtn;
}
