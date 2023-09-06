#pragma once
#ifndef SMTP_SERVER_H
#define SMTP_SERVER_H
#endif
#include "server.h"
#include "Smtp_proto.hpp"
#include <vector>
#include <algorithm>
using std::vector;
using namespace STMP_NSP;


class Smtp_Server:public Server_Base
{
public:
    Smtp_Server():Server_Base(){}

    Tcp_Conn_Ptr Smtp_Connect(string sip,uint32_t sport,string account,string password);

    void Smtp_Send_Msg(Tcp_Conn_Ptr &conn_ptr, string account,vector<string> &receivers, string msg_topic, 
        string msg_sender, string msg_type, string msg_charset, string real_msg);

    void Smtp_Quit(Tcp_Conn_Ptr& conn_ptr);

private:
    void Exchange_Msg(Tcp_Conn_Ptr& conn_ptr,string buffer);
private:
    SMTP smtp_protocol;
};

using Smtp_Server_Ptr = std::shared_ptr<Smtp_Server>;