#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <fstream>
#include <rapidjson/document.h>
#include <filesystem>
#include "smtp_server.h"
#include "reactor.h"
#include "HTTP.hpp"

#define SOURCE_FILE_PATH "../html/example.html"
#define DEFAULT_CONFIG_PATH "../conf/config.json"
#define DEFAULT_RECV_LENGTH 1024
#define RET_JSON_ERROR_STR "json has some error"

static string global_smtp_msg_content;


static uint32_t global_bind_port ;
static uint16_t global_backlog;
static uint32_t global_event_num;
static string global_account;
static string global_password;
static uint32_t global_smtp_port;
static string global_msg_topic;
static string global_msg_sender;
static string global_msg_type;
static string global_msg_charset;
static string global_domain_name;

string Get_File_Content(string file_path)
{
    std::ifstream file_in;
    file_in.open(file_path);
    if(file_in.fail()){
        printf("file open fail\n");
        return "";
    }
    file_in.seekg(0,std::ios_base::end);
    int len = file_in.tellg();
    file_in.seekg(0,std::ios_base::beg);
    char *buffer=new char[len];
    memset(buffer,0,len);
    file_in.read(buffer,len);
    std::cout<<buffer<<std::endl;
    string ret(buffer);
    delete buffer;
    file_in.close();
    return ret;
}

