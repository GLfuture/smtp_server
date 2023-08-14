#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include "Smtp/Smtp.hpp"
#include "Client_Socket/Client_Socket.hpp"
#include <random>
#include <sstream>
#define DEFAULT_SEND_LEN -1
#define DEFAULT_RECV_LEN -1
#define SENDER_MAILBOX "your email"
#define RECIVER_MAILBOX "recviever"
#define PASSWORD "授权码"
using namespace STMP_NSP;
using namespace Client_Socket_NSP;

std::string GenerateHTMLBody(const std::string& verificationCode) {
    // 使用红色显示验证码
    std::stringstream ss;
    ss << "<html><body>"
       << "<h1>Verification Code</h1>"
       << "<p>Your verification code is: <span style=\"color: red\">" << verificationCode << "</span></p>"
       << "</body></html>";
    return ss.str();
}



void Clean_Buffer(Client_Socket& client)
{
    client.Clean_Read_Buffer();
}

void Proc(Client_Socket&client,std::string buffer)
{
    client.Set_Write_Buffer(buffer);
    std::cout<<buffer<<std::endl;
    int slen = client.Send(DEFAULT_SEND_LEN);
    int rlen = client.Recv(DEFAULT_RECV_LEN);
    std::cout<<client.Get_Read_Buffer()<<std::endl;
    Clean_Buffer(client);

}
int main()
{
    SMTP smtp;
    hostent *host = gethostbyname("smtp.163.com");
    if(!host){
       printf("gethostbyname failed!\n");
       exit(-1);
    }
    char str[INET_ADDRSTRLEN];
    inet_ntop(host->h_addrtype,host->h_addr_list[0],str,INET_ADDRSTRLEN);
    printf("%s\n",str);
    Client_Socket client(str,25,1024);
    int fd=client.Init_Sock(9999);
    if(fd!=0){
        printf("init failed!\n");
        exit(-1);
    }
    if(client.Connect()!=0){
        printf("connect failed!\n");
        exit(-1);
    }
    client.Recv(DEFAULT_RECV_LEN);
    std::cout<<client.Get_Read_Buffer()<<std::endl;
    client.Clean_Read_Buffer();
    Proc(client,smtp.Hello_Msg());
    Proc(client,smtp.Auth());
    Proc(client,smtp.Account_Base64(SENDER_MAILBOX));
    Proc(client,smtp.Password_Base64(PASSWORD));
    Proc(client,smtp.Mail_From(SENDER_MAILBOX));
    Proc(client,smtp.Rcpt_to(RECIVER_MAILBOX));
    Proc(client,smtp.Data());
    srand(time(NULL));
    int code = random() %9000+1000;
    std::string body = GenerateHTMLBody(std::to_string(code));
    Proc(client, smtp.Msg(SENDER_MAILBOX, RECIVER_MAILBOX ,"text/html","utf-8","topic",body));
    Proc(client, smtp.Quit());
    client.Close();
    return 0;
}