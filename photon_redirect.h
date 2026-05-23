#pragma once
#include "pch.h"

class PhotonRedirector {
private:
    std::map<std::string, std::string> m_redirects;
    void LoadConfig();

public:
    PhotonRedirector();
    std::string Redirect(const std::string& domain);
};

extern PhotonRedirector g_Redirector;