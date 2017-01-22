#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "pswmgr.grpc.pb.h"

class PasswordManagerClient final
{
public:
    PasswordManagerClient(std::shared_ptr<grpc::Channel> channel);

    bool Authenticate(const std::string& user, const std::string& pass, bool create = false);
    bool CreateUser(const std::string& user, const std::string& pass);
    const std::string& GetLastError() const { return m_LastError; }

    static auto GetChannel(const std::string& address) -> decltype(grpc::CreateChannel("", grpc::SslCredentials(grpc::SslCredentialsOptions())))
    {
        std::ifstream file("/home/mfilion/programming/pswmgr/easy-rsa/keys/ca.crt", std::ifstream::in);
        std::string ca = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        auto credOptions = grpc::SslCredentialsOptions();
        credOptions.pem_root_certs = ca;
        auto sslCreds = grpc::SslCredentials(credOptions);
        return grpc::CreateChannel(address, sslCreds);
    }

private:
    std::unique_ptr<pswmgr::Authentication::Stub>  m_AuthStub;
    std::unique_ptr<pswmgr::PasswordManager::Stub> m_PassMgrStub;
    std::unique_ptr<pswmgr::UserManagement::Stub>  m_UserMgrStub;
    std::string m_LastError;
};
