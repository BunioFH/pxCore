#ifndef __RT_RPC_TRANSPORT_H__
#define __RT_RPC_TRANSPORT_H__

#include <map>
#include <string>
#include <vector>

#include <rtAtomic.h>
#include <rtError.h>
#include <rtValue.h>

#include <sys/socket.h>
#include <pthread.h>

#include "rtSocketUtils.h"

class rtValueWriter
{
  static rtError toString(rtValue const& val, char* buff, int n);
};

class rtValueReader
{
public:
  static rtError fromString(rtValue& val, char const* buff, int n);
};

class rtRpcTransport
{
public:
  rtRpcTransport(sockaddr_storage const& ss);
  ~rtRpcTransport();

  rtError start();
  rtError start_session(std::string const& object_id);

  inline void keep_alive(std::string const& s)
    { m_object_list.push_back(s); }

private:
  typedef rtError (rtRpcTransport::*message_handler_t)(docptr_t const&);
  typedef std::map< std::string, message_handler_t > msghandler_map_t;
  typedef std::map< rtAtomic, docptr_t > request_map_t;

  rtError connect_rpc_endpoint();
  rtError send_keep_alive();
  rtError run_listener();
  rtError readn(int fd, rt_sockbuf_t& buff);
  rtError dispatch(docptr_t const& doc);

  // message handlers
  rtError on_start_session(docptr_t const& doc);

  static void* run_listener(void* argp);

private:
  sockaddr_storage          m_remote_endpoint;
  int                       m_fd;
  std::vector<std::string>  m_object_list;
  pthread_t                 m_thread;
  pthread_mutex_t           m_mutex;
  pthread_cond_t            m_cond;
  msghandler_map_t          m_message_handlers;
  rtAtomic                  m_corkey;
  request_map_t             m_requests;
};

#endif