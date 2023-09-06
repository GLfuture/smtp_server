#include "smtp_server.h"

Tcp_Conn_Ptr Smtp_Server::Smtp_Connect(string sip, uint32_t sport, string account, string password)
{
    Tcp_Conn_Ptr conn_ptr = Conncet(sip, sport);
    Exchange_Msg(conn_ptr, smtp_protocol.Hello_Msg());
    Exchange_Msg(conn_ptr, smtp_protocol.Auth());
    Exchange_Msg(conn_ptr, smtp_protocol.Account_Base64(account));
    Exchange_Msg(conn_ptr, smtp_protocol.Password_Base64(password));
    return conn_ptr;
}

void Smtp_Server::Smtp_Send_Msg(Tcp_Conn_Ptr &conn_ptr, string account,vector<string> &receivers, string msg_topic, string msg_sender, string msg_type, string msg_charset, string real_msg)
{
    Exchange_Msg(conn_ptr, smtp_protocol.Mail_From(account));
    for(int i=0;i<receivers.size();i++)
    {
        Exchange_Msg(conn_ptr, smtp_protocol.Rcpt_to(receivers[i]));
    }
    Exchange_Msg(conn_ptr, smtp_protocol.Data());
    Exchange_Msg(conn_ptr, smtp_protocol.Msg(msg_sender, receivers, msg_type, msg_charset, msg_topic, real_msg));
}

void Smtp_Server::Smtp_Quit(Tcp_Conn_Ptr &conn_ptr)
{
    Exchange_Msg(conn_ptr, smtp_protocol.Quit());
    Close(conn_ptr->Get_Conn_fd());
}


void Smtp_Server::Exchange_Msg(Tcp_Conn_Ptr &conn_ptr, string buffer)
{
    conn_ptr->Appand_Wbuffer(buffer);
    int slen = Send(conn_ptr, conn_ptr->Get_Wbuffer_Length());
    conn_ptr->Erase_Wbuffer(slen);
    int rlen = Recv(conn_ptr, 1024);
    std::cout << conn_ptr->Get_Rbuffer() << std::endl;
    conn_ptr->Erase_Rbuffer(rlen);
}
