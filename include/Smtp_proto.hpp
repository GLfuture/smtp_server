#pragma once
#ifndef SMTP_HPP
#define SMTP_HPP
#endif
#include "base64.h"
#include <string>
#include <vector>
namespace STMP_NSP {
/*
1.HELO MSG\r\n
2.AUTH LOGIN\r\n
3.分别发送base64加密账号，密码
4.MAIL FROM:<>\r\n 发送发件人邮箱
5.RCPT TO:<>\r\n 收件人邮箱
6.DATA\r\n发送数据 
7.From:发件人\r\nSubject:标题\r\n\r\n正文\r\n\r\n\r\n.\r\n 发送消息体
*/
class SMTP {
public:
    const std::string Hello_Msg()
    {
        return "HELO MSG\r\n";
    }

    const std::string Auth()
    {
        return "AUTH LOGIN\r\n";
    }

    const std::string Account_Base64(const std::string account)
    {
        return base64_encode(account)+"\r\n";
    }

    const std::string Password_Base64(const std::string password)
    {
        return base64_encode(password)+"\r\n";
    }

    const std::string Mail_From(const std::string sender)
    {
        std::string ret="MAIL FROM:<"+sender+">\r\n";
        return ret;
    }

    const std::string Rcpt_to(string reciever)
    {
        std::string ret="RCPT TO:";
        ret=ret+"<"+reciever+">";
        ret+="\r\n";
        return ret;
    }

    const std::string Data()
    {
        return "DATA\r\n";
    }

    const std::string Msg(const std::string sender,std::vector<std::string>& receivers,const std::string type,const std::string charset,const std::string topic,const std::string body)
    {
        std::string ret = "From: " + sender + "\r\n";
        ret += "To: ";
        for(int i=0;i<receivers.size();i++)
        {
            ret = ret +"<" +receivers[i]+">";
            if(i!=receivers.size()-1){
                ret+=", ";
            }

        }
        ret += "\r\n";
        ret = ret + "Subject: " + topic + "\r\n";
        ret = ret + "Content-Type: "+type+";";
        ret = ret + " charset="+charset+"\r\n\r\n";
        ret = ret + body+"\r\n\r\n\r\n.\r\n" ;
        return ret;
    }


    const std::string Quit()
    {
        return "QUIT\r\n";
    }
};


} // namespace STMP_NSP