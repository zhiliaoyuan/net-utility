#ifndef _UTCPSOCKET_H__
#define _UTCPSOCKET_H__

#include "utimer.h"
#include "ustream/basic_tcp_stream.h"

#include <sys/epoll.h>

enum 
{
    en_socket_refused = -1,
    en_socket_timeout = -300,
    en_socket_normal_closed = -301,
};

class uschedule;

class utcpsocket 
    : public basic_tcp_stream
    , public utimer
{
public:
    static int connect(const char * host, int port);
        
public:
    utcpsocket(size_t buf_size, int sockfd, uschedule * sched, 
        bool nonblock = true, int socket_timeo = 5000, 
        int connect_timeo = 200, bool no_delay = true);

	virtual ~utcpsocket();

	virtual bool set_timeout(int ms);

	virtual int last_error();

    struct epoll_event & event()    { return event_;    }

    void set_errno(int no)  { errno_ = no; }

    int socket_timeo() { return socket_timeo_; }

    int connect_timeo() { return connect_timeo_; }
    
  	virtual int socket();

private:
    bool setnonblock(bool nonblock);
    bool setnodelay(bool nodelay);

private:
	uschedule * schedule_;
    struct epoll_event event_;
    
	int socket_fd_;
	int connect_timeo_;
	int socket_timeo_;
    int errno_;
};

#endif