//to do
void Prase_Config(string config_json)
{
    rapidjson::Document doc;
    //std::cout<<config_json<<std::endl;
    doc.Parse(config_json.c_str());
    if(doc.HasParseError()){
        printf("config json has some errors\n");
        exit(-1);
    }
    if(doc.HasMember("smtp_server_domain_name"))
    {
        if(doc["smtp_server_domain_name"].IsString()){
            global_domain_name = doc["smtp_server_domain_name"].GetString();
        }else exit(-1);
    }else exit(-1);
    if(doc.HasMember("account")){
        if(doc["account"].IsString()){
            global_account = doc["account"].GetString();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("password")){
        if(doc["password"].IsString()){
            global_password = doc["password"].GetString();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("smtp_port")){
        if(doc["smtp_port"].IsInt()){
            global_smtp_port = doc["smtp_port"].GetInt();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("topic")){
        if(doc["topic"].IsString()){
            global_msg_topic = doc["topic"].GetString();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("proxy_sender")){
        if(doc["proxy_sender"].IsString()){
            global_msg_sender = doc["proxy_sender"].GetString();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("type")){
        if(doc["type"].IsString()){
            global_msg_type = doc["type"].GetString();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("charset")){
        if(doc["charset"].IsString())
        {
            global_msg_charset = doc["charset"].GetString();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("bind_port"))
    {
        if(doc["bind_port"].IsInt()){
            global_bind_port = doc["bind_port"].GetInt();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("backlog")){
        if(doc["backlog"].IsInt()){
            global_backlog = doc["backlog"].GetInt();
        }else exit(-1);
    }else exit(-1);

    if(doc.HasMember("event_num")){
        if(doc["event_num"].IsInt()){
            global_event_num = doc["event_num"].GetInt();
        }else exit(-1);
    }else exit(-1);
}


vector<string> Proc_Msg(string_view &json)
{
    rapidjson::Document doc;
    vector<string> ret;
    doc.Parse(json.cbegin());
    if(doc.HasParseError())
    {
        ret.push_back("json error");
        return ret;
    }
    if(doc.HasMember("exit")){
        if(doc["exit"].IsBool()){
            if(doc["exit"].GetBool()==true){
                ret.push_back("exit");
                return ret;
            }
        }
    }
    if(doc.HasMember("emails")){
        if(doc["emails"].IsArray()){
            const rapidjson::Value& array = doc["emails"].GetArray();
            for(rapidjson::SizeType i = 0;i<array.Size();i++)
            {
                const rapidjson::Value &e = array[i];
                if(e.IsString()){
                    ret.push_back(e.GetString());
                }
            }
        }
    }
    return ret;
}


void accept_cb(Reactor& R)
{
    Smtp_Server_Ptr server = std::static_pointer_cast<Smtp_Server>(R.Get_Server());
    int fd = server->Accept();
    if(fd==-1)
    {
        printf("accept failed\n");
        return;
    }
    R.Add_Reactor(fd,EPOLLIN);
}

void recv_cb(Reactor& R,Tcp_Conn_Ptr smtp_conn)
{
    int fd = R.Get_Now_Event().data.fd;
    Smtp_Server_Ptr server = std::static_pointer_cast<Smtp_Server>(R.Get_Server());
    Tcp_Conn_Ptr conn = server->Get_Conn(fd);
    int rlen = server->Recv(conn,DEFAULT_RECV_LENGTH);
    if(rlen <= 0){
        server->Close(fd);
        R.Del_Reactor(fd,EPOLLIN);
    }
    //未解决tcp粘包问题
    string_view request = conn->Get_Rbuffer();
    HTTP_NSP::HTTP http;
    http.Request_Decode(string(request));
    http.Response_Set_Key_Value("Access-Control-Allow-Origin","*");
    if(http.Request_Get_Http_Type().compare("OPTIONS") == 0)
    {
        http.Response_Set_Key_Value("Access-Control-Allow-Methods","POST");
        http.Response_Set_Key_Value("Content-Length","0");
    }
    else if(http.Request_Get_Http_Type().compare("POST") == 0)
    {
        http.Response_Set_Status(200);
        HTTP_NSP::Http_String json = http.Request_Get_Body();
        vector<string> ret = Proc_Msg(json);
        if(ret[0].compare("exit")==0){
            close(server->Get_Sock());
            R.Exit();
        }else if(ret[0].compare("json error")==0){
            http.Response_Set_Key_Value("Content-Length","19");
            http.Response_Set_Key_Value("Content-Type","text/plain");
            conn->Appand_Wbuffer(http.Response_Content_Head()+"json has some error\r\n\r\n");

        }else{
            
            server->Smtp_Send_Msg(smtp_conn,global_account,ret,global_msg_topic,global_msg_sender,global_msg_type,global_msg_charset,global_smtp_msg_content);
            http.Response_Set_Key_Value("Content-Length","2");
            http.Response_Set_Key_Value("Content-Type","text/plain");
            conn->Appand_Wbuffer(http.Response_Content_Head()+"ok\r\n");
        }
    }else{
        http.Response_Set_Status(400);
        http.Response_Set_Key_Value("Content-Length","0");
        conn->Appand_Wbuffer(http.Response_Content_Head());
    }


    conn->Erase_Rbuffer(request.length());
    R.Mod_Reactor(fd,EPOLLOUT);
}




void send_cb(Reactor& R)
{
    int fd = R.Get_Now_Event().data.fd;
    Smtp_Server_Ptr server = std::static_pointer_cast<Smtp_Server>(R.Get_Server());
    Tcp_Conn_Ptr conn = server->Get_Conn(fd);
    server->Send(conn,conn->Get_Wbuffer_Length());
    R.Del_Reactor(conn->Get_Conn_fd(),EPOLLOUT);
    server->Close(fd);
}

int main(int argc,char*argv[])
{
    string config_path="";
    if(argc < 2){
        config_path = DEFAULT_CONFIG_PATH;
    }
    if(argc == 3){
        if(strcmp(argv[1],"-c")==0){
            config_path = argv[2];
        }
    }
    if(!std::filesystem::exists(config_path)){
        printf("config file is not exit\n");
        exit(-1);
    }
    global_smtp_msg_content = Get_File_Content(SOURCE_FILE_PATH);
    string config_json = Get_File_Content(config_path);
    Prase_Config(config_json);


    
    //获取ip
    hostent* host = gethostbyname(global_domain_name.c_str());
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET,host->h_addr_list[0],ip,INET_ADDRSTRLEN);

    Smtp_Server_Ptr server=std::make_shared<Smtp_Server>();
    server->Bind(global_bind_port);
    server->Listen(global_backlog);

    Tcp_Conn_Ptr smtp_conn = server->Smtp_Connect(ip,global_smtp_port,global_account,global_password);
    Reactor R(global_event_num);
    R.Add_Server(server);
    R.Add_Reactor(server->Get_Sock(),EPOLLIN);
    R.Set_Accept_cb(std::bind(accept_cb,std::ref(R)));
    R.Set_Read_cb(std::bind(recv_cb,std::ref(R),smtp_conn));
    R.Set_Write_cb(std::bind(send_cb,std::ref(R)));
    R.Event_Loop();
    return 0;
}