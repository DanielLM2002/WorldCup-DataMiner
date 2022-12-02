// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef COMMON_HPP
#define COMMON_HPP

/// Declare four of the rule-of-the-five methods
#define DECLARE_RULE4(Class, action) \
  Class(const Class& other) = action; \
  Class(Class&& other) = action; \
  Class& operator=(const Class& other) = action; \
  Class& operator=(Class&& other) = action

/// Disable default methods for copying objects
#define DISABLE_COPY(Class) \
  DECLARE_RULE4(Class, delete)

/// For data transmissions
typedef unsigned char byte;





#define MAXLINE       1024
#define SEPARATOR     "\t" // defined by the ci-0123 class protocol
#define GROUPS        "E"

#define SERVER_PORT   2020
#define SERVER_HOST_IP "127.0.0.1"
#define SERVER_HTTP_PORT 9876
#define SERVERD_DEAD_WORD "DEAD"

#define ROUTER_PORT   2022
#define ROUTER_HTTP_PORT 9877
#define MAXLINE       1024
#define PROTOCOL_INDEX_IP 0
#define PROTOCOL_INDEX_GROUP 1
#define ROUTER_HOST_IP "127.0.0.1" // IP OF THE COMPUTER WHERE THE ROUTER IS RUNNING



#endif  // COMMON_HPP
